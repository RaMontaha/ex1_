#include <stdlib.h>
#include "RLEList.h"

#define ONE 1
#define ZERO 0
struct RLEList_t {
    char character;
    int count;
    struct RLEList_t *next;
};

//implement the functions here

static int RLEListNodesCount(RLEList list) {
    int counter = 0;
    //first node is for helping only
    RLEList tmp = list->next;
    while (tmp) {
        counter++;
        tmp = tmp->next;
    }
    return counter;
}

static int numOfDigitsInAllNodes(RLEList list) {

    int counter = 0;
//first node is for helping only
    RLEList tmp = list->next;
    while (tmp) {
        int tmpCounter = tmp->count;
        while (tmpCounter != 0) {
            counter++;
            tmpCounter = tmpCounter / 10;
        }
        tmp = tmp->next;
    }
    return counter;
}

RLEList RLEListCreate() {
    RLEList newList = malloc(sizeof(*newList));
    if (!newList) {
        return NULL;
    }
// first node is for help only
    newList->character = '\0';
    newList->next = NULL;
    newList->count = ZERO;
    return newList;
}


void RLEListDestroy(RLEList list) {
    if (list) {
        RLEList destroyList = list;
        while (destroyList) {
            list = list->next;
            free(destroyList);
            destroyList = list;
        }
    }

}


RLEListResult RLEListAppend(RLEList list, char value) {
    if (!list || !value) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tmp = list;
    while (tmp->next) {
        tmp = tmp->next;
    }
    if (tmp->character == value) {
        (tmp->count)++;
        return RLE_LIST_SUCCESS;
    }
    //else the last character is different
    RLEList newList = malloc(sizeof(*newList));
    if (!newList) {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newList->character = value;
    newList->count = ONE;
    tmp = list;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = newList;
    return RLE_LIST_SUCCESS;

}


int RLEListSize(RLEList list) {
    if (list == NULL
        || list->next==NULL) {
        return -1;
    }
    int counter = 0;
//first node is for helping only
    RLEList tmp = list->next;
    while (tmp) {
        counter += tmp->count;
        tmp = tmp->next;
    }
    return counter;
}


RLEListResult RLEListRemove(RLEList list, int index) {
    if (list == NULL
        || list->next==NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index < 0) {
        return RLE_LIST_ERROR;
    }
    RLEList currentNode = list->next;
    RLEList prevNode = list;
    int indexOfNode = 0;
    int counter = 1;
    while (currentNode) {
        if (counter == currentNode->count) {
            if (index == indexOfNode) {
                if(prevNode->character == currentNode->next->character
                   && currentNode->next
                   && currentNode->next->next ){
                    prevNode->next=currentNode->next->next;
                    prevNode->count+= currentNode->next->count;
                    free(currentNode->next);
                }
                else{
                    prevNode->next = currentNode->next;
                }
                free(currentNode);
                return RLE_LIST_SUCCESS;
            }
            prevNode = prevNode->next;
            currentNode = currentNode->next;
            counter = 1;
            indexOfNode++;
        } else {
            if (indexOfNode == index) {
                currentNode->count--;
                return RLE_LIST_SUCCESS;

            }
            counter++;
            indexOfNode++;
        }
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}


char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (list == NULL
        || list->next==NULL) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;

        }
        return 0;
    }
    if (index < 0) {
        return RLE_LIST_ERROR;
    }
    //the first node is for helping only
    RLEList tmp = list->next;
    int indexOfNode = 0, counter = 0;
    while (tmp != NULL) {
        if (index == indexOfNode) {
            if (result) {
                *result = RLE_LIST_SUCCESS;

            }
            return tmp->character;
        }
        indexOfNode++;
        counter++;
        if (counter == tmp->count) {
            tmp = tmp->next;
            counter = 0;
        }

    }
    if (result) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return 0;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if (list == NULL
        || list->next==NULL
        || map_function == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    //first node is for helping only
    RLEList tmp = list->next;
    while (tmp) {
        tmp->character = map_function(tmp->character);
        tmp = tmp->next;
    }
    return RLE_LIST_SUCCESS;
}


char *RLEListExportToString(RLEList list, RLEListResult *result) {
    if (list == NULL
        || list->next==NULL) {
        if (result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    RLEList tmp = list->next;
    int nodesCounter = RLEListNodesCount(list), lineLen;
    int allNumbersLength = numOfDigitsInAllNodes(list);
    char *out = malloc(sizeof(*out) * nodesCounter * 3 + allNumbersLength + 1);
    char *output = out;
    while (tmp) {
        lineLen = sprintf(output, "%c%d\n", tmp->character, tmp->count);
        output += lineLen;
        tmp = tmp->next;
    }
    if (result) {
        *result = RLE_LIST_SUCCESS;
    }
    return out;
}