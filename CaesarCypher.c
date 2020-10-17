#include <stdio.h>

char* encode(char* input) {

    return input;
};

char* decode(char* input) {

    return input;
};

int main(int argc, char *argv[]) {

    if (argc == 2) {

        // read from file here
        printf("The argument supplied is %s\n\n", argv[1]);
   }

   else if (argc > 2) {

       printf("Too many arguments supplied.\n\n");
   }

   else {

       char* input;

       int choice;

       printf("Please enter 1 to 'encode' some text, and 2 to 'decode' some text:\n\n");

       choice = getchar();

       if (choice == 1) {

           printf("Please enter the message to encode:\n\n");

           fgets(input);

           encode(input);
       }

       else {

           printf("Please enter the message to decode:\n\n");

           fgets(input);

           decode(input);
       }

       // ask for user input here
   }

    return 0;
}
