/*
 *
 *	Author: Dante A Trisciuzzi
 *	Purpose: SNHU CS320 Project One
 *	Date: 4.3.2023
 *
 */

package tests;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import app.ContactService;

class ContactServiceTest {

	/*
	 * Tests to check add contact functionality
	 */
	
	@Test
	void testContactServiceAddContactsValid() {
		ContactService contactService = new ContactService();
		contactService.addContact(
						"ID-1234567",
						"Dante",
						"Trisciuzzi",
						"1112223334",
						"1337 Deadbeef Drive");
		contactService.addContact(
						"ID-9876543",
						"Jeffery",
						"Lebowski",
						"0987654321",
						"123 White Russian Ln.");
	}
	
	@Test
	void testContactServiceAddContactsDuplicateId() {
		ContactService contactService = new ContactService();
		contactService.addContact(
						"ID-1234567",
						"Dante",
						"Trisciuzzi",
						"1112223334",
						"1337 Deadbeef Drive");
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.addContact(
					"ID-1234567",
					"Jeffery",
					"Lebowski",
					"0987654321",
					"123 White Russian Ln.");
		});
	}
	
	
	/*
	 * Tests to check the delete functionality
	 */
	
	@Test
	void testContactServiceDeleteContactValidId() {
		ContactService contactService = new ContactService();
		contactService.addContact(
						"ID-1234567",
						"Dante",
						"Trisciuzzi",
						"1112223334",
						"1337 Deadbeef Drive");
		
		// Test will fail if this throws an exception
		contactService.deleteContact("ID-1234567");
		
		// We then check if we can get the contact
		// ..this SHOULD throw an exception (since the contact is expected to be deleted)
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.getContact("ID-1234567");
		});
	}
	
	@Test
	void testContactServiceDeleteContactInvalidId() {
		ContactService contactService = new ContactService();
		contactService.addContact(
						"ID-1234567",
						"Dante",
						"Trisciuzzi",
						"1112223334",
						"1337 Deadbeef Drive");
		
		
		// We expect this to fail, since the ID is wrong
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.deleteContact("999999999");
		});
		
		// We then check if we can get the contact
		// .. This should be successful, otherwise the test fails
		contactService.getContact("ID-1234567");
	}
	
	/*
	 * Tests to check the update functionality
	 */
	
	@Test
	void testContactServiceUpdateFirstName() {
		ContactService contactService = new ContactService();
		contactService.addContact(
						"ID-1234567",
						"Dante",
						"Trisciuzzi",
						"1112223334",
						"1337 Deadbeef Drive");
		
		contactService.updateContactFirstName("ID-1234567", "Jeffery");
		
		assertTrue(contactService.getContact("ID-1234567").getFirstName().equals("Jeffery"));
	}
	
	@Test
	void testContactServiceUpdateLastName() {
		ContactService contactService = new ContactService();
		contactService.addContact(
						"ID-1234567",
						"Dante",
						"Trisciuzzi",
						"1112223334",
						"1337 Deadbeef Drive");
		
		contactService.updateContactLastName("ID-1234567", "Lebowski");
		
		assertTrue(contactService.getContact("ID-1234567").getLastName().equals("Lebowski"));
	}
	
	@Test
	void testContactServiceUpdatePhone() {
		ContactService contactService = new ContactService();
		contactService.addContact(
						"ID-1234567",
						"Dante",
						"Trisciuzzi",
						"1112223334",
						"1337 Deadbeef Drive");
		
		contactService.updateContactPhone("ID-1234567", "0987654321");
		
		assertTrue(contactService.getContact("ID-1234567").getPhone().equals("0987654321"));
	}
	
	@Test
	void testContactServiceUpdateAddress() {
		ContactService contactService = new ContactService();
		contactService.addContact(
						"ID-1234567",
						"Dante",
						"Trisciuzzi",
						"1112223334",
						"1337 Deadbeef Drive");
		
		contactService.updateContactAddress("ID-1234567", "123 Seasame Street");
		
		assertTrue(contactService.getContact("ID-1234567").getAddress().equals("123 Seasame Street"));
	}

}
