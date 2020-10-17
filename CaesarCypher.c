#include <stdio.h>
#include <stdlib.h>

char* inputString(FILE* fp, size_t size) {

    char* str;
    int ch;
    size_t len = 0;

    str = (char *) malloc(sizeof(char) * size);

    if (!str) {
        return str;
    }

    while (EOF != (ch = fgetc(fp)) && ch != '\n') {

        str[len++] = ch;

        if (len == size) {

            str = realloc(str, sizeof(char) * (size += 10));

            if (!str) {
                return str;
            }
        }
    }

    str[len++] = '\0';

    return realloc(str, sizeof(char) * len);
}

char* encode(char* input, int shiftSize) {

    char result[sizeof(input)];

    for (int i = 0; input[i] != '\0'; i++) {

        if (input[i] >= 'a' && input[i] <= 'z') {

            result[i] = input[i] + shiftSize;

            if (input[i] > 'z') {

                result[i] = input[i] - 'z' - 1 + 'a';
            }
        }


        else if (input[i] >= 'A' && input[i] <= 'X') {

            result[i] = input[i] + shiftSize;

            if (input[i] > 'Z') {

                result[i] = input[i] - 'Z' - 1 + 'A';
            }
        }
    }

    printf("resulting string: %s\n", result);

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

       char choice;

       char shift;

       int shiftSize;

       printf("Please enter 1 to 'encode' some text, and 2 to 'decode' some text:\n\n");

       choice = getchar();

       fflush(stdin);

       choice -= '0';

       printf("Please enter shift size:\n\n");

       shift = getchar();

      fflush(stdin);

       shift -= '0';

       if (choice == 1) {

           printf("Please enter the message to encode:\n\n");

           input = inputString(stdin, 10);

           encode(input, shift);
       }

       else {

           printf("Please enter the message to decode:\n\n");

           input = inputString(stdin, 10);

           decode(input);
       }
   }

   return 0;
}
