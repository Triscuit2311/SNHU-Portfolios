/*
 *
 *	Author: Dante A Trisciuzzi
 *	Purpose: SNHU CS320 Project One
 *	Date: 4.3.2023
 *
 */

package app;

// Imports for the built-in hash map
import java.util.HashMap;
import java.util.Map;

public class ContactService {
	
	// I chose a hash map because we're using a string ID
	// .. This should make it easier and faster to check for existing contacts
    private Map<String, Contact> contacts;

    public ContactService() {
        contacts = new HashMap<String, Contact>();
    }
    
    /**
     * Checks if a contact exists in the hash map.
     */
    private boolean doesContactExist(String ID) {
    	if (contacts.containsKey(ID)) {
    		return true;
    	}
    	return false;
    }

    /**
     * Adds a new contact to the hash map if the ID is unique and does not already exist.
     */
    public void addContact(String ID, String firstName, String lastName, String phone, String address) {
        if (doesContactExist(ID)) {
            throw new IllegalArgumentException("Contact ID is not unique");
        }
        Contact contact = new Contact(ID,firstName,lastName, phone, address);
        contacts.put(contact.getID(), contact);
    }

    /**
     * Removes a contact from the hash map if the ID is valid and exists.
     */
    public void deleteContact(String ID) {
        if (!doesContactExist(ID)) {
            throw new IllegalArgumentException("Contact ID not found");
        }
        contacts.remove(ID);
    }
    
    
    /**
     * Gets a contact from the hash map if the ID is valid and exists.
     */
    public Contact getContact(String ID) {
        if (!doesContactExist(ID)) {
            throw new IllegalArgumentException("Contact ID not found");
        }
        return contacts.get(ID);
    }

    
    /*
     * Update methods for modifying contact information.
     * .. No method for changing the contact ID, 
     * .. as it should not be changed once initialized.
     */
    
    
    public void updateContactFirstName(String ID, String firstName) {
        if (!doesContactExist(ID)) {
            throw new IllegalArgumentException("Contact ID not found");
        }
        contacts.get(ID).setFirstName(firstName);
    }
    
    public void updateContactLastName(String ID, String lastName) {
        if (!doesContactExist(ID)) {
            throw new IllegalArgumentException("Contact ID not found");
        }
        contacts.get(ID).setLastName(lastName);
    }
    
    public void updateContactPhone(String ID, String phone) {
        if (!doesContactExist(ID)) {
            throw new IllegalArgumentException("Contact ID not found");
        }
        contacts.get(ID).setPhone(phone);
    }
    
    public void updateContactAddress(String ID, String address) {
        if (!doesContactExist(ID)) {
            throw new IllegalArgumentException("Contact ID not found");
        }
        contacts.get(ID).setAddress(address);
    }
}
