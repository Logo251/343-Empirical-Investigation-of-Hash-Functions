
#include "Hash.h"

Hash::Hash() {
   
   //Assign every element of the array to nullptr.
   for (int i = 0; i < 4177; i++) { //4177 is the size of the hash table.
      hashTable[i] = nullptr;
   }
}

Hash::~Hash() {
   for (Node* i : hashTable) {
      if (i != nullptr) {
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
}

void Hash::AddUsingNumber(std::string inputName, int inputNumbers[]) {

   //Local Variables
   long long int addedNumbers = 0;
   long long int phoneNumber = 0;

   //Get the phone number in int form.
   phoneNumber = ConvertIntArrayToInt(inputNumbers);
   addedNumbers = phoneNumber;

   assert(addedNumbers >= 0); //should never be negative.

   addedNumbers %= 4177; //4177 is the size of the hash table.

   AddToHashTable(inputName, phoneNumber, addedNumbers);
}

void Hash::AddUsingName(std::string inputName, int inputNumbers[]) {

   //Local Variables
   long long int addedNumbers = 0;
   long long int phoneNumber;

   //Convert to Ascii value of the character.
   for(char i : inputName) {
      addedNumbers += (int)i;
   }

   //Get the phone number in int form.
   phoneNumber = ConvertIntArrayToInt(inputNumbers);
   addedNumbers = phoneNumber;

   assert(addedNumbers >= 0); //should never be negative.

   addedNumbers %= 4177; //4177 is the size of the hash table.

   AddToHashTable(inputName, phoneNumber, addedNumbers);
}

void Hash::AddUsingNameAndNumber(std::string inputName, int inputNumbers[]) {

   //Local Variables
   long long int addedNumbers = 0;
   long long int phoneNumber = 0;

   //Get the phone number in int form.
   phoneNumber = ConvertIntArrayToInt(inputNumbers);
   addedNumbers = phoneNumber;

   //Convert to Ascii value of the character.
   for (char i : inputName) {
      addedNumbers += (int)i;
   }

   assert(addedNumbers >= 0); //should never be negative.

   addedNumbers %= 4177; //4177 is the size of the hash table.

   AddToHashTable(inputName, phoneNumber, addedNumbers);
}

long long int Hash::ConvertIntArrayToInt(int inputArray[]) {

   //Local Variables
   long long int phoneNumber = 0; //Needs to be this big otherwise phone number breaks on last x10.

   //Convert phone number array to phone number.
   for (int i = 0; i < 10; i++) {   //10 is the number of digits in a phone number.
      phoneNumber += inputArray[i];
      phoneNumber *= 10;
   }
   phoneNumber /= 10; //Remove the last x10, so we have a 10 digit phone number.

   assert(phoneNumber >= 0); //should never be negative.
   return phoneNumber;
}

void Hash::AddToHashTable(std::string name, long long int phoneNumber, long long int position) {

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
   int chainSize = 0;
   int countOfChains = 0; //This is the number of chains with a certain length.
   Hash::Node* chainLink;
   int lengthStorage[4177] = { 0 }; //Stores the lengths of each bin's chain.

   //This takes the length of each chain, and puts the value in another array in the same position as the other.
   for(int i = 0; i < 4177; i++) { //4177 is the size of the hash table.
      chainLink = hash.hashTable[i];
      if(chainLink != nullptr) {
         chainSize++; //count the first node.
         while(chainLink->nextNode != nullptr) {
            chainSize++;
            chainLink = chainLink->nextNode;
         }
         if (i == 480) {
         }
         if(longestChain < chainSize) {
            longestChain = chainSize;
         }
         lengthStorage[i] = chainSize;
         chainSize = 0;
      }
   }

   //Counts the number of each chain length, and prints it.
   for(int i = 1; i <= longestChain; i++) {
      for(int j = 0; j < 4177; j++) {
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

Hash::Node::Node(std::string name, long long int number) {
   this->name = name;
   this->number = number;
}
