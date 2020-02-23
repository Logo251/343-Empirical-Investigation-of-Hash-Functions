
#include "Hash.h"

Hash::Hash() {
   
   //Assign every element of the array to nullptr.
   for (int i = 0; i < 4177; i++) { //4177 is the size of the hash table.
      //Every data point inside hashTable has not been interated through yet.

      //Assign it to nullptr.
      hashTable[i] = nullptr;
   }
}

Hash::~Hash() {
   for (Node* i : hashTable) {
      //Every data point inside hashTable has not been interated through yet.
      if (i != nullptr) {
         if (i->nextNode != nullptr) {
            delete i;
         }
         else {
            Node* thisNode = i;
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

Hash::Node::Node(std::string name, long long int number) {
   this->name = name;
   this->number = number;
}
