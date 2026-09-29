#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "hash_table_iterator.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

/// @brief Process a single word, updating its frequency
/// @param word the word to process
/// @param ht a hash table containing the frequencies of the words found so far
void process_word(char *word, ioopm_hash_table_t *ht)
{
    elem_t result = int_elem(0);

    ioopm_hash_table_lookup(ht, string_elem(word), &result);

    if (result.i == 0)
    {
        ioopm_hash_table_insert(ht, string_elem(strdup(word)), int_elem(1));
    }
    else
    {
        ioopm_hash_table_insert(ht, string_elem(word), int_elem(result.i + 1));
    }
}

/// @brief Process a single file, updating the frequencies of its words
/// @param filename the name of the file to process
/// @param ht a hash table containing the frequencies of the words found so far
void process_file(char *filename, ioopm_hash_table_t *ht)
{
    FILE *f = fopen(filename, "r");
    while (true)
    {
        char *buf = NULL;
        size_t len = 0;
        getline(&buf, &len, f);

        for (char *word = strtok(buf, Delimiters);
             word && *word;
             word = strtok(NULL, Delimiters))
        {
            process_word(word, ht);
        }

        free(buf);

        if (feof(f))
        {
            break;
        }
    }

    fclose(f);
}

/// @brief A word together with its frequency
struct freq_word
{
    char *word;
    int freq;
};

/// @brief Compare the frequency of two freq_words through pointers to them
/// @param p1 the first freq_word
/// @param p2 the second freq_word
/// @return a number @n@:
/// @n@ > 0 if @p1@'s frequency is higher than @p2@'s
/// @n@ < 0 if @p1@'s frequency is lower than @p2@'s
/// @n@ == 0 if @p1@'s frequency is equal to @p2@'s
static int cmp_freq_words(const void *p1, const void *p2)
{
    const struct freq_word *w1 = p1;
    const struct freq_word *w2 = p2;
    return w1->freq - w2->freq;
}

/// @brief Like @cmp_freq_words@ but with the comparison result reversed
static int cmp_freq_words_reverse(const void *p1, const void *p2)
{
    return -cmp_freq_words(p1, p2);
}

/// @brief Sort an array of @freq_word@s in descending frequency order
/// @param words the array to be sorted
/// @param no_words the number of elements in the array
void sort_freq_words(struct freq_word words[], int no_words)
{
    qsort(words, no_words, sizeof(struct freq_word), cmp_freq_words_reverse);
}

/// @brief Creates a hash from a string
size_t string_knr_hash(elem_t str)
{
    size_t result = 0;
    while (*str.s != '\0')
    {
        result = result * 31 + ((unsigned char)*str.s);
        str.s++;
    }
    return result;
}

/// @brief Compares two strings
bool string_compare(elem_t str1, elem_t str2)
{
    return strcmp(str1.s, str2.s) == 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s file1 ... filen\n", argv[0]);
        return 1;
    }
    ioopm_hash_table_t *ht = ioopm_hash_table_create(string_knr_hash, string_compare);
    for (int i = 1; i < argc; ++i)
    {
        process_file(argv[i], ht);
    }
    int size = ioopm_hash_table_size(ht);
    struct freq_word freq_words[size];

    ioopm_hash_table_iterator_t *it;
    int i = 0;

    for (
        it = ioopm_hash_table_iterator_create(ht);
        !ioopm_hash_table_iterator_at_end(it);
        ioopm_hash_table_iterator_advance(it))
    {
        struct freq_word word =
            {
                .word = ioopm_hash_table_iterator_current_key(it).s,
                .freq = ioopm_hash_table_iterator_current_value(it).i};

        freq_words[i] = word;

        i++;
    }

    ioopm_hash_table_iterator_destroy(it);

    sort_freq_words(freq_words, size);

    for (int i = 0; i < size; ++i)
    {
        printf("%s: %d\n", freq_words[i].word, freq_words[i].freq);

        free(freq_words[i].word);
    }

    ioopm_hash_table_destroy(ht);
}
