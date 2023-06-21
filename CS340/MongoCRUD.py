## Author: Dante Trisciuzzi
## Date: 5.30.2023
## Class: CS-340 SNHU
 
from pymongo import MongoClient
from bson.objectid import ObjectId
 
class MongoCRUD(object):
    """ CRUD operations for MongoDB """
 
    def __init__(self, username, password, database, collection):
        USER = username
        PASS = password
        HOST = 'nv-desktop-services.apporto.com'
        PORT = 30130
        DB = database
        COL = collection
 
        # Establish a connection to the MongoDB server
        self.client = MongoClient('mongodb://%s:%s@%s:%d' % (USER, PASS, HOST, PORT))
 
        # Access the specified database and collection
        self.database = self.client['%s' % (DB)]
        self.collection = self.database['%s' % (COL)]
 
 
    def create(self, data):
        """
        Create a new document in thecollection.
 
        Args:
            data: A dictionary containing the data for the new document.
 
        Returns:
            True if the document was successfully created, False otherwise.
 
        Raises:
            Exception: If the data parameter is empty.
        """
        if data is not None:
            try:
                # Insert the data as a new document in the collection
                self.database.animals.insert_one(data)
                return True
            except:
                return False            
        else:
            raise Exception("Nothing to save because the data parameter is empty")
 
    def read(self, query):
        """
        Retrieve documents from the collection based on the specified query.
 
        Args:
            query: A dictionary representing the query to filter the documents.
 
        Returns:
            A list of documents that match the query, or an empty list if no matches were found.
 
        Raises:
            Exception: If the query parameter is empty.
        """
        if query is not None:
            # Find documents in the collection based on the query
            result = self.database.animals.find(query)
            return list(result) if result else []
        else:
            raise Exception("Nothing to read because the query parameter is empty")

    def update(self, query, update_data):
        """
        Update documents in the collection based on the specified query.
 
        Args:
            query: A dictionary representing the query to filter the documents.
            update_data: A dictionary containing the data to update the matching documents.
 
        Returns:
            True if the documents were successfully updated, False otherwise.
 
        Raises:
            Exception: If either the query or update_data parameters are empty.
        """
        if query is not None and update_data is not None:
            try:
                # Update the matching documents in the collection with the provided data
                self.collection.update_many(query, {'$set': update_data})
                return True
            except:
                return False
        else:
            raise Exception("Nothing to update because the query or update_data parameter is empty")
 
    def delete(self, query):
        """
        Delete documents from the collection based on the specified query.
 
        Args:
            query: A dictionary representing the query to filter the documents to be deleted.
 
        Returns:
            True if the documents were successfully deleted, False otherwise.
 
        Raises:
            Exception: If the query parameter is empty.
        """
        if query is not None:
            try:
                # Delete the matching documents from the collection
                self.collection.delete_many(query)
                return True
            except:
                return False
        else:
            raise Exception("Nothing to delete because the query parameter is empty")
