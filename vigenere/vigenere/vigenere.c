//
//  vigenere.c
//
//
//  Created by Carolina Santos on 2/24/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Constants
#define CHAR_ARRAY_LENGTH 512

int main(int argc, const char * argv[]) {
    // Initial values
    int length = 0;
    int difference = 0;
    int end = 0;
    int counter = 0;
    
    // Declarations of char arrrays to copy plain text and key
    char * plainText;
    char * key;
    
    // Allocate memory for plainText and key char array
    plainText = (char*)malloc(CHAR_ARRAY_LENGTH * sizeof(char));
    key = (char*)malloc(CHAR_ARRAY_LENGTH * sizeof(char));
    
    // Read key text file
    FILE *keyFile = fopen(argv[1], "r");
    
    fprintf(stdout, "\n\n");
    
    // Print key text
    fprintf(stdout, "Vigenere Key:\n\n");
    while(!feof(keyFile)) {
        char temp;
        // Checks that length is not equal CHAR_ARRAY_LENGTH
        if(length != CHAR_ARRAY_LENGTH) {
            temp = fgetc(keyFile);
            // Checks if character is a letter
            if(isalpha(temp)) {
                key[length] = tolower(temp);
                fprintf(stdout, "%c", tolower(temp));
                length++;
                counter++;
            }
            if (counter % 80 == 0 && counter != 0) {
                fprintf(stdout, "\n");
            }
        // Otherwise temporarily store remaining characters
        } else {
            temp = fgetc(keyFile);
        }
    }
    
    // Close key text file
    fclose(keyFile);
    
    // Marks the end of the array
    end = length;
    
    // Calculates the remaining space in the key array
    difference = CHAR_ARRAY_LENGTH - end;
    
    // Replicates key until reaches CHAR_ARRAY_LENGTH
    for (int j = 0; j < difference; j++) {
        key[end + j] = key[j];
    }

    fprintf(stdout, "\n\n");
    
    // Reset counter and length variables
    counter = 0;
    length = 0;
    
    // Read plain text file
    FILE *plainFile = fopen(argv[2], "r");
    
    // Read file and copy into the plainText until the end of the file
    while(!feof(plainFile)) {
        char temp;
        // Checks that length is not equal CHAR_ARRAY_LENGTH
        if(length != CHAR_ARRAY_LENGTH) {
            temp = fgetc(plainFile);
            // Checks if character is a letter and increments length
            if(isalpha(temp)) {
                // Converts all letters to lowercase
                plainText[length] = tolower(temp);
                length++;
            }
        }
        // Otherwise temporarily store remaining characters
        else {
            temp = fgetc(plainFile);
        }
    }
    
    // Closes file
    fclose(plainFile);
    
    // Marks the end of the array
    end = length;
    
    // Calculates the remaining space in the plainText array
    difference = CHAR_ARRAY_LENGTH - end;
    
    // Assigns padding in the plainText array as x's
    for(int i = 0 ; i < difference; i++) {
        plainText[length + i] = 'x';
    }
    
    // Print plain text
    fprintf(stdout, "\nPlaintext:\n\n");
    for (int i = 0; i < CHAR_ARRAY_LENGTH ; i++) {
        fprintf(stdout, "%c", plainText[i]);
        counter++;
        if (counter % 80 == 0) {
            fprintf(stdout, "\n");
        }
    }

    // Reset counter
    counter = 0;
    
    fprintf(stdout, "\n\n");
    
    // Print cipher text
    fprintf(stdout, "\nCiphertext:\n\n");
    for (int i = 0; i < CHAR_ARRAY_LENGTH ; i++) {
        char cipher;
        cipher = (char)(plainText[i] + key[i] - 2 * 'a') % 26 + 'a';
        fprintf(stdout, "%c", cipher);
        counter++;
        if (counter % 80 == 0) {
            fprintf(stdout, "\n");
        }
    }
    printf( "\n");
}
