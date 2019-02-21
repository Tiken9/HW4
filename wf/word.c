#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word.h"

typedef struct
{
    char* word;
    int counter;
}unit_data;


void fix_counter(unit* smth);

int print_word(unit* smth);

void word_destroy(unit* smth);

int compare_words(struct unit* smth, char* word);



unit* init_word(char* word)
{
    unit* buffer = (unit*)calloc(sizeof(unit) + sizeof(unit_data), 1);
    if(buffer == NULL)
        return NULL;

    size_t size = strlen(word);

    unit_data* buffer_data = (unit_data*)(buffer + 1);

    buffer_data->word = (char*)calloc(sizeof(char), size);
    for(int i = 0; i < size; i++)
        buffer_data->word[i] = word[i];

    buffer->destroy = word_destroy;
    buffer->fix = fix_counter;
    buffer->print = print_word;
    buffer->compare = compare_words;

    return buffer;
}


void fix_counter(unit* smth)
{
    unit_data* smth_data = (unit_data*)(smth + 1);
    smth_data->counter++;
}

int print_word(unit* smth)
{
    unit_data* smth_data = (unit_data*)(smth + 1);
    if(printf("%s - %d\n", smth_data->word, smth_data->counter) <= 0)
        return 1;
    return 0;
}

void word_destroy(unit* smth)
{
    unit_data* smth_data = (unit_data*)(smth + 1);
    free(smth_data->word);
}

int compare_words(struct unit* smth, char* word)
{
    unit_data* smth_data = (unit_data*)(smth + 1);
    return strcmp(word, smth_data->word);
}