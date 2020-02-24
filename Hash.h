/*
File Name:  Hash.h
Author:     Logan Petersen
Date:       Febuary 22, 2020
Purpose:    This is the header file for the Hash class containing Hash's interface.
            The purpose of this code is to provide the function prototypes for both
            Hash and its internal structure Node, as well as define some defaults
            for variables.
*/

#pragma once

#include <string>    //Used in the functions to store the entry's name.
#include <iostream>  //Used for operator<<().
#include <cassert>   //Grants asserts. Used to ensure code is working properly.

class Hash {
public:
   /*
   Purpose:          Construct the heap when Heap is created without arguments.
   Parameters:       None.
   Preconditions:    This specific Heap object has not been instantiated.
   Postconditions:   Heap object has been instantiated with default values.
   Return value:     None.
   Functions Called: None.
   */
   Hash();

   /*
   Purpose:          Delete the memory allocated by this Heap object.
   Parameters:       None.
   Preconditions:    This specific Heap object has left scope.
   Postconditions:   Heap object no longer longer exists and its associated memory has been deallocated.
   Return value:     None.
   Functions Called: None.
   */
   ~Hash();

   /*
   Purpose:          Adds a new element to the hash table after computing it using inputNumbers.     
   Parameters:       string inputName, the name of the entry. Integer inputNumbers is the phone number in
                     the entry stored in an array.
   Preconditions:    Heap has been instantiated.
   Postconditions:   Heap's hashTable contains a new entry containing the name and phone number given to it.
   Return value:     None.
   Functions Called: ConverIntArrayToInt(). This is used to convert the given phone number in int form into
                     a long long int. this is needed for the modulus operator.
                     AddToHashTable(). This is used to place the entry in the calculated bin.
   */
   const void AddUsingNumber(std::string inputName, int inputNumbers[]);

   /*
   Purpose:          Adds a new element to the hash table after computing it using inputName.
   Parameters:       string inputName, the name of the entry. Integer inputNumbers is the phone number in
                     the entry stored in an array.
   Preconditions:    Heap has been instantiated.
   Postconditions:   Heap's hashTable contains a new entry containing the name and phone number given to it.
   Return value:     None.
   Functions Called: ConverIntArrayToInt(). This is used to convert the given phone number in int form into
                     a long long int. this is needed for the modulus operator.
                     AddToHashTable(). This is used to place the entry in the calculated bin.
   */
   const void AddUsingName(std::string inputName, int inputNumbers[]);

   /*
   Purpose:          Adds a new element to the hash table after computing it using inputName and inputNumbers.
   Parameters:       string inputName, the name of the entry. Integer inputNumbers is the phone number in
                     the entry stored in an array.
   Preconditions:    Heap has been instantiated.
   Postconditions:   Heap's hashTable contains a new entry containing the name and phone number given to it.
   Return value:     None.
   Functions Called: ConverIntArrayToInt(). This is used to convert the given phone number in int form into
                     a long long int. this is needed for the modulus operator.
                     AddToHashTable(). This is used to place the entry in the calculated bin.
   */
   const void AddUsingNameAndNumber(std::string inputName, int inputNumbers[]);

   /*
   Purpose:          Output the hash statistics according to specifications.
   Parameters:       out, the ostream that is the stream of characters being sent to the terminal.
                     heah, the Heap that is going to be printed according to specifications.
   Preconditions:    The Heap has been instantiated.
   Postconditions:   If the Heap is empty, print a statement that Heap is empty.
                     Otherwise, display the number of chains with their length according to specifications.
   Return value:     out, an ostream to allow statements to be chained according to operator<<'s specification.
   Functions Called: none.
   */
   friend std::ostream& operator<<(std::ostream& out, const Hash& hash);

private:

   /*
   Purpose:          Convert an integer array into a long long int. Used for converting the phone number given
                     through the file read into an integer so it can be modulated.
   Parameters:       Integer array[]. This is converted to a phone number. Must be at most 10 digits, more will
                     not be read.
   Preconditions:    The Heap has been instantiated.
   Postconditions:   A phone number is given in a long long int.
   Return value:     A phone number is returned in a long long int.
   Functions Called: none.
   */
   const long long int ConvertIntArrayToInt(int array[]);

   /*
   Purpose:          Adds a chain link containing the name and phone number given to the position given.
   Parameters:       String name, the name of the entry. Stored for retrieval if needed later, how a hash works.
                     Long long integer phoneNumber, the phone number of the entry. Stored for retrieval if needed
                     later, how a hash works.
                     Long long int position, where the new node should be placed in the hash table.
   Preconditions:    The Heap has been instantiated.
   Postconditions:   A node is added at the given location containing the given values.
   Return value:     None.
   Functions Called: None.
   */
   void AddToHashTable(std::string name, long long int phoneNumber, long long int position);

   struct Node {

      /*
      Purpose:          Construct a node when Node is created with arguments.
      Parameters:       String name, stored for retrieval if needed later, like a hash would.
                        Long long int number, stored for retrieval if needed later, like a hash would.
      Preconditions:    This specific Node object has not been instantiated.
      Postconditions:   Node object has been instantiated with the given values values.
      Return value:     None.
      Functions Called: None.
      */
      Node(std::string name, long long int number);

      std::string name;          //This is the name of the person for the entry given.
      long long int number;      //This is the phone number of the person in the entry given.
      Node* nextNode = nullptr;  //This is a pointer to the next node in the chain, if one exists.
   };

   bool filled = false;   //set to true when something is added to hash. If nothing is added,
                          //operator<< should behave differently.
   Node* hashTable[4177]; //This is the hash table that nodes will be stored in. It is 4,177
                          //nodes because that is the size the specifications said it must be.
};
