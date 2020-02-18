
#include "Hash.h"

Hash::~Hash() {
   for (Node* i : hashTable) {
      if (i->nextNode != nullptr) {
         delete i;
      }
      else {
         Node* thisNode = i;
         Node* nextNodeStorage = thisNode->nextNode;

         while (nextNodeStorage != nullptr) {
            delete thisNode;
            nextNodeStorage = thisNode;
            nextNodeStorage = thisNode->nextNode;
         }
      }
   }
}

void Hash::AddOne(std::string inputName, int inputNumbers[]) {
   //Local Variables
   int addedNumbers = 0;
   int phoneNumber = 0;

   for (int i = 0; i < 10; i++) {   //10 is the number of digits in a phone number.
      addedNumbers += inputNumbers[i];

      phoneNumber += inputNumbers[i];
      phoneNumber *= 10;
   }
   phoneNumber /= 10; //Remove the last x10, so we have a 10 digit phone number.

   addedNumbers %= 4177; //4177 is the size of the hash table.
   Node* chainLink = new Node(inputName, phoneNumber);
   if (hashTable[addedNumbers] == nullptr) {
      hashTable[addedNumbers] = chainLink;
   }
   else {
      Node* endNode = hashTable[addedNumbers];
      while (endNode->nextNode != nullptr) {
         endNode = endNode->nextNode;
      }
      endNode->nextNode = chainLink;
   }
}

void Hash::AddTwo(std::string inputName, int inputNumbers[]) {

}

void Hash::AddThree(std::string inputName, int inputNumbers[]) {
   
}

std::ostream& operator<<(std::ostream& out, const Hash& hash) {
   return out;
}

Hash::Node::Node(std::string name, int number) {
   name = this->name;
   number = this->number;
}
