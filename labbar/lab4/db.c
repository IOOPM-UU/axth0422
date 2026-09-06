#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *strdup(const char *);

struct item
{
    char *name;
    char *desc;
    int price;
    char *shelf;
};

typedef struct item item_t;

void print_item(item_t *item)
{
    printf("Name:  %s\n", item->name);
    printf("Desc:  %s\n", item->desc);
    printf("Price: %d.%d\n", item->price / 100, item->price % 100);
    printf("Shelf: %s\n", item->shelf);
}

item_t make_item(char *name, char *desc, int price, char *shelf)
{
    item_t item = {.name = name, .desc = desc, .price = price, .shelf = shelf};
    return item;
}

char *ask_question_shelf(char *question)
{
    return ask_question(question);
}

void input_item()
{
    char *name = ask_question_string("Skriv in produktens namn:");
    char *desc = ask_question_string("Skriv en beskrivning till produkten:");
    int price = ask_question_int("Skriv in produktens pris, angivet i öre:");
}

int main(void)
{
    return 0;
}