#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/utils.h"
#include "db.h"

answer_t convert_string(char *str)
{
    return (answer_t){.string_value = strdup(str)};
}

bool check_func(char *answer, char *accepted_answers)
{
    return strlen(answer) == 1 && strchr(accepted_answers, answer[0]) != NULL;
}

bool always_true(char *answer)
{
    (void)answer;
    return true;
}

char ask_question_action_code(char *question, char *accepted_answers)
{
    char *response;

    do
    {
        response = ask_question_string(question);
    } while (!check_func(response, accepted_answers));

    char code = response[0];
    free(response);
    return code;
}

void add_merch(ioopm_db_t *db)
{
    char *name = ask_question_string("Enter the name of the new merchandise: ");
    char *description = ask_question_string("Enter the description: ");
    int price = ask_question_int("Enter the price: ");

    while (!ioopm_add_merch(db, name, description, price))
    {
        puts("Could not add merchandise, please try again.");
        name = ask_question_string("Enter the name of the new merchandise: ");
        description = ask_question_string("Enter the description: ");
        price = ask_question_int("Enter the price: ");
    }

    free(name);
    free(description);
}

void list_merch(ioopm_db_t *db)
{
    size_t i = 0;
    char result[255 * 20];
    while (ioopm_list_merch(db, result, i))
    {
        printf("%s", result);
        if (!ioopm_list_merch(db, result, i + 1))
        {
            return;
        }
        char *answer = ask_question("Enter [N] to exit.", always_true, convert_string).string_value;
        if (answer[0] == 'N' || answer[0] == 'n')
        {
            return;
        }
        i++;
    }
    puts("All items displayed.");
}

void remove_merch(ioopm_db_t *db)
{
    char *name = ask_question_string("Enter the name of the merchandise to remove: ");
    char *answer = ask_question_string("Enter [Y] to continue.");
    bool remove = answer[0] == 'Y' || answer[0] == 'y';

    while (remove && !ioopm_remove_merch(db, name))
    {
        puts("Could not remove merchandise, please try again.");
        name = ask_question_string("Enter the name of the merchandise to remove: ");
        answer = ask_question_string("Enter [Y] to continue.");
        remove = answer[0] == 'Y' || answer[0] == 'y';
    }

    free(name);
    free(answer);
}

void edit_merch(ioopm_db_t *db)
{
    char *old_name = ask_question_string("Enter the old name of the merchandise to edit: ");
    char *new_name = ask_question_string("Enter the new name of the merchandise: ");
    char *new_desc = ask_question_string("Enter the new description of the merchandise: ");
    int new_price = ask_question_int("Enter the new price of the merchandise: ");
    char *answer = ask_question_string("Enter [Y] to continue.");
    bool edit = answer[0] == 'Y' || answer[0] == 'y';

    while (edit && !ioopm_edit_merch(db, old_name, new_name, new_desc, new_price))
    {
        old_name = ask_question_string("Enter the old name of the merchandise to edit: ");
        new_name = ask_question_string("Enter the new name of the merchandise: ");
        new_desc = ask_question_string("Enter the new description of the merchandise: ");
        new_price = ask_question_int("Enter the new price of the merchandise: ");
        answer = ask_question_string("Enter [Y] to continue.");
        edit = answer[0] == 'Y' || answer[0] == 'y';
    }

    free(old_name);
    free(new_name);
    free(new_desc);
    free(answer);
}

void show_stock(ioopm_db_t *db)
{
    char result[255 * 20];

    char *name = ask_question_string("Enter the name of the merchandise: ");

    while (!ioopm_show_stock(db, result, name))
    {
        puts("Could not show stock, please try again");
        name = ask_question_string("Enter the name of the merchandise: ");
    }

    free(name);

    printf("%s", result);
}

void replenish(ioopm_db_t *db)
{
    char *location = ask_question_string("Enter the shelf to replenish: ");
    char *name = ask_question_string("Enter the merchandise to replenish: ");
    int amount = ask_question_int("Enter how much to add");
    while (!ioopm_replenish(db, name, location, amount))
    {
        puts("Could not replenish, please try again.");
        location = ask_question_string("Enter the shelf to replenish: ");
        name = ask_question_string("Enter the merchandise to replenish: ");
        amount = ask_question_int("Enter how much to add: ");
    }

    free(location);
    free(name);
}

void create_cart(ioopm_db_t *db)
{
    size_t id = ioopm_create_cart(db);
    printf("New cart created with ID: %d\n", (int)id);
}

void remove_cart(ioopm_db_t *db)
{
    size_t id = (size_t)ask_question_int("Enter the id of the cart you want to remove: ");
    char *answer = ask_question_string("Enter [Y] if you want to continue.");
    bool remove = answer[0] == 'Y' || answer[0] == 'y';

    while (remove && !ioopm_remove_cart(db, id))
    {
        id = (size_t)ask_question_int("Enter the id of the cart you want to remove: ");
        answer = ask_question_string("Enter [Y] if you want to continue.");
        remove = answer[0] == 'Y' || answer[0] == 'y';
    }

    free(answer);
}

void add_to_cart(ioopm_db_t *db)
{
    size_t id = (size_t)ask_question_int("Enter the ID of the cart: ");
    char *name = ask_question_string("Enter the item you want to add to the cart: ");
    int amount = ask_question_int("Enter the amount you want to add: ");

    while (!ioopm_add_to_cart(db, id, name, amount))
    {
        puts("Could not add to cart, please try again.");
        id = (size_t)ask_question_int("Enter the ID of the cart:");
        name = ask_question_string("Enter the item you want to add to the cart: ");
        amount = ask_question_int("Enter the amount you want to add: ");
    }

    free(name);
}

void remove_from_cart(ioopm_db_t *db)
{
    size_t id = (size_t)ask_question_int("Enter the ID of the cart: ");
    char *name = ask_question_string("Enter the item you want to remove from the cart: ");
    int amount = ask_question_int("Enter the amount you want to remove: ");

    while (!ioopm_remove_from_cart(db, id, name, amount))
    {
        puts("Could not remove from cart, please try again.");
        id = (size_t)ask_question_int("Enter the ID of the cart:");
        name = ask_question_string("Enter the item you want to remove from the cart: ");
        amount = ask_question_int("Enter the amount you want to remove: ");
    }

    free(name);
}

void calculate_cost(ioopm_db_t *db)
{
    size_t id = (size_t)ask_question_int("Enter the ID of the cart: ");

    int result = 0;

    while (!ioopm_cart_calculate_cost(db, id, &result))
    {
        puts("Could not calculate cost, please try again.");
        id = (size_t)ask_question_int("Enter the ID of the cart:");
    }

    printf("Total cost: %d SEK\n", result);
}

void checkout(ioopm_db_t *db)
{
    size_t id = (size_t)ask_question_int("Enter the ID of the cart: ");

    while (!ioopm_checkout(db, id))
    {
        puts("Could not checkout, please try again.");
        id = (size_t)ask_question_int("Enter the ID of the cart:");
    }
}

int main(void)
{
    ioopm_db_t *db = ioopm_create_db();

    while (true)
    {
        puts("Please choose one of the following actions:");
        puts("[A]: Add merchandise");
        puts("[L]: List merchandise");
        puts("[D]: Remove merchandise");
        puts("[E]: Edit merchandise");
        puts("[S]: Show stock");
        puts("[P]: Replenish");
        puts("[C]: Create cart");
        puts("[R]: Remove cart");
        puts("[+]: Add to cart");
        puts("[-]: remove from cart");
        puts("[=]: Calculate cost");
        puts("[O]: Checkout");
        puts("[Q]: Quit");

        char answer = ask_question_action_code("Enter the action code: ", "ALDESPCR+-=OQ");

        if (answer == 'A')
        {
            add_merch(db);
        }
        else if (answer == 'L')
        {
            list_merch(db);
        }
        else if (answer == 'D')
        {
            remove_merch(db);
        }
        else if (answer == 'E')
        {
            edit_merch(db);
        }
        else if (answer == 'S')
        {
            show_stock(db);
        }
        else if (answer == 'P')
        {
            replenish(db);
        }
        else if (answer == 'C')
        {
            create_cart(db);
        }
        else if (answer == 'R')
        {
            remove_cart(db);
        }
        else if (answer == '+')
        {
            add_to_cart(db);
        }
        else if (answer == '-')
        {
            remove_from_cart(db);
        }
        else if (answer == '=')
        {
            calculate_cost(db);
        }
        else if (answer == 'O')
        {
            checkout(db);
        }
        else if (answer == 'Q')
        {
            char *quit = ask_question_string("Enter [Y] to quit.");
            if (quit[0] == 'Y' || quit[0] == 'y')
            {
                free(quit);
                ioopm_delete_db(db);
                return 0;
            }
            free(quit);
        }
    }
}