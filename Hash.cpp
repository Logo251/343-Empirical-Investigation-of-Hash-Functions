
#include "Hash.h"

Hash::Hash() {
   
   //Assign every element of the array to nullptr.
   for (int i = 0; i < 4177; i++) { //4177 is the size of the hash table.
      hashTable[i] = nullptr;
   }
}

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

void Hash::AddUsingNumber(std::string inputName, int inputNumbers[]) {

   //Local Variables
   int addedNumbers = 0;
   int phoneNumber = 0;

   //Get the phone number in int form.
   phoneNumber = ConvertIntArrayToInt(inputNumbers);
   addedNumbers = phoneNumber;

   addedNumbers %= 4177; //4177 is the size of the hash table.

   AddToHashTable(inputName, phoneNumber, addedNumbers);
}

void Hash::AddUsingName(std::string inputName, int inputNumbers[]) {

   //Local Variables
   int addedNumbers = 0;
   int phoneNumber;

   //Convert to Ascii value of the character.
   for(char i : inputName) {
      addedNumbers += (int)i;
   }

   //Get the phone number in int form.
   phoneNumber = ConvertIntArrayToInt(inputNumbers);
   addedNumbers = phoneNumber;

   addedNumbers %= 4177; //4177 is the size of the hash table.

   AddToHashTable(inputName, phoneNumber, addedNumbers);
}

void Hash::AddUsingNameAndNumber(std::string inputName, int inputNumbers[]) {

}

int Hash::ConvertIntArrayToInt(int inputArray[]) {

   //Local Variables
   long long int phoneNumber = 0; //Needs to be this big otherwise phone number breaks on last x10.

   //Convert phone number array to phone number.
   for (int i = 0; i < 10; i++) {   //10 is the number of digits in a phone number.
      phoneNumber += inputArray[i];
      phoneNumber *= 10;
   }
   phoneNumber /= 10; //Remove the last x10, so we have a 10 digit phone number.
   return phoneNumber;
}

void Hash::AddToHashTable(std::string name, int phoneNumber, int position) {

   //Local Variables
   Node* chainLink = new Node(name, phoneNumber);

   if (hashTable[position] == nullptr) {
      hashTable[position] = chainLink;
   }
   else {
      Node* endNode = hashTable[position];
      while (endNode->nextNode != nullptr) {
         endNode = endNode->nextNode;
      }
      endNode->nextNode = chainLink;
   }
}

std::ostream& operator<<(std::ostream& out, const Hash& hash) {

   //Local Variables
   int longestChain = 0;
   int numberOfChains = 0;
   int countOfChains = 0; //This is the number of chains with a certain length.
   Hash::Node* chainLink;
   int chainLength[4177]; //This will be used to store, for each bin, the length of its chain.

   for(int i = 0; i < 4177; i++) { //4177 is the size of the hash table.
      chainLink = hash.hashTable[i];
      while(chainLink->nextNode != nullptr) {
         numberOfChains++;
      }
      if(longestChain < numberOfChains) {
         longestChain = numberOfChains;
      }
      chainLength[i] = numberOfChains;
      numberOfChains = 0;
   }

   for(int i = 0; i < longestChain; i++) {
      for(int j = 0; j < 4177; j++) {
         if(chainLength[j] == i) {
            numberOfChains++;
         }
      }
      std::cout << "The number of chains with length " << i << " is " << numberOfChains << std::endl;
      numberOfChains = 0;
   }
   return out;
}

Hash::Node::Node(std::string name, int number) {
   this->name = name;
   this->number = number;
}
