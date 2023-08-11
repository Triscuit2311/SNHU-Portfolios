/*
 * Dante Trisciuzzi
 * CS-350 SNHU
 * 8.10.2023
 * Prof. Megan Allen Black
 */

/*
 * Copyright (c) 2017-2020, Texas Instruments Incorporated
 * Full Terms at EOF
*/


#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/UART2.h>
#include <ti/drivers/Timer.h>
#include "ti_drivers_config.h"


// Forward Declarations
void initTimer(void);
void uart_output(UART2_Handle uart, const char *text);
void initUART(void);
void initI2C(void);
int16_t readTemp(void);
void buttonTask(void);
void temperatureTask(void);
void updateTask(void);


// Global variables
Timer_Handle g_timer0;
volatile unsigned char g_TimerFlag = 0;
UART2_Handle g_UART;
I2C_Transaction g_i2cTransaction;
I2C_Handle g_i2c;
uint8_t g_txBuffer[1];
uint8_t g_rxBuffer[2];

static const struct {
    uint8_t address;
    uint8_t resultReg;
    char *id;
} g_sensors[3] = {
    {0x48, 0x0000, "11X"},
    {0x49, 0x0000, "116"},
    {0x41, 0x0001, "006"}
};


// Task function type definition
typedef void (*taskFunction_t)(void);

// Task structure containing the task function, run interval, and next run tick
typedef struct {
    taskFunction_t taskFunction;
    uint32_t runInterval;
    uint32_t nextRunTick;
} task_t;


// Task array with three tasks and their respective run intervals (in units of 100ms ticks)
task_t tasks[] = {
    { buttonTask, 2, 0 },      // 200ms
    { temperatureTask, 5, 0 }, // 500ms
    { updateTask, 10, 0 },     // 1 second
};

// Global variables for temperatures and time tracking
int16_t setPointTemperature = 20;
int16_t currentTemperature;
uint32_t secondsSinceReset = 0;
volatile int increaseTemperatureFlag = 0;
volatile int decreaseTemperatureFlag = 0;

// System tick counter incremented every 100ms
uint32_t systemTick = 0;

// Task to check and update the current temperature
void temperatureTask(void) {
    currentTemperature = readTemp();
}

void buttonTask(void) {
    // Check if the increase temperature button has been pressed
    if (increaseTemperatureFlag) {
        setPointTemperature++;
        increaseTemperatureFlag = 0; // Reset the flag
    }

    // Check if the decrease temperature button has been pressed
    if (decreaseTemperatureFlag) {
        setPointTemperature--;
        decreaseTemperatureFlag = 0; // Reset the flag
    }
}


// Button callbacks
void gpioButtonFxn0(uint_least8_t index) {
    increaseTemperatureFlag = 1;
}

void gpioButtonFxn1(uint_least8_t index) {
    decreaseTemperatureFlag = 1;
}

// Task to update LED and report to the server via UART
void updateTask(void) {
    secondsSinceReset++;
    char heatStatus = '0';

    if (currentTemperature < setPointTemperature) {
        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
        heatStatus = '1';
    } else {
        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
    }

    char uartMessage[20];
    snprintf(uartMessage, sizeof(uartMessage), "<%02d,%02d,%c,%04d>", currentTemperature, setPointTemperature, heatStatus, secondsSinceReset);
    uart_output(g_UART, uartMessage);
}



void timerCallback(Timer_Handle myHandle, int_fast16_t status) {
    g_TimerFlag = 1;
}

void *mainThread(void *arg0) {


    GPIO_init();
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);


    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioButtonFxn0);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);
    GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioButtonFxn1);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_1);

    // Init drivers
    initTimer();
    initUART();
    initI2C();

    // Compute the number of tasks in the array
       size_t numTasks = sizeof(tasks) / sizeof(task_t);

       while (1) {
           // Check if timer flag is set
           if (g_TimerFlag) {
               g_TimerFlag = 0;
               systemTick++; // Increment system tick every 100ms

               // Iterate through all tasks
               for (size_t i = 0; i < numTasks; i++) {
                   // Check if the task should be executed
                   if (systemTick >= tasks[i].nextRunTick) {
                       tasks[i].taskFunction(); // Execute task
                       tasks[i].nextRunTick = systemTick + tasks[i].runInterval; // Schedule next run
                   }
               }
           }
       }

    return (NULL);
}


void initTimer(void)
{
    Timer_Params params;
    // Init the driver
    Timer_init();

    // Configure the driver
    Timer_Params_init(&params);

    // 100ms
    params.period = 100000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;

    // Open the driver
    g_timer0 = Timer_open(CONFIG_TIMER_0, &params);
    if (g_timer0 == NULL) {
        while (1) {}
    }
    if (Timer_start(g_timer0) == Timer_STATUS_ERROR) {
        while (1) {}
    }
}


void uart_output(UART2_Handle uart, const char *text) {
    size_t textLength = strlen(text);
    UART2_write(uart, text, textLength, NULL);
}


void initUART(void) {
    UART2_Params uartParams;
    UART2_Params_init(&uartParams);
    uartParams.writeMode = UART2_Mode_BLOCKING;
    uartParams.readMode = UART2_Mode_BLOCKING;
    uartParams.readReturnMode = UART2_ReadReturnMode_FULL;
    uartParams.baudRate = 115200;
    g_UART = UART2_open(CONFIG_UART2_0, &uartParams);
    if (g_UART == NULL) {
        while (1);
    }
}



void initI2C(void) {
  int8_t i, found;
  I2C_Params i2cParams;
  uart_output(g_UART, "Initializing I2C Driver - ");
  I2C_init();
  I2C_Params_init(&i2cParams);
  i2cParams.bitRate = I2C_400kHz;
  g_i2c = I2C_open(CONFIG_I2C_0, &i2cParams);
  if (g_i2c == NULL) {
      uart_output(g_UART, "Failed\n\r");
    while (1);
  }
  uart_output(g_UART, "Passed\n\r");
  g_i2cTransaction.writeBuf = g_txBuffer;
  g_i2cTransaction.writeCount = 1;
  g_i2cTransaction.readBuf = g_rxBuffer;
  g_i2cTransaction.readCount = 0;
  found = false;
  for (i = 0; i < 3; ++i) {
      g_i2cTransaction.targetAddress = g_sensors[i].address;
      g_txBuffer[0] = g_sensors[i].resultReg;
    uart_output(g_UART, "Is this ");
    uart_output(g_UART, g_sensors[i].id);
    uart_output(g_UART, "? ");
    if (I2C_transfer(g_i2c, &g_i2cTransaction)) {
        uart_output(g_UART, "Found\n\r");
      found = true;
      break;
    }
    uart_output(g_UART, "No\n\r");
  }
  if (found) {
      char tempBuffer[64];
      snprintf(tempBuffer, sizeof(tempBuffer), "Detected TMP%s I2C address: %x\n\r", g_sensors[i].id, g_i2cTransaction.targetAddress);
      uart_output(g_UART, tempBuffer);
  } else {
      uart_output(g_UART, "Temperature sensor not found, contact professor\n\r");
  }
}

int16_t readTemp(void) {
  int j;
  int16_t temperature = 0;
  g_i2cTransaction.readCount = 2;
  if (I2C_transfer(g_i2c, &g_i2cTransaction)) {
    temperature = (g_rxBuffer[0] << 8) | (g_rxBuffer[1]);
    temperature *= 0.0078125;
    if (g_rxBuffer[0] & 0x80) {
      temperature |= 0xF000;
    }
  } else {
    uart_output(g_UART, "Please power cycle your board by unplugging USB and plugging back in.\n\r");
  }
  return temperature;
}

/*
 * Copyright (c) 2017-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,

 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
