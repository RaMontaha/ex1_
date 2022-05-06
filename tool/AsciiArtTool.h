//
// Created by montaha rayyan on 5/6/22.
//

#ifndef EX1__ASCIIARTTOOL_H
#define EX1__ASCIIARTTOOL_H

#include <stdio.h>
#include <assert.h>
#include "/home/mtm/public/2122b/ex1/RLEList.h"

/**
 * The following functions are available:
 * asciiArtRead - Compresses the image in the given file using RLE method.
 * asciiArtPrint- Writes the image (represented by a list) in the given file.
 * asciiArtPrintEncoded- Writes the encoded form for the list in the given file
 */


#define PRINT_ERROR(message) printf("%s",#message)


// this macro to print an error caused by opening/closing a file
#define PRINT_FILE_ERROR(message, file_name) printf("%s %s",#message , file_name)


/**
 * asciiArtRead: Reads the image in the given file and compresses it using the RLE method.
 * note: the function prints error messages depending on the return results from the helper function.
 *
 * @param in_stream - file contains the image which needs to be compressed.
 * @return
 * A list of RLEList type that contains all the characters in the image, NULL if the function failed.
 */
RLEList asciiArtRead(FILE *in_stream);


/**
 * asciiArtPrint: writes an image represented by a list of type RLEList to a file.
 *
 * @param list -A list of the RLEList type that contains the characters in the image.
 * @param out_stream -A file to which the image will be written.
 *                      note: the given file should be opened
 * @return
  *      RLE_LIST_NULL_ARGUMENT if one of the parameters is NULL.
  *      RLE_LIST_SUCCESS if the image has been written in the given file successfully.
 */
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
 * asciiArtPrintEncoded: Writes the image to the file in an encoded form, as a string .
 *                      (for more information about encoded form see the comment of RLEListExportToString function).
 *
 * @param list -A list of the RLEList type that contains the characters in the image.
 * @param out_stream -A file to which the encoded image will be written.
 *                      note: the given file should be opened
 * @return
 *      RLE_LIST_SUCCESS if the the encoded image has been written in the given file successfully.
 *      RLE_LIST_NULL_ARGUMENT if one of the parameters is NULL or, one of the helper functions failed.
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);
#endif //EX1__ASCIIARTTOOL_H
