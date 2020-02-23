
#pragma once

#include <string>
#include <iostream>
#include <cassert>

class Hash {
public:
   Hash();
   ~Hash();
   const void AddUsingNumber(std::string inputName, int inputNumbers[]);
   const void AddUsingName(std::string inputName, int inputNumbers[]);
   const void AddUsingNameAndNumber(std::string inputName, int inputNumbers[]);
   friend std::ostream& operator<<(std::ostream& out, const Hash& hash);

private:
   const long long int ConvertIntArrayToInt(int array[]);
   void AddToHashTable(std::string name, long long int phoneNumber, long long int position);

   struct Node {
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
