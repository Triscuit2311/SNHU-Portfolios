/*
* 	CS230 - Project 1
*	Dante Trisciuzzi
*	7.13.2022
*/


package com.gamingroom;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * A singleton service for the game engine
 * 
 * @author coce@snhu.edu
 */
public class GameService {

	/**
	 * A list of the active games
	 */
	private static final List<Game> games = new ArrayList<>();

	/*
	 * Holds the next game identifier
	 */
	private static long nextGameId = 1;
	private static long nextTeamId = 1;
	private static long nextPlayerId = 1;


	// Singleton Pattern
	// I use a unique (static) instance of the class as well as a private constructor
	// I create a public getInstance() method that creates an instance of the class if one does not already exist
	// ... and either way returns the unique instance to the caller
	private static GameService instance = null;

	/**
	 * Private constructor for singleton pattern.
	 */
	private GameService(){}

	/**
	 * @return Instance of the singleton class GameService.
	 */
	public static GameService getInstance(){
		if(instance == null) {
			instance = new GameService();
		}
		return instance;
	}


	/**
	 * Construct a new game instance
	 * 
	 * @param name the unique name of the game
	 * @return the game instance (new or existing)
	 */
	public Game addGame(String name) {

		// Check if any game exists with the requested name
		// ... return it if so
		for (Game g: games) {
			if(Objects.equals(g.getName(), name)) {
				return g;
			}
		}

		// If no game exists with the given name, we create one
		Game game = new Game(nextGameId++, name);
		games.add(game);
		return game;
	}


	/**
	 * Returns the game instance at the specified index.
	 * <p>
	 * Scope is package/local for testing purposes.
	 * </p>
	 * @param index index position in the list to return
	 * @return requested game instance
	 */
	// I changed the name here, since having getGame(long) and getGame(int) is a poor design choice.
	// ... Since we overload this method again with a long argument, it is likely to be called
	// ... by mistake if a developer is looking to get a game by unique id.
	Game getGameByIndex(int index) {
		return games.get(index);
	}
	
	/**
	 * Returns the game instance with the specified id.
	 * 
	 * @param id unique identifier of game to search for
	 * @return requested game instance
	 */
	public Game getGame(long id) {
		// if found, simply return the existing instance
		for (Game g: games) {
			if (g.getId() == id) {
				return g;
			}
		}

		// If no game found with this id, return null instance of Game
		return null;
	}

	/**
	 * Returns the game instance with the specified name.
	 * 
	 * @param name unique name of game to search for
	 * @return requested game instance
	 */
	public Game getGame(String name) {
		// if found, simply return the existing instance
		for (Game g: games) {
			if(Objects.equals(g.getName(), name)) {
				return g;
			}
		}

		// If no game found with this name, return null instance of Game
		return null;
	}

	/**
	 * Returns the number of games currently active
	 * 
	 * @return the number of games currently active
	 */
	public int getGameCount() {
		return games.size();
	}

	/**
	 * @return Next unique team ID.
	 *  This method is not marked static on the UML Diagram, but can be static.
	 */
	public long getNextTeamId(){
		var next = nextTeamId;
		nextTeamId++;
		return next;
	}

	/**
	 * @return Next unique Player ID.
	 * This method is not marked static on the UML Diagram, but can be static.
	 */
	public long getNextPlayerId(){
		var next = nextPlayerId;
		nextPlayerId++;
		return next;
	}
}
