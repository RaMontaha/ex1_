//
// Created by montaha rayyan on 5/6/22.
//

#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE *in_stream) {
    RLEList head = RLEListCreate();
    RLEList node = head;
    char tmp_character;
    RLEListResult result;

    // read first character
    tmp_character = fgetc(in_stream);

    while (!feof(in_stream)) {
        result = RLEListAppend(node, tmp_character);
        if(tmp_character>0){
            if (result != RLE_LIST_SUCCESS) {
                PRINT_ERROR(result);
                RLEListDestroy(head);
                return NULL;
            }
            // get character from the file
            tmp_character = fgetc(in_stream);
        }

    }

    return head;

}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if (!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    // variables
    RLEListResult result;
    char tmp_character;
    int list_size = RLEListSize(list);

    for (int i = 0; i < list_size; i++) {
        tmp_character = RLEListGet(list, i, &result);

        // check if the
        if (result != RLE_LIST_SUCCESS) {
            //if it gets here the list is not NULL
            return RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        fputs(&tmp_character, out_stream);
    }

    assert(result == RLE_LIST_SUCCESS);
    return
            result;

}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    RLEListResult result = RLE_LIST_NULL_ARGUMENT;

    if (!list || !out_stream) {
        return result;
    }

    char *str = RLEListExportToString(list, &result);

    if (result != RLE_LIST_SUCCESS || !str) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    // print the encoded image in out_stream file
    fputs(str, out_stream);

    assert(result == RLE_LIST_SUCCESS);
    return result;
}

