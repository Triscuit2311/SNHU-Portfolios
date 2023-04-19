/*
 *
 *	Author: Dante A Trisciuzzi
 *	Purpose: SNHU CS320 Project One
 *	Date: 4.3.2023
 *
 */

package app;

public class Contact {
	
    private String ID;
    private String firstName;
    private String lastName;
    private String phone;
    private String address;

    public Contact(String ID, String firstName, String lastName, String phone, String address) {
        StringIsValid(ID, 1, 10, "Invalid ID");
        StringIsValid(firstName, 1, 10, "Invalid First Name");
        StringIsValid(lastName, 1, 10, "Invalid Last Name");
        StringIsValid(phone, 10, 10, "Invalid Phone Number");
        StringIsValid(address, 1, 30, "Invalid Address");
        
        this.ID = ID;
        this.firstName = firstName;
        this.lastName = lastName;
        this.phone = phone;
        this.address = address;
    }
    
    /**
     * Ensures a string is not null, and within length bounds. Otherwise throws an IllegalArgumentException.
     */
    private boolean StringIsValid(String str, int minLength, int maxLength, String errorMsg) {
    	if(!(str == null) && str.length() >= minLength && str.length() <= maxLength) {
    		return true;
    	}
    	throw new IllegalArgumentException("Illegal argument. " + errorMsg );
    }

    
    /*
     * Getters and setters.
     * ... Note that ID only has a getter, no setter as it should not be mutable after initialization.
     */
    
    
    public String getID() {
        return ID;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
    	StringIsValid(firstName, 1, 10, "Invalid First Name");
    	this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
    	StringIsValid(lastName, 1, 10, "Invalid Last Name");
    	this.lastName = lastName;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
    	StringIsValid(phone, 10, 10, "Invalid Phone Number");
    	this.phone = phone;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
    	StringIsValid(address, 1, 30, "Invalid Address");
    	this.address = address;
    }
  
    
}
