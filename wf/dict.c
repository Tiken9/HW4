#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dict.h"

typedef struct
{
    int count;
    unit** smth;
}dict_data;

int add_word(char* word, dict* dictionary);

int print_dictionary(dict* dictionary);

void dict_destroy(dict* dictionary);


dict* dictionary()
{
    dict* buffer = (dict*)calloc(sizeof(dict) + sizeof(dict_data), 1);
    if(buffer == NULL)
        return NULL;

    dict_data* buffer_data = (dict_data*)(buffer + 1);

    buffer_data->smth = (unit**)calloc(sizeof(unit*), 100);
    if(buffer_data->smth == NULL)
        return NULL;

    buffer->destroy = dict_destroy;
    buffer->print = print_dictionary;
    buffer->add = add_word;
    return buffer;
}

int add_word(char* word, dict* dictionary)
{
    dict_data* dictionary_data = (dict_data*)(dictionary + 1);

    for(int i = 0; i < dictionary_data->count; i++)
    {
        if(dictionary_data->smth[i]->compare(dictionary_data->smth[i], word) == 0)
        {
            dictionary_data->smth[i]->fix(dictionary_data->smth[i]);
            return 0;
        }
    }

    unit* unit = init_word(word);
    unit->fix(unit);
    dictionary_data->smth[dictionary_data->count++] = unit;
    return 0;
}

int print_dictionary(dict* dictionary)
{
    dict_data* dictionary_data = (dict_data*)(dictionary + 1);

    for(int i = 0; i < dictionary_data->count; i++)
        dictionary_data->smth[i]->print(dictionary_data->smth[i]);
    return 0;
}

void dict_destroy(dict* dictionary)
{
    dict_data* dictionary_data = (dict_data*)(dictionary + 1);

    for(int i = 0; i < dictionary_data->count; i++)
    {
        dictionary_data->smth[i]->destroy(dictionary_data->smth[i]);
        free(dictionary_data->smth[i]);
    }

    free(dictionary_data->smth);
    free(dictionary);
}