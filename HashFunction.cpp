/*

*/

#include "Hash.h"    //My hash function.
#include <iostream>  //Used to display hash information
#include <string>    //Used to store the name in the entries.
#include <fstream>   //Used to read from file.


int main(int argc, char** argv) {

   //Local Variables
   Hash hashOne;        //This is the first hash add.
   Hash hashTwo;        //This is the second hash add.
   Hash hashThree;      //This is the third hash add.
   std::fstream file;   //This is for reading from the file.
   int phoneNumber[10]; //Phone number will be stored here.
   std::string name;    //Name in the entry.
   char input;   //Used for processing the file, what file.get() reads in to.


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
         if(std::isdigit(file.peek())) {
            for(int i = 0; i < 10; i++) {
               file.get(input);
               if(input == '-') {
                  file.get(input);
               }
               phoneNumber[i] = input;
            }
         }

         //If not phone number condition is handled above, at this point the concern
         // is if it is a space
         if(!std::isspace(input)) {
            name += input;
         }

         //End of entry.
         if(input == '\n') {
            hashOne.AddOne(name, phoneNumber);
            hashTwo.AddTwo(name, phoneNumber);
            hashThree.AddThree(name, phoneNumber);
            name.clear();
            file.get(input);
         }
      }
   }
   std::cout << hashOne << std::endl;
   std::cout << hashTwo << std::endl;
   std::cout << hashThree << std::endl;
   return 0;
}
