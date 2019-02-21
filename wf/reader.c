#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "reader.h"

typedef struct reader_data
{
    char* buffer;
    FILE* file;
}reader_data;

void read_file(reader* read, FILE* file);

char* get_word(reader* read);

void reader_destroy(reader* read);


reader* reader_init()
{
    reader* unit = (reader*)calloc(1, sizeof(reader) + sizeof(reader_data));

    reader_data* unit_data = (reader_data*)(unit + 1);

    unit_data->buffer = (char*)calloc(sizeof(char), 100);
    if(unit_data->buffer == NULL)
        return NULL;

    unit->get = get_word;
    unit->read = read_file;
    unit->destroy = reader_destroy;

    return unit;
}

void read_file(reader* read, FILE* file)
{
    reader_data* read_data = (reader_data*)(read + 1);
    read_data->file = file;
}


char* get_word(reader* read)
{
    char symbol;
    int counter = 0;

    reader_data* read_data = (reader_data*)(read + 1);

    while(isalpha(symbol = fgetc(read_data->file)) == 0)
    {
        if(symbol == EOF)
            return NULL;
    }
    read_data->buffer[counter++] = symbol;

    while(isalpha(symbol = fgetc(read_data->file)) != 0)
    {
        read_data->buffer[counter++] = symbol;
    }
    read_data->buffer[counter] = '\0';
    return read_data->buffer;
}

void reader_destroy(reader* read)
{
    reader_data* read_data = (reader_data*)(read + 1);

    free(read_data->buffer);
    free(read);
}