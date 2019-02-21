#include <stddef.h>
#include <stdio.h>
#include "reader.h"
#include "dict.h"

int main(int argc, char* argv[])
{

    reader* rd = reader_init();
    dict* dict = dictionary();
    char* word;

    if(argc == 1)
    {
        rd->read(rd, stdin);

        while((word = rd->get(rd)) != NULL)
            dict->add(word, dict);
    }
    else
    {
        for(int i = 1; i < argc; i++)
        {
            FILE* open_file = fopen(argv[i], "r");
            if( open_file == NULL)
            {
                perror("Can't open file\n");
                return 0;
            }

            rd->read(rd, open_file);

            while((word = rd->get(rd)) != NULL)
                dict->add(word, dict);

            fclose(open_file);
        }
    }

    dict->print(dict);

    rd->destroy(rd);
    dict->destroy(dict);
    return 0;
}