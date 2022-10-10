package com.gamingroom.gameauth.auth;

import io.dropwizard.auth.Authorizer;

public class GameAuthorizer implements Authorizer<GameUser> 
{
    @Override
    public boolean authorize(GameUser user, String role) {
        // Make sure the set returned by user.getRoles is valid
        // ... and check that it contains the supplied role
        return user.getRoles() != null && user.getRoles().contains(role);
    }
}