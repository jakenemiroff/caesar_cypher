#include <stdio.h>
#include <stdlib.h>

char* inputString(FILE* fp, size_t size) {
//The size is extended by the input with the value of the provisional
    char* str;
    int ch;
    size_t len = 0;

    str = (char *) malloc(sizeof(char) * size);//size is start size

    if (!str) {
        return str;
    }

    while (EOF != (ch = fgetc(fp)) && ch != '\n') {

        str[len++]=ch;
        if (len==size) {
            str = realloc(str, sizeof(char)*(size+=16));

            if (!str) {
                return str;
            }
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}

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

       input = (char *) malloc(sizeof(char) * 100);

       int choice;

       printf("Please enter 1 to 'encode' some text, and 2 to 'decode' some text:\n\n");

       choice = getchar();

       fflush(stdin);

       if (choice == 1) {

           printf("Please enter the message to encode:\n\n");

           input = inputString(stdin, 10);

           encode(input);
       }

       else {

           printf("Please enter the message to decode:\n\n");

           input = inputString(stdin, 10);

           decode(input);
       }

       // ask for user input here

      free(input);
   }

   return 0;
}
