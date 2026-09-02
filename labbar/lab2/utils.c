#include <stdio.h>


int ask_question_int(char *question)
{
    int result = 0;
    int conversions = 0;
    do
    {
        printf("%s\n", question);
        conversions = scanf("%d", &result);
        int c;

        do
        {
            c = getchar();
        } while (c != '\n' && c != EOF);

        putchar('\n');
    } while (conversions < 1);

    return result;
}

char *ask_question_string(char *question)
{
    char result[255];
    do
}

int main()
{
    int tal;
    
    tal = ask_question_int("Första talet:");
    printf("Du skrev '%d'\n", tal);

    tal = ask_question_int("Andra talet:");
    printf("Du skrev '%d*\n", tal);
    return 0;
}