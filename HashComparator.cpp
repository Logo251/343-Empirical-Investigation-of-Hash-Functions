/*
   File Name:  HashComparator.cpp
   Author:     Logan Petersen
   Date:       Febuary 22, 2020
   Purpose:    The purpose of this program is to compare three hash function. It compares their performance based entirely
               on the number of collisions each hash has. It does this because goal is to, in the end, choose a single hash
               that is best for data in this format. To achieve this, three different hash methods will be created, timed,
               and have the number of collisions counted. Then, this data will be compared, and the hash that causes the
               least amount of collisions will be chosen as the best hash function available. It is assumed that, in this
               case, the best hash is a hash that lacks collisions, based on the report that will be written including a
               histogram focusing on number and depth of collisions. All hash functions must write to a hash table with a
               size of 4,177, which is a prime number, and the hash table must be implemented using separate chaining.

               Provided to solve this problem is a phonebook.txt, a list of names and phone numbers, assumed to be related
               to the names.

               This list is 46,332 entries long. The file is sorted alphabetically, features many duplicate names and duplicate
               phone numbers, although no two entries exist with the same name and phone number.

               The only definitive requirement required by the problem is sufficient output to compare various hash functions
               in a histogram containing the chain length and number of entries with that length.

               Input is phonebook.txt, a file containing 46,332 entries, each one name, a tab, and a phone number, sorted
               alphabetically. This is provided through a command line argument. There are many duplicate phone numbers and
               duplicate names, although there does not appear to be two entries with the same name and phone number. The
               format for the is as follows:

               Jackson, Andrew	(111) 111-1111
               Jackson, Andrew	(111) 121-1314
               Jackson, Raphaela	(111) 111-1111

               The output is required to be data sufficient to identify the number of chains and length of those chains, for
               example there was 30 chains of length 2, the initial node and one collision. Therefore, the output of the program
               will be a report stating the total numbers of each chain length. An example is below.

               HASH ONE:
               The number of chains with length 1 is 40000
               The number of chains with length 2 is 2000
               The number of chains with length 3 is 2500
               The number of chains with length 4 is 13

               HASH TWO:
               The number of chains with length 4 is 46332
*/

#include "Hash.h"    //My hash function.
#include <iostream>  //Used to display hash information
#include <string>    //Used to store the name in the entries.
#include <fstream>   //Used to read from file.


int main(int argc, char** argv) {

   //Local Variables
   Hash hashByNumber;           //This will be hashing using the number.
   Hash hashByName;             //This will be hashing using the name.
   Hash hashByNameAndNumber;    //This will be hashing using both name and number.
   std::fstream file;           //This is for reading from the file.
   int phoneNumber[10] = { 0 }; //Phone number will be stored here. Each digit's valid range is any non-negative number.
   std::string name;            //Name in the entry.
   char input;                  //Used for processing the file, what file.get() reads in to.
   int progress = 0;            //Progress in adding. Valid range is any non-negative number.


   //If no argument was given.
   if (argv[1] == nullptr) {
      std::cout << "No arguments.\n";
      return 0;
   }

   //Open the file for read.
   file.open(argv[1]);

   //If file is open.
   if(file) {
      while(file.get(input)) {

         //Handle the phone number component.
         if(std::isdigit(input)) {

            //Convert to the number expressed as a char, not its ascii value.
            phoneNumber[progress] = (int)input - 48; //The 48 compensates for the conversion to ascii, 0 starts at 48.
            progress++;
         }

         //Handles the name component.
         if(std::isalpha(input)) {
            name += input;
         }

         //End of entry.
         if(input == '\n') {
            //hashByNumber.AddUsingNumber(name, phoneNumber); //Commented out because of program specifications.
            //hashByName.AddUsingName(name, phoneNumber);     //Commented out because of program specifications.
            hashByNameAndNumber.AddUsingNameAndNumber(name, phoneNumber);
            name.clear();
            progress = 0;
         }
      }
   }
   //std::cout << "Hashing using Number:\n" << hashByNumber << std::endl; //Commented out because of program specifications.
   //std::cout << "Hashing using Name:\n" << hashByName << std::endl;     //Commented out because of program specifications.
   std::cout << "Hashing using Name and Number:\n" << hashByNameAndNumber << std::endl;
   return 0;
}
