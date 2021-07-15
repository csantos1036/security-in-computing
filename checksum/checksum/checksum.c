/*=============================================================================
| Assignment: HW 02 – Calculating the 8, 16, or 32 bit checksum for a
| given input file
|
| Author: Carolina Santos
| Language: c
|
| To Compile: gcc checksum.c
|
| To Execute: ./a.out textfile.txt checksum_size
| where the files in the command line are in the current directory.
|
| The text file contains text is mixed case with spaces, punctuation,
| and is terminated by the hexadecimal ‘0A’, inclusive.
| (The 0x’0A’ is included in the checksum calculation.)
|
| The checksum_size contains digit(s) expressing the checksum size
| of either 8, 16, or 32 bits
 |
| Class: CIS3360 - Security in Computing – Spring 2021
| Instructor: McAlpin
| Due Date: 04/18/21
|
+=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Constants
#define CHAR_ARRAY_LENGTH 512

int main(int argc, char **argv) {
    // Initial variables
    int counter = 0;
    int checkSumSize = atoi(argv[2]);
    int characterCount = 0;
    long int checksum = 0;
    int padding = 0;
    
    // Check to make sure input is a valid value
    if (checkSumSize == 8 || checkSumSize == 16 || checkSumSize == 32) {
        // Declare and initilize a char array to store input
        char * input = (char*)malloc(CHAR_ARRAY_LENGTH * sizeof(char));
        
        // Open input file
        FILE *inputFile = fopen(argv[1], "r");
        
        // Store every character in input array
        while(!feof(inputFile)) {
            input[counter] = fgetc(inputFile);
            counter++;
        }
        
        // Number of characters in input file
        characterCount = counter - 1;
        
        
        // Close file
        fclose(inputFile);
        
        // Add padding if needed
        if (checkSumSize == 16) {
            padding = characterCount % 2;
            while (padding != 0) {
                input[counter - 1] = 'X';
                counter++;
                padding--;
            }
        }
        else if (checkSumSize == 32) {
            int remainder = 0;
            remainder = characterCount % 4;
            padding = 4 - remainder;
            while (padding != 0) {
                input[counter - 1] = 'X';
                counter++;
                padding--;
            }
        }
        
        // Number of characters
        characterCount = counter - 1;
        
        
        printf("\n");
        // Echo the input file
        for(int i = 0; i < counter - 1; i++) {
            if (i % 80 == 0 && i != 0) {
                printf("\n");
            }
            printf("%c", input[i]);
        }
        printf("\n");
        
        // Calculate checksum
        if (checkSumSize == 8) {
            for(int i = 0; i < counter - 1; i++) {
                checksum += input[i];
            }
            checksum = (uint8_t)checksum;
        }
        else if (checkSumSize == 16) {
            for(int i = 0; i < counter - 1; i += 2) {
                checksum += (input[i] << 8) + (input[i + 1] & 0x0000FFFF);
            }
            
            checksum = (uint16_t)checksum;
        }
        else if (checkSumSize == 32) {
            for(int i = 0; i < counter - 1; i += 4) {
                checksum += (input[i] << 24) + (input[i + 1] << 16) + (input[i + 2] << 8) + (input[i + 3] & 0x0000FFFF);
            }
            checksum = (uint32_t)checksum;
        }
          
        // Print the checksum
        printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCount);
    }
    else {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
    }
}

/*=============================================================================
| I, Carolina Santos (4680884), affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
