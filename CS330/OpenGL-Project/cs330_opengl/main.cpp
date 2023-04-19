/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#include "pch.h"

#include "Camera.h"
#include "RandomHelpers.h"
#include "Mesh.h"
#include "OpenGlWindowManager.h"
#include "ShaderProgram.h"
#include "TextureHelper.h"

// These need static duration to be captured in the OglCallbacks
// .. I'd like to find a better way
OpenGlWindowManager window;
Camera camera;

// Mouse callback to set later
void MouseMovementCallback(GLFWwindow* glWindow, const double xIn, const double yIn)
{
	// Cast doubles to floats safely
	const auto newX = static_cast<float>(xIn);
	const auto newY = static_cast<float>(yIn);

	// Once-time init for mouse positions
	if (!camera.IsCameraMoveInitialized)
	{
		camera.LastMouseXPos = newX;
		camera.LastMouseYPos = newY;
		camera.IsCameraMoveInitialized = true;
	}

	// Calculate amount changed since last update
	const float deltaX = (newX - camera.LastMouseXPos) * camera.LookSensitivity;
	const float deltaY = (camera.LastMouseYPos - newY) * camera.LookSensitivity;

	// store current positions for next update
	camera.LastMouseXPos = newX;
	camera.LastMouseYPos = newY;

	// Calculate euler angles
	// .. I use a struct I created in Math.h for storing the angles
	camera.Angle.Yaw += deltaX;
	camera.Angle.Pitch = Math::Clamp(camera.Angle.Pitch + deltaY, -89.0f, 89.0f);

	// Set camera direction based on camera euler angles
	// .. I wrote this method in the Math.h header
	camera.SetCameraDirection(NormalizedDirectionFromEulerAngle(camera.Angle));
}


// Mouse scroll callback for setting later
void MouseScrollCallback(GLFWwindow* glWindow, const double horizontal, const double vertical)
{
	// Adjusting Move Speed instead of FOV
	camera.SetMoveSpeed(Math::Clamp(
		camera.MoveSpeed +
		(static_cast<float>(vertical) * camera.MoveSpeedChangeSensitivity),
		camera.MoveSpeedMin,
		camera.MoveSpeedMax
	));
}


int main(const int argv, const char* argc[])
{
	// Init random seed
	RandomHelpers::Init();

	// Create and init the window
	if (!window.Init())
		return 1;

	// Setup a background color
	OpenGlWindowManager::SetWindowBackgroundColor(0.1f, 0.1f, 0.1f);

	// FOR DEBUG: Wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Scope for gl objects
	{
		// Setup textures
		
		GLuint pencilTipTexture = TextureHelper::CreateTexture("textures/pencil_tip.jpg");
		if (pencilTipTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}
		GLuint deskTexture = TextureHelper::CreateTexture("textures/desktop_texture.jpg");
		if (deskTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}
		GLuint pencilBodyTexture = TextureHelper::CreateTexture("textures/pencil_body.jpg");
		if (pencilBodyTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}

		GLuint postitTexture = TextureHelper::CreateTexture("textures/postit_note.jpg");
		if (postitTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}

		GLuint bottleTexture = TextureHelper::CreateTexture("textures/bottle.jpg");
		if (bottleTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}
		GLuint bottleTopTexture = TextureHelper::CreateTexture("textures/bottle_top.jpg");
		if (bottleTopTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}


		GLuint bottleCapTexture = TextureHelper::CreateTexture("textures/bottle_cap.jpg");
		if (bottleCapTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}

		GLuint boxTopTexture = TextureHelper::CreateTexture("textures/box_top.jpg");
		if (boxTopTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}


		GLuint boxSideTexture = TextureHelper::CreateTexture("textures/box_side.jpg");
		if (boxSideTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}

		GLuint boxBottomTexture = TextureHelper::CreateTexture("textures/box_bottom.jpg");
		if (boxBottomTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}

		GLuint panoramaTexture = TextureHelper::CreateTexture("textures/panorama_bg.jpg");
		if (panoramaTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}

		GLuint monitorTexture = TextureHelper::CreateTexture("textures/monitor.jpg");
		if (monitorTexture == 0)
		{
			std::cerr << "Error creating texture, exiting." << std::endl;
			return 1;
		}


		// Create a container for meshes
		// .. so we only need to capture one variable for the render loop
		// .. and simplify rendering of meshes
		std::vector<Mesh*> sceneMeshes;


		//Meshes for desktop scene

		Plane deskPlane(60, 60, deskTexture);
		deskPlane.SetRotation(0, -1, 0);
		deskPlane.SetTranslation(0, -0.5, 0);
		deskPlane.Rotate(0, 1, 0, 90);
		sceneMeshes.emplace_back(&deskPlane);


		Plane postitPlane(5, 5, postitTexture);
		postitPlane.SetRotation(0, -1, 0);
		postitPlane.SetTranslation(-2, -0.4, 0);
		postitPlane.Rotate(0, 1, 0, -0.5);
		sceneMeshes.emplace_back(&postitPlane);

		Cone pencilTipMesh(20, 0.5f, 3,
		                   pencilTipTexture, false);
		pencilTipMesh.SetRotation(0, -1, 0);
		sceneMeshes.emplace_back(&pencilTipMesh);

		Cylinder pencilBodyMesh(20, 0.5f, 10,
		                        pencilBodyTexture, true);
		pencilBodyMesh.SetRotation(0, -1, 0);
		pencilBodyMesh.SetTranslation(6.5, 0, 0);
		sceneMeshes.emplace_back(&pencilBodyMesh);


		Cylinder bottleMesh(100, 1.8f, 5,
		                    bottleTexture, false, true);
		bottleMesh.SetRotation(-1, 0, 0);
		bottleMesh.SetTranslation(-1, 2.5, -4.5);
		sceneMeshes.emplace_back(&bottleMesh);
		bottleMesh.Rotate(0, 0, 1, 110);

		Cylinder bottleTopMesh(100, 1.3f, 1,
		                       bottleTopTexture, false, true);
		bottleTopMesh.SetRotation(-1, 0, 0);
		bottleTopMesh.SetTranslation(-1, 5, -4.5);
		sceneMeshes.emplace_back(&bottleTopMesh);

		Cylinder bottleCapMesh(100, 0.75, 1,
		                       bottleCapTexture, false, true);
		bottleCapMesh.SetRotation(-1, 0, 0);
		bottleCapMesh.SetTranslation(-1, 6, -4.5);
		sceneMeshes.emplace_back(&bottleCapMesh);

		Plane boxTopPlane(7, 7, boxTopTexture);
		boxTopPlane.SetRotation(0, -1, 0);
		boxTopPlane.SetTranslation(7, 1.5, -6);
		boxTopPlane.Rotate(0, 1, 0, -45);
		sceneMeshes.emplace_back(&boxTopPlane);

		Plane boxSidePlane(7, 7, boxSideTexture);
		boxSidePlane.SetRotation(0, -1, 0);
		boxSidePlane.SetTranslation(4.53, -2, -3.53);
		boxSidePlane.Rotate(0, 0, 1, 90);
		boxSidePlane.Rotate(1, 0, 0, 45);
		boxSidePlane.Rotate(1, 0, 0, -90);
		sceneMeshes.emplace_back(&boxSidePlane);

		Plane boxBottomPlane(7, 7, boxBottomTexture);
		boxBottomPlane.SetRotation(0, -1, 0);
		boxBottomPlane.SetTranslation(9.47f, -2, -3.53f);
		boxBottomPlane.Rotate(1, 0, 0, -90);
		boxBottomPlane.Rotate(0, 0, 1, -45);
		sceneMeshes.emplace_back(&boxBottomPlane);


		//12496 x 2208 original size
		float panoramaScale = 8;
		Cylinder backgroundCylinder(
			100,
			// r = C / (2 * pi)
			(12496.0f / panoramaScale) / (2 * glm::pi<float>()),
			2208.0f / panoramaScale,
			panoramaTexture,
			false, true);
		backgroundCylinder.SetTranslation(0, (2208.0f / panoramaScale / 7), 0);
		backgroundCylinder.SetRotation(-1, 0, 0);
		backgroundCylinder.Rotate(0, 0, 1, 180);
		sceneMeshes.emplace_back(&backgroundCylinder);


		//3kx3976
		float monitorScale = 70;
		Plane monitorPlane(3000.0f / monitorScale, 3976.0f / monitorScale, monitorTexture);
		monitorPlane.SetTranslation(-20, (3976.0f / monitorScale / 2.0f) + 1.5f, 0);
		monitorPlane.SetRotation(-1, 0, 0);
		monitorPlane.Rotate(0, 0, 1, 75);

		sceneMeshes.emplace_back(&monitorPlane);


		ShaderProgram objectShaderProgram(
			OpenGlConstants::Shaders::ObjectVertexShaderSource,
			OpenGlConstants::Shaders::ObjectFragmentShaderSource);
		if (!objectShaderProgram.Compile())
			return 1;

		// Create camera using shader program ID, make sure it is successful
		if (!camera.Init(objectShaderProgram.GetProgramId()))
			return 1;
		camera.SetTranslate(22, 7.5, 10);


		// Setup Mouse movement and scroll callbacks
		glfwSetCursorPosCallback(window.GetWindowPtr(), MouseMovementCallback);
		glfwSetScrollCallback(window.GetWindowPtr(), MouseScrollCallback);


		// Render loop
		if (!window.RenderLoop([&]
	       {
	           // Set the camera matrix values
	           camera.SetFrameMatrix();
	           camera.UpdateShader(objectShaderProgram.GetProgramId());


	           // Setup main light to simulate the warm color of the interior lights
	           // .. in my home where the image was taken. This light has an orange tint
	           const GLint fillLightCol = glGetUniformLocation(
	               objectShaderProgram.GetProgramId(),
	               "fillLightColor");
	           const GLint fillLightLoc = glGetUniformLocation(
	               objectShaderProgram.GetProgramId(),
	               "fillLightLoc");
	           const GLint fillLightAmb = glGetUniformLocation(
	               objectShaderProgram.GetProgramId(),
	               "fillAmbientMult");
	           glUniform3f(fillLightCol, 0.2f, 0.2f, 0.4f);
	           glUniform3f(fillLightLoc, 0, 5, -20);
	           glUniform1f(fillLightAmb, 0.1f);


	           // Setup a fill light to simulate the cool light reflecting off the snow
	           // .. though the window. This light has a blue tint
	           const GLint mainLightCol = glGetUniformLocation(
	               objectShaderProgram.GetProgramId(),
	               "mainLightColor");
	           const GLint mainLightLoc = glGetUniformLocation(
	               objectShaderProgram.GetProgramId(),
	               "mainLightLoc");
	           const GLint mainLightAmb = glGetUniformLocation(
	               objectShaderProgram.GetProgramId(),
	               "mainAmbientMult");
	           glUniform3f(mainLightCol, 0.35f, 0.3f, 0.25f);
	           glUniform3f(mainLightLoc, 10, 20, 30);
	           glUniform1f(mainLightAmb, 0.3f);


	           // set current shader
	           objectShaderProgram.SetCurrent();


	           // Render all meshes in the Scene
	           // .. using pointers to the mesh objects
	           for (const auto meshPtr : sceneMeshes)
	               meshPtr->Render(objectShaderProgram.GetProgramId());
	       },
	       // Input Callback
	       [](GLFWwindow* win)
	       {
	           camera.ProcessCameraInputs(window.GetDelta(), win, camera);
	       }))
		{
			std::cerr << "RenderLoop exited with an error." << std::endl;
		}

		// shaderProgram and meshes go out of scope here
		// .. Their de-constructors clean them up in the gl context.
	}

	return 0;
}
