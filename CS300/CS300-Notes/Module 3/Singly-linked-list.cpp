
/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Personal Code Notes for CS300 (DSA)
 .. Writing a singly-linked list implementation
 .. Before starting this section of the coursework
 .. Just to see how my approach might change.
 .. I have never written a singly-linked list before.
*/


#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <functional>
using namespace std;

// Listnode
struct listNode{
    // Contains a pointer to the next potential node
    // .. and an integer value
    listNode * next;
    int value;

    // Defaults to nullptr for next node.
    listNode(int val, listNode * _next = nullptr){
        next = _next;
        value = val;
    }
};


class tList{
    private:
        // Contains a head node for a constant pointer
        // .. to the first node in the list
        listNode * head = nullptr;

        // Size of the list gets increments when a node is added
        size_t size = 0;

    public:

    tList(){}

    // Constructor to take a vector
    tList(vector<int> values){
        for(auto & n : values)
            this->Append(n);
    }

    // Constructor to take an array
    tList(int values[], int size){
        for(auto i = 0; i < size; i++)
            this->Append(values[i]);
    }

    // Deconstructor
    // ..Iterates each node and removes it
    // ..Also removes the head node.
    ~tList(){
        while(head != nullptr){
            auto tempNext = head->next;
            delete head;
            head = tempNext;
        }
        if(head != nullptr) delete head;
    }

    int Size(){
        return size;
    };

    // Append
    // .. Appends new node with given value
    // .. Instantiates head node if uninitialized
    void Append(int value){
        // Increment size of list 
        size++;

        // If no head node exists, create it
        if( head == nullptr){
            head = new listNode(value);
            head->next = nullptr;
            return;
        }

        // Create a temporary node pointer for iteration
        auto t = head;

        // Iterate to the last node
        while(t != nullptr && t->next != nullptr){
            t = t->next;
        }

        // Add new node to be the next node from the previous last node
        t->next = new listNode(value);
    };

    // Print
    // .. Print all values in the list
    void Print(){
        auto t = head;

        // Iterate every node (including the last node)
        // and print the value.
        while(t != nullptr){
            cout << t->value << ' ';
            t = t->next;
        }
        cout << endl;
    };

    // ForEach
    // .. takes a callback and executes it for each
    // .. value in the list
    void ForEach(std::function<void(int)> operation){
        auto t = head;
        while(t != nullptr){
            operation(t->value);
            t = t->next;
        }
    }

    // FindFirstOf
    // .. Iterate the list until value matches
    // .. otherwise returns -1 index
    int FindFirstOf(int value){
        auto t = head;
        auto i = 0;
        while(t != nullptr){
            if(t->value == value)
                return i;
            t = t->next;
            i++;
        }
        return -1;
    }

    // Remove
    // .. Removes a node from the list
    bool Remove(int index){

        // Create an iterator, last node and an index
        auto t = head;
        auto last = t;
        auto i = 0;

        while(t != nullptr){

            // If we find the index, set the next pointer
            // .. from the previous node to be the current node's next
            // .. then remove the current node
            if( i == index){
                last->next = t->next;
                delete t;
                return true;
            }

            // traverse list, increment index
            last = t;
            t = t->next;
            i++;
        }

        // node index invalid, return false
        return false;
    }
};

void testLinkedList(tList &l){
    cout << "\tSize: " << l.Size() <<endl;
    cout << "\tExecute ForEach (Lambda that prints with braces): \n\t";
    l.ForEach([](int n){cout << '[' << n << ']';});
    cout << "\n\tPrint List: \n\t";
    l.Print();
    cout << "\tGet Index of Value (6), and remove it: \n\tIndex: " << l.FindFirstOf(6) << endl;
    l.Remove(l.FindFirstOf(6));
    cout << "\tNew List:\n\t";
    l.Print();
}


int main(char* __argc, int __argv) {

    cout << "\n\n## Testing Manually Appending Values ##\n" << endl;
    {
        tList l;
        l.Append(2);
        l.Append(4);
        l.Append(6);
        l.Append(8);
        l.Append(10);
        testLinkedList(l);
    }

    cout << "\n\n## Testing Vector Constructor ##\n" << endl;
    {
        vector<int> vec = {1, 3, 7, 32, 6, 8, 9, 2, 12};
        tList l(vec);
        testLinkedList(l);
    }

    cout << "\n\n## Testing Array Constructor ##\n" << endl;
    {
        int arr[] = {83, 33, 21, 82, 6, 55, 4, 2, 1, 0};
        tList l(arr, 10);
        testLinkedList(l);
    }

    return 0;
}
