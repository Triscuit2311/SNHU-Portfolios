/*
 * 	CS230 - Project 1
 *	Dante Trisciuzzi
 *	7.13.2022
 */

package com.gamingroom;

import java.util.Objects;

/**
 * Application start-up program
 * 
 * @author coce@snhu.edu
 */
public class ProgramDriver {
	
	/**
	 * The one-and-only main() method
	 * 
	 * @param args command line arguments
	 */
	public static void main(String[] args) {

		GameService service = GameService.getInstance();
		
		System.out.println("\nAbout to test initializing game data...");
		
		// Initialize a game
		Game game1 = service.addGame("Game #1");
		Game game2 = service.addGame("Game #2");


		System.out.println(game1);

		// Add two teams
		Team blueTeam = game1.addTeam("Blue Team");
		Team redTeam = game1.addTeam("Red Team");

		System.out.println(blueTeam);
		System.out.println(redTeam);

		// Add some players
		Player b_1 = blueTeam.addPlayer("Jeffrey Lebowski");
		Player b_2 = blueTeam.addPlayer("Walter Sobchak");

		Player r_1 = blueTeam.addPlayer("Jesus Quintana");
		Player r_2 = blueTeam.addPlayer("Liam O'Brien");

		System.out.println(b_1);
		System.out.println(b_2);

		System.out.println(r_1);
		System.out.println(r_2);




		// Test adding games that already exist
		System.out.println("\nTesting adding already added Games, these objects should be the same (True):");
		Game game1_test = service.addGame("Game #1");
		Game game2_test = service.addGame("Game #2");
		System.out.println("\tgame1 == game1_test: " + (game1.equals(game1_test)));
		System.out.println("\tgame2 == game2_test: " + (game2.equals(game2_test)));

		// Test adding teams that already exist
		System.out.println("\nTesting adding already added Teams, these objects should be the same (True):");
		Team blueTeam_test = game1.addTeam("Blue Team");
		Team redTeam_test = game1.addTeam("Red Team");
		System.out.println("\tblueTeam == blueTeam_test: " + (blueTeam.equals(blueTeam_test)));
		System.out.println("\tredTeam == redTeam_test: " + (redTeam.equals(redTeam_test)));


		// Test adding players that already exist
		System.out.println("\nTesting adding already added Players, these objects should be the same (True):");
		Player b_1_test = blueTeam.addPlayer("Jeffrey Lebowski");
		Player r_1_test = blueTeam.addPlayer("Jesus Quintana");
		System.out.println("\tb_1 == b_1_test: " + (b_1.equals(b_1_test)));
		System.out.println("\tr_1 == r_1_test: " + (r_1.equals(r_1_test)));


		// Test otherwise unused methods from GameService
		System.out.println("\nTesting getting a Game by name, these objects should be the same (True):");
		System.out.println("\tgame1 == GameService.getInstance().getGame(\"Game #1\"): "
				+ (game1.equals(GameService.getInstance().getGame("Game #1"))));

		System.out.println("\nTesting getting a Game by id, this should give us a game::");
		System.out.println("\t" + GameService.getInstance().getGame(1));



		// use another class to prove there is only one instance
		SingletonTester tester = new SingletonTester();
		tester.testSingleton();
	}
}
