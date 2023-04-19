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

import app.Contact;

class ContactTest {

	/*
	 * Test Constructor with valid Parameters
	 */
	
	@Test
	void testContactClassWithValidParameters() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		assertTrue(contact.getID().equals("ID-1234567"));
		assertTrue(contact.getFirstName().equals("Dante"));
		assertTrue(contact.getLastName().equals("Trisciuzzi"));
		assertTrue(contact.getPhone().equals("1112223334"));
		assertTrue(contact.getAddress().equals("1337 Deadbeef Drive"));
	}
	
	
	/*
	 * Test Constructor with invalid Parameters
	 * .. one test for each: long, null 
	 * .. and short for phone number
	 */
	
	@Test
	void testContactClassWithLongID() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567x",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		});
	}
	
	@Test
	void testContactClassWithNullID() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				null,
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		});
	}
	
	@Test
	void testContactClassWithLongFirstName() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante-Bologna",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		});
	}
	
	@Test
	void testContactClassWithNullFirstName() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567",
				null,
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		});
	}
	
	@Test
	void testContactClassWithLongLastName() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi-x",
				"1112223334",
				"1337 Deadbeef Drive");
		});
	}
	
	@Test
	void testContactClassWithNullLastName() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				null,
				"1112223334",
				"1337 Deadbeef Drive");
		});
	}
	
	@Test
	void testContactClassWithLongPhone() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334555",
				"1337 Deadbeef Drive");
		});
	}
	
	@Test
	void testContactClassWithNullPhone() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				null,
				"1337 Deadbeef Drive");
		});
	}
	
	@Test
	void testContactClassWithShortPhone() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"123",
				"1337 Deadbeef Drive");
		});
	}
	
	@Test
	void testContactClassWithLongAddress() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive, Vermont, USA, Earth, Milky Way, Universe, ZIP: 12345");
		});
	}
	
	@Test
	void testContactClassWithNullAddress() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				null);
		});
	}
	
	
	/*
	 * Test Setters with valid parameters
	 */
	
	@Test
	void testContactSetFirstNameValid() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		contact.setFirstName("Jeffery");
		assertTrue(contact.getFirstName().equals("Jeffery"));
	}
	
	@Test
	void testContactSetLastNameValid() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		contact.setLastName("Lebowski");
		assertTrue(contact.getLastName().equals("Lebowski"));
	}
	
	@Test
	void testContactSetPhoneValid() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		contact.setPhone("5556667778");
		assertTrue(contact.getPhone().equals("5556667778"));
	}
	
	@Test
	void testContactSetAddressValid() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		contact.setAddress("123 Seasame Street");
		assertTrue(contact.getAddress().equals("123 Seasame Street"));
	}
	
	
	/*
	 * Test Setters with invalid parameters
	 * .. one test for each: long, null 
	 * .. and short for phone number
	 */
	
	@Test
	void testContactSetFirstNameLong() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contact.setFirstName("Jeffery_abcdefg");
		});
	}
	
	@Test
	void testContactSetFirstNameNull() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contact.setFirstName(null);
		});
	}
	
	@Test
	void testContactSetLastNameLong() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contact.setLastName("Lebowski_abcdefg");
		});
	}
	
	@Test
	void testContactSetLastNameNull() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contact.setLastName(null);
		});
	}
	
	@Test
	void testContactSetPhoneLong() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contact.setPhone("12345678901");
		});
	}
	
	@Test
	void testContactSetPhoneNull() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contact.setPhone(null);
		});
	}
	
	@Test
	void testContactSetPhoneShort() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contact.setPhone("12345678");
		});
	}
	
	@Test
	void testContactSetAddressLong() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contact.setAddress("123 Seasame Street, Disney Land, Anahiem California, ZIP: 12345");
		});
	}
	
	@Test
	void testContactSetAddressNull() {
		Contact contact = new Contact(
				"ID-1234567",
				"Dante",
				"Trisciuzzi",
				"1112223334",
				"1337 Deadbeef Drive");
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contact.setAddress(null);
		});
	}

}
