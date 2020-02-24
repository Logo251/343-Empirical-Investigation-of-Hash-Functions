/*
File Name:  Hash.cpp
Author:     Logan Petersen
Date:       Febuary 22, 2020
Purpose:    The purpose of this code is to be the function definitions for
            the function prototypes defined in Hash.h. The code allows creation
            of Hash and its internal structure Vertex, the use of Hash, and the
            eventual deletion of both objects.
*/

#include "Hash.h"

/*
Purpose:          Construct the heap when Heap is created without arguments.
Parameters:       None.
Preconditions:    This specific Heap object has not been instantiated.
Postconditions:   Heap object has been instantiated with default values.
Return value:     None.
Functions Called: None.
*/
Hash::Hash() {
   
   //Assign every element of the array to nullptr.
   for (int i = 0; i < 4177; i++) { //4177 is the size of the hash table.
      //Every data point inside hashTable has not been interated through yet.

      //Assign it to nullptr.
      hashTable[i] = nullptr;
   }
}

/*
Purpose:          Delete the memory allocated by this Heap object.
Parameters:       None.
Preconditions:    This specific Heap object has left scope.
Postconditions:   Heap object no longer longer exists and its associated memory has been deallocated.
Return value:     None.
Functions Called: None.
*/
Hash::~Hash() {
   for (int i = 0; i < 4177; i++) {
      //Every data point inside hashTable has not been interated through yet.
      if (hashTable[i] != nullptr) {
         if (hashTable[i]->nextNode != nullptr) {
            delete hashTable[i];
         }
         else {
            Node* thisNode = hashTable[i];
            Node* nextNodeStorage = thisNode->nextNode;

            while (nextNodeStorage != nullptr) {
               //Every Node inside this bin has not been iterated through yet.
               delete thisNode;
               nextNodeStorage = thisNode;
               nextNodeStorage = thisNode->nextNode;
            }
         }
      }
   }
}

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
const void Hash::AddUsingNumber(std::string inputName, int inputNumbers[]) {

   //Local Variables
   long long int hashPosition = 0;  //Where this name and phone number should be placed. Can be any non-negative value.
   long long int phoneNumber = 0;   //Stores the phone number in int form for math purposes. Can be any non-negative value.

   //Get the phone number in int form.
   phoneNumber = ConvertIntArrayToInt(inputNumbers);
   hashPosition = phoneNumber;

   assert(hashPosition >= 0 && phoneNumber >= 0); //should never be negative.

   hashPosition %= 4177; //4177 is the size of the hash table.

   AddToHashTable(inputName, phoneNumber, hashPosition);
}

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
const void Hash::AddUsingName(std::string inputName, int inputNumbers[]) {

   //Local Variables
   long long int hashPosition = 0;  //Where this name and phone number should be placed. Can be any non-negative value.
   long long int phoneNumber = 0;   //Stores the phone number in int form for math purposes. Can be any non-negative value.

   //Convert to Ascii value of the character.
   for(char i : inputName) {
      //Every character in the string has not been iterated through yet.

      hashPosition += (int)i;
   }

   //Get the phone number in int form.
   phoneNumber = ConvertIntArrayToInt(inputNumbers);

   assert(hashPosition >= 0 && phoneNumber >= 0); //should never be negative.

   hashPosition %= 4177; //4177 is the size of the hash table.

   AddToHashTable(inputName, phoneNumber, hashPosition);
}

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
const void Hash::AddUsingNameAndNumber(std::string inputName, int inputNumbers[]) {

   //Local Variables
   long long int hashPosition = 0;  //Where this name and phone number should be placed. Can be any non-negative value.
   long long int phoneNumber = 0;   //Stores the phone number in int form for math purposes. Can be any non-negative value.

   //Get the phone number in int form.
   phoneNumber = ConvertIntArrayToInt(inputNumbers);
   hashPosition = phoneNumber;

   //Convert to Ascii value of the character and add it to the phonenumber.
   for (char i : inputName) {
      //Every character in the string has not been iterated through yet.

      hashPosition += (int)i;
   }

   assert(hashPosition >= 0 && phoneNumber >= 0); //should never be negative.

   hashPosition %= 4177; //4177 is the size of the hash table.

   AddToHashTable(inputName, phoneNumber, hashPosition);
}

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
const long long int Hash::ConvertIntArrayToInt(int inputArray[]) {

   //Local Variables
   long long int phoneNumber = 0; //Needs to be this big otherwise phone number breaks on last x10.

   //Convert phone number array to phone number.
   for (int i = 0; i < 10; i++) {   //10 is the number of digits in a phone number.
      //Every digit in the phone number array inputArray[] has not been iterated through yet.

      phoneNumber += inputArray[i];

      //This is used to add a new place for another digit.
      phoneNumber *= 10;
   }
   phoneNumber /= 10; //Remove the last x10, so we have a 10 digit phone number.

   assert(phoneNumber >= 0); //should never be negative.
   return phoneNumber;
}

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
void Hash::AddToHashTable(std::string name, long long int phoneNumber, long long int position) {

   //Local Variables
   Node* chainLink = new Node(name, phoneNumber);

   //When there is an open spot.
   if (hashTable[position] == nullptr) {
      hashTable[position] = chainLink;
   }
   //Iterate down the chain existing in this bin, put new node at the end.
   else {
      Node* endNode = hashTable[position];
      while (endNode->nextNode != nullptr) {
         //The program is not at the end of the chain yet.

         endNode = endNode->nextNode;
      }
      endNode->nextNode = chainLink;
   }

   //Set filled to true, so operator<< knows that it has information to print.
   filled = true;
}

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
std::ostream& operator<<(std::ostream& out, const Hash& hash) {

   //Local Variables
   int longestChain = 0;   //This is storage of the longest chain. Valid range is all non-negative numbers.
   int chainSize = 0;      //This is the size of the current chain in question. Valid range is all non-negative numbers.
   int countOfChains = 0;  //This is the number of chains with a certain length. Valid range is all non-negative numbers.
   Hash::Node* chainLink;  //This is used to point to a chain node so we can iterate down a chain to count.
   int lengthStorage[4177] = { 0 }; //Stores the lengths of each bin's chain. Each digit's valid range is any non-negative number.

   //If nothing is in hash, no need to attempt to print.
   if (!hash.filled) {
      std::cout << "Nothing was in the file.\n";
      return out;
   }

   //This takes the length of each chain, and puts the value in another array in the same position as the other.
   for(int i = 0; i < 4177; i++) { //4177 is the size of the hash table.
      //Every bin inside hashTable has not been interated through yet.

      chainLink = hash.hashTable[i];
      if(chainLink != nullptr) {
         chainSize++; //count the first node.
         while(chainLink->nextNode != nullptr) {
            //Every Node inside this bin has not been iterated through yet.

            chainSize++;
            chainLink = chainLink->nextNode;
         }
         
         //If new chain is longer than previous best, replace.
         if(longestChain < chainSize) {
            longestChain = chainSize;
         }
         lengthStorage[i] = chainSize;
         chainSize = 0;
      }
   }

   //Counts the number of each chain length, and prints it.
   for(int i = 1; i <= longestChain; i++) {
      //We have not iterated through every possible chain length.

      for(int j = 0; j < 4177; j++) {
         //We have not iterated through every bin in lengthStorage.

         if(lengthStorage[j] == i) {
            countOfChains++;
         }
      }
      if (countOfChains != 0) {
         std::cout << "The number of chains with length " << i << " is " << countOfChains << std::endl;
         countOfChains = 0;
      }
      countOfChains = 0;
   }
   return out;
}

/*
Purpose:          Construct a node when Node is created with arguments.
Parameters:       String name, stored for retrieval if needed later, like a hash would.
                  Long long int number, stored for retrieval if needed later, like a hash would.
Preconditions:    This specific Node object has not been instantiated.
Postconditions:   Node object has been instantiated with the given values values.
Return value:     None.
Functions Called: None.
*/
Hash::Node::Node(std::string name, long long int number) {
   this->name = name;
   this->number = number;
}
