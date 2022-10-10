/*
 * 	CS230 - Project 1
 *	Dante Trisciuzzi
 *	7.13.2022
 */

package com.gamingroom;

/**
 * A class to test a singleton's behavior
 * 
 * @author coce@snhu.edu
 */
public class SingletonTester {

	public void testSingleton() {
		
		System.out.println("\nAbout to test the singleton...");

		GameService service = GameService.getInstance(); // replace null with ???
		
		// a simple for loop to print the games
		for (int i = 0; i < service.getGameCount(); i++) {
			System.out.println(service.getGameByIndex(i));
		}

	}
	
}
