//
// Created by montaha rayyan on 5/6/22.
//

#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "tool/AsciiArtTool.h"

//used in comparing between strings
#define EQUAL 0

//map_space_character defines
#define SPACE ' '
#define AT '@'


typedef enum {
    FLAG = 1, SRC = 2, TARGET = 3
} ASCII_ART_FILE;


#define ENCODED_FLAG "-e"
#define INVERTED_FLAG "-i"

/**
 * mapSpaceCharacter: converts the space character to at sign '@'.
 *
 * @param character  the character which needs to be converted
 * @return
 * returns at sign '@' if the character is space character ,else returns the same character.
 */
char mapSpaceCharacter(char character) {
    if (character == SPACE) {
        return AT;
    }
    return character;
}


/**
 * asciiToolArt: prints the image depending on the given flag:
 *              if flag = ENCODED_FLAG(see define) prints the image in the RLE format.
 *              if flag = INVERTED_FLAG(see define) prints inverted image after calling mapSpaceCharacter function.
 *              else, error: the flag is incorrect.
 *
 * @param flag- defines what action to take on the image.
 * @param source- input file contains ASCII ART image.
 * @param target- output file to which the inverted/compressed image will be written.
 * @return
 *          RLE_LIST_NULL_ARGUMENT if one of the arguments is NULL or one of the helper function failed.
 *          RLE_LIST_SUCCESS if the the image printed in the output file successfully.
 *          RLE_LIST_ERROR if the given flag is incorrect.
 */
RLEListResult asciiArtTool(char *flag, FILE *source, FILE *target) {
    if (!source || !target) {
        PRINT_ERROR("Error:null argument");
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList list = asciiArtRead(source);
    RLEListResult result;

    if (strcmp(flag, ENCODED_FLAG) == EQUAL) {

        result = asciiArtPrintEncoded(list, target);

    } else if (strcmp(flag, INVERTED_FLAG) == EQUAL) {
        RLEListMap(list, mapSpaceCharacter);
        result = asciiArtPrint(list, target);

    } else {
        PRINT_ERROR("Incorrect flag");
        result = RLE_LIST_ERROR;
    }

    RLEListDestroy(list);
    return result;
}


/**
 * initInputFile: opens the given file to read only.
 *
 * @param argv- arguments vector.
 */
FILE *initInputFile(char **argv) {
    return fopen(argv[SRC], "r");
}

/**
 * initOutputFile: opens the given file to write only.
 *
 * @param argv- arguments vector
 */
FILE *initOutputFile(char **argv) {

    return fopen(argv[TARGET], "w");
}


int main(int argc, char **argv) {
    if (argc != 4) {
        PRINT_ERROR("Incorrect number of arguments");
        return 0;
    }

    //open files
    FILE *source = initInputFile(argv);
    if (!source) {
        PRINT_FILE_ERROR("Error: cannot open ", argv[SRC]);
        return 0;
    }

    FILE *target = initOutputFile(argv);
    if (!target) {
        PRINT_FILE_ERROR("Error: cannot open ", argv[TARGET]);
        return 0;
    }

    //asciiToolArt
    RLEListResult result = asciiArtTool(argv[FLAG],source,target);
    if(result!=RLE_LIST_SUCCESS)
    {
        PRINT_ERROR("asciiArtTool function failed");
        return 0;
    }

    //close files
    if (source != stdin) {
        fclose(source);
    }
    if (target != stdout) {
        fclose(target);
    }


    return 0;
}