#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *inputString(FILE *fp, size_t size) {

    char *str;
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

char *concat(const char *s1, const char *s2) {

    char *result = malloc(strlen(s1) + strlen(s2) + 1);

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

char *encode(char *input, int shiftSize) {

    char *result = (char *) malloc(sizeof(input));

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

    return result;
}

char *decode(char *input, int shiftSize) {

    char *result = (char *) malloc(sizeof(input));

    for (int i = 0; input[i] != '\0'; i++) {

        if (input[i] >= 'a' && input[i] <= 'z') {

            result[i] = input[i] - shiftSize;

            if (input[i] > 'z') {

                result[i] = input[i] + 'z' + 1 - 'a';
            }
        }

        else if (input[i] >= 'A' && input[i] <= 'X') {

            result[i] = input[i] - shiftSize;

            if (input[i] > 'Z') {

                result[i] = input[i] + 'Z' + 1 - 'A';
            }
        }
    }

    return result;
}

int main(int argc, char *argv[]) {

    if (argc == 2) {

        FILE *infile;
        FILE *outfile;
        char choice;
        int shift;
        char *buffer;
        long numbytes;
        char *result;

        infile = fopen(argv[1], "r");

        if (infile == NULL) {

            printf("unable to open file\n");
            return 1;
        }

        printf("\nPlease enter 1 to 'encode' the file, and 2 to 'decode' the file: ");

        choice = getchar();

        fflush(stdin);

        choice -= '0';

        printf("\nPlease enter shift size: ");

        scanf("%d", &shift);

        fflush(stdin);

        if (choice == 1) {

            fseek(infile, 0L, SEEK_END);
            numbytes = ftell(infile);

            fseek(infile, 0L, SEEK_SET);

            buffer = (char *) malloc(numbytes * sizeof(char));

            if(buffer == NULL) {

                return 1;
            }

            fread(buffer, sizeof(char), numbytes, infile);
            fclose(infile);

            result = encode(buffer, shift);

            char *outfileName;

            outfileName = concat(argv[1], "-output");

            outfile = fopen(outfileName, "w");

            fprintf(outfile, "%s", result);

            fclose(outfile);
            free(outfileName);
            free(buffer);
        }

        else {

            fseek(infile, 0L, SEEK_END);
            numbytes = ftell(infile);

            fseek(infile, 0L, SEEK_SET);

            buffer = (char *) malloc(numbytes * sizeof(char));

            if(buffer == NULL) {

                return 1;
            }

            fread(buffer, sizeof(char), numbytes, infile);
            fclose(infile);

            result = decode(buffer, shift);

            char *outfileName;

            outfileName = concat(argv[1], "-output");

            outfile = fopen(outfileName, "w");

            fprintf(outfile, "%s", result);

            fclose(outfile);
            free(outfileName);
            free(buffer);
        }
   }

   else if (argc > 2) {

       printf("Too many arguments supplied.\n");
   }

   else {

       char *input;
       char choice;
       int shift;
       char *result;

       printf("\nPlease enter 1 to 'encode' some text, and 2 to 'decode' some text: ");

       choice = getchar();

       fflush(stdin);

       choice -= '0';

       printf("\nPlease enter shift size: ");

       scanf("%d", &shift);

       fflush(stdin);

       if (choice == 1) {

           printf("\nPlease enter the message to encode: ");

           input = inputString(stdin, 10);

           result = encode(input, shift);

           printf("\nEncoded string: %s\n", result);
       }

       else {

           printf("\nPlease enter the message to decode: ");

           input = inputString(stdin, 10);

           result = decode(input, shift);

           printf("\nDecoded string: %s\n", result);
       }
   }

   return 0;
}
