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
 * A simple class to hold information about a game
 * 
 * <p>
 * Notice the overloaded constructor that requires
 * an id and name to be passed when creating.
 * Also note that no mutators (setters) defined so
 * these values cannot be changed once a game is
 * created.
 * </p>
 * 
 * @author coce@snhu.edu
 *
 */
public class Game extends Entity {
	List<Team> teams;

	/**
	 * Constructor with an identifier and name
	 */
	public Game(long id, String name) {
		super(id, name);
		teams = new ArrayList<>();
	}

	/**
	 * @param name Name of team to add.
	 * @return Existing or new team.
	 */
	public Team addTeam(String name){
		// Check if any team exists with the requested name
		// ... return it if so
		for (Team t: teams) {
			if(Objects.equals(t.getName(), name)) {
				return t;
			}
		}

		// If no team exists with the given name, we create one
		Team team = new Team(GameService.getInstance().getNextTeamId(), name);
		teams.add(team);
		return team;
	}

	// Removed getId and getName methods as they are implemented in the base class

	@Override
	public String toString() {
		return "Game " + super.toString();
	}

}
