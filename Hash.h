
#pragma once

#include <string>
#include <iostream>

class Hash {
public:
   ~Hash();
   void AddUsingNumber(std::string inputName, int inputNumbers[]);
   void AddUsingName(std::string inputName, int inputNumbers[]);
   void AddUsingNameAndNumber(std::string inputName, int inputNumbers[]);
   friend std::ostream& operator<<(std::ostream& out, const Hash& hash);

private:
   struct Node {
      Node(std::string name, int number);

      std::string name; //This is the name of the person for the entry given.
      int number;       //This is the phone number of the person in the entry given.
      Node* nextNode = nullptr;   //This is a pointer to the next node in the chain, if one exists.
   };

   int addTime = 0; //The time it takes for a hash function to add all the entries.
   Node* hashTable[4177]; //This is the hash table that nodes will be stored in. It is 4,177
                          //nodes because that is the size the specifications said it must be.
};
