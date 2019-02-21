#ifndef WF_READER_H
#define WF_READER_H

#include <bits/types/FILE.h>



typedef struct reader
{
    void (*read)(struct reader* reader, FILE* file);
    char* (*get)(struct reader* reader);
    void (*destroy)(struct reader* reader);
} reader;

reader* reader_init();


#endif //WF_READER_H