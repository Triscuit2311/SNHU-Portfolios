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
 * A simple class to hold information about a team
 * <p>
 * Notice the overloaded constructor that requires
 * an id and name to be passed when creating.
 * Also note that no mutators (setters) defined so
 * these values cannot be changed once a team is
 * created.
 * </p>
 * @author coce@snhu.edu
 *
 */

public class Team extends Entity {
	List<Player> players;
	
	/*
	 * Constructor with an identifier and name
	 */
	public Team(long id, String name) {
		super(id, name);
		players = new ArrayList<>();
	}

	/**
	 * @param name Name of player to create.
	 * @return Existing or new player.
	 */
	public Player addPlayer(String name){
		// Check if any Player exists with the requested name
		// ... return it if so
		for (Player p: players) {
			if(Objects.equals(p.getName(), name)) {
				return p;
			}
		}

		// If no team exists with the given name, we create one
		Player player = new Player(GameService.getInstance().getNextPlayerId(), name);
		players.add(player);
		return player;
	}

	// Removed getId and getName methods as they are implemented in the base class

	@Override
	public String toString() {
		return "Team " + super.toString();
	}
}
