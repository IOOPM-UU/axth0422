#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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
    if (item->price % 100 < 10)
    {
        printf("Price: %d.0%d SEK\n", item->price / 100, item->price % 100);
    }
    else
    {
        printf("Price: %d.%d SEK\n", item->price / 100, item->price % 100);
    }
    printf("Shelf: %s\n", item->shelf);
}

item_t make_item(char *name, char *desc, int price, char *shelf)
{
    item_t item = {.name = name, .desc = desc, .price = price, .shelf = shelf};
    return item;
}

bool is_shelf(char *str)
{
    int length = strlen(str);
    if (length < 2)
    {
        return false;
    }

    if (str[0] < 65 || str[0] > 122 || (str[0] < 97 && str[0] > 90))
    {
        return false;
    }

    for (int i = 1; i < length; i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

char *ask_question_shelf(char *question)
{
    return ask_question(question, is_shelf, (convert_func_t *)strdup).string_value;
}

item_t input_item()
{
    char *name = ask_question_string("Skriv in produktens namn:");
    char *desc = ask_question_string("Skriv en beskrivning till produkten:");
    int price = ask_question_int("Skriv in produktens pris, angivet i öre:");
    char *shelf = ask_question_shelf("Skriv in produktens hylla:");

    return make_item(name, desc, price, shelf);
}

char *magick(char *array1[], char *array2[], char *array3[], int array_length)
{
    char buf[255];
    int index = 0;

    int random_index = random() % array_length;
    char *random_word = array1[random_index];
    size_t random_word_length = strlen(random_word);

    for (size_t i = 0; i < random_word_length; i++, index++)
    {
        buf[index] = random_word[i];
    }

    buf[index] = '-';
    index++;

    random_index = random() % array_length;
    random_word = array2[random_index];
    random_word_length = strlen(random_word);

    for (size_t i = 0; i < random_word_length; i++, index++)
    {
        buf[index] = random_word[i];
    }

    buf[index] = '-';
    index++;

    random_index = random() % array_length;
    random_word = array3[random_index];
    random_word_length = strlen(random_word);

    for (size_t i = 0; i < random_word_length; i++, index++)
    {
        buf[index] = random_word[i];
    }

    buf[index] = '\0';    

    return strdup(buf);
}

void list_db(item_t *items, int no_items)
{
    for (int i = 0; i < no_items; i++)
    {
        printf("%d. %s\n", i + 1, items[i].name);
    }
}

void edit_db(item_t *items, int no_items)
{
    list_db(items, no_items);

    int item_index;

    do
    {
        item_index = ask_question_int("För att redigera, ge siffran som motsvarar varans position i listan, eller skriv -1 för att avsluta:") - 1;

        if (item_index == -2)
        {
            return;
        }
    }
    while (item_index < 0 || item_index >= no_items);

    print_item(&items[item_index]);

    puts("Ange varans nya information");

    item_t item = input_item();

    items[item_index] = item;
}

int main(int argc, char *argv[])
{
    char *array1[] = { "Night", "Devilry", "Master", "Honour", "Born" };
    char *array2[] = { "is", "of", "of", "and", "to" };
    char *array3[] = { "Calling", "Ecstasy", "Illusion", "Devotion", "Die" };

    if (argc < 2)
    {
        printf("Usage: %s number\n", argv[0]);
    }
    else
    {
        item_t db[16]; // Array med plats för 16 varor
        int db_siz = 0; // Antalet varor i arrayen just nu

        int items = atoi(argv[1]); // Antalet varor som skall skapas

        if (items > 0 && items <= 16)
        {
            for (int i = 0; i < items; ++i)
            {
                // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
                item_t item = input_item();
                db[db_siz] = item;
                ++db_siz;
            }
        }
        else
        {
            puts("Sorry, must have [1-16] items in database.");
            return 1; // Avslutar programmet!
        }

        for (int i = db_siz; i < 16; ++i)
        {
            char *name = magick(array1, array2, array3, 5); // TODO: Lägg till storlek
            char *desc = magick(array1, array2, array3, 5); // TODO: Lägg till storlek
            int price = random() % 200000;
            char shelf[] = { random() % ('Z'-'A') + 'A',
                            random() % 10 + '0',
                            random() % 10 + '0',
                            '\0' };
            item_t item = make_item(name, desc, price, strdup(shelf));

            db[db_siz] = item;
            ++db_siz;
        }

        edit_db(db, db_siz);
    }

    return 0;
}