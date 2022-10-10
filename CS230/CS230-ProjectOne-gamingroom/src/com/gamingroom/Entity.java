/*
 * 	CS230 - Project 1
 *	Dante Trisciuzzi
 *	7.13.2022
 */

package com.gamingroom;

public abstract class Entity {
    private long id;
    private String name;

    private Entity(){

    }

    public Entity(long id, String name){
        this.id = id;
        this.name = name;
    }

    public long getId(){
        return id;
    }
    public String getName(){
        return name;
    }

    @Override
    public String toString(){
        return String.format("[id=%d name=%s]", id, name);
    }


}
