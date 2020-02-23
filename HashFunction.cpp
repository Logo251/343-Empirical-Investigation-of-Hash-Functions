/*

*/

#include "Hash.h"    //My hash function.
#include <iostream>  //Used to display hash information
#include <string>    //Used to store the name in the entries.
#include <fstream>   //Used to read from file.


int main(int argc, char** argv) {

   //Local Variables
   Hash hashByNumber;        //This will be hashing using the number.
   Hash hashByName;        //This will be hashing using the name.
   Hash hashByNameAndNumber;      //This will be hashing using both name and number.
   std::fstream file;   //This is for reading from the file.
   int phoneNumber[10] = { 0 }; //Phone number will be stored here.
   std::string name;    //Name in the entry.
   char input;          //Used for processing the file, what file.get() reads in to.
   int progress = 0;    //Progress in adding.


   //If no argument was given.
   if (argv[1] == nullptr) {
      std::cout << "No arguments.\n";
      return 0;
   }

   //Open the file for read.
   file.open(argv[1]);

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
            hashByNumber.AddUsingNumber(name, phoneNumber);
            hashByName.AddUsingName(name, phoneNumber);
            hashByNameAndNumber.AddUsingNameAndNumber(name, phoneNumber);
            name.clear();
            progress = 0;
         }
      }
   }
   std::cout << "Hashing using Number:\n" << hashByNumber << std::endl;
   std::cout << "Hashing using Name:\n" << hashByName << std::endl;
   std::cout << "Hashing using Name and Number:\n" << hashByNameAndNumber << std::endl;
   return 0;
}
