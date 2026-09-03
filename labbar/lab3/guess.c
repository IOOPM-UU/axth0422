#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main()
{
    char *name = ask_question_string("Skriv in ditt namn:");
    printf("Du %s, jag tänker på ett tal. Kan du gissa vilket?\n", name);

    int random_int = random() % 1024;

    int guess;

    for (int guesses = 1; guesses <= 15; guesses++)
    {
        guess = ask_question_int("Gissa på ett nummer:");

        if (guess == random_int)
        {
            printf("Bingo!\nDet tog %s %d gissningar att komma fram till %d\n", name, guesses, random_int);
            return 0;
        }

        if (guess > random_int)
        {
            printf("För stort!\n");
        }
        else
        {
            printf("För litet\n");
        }
    }

    printf("Nu har du slut på gissningar! Jag tänkte på %d!\n", random_int);

    return 0;
}   