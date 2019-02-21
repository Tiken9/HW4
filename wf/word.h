#ifndef WF_WORD_H
#define WF_WORD_H


typedef struct unit
{
    void (*fix)(struct unit* smth);
    int (*print)(struct unit* smth);
    void (*destroy)(struct unit* smth);
    int (*compare)(struct unit* smth, char* word);

}unit;

unit* init_word(char* word);



#endif //WF_WORD_H
