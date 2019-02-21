#ifndef WF_DICT_H
#define WF_DICT_H

#include "word.h"
typedef struct dict
{
    int (*add)(char* word, struct dict* dictionary);

    int (*print)(struct dict* dictionary);

    void (*destroy)(struct dict* dictionary);
}dict;

dict* dictionary();



#endif //WF_DICT_H
