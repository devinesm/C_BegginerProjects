#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void create_account(void);
int login_account(char *logged_in_user);
void second_menu(const char *username);

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    double balance;
} Account;

int main(void)
{
    int choice;
    int logged_in = 0;
    char logged_in_user[MAX_USERNAME_LENGTH] = {0};

    while (1)
    {
        printf("----------------------------");
        printf("\nWelcome to Mini Bank in C!\n");
        printf("\n1. Create a new account");
        printf("\n2. Log in");
        printf("\n3. Exit Bank");
        printf("\nChoose an option: ");
        scanf("%i", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                create_account();
                break;
            
            case 2:
                logged_in = login_account(logged_in_user);
                if (logged_in)
                {
                    second_menu(logged_in_user);
                }
                break;

            case 3:
                printf("Thanks for using our bank!\n");
                return (0);

            default: 
                printf("Error: Invalid option.\n");
        }
    }
    return (0);
}

void create_account(void)
{
    Account new_account;
    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        printf("Error: Cannot open file to read.\n");
        return ;
    }

    int username_exists = 0;
    char username_in_file[MAX_USERNAME_LENGTH];
    char password_in_file[MAX_PASSWORD_LENGTH];

    printf("----------------------------\n");
    printf("Create a New Account\n");

    while (1)
    {
        printf("Enter your username: ");
        fgets(new_account.username, MAX_USERNAME_LENGTH, stdin);
        new_account.username[strcspn(new_account.username, "\n")] = '\0';

        username_exists = 0;
        while (fscanf(file, "%s %s %lf", username_in_file, password_in_file, &new_account.balance) != EOF)
        {
            if (strcmp(username_in_file, new_account.username) == 0)
            {
                printf("Username already exists. Please choose another username.\n");
                username_exists = 1;
                break;
            }
        }

        if (!username_exists) 
        {
            break;
        }

        rewind(file);
    }

    printf("Enter your password: ");
    fgets(new_account.password, MAX_PASSWORD_LENGTH, stdin);
    new_account.password[strcspn(new_account.password, "\n")] = '\0';

    FILE *file_append = fopen("accounts.txt", "a");
    if (file_append == NULL)
    {
        printf("Error: Cannot open file to create account.\n");
        fclose(file);
        return ;
    }

    new_account.balance = 50.0;

    fprintf(file_append, "%s %s %.2f\n", new_account.username, new_account.password, new_account.balance);
    fclose(file);
    fclose(file_append);

    printf("Account created successfully!\n");
}

int login_account(char *logged_in_user)
{
    Account user_account;
    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        printf("Error: No accounts found. Please create an account first!\n");
        return (0);
    }

    char entered_username[MAX_USERNAME_LENGTH];
    char entered_password[MAX_PASSWORD_LENGTH];
    int found = 0;

    printf("----------------------------\n");
    printf("Login\n");
    printf("Enter username: ");
    fgets(entered_username, MAX_USERNAME_LENGTH, stdin);
    entered_username[strcspn(entered_username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(entered_password, MAX_PASSWORD_LENGTH, stdin);
    entered_password[strcspn(entered_password, "\n")] = '\0';

    while (fscanf(file, "%s %s %lf", user_account.username, user_account.password, &user_account.balance) != EOF)
    {
        if (strcmp(user_account.username, entered_username) == 0 && 
            strcmp(user_account.password, entered_password) == 0)
        {
            strcpy(logged_in_user, user_account.username);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf("Login successful! Welcome to your bank.\n");
        return (1);
    }
    else
    {
        printf("Invalid username or password.\n");
        return (0);
    }
}

void second_menu(const char *username)
{
    int choice;
    Account user_account;
    FILE *file = fopen("accounts.txt", "r+");

    if (file == NULL)
    {
        printf("Error: No accounts found.\n");
        return ;
    }

    Account accounts[100];
    int account_count = 0;

    while (fscanf(file, "%s %s %lf", user_account.username, user_account.password, &user_account.balance) != EOF)
    {
        accounts[account_count++] = user_account;
    }
    
    fclose(file);

    int user_found = 0;
    for (int i = 0; i < account_count; i++)
    {
        if (strcmp(accounts[i].username, username) == 0)
        {
            user_account = accounts[i];
            user_found = 1;
            break;
        }
    }

    if (!user_found)
    {
        printf("Error: Account not found.\n");
        return ;
    }

    while (1)
    {
        printf("----------------------------\n");
        printf("\nBanking Operations");
        printf("\n1. Check Balance");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Exit Operations Menu\n");
        printf("Choose an option: ");
        scanf("%i", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                printf("Current Balance: %.2f\n", user_account.balance);
                break;

            case 2:
                {
                    double deposit;
                    printf("Enter the amount to deposit: ");
                    scanf("%lf", &deposit);

                    if (deposit > 0)
                    {
                        user_account.balance += deposit;
                        printf("Deposit of %.2f completed successfully! Your new balance is %.2f.\n", deposit, user_account.balance);
                    }
                    else
                    {
                        printf("Invalid deposit amount.\n");
                    }
                }
                break;

            case 3:
                {
                    double withdraw;
                    printf("Enter the amount to withdraw: ");
                    scanf("%lf", &withdraw);

                    if (withdraw > 0 && withdraw <= user_account.balance)
                    {
                        user_account.balance -= withdraw;
                        printf("Withdrawal of %.2f completed successfully! Your new balance is %.2f.\n", withdraw, user_account.balance);
                    }
                    else
                    {
                        printf("Invalid withdrawal amount or insufficient funds.\n");
                    }
                }
                break;

            case 4:
                file = fopen("accounts.txt", "w");
                if (file == NULL)
                {
                    printf("Error: Cannot open file to save account details.\n");
                    return ;
                }

                for (int i = 0; i < account_count; i++)
                {
                    if (strcmp(accounts[i].username, username) == 0)
                    {
                        fprintf(file, "%s %s %.2f\n", accounts[i].username, accounts[i].password, user_account.balance);
                    }
                    else
                    {
                        fprintf(file, "%s %s %.2f\n", accounts[i].username, accounts[i].password, accounts[i].balance);
                    }
                }

                fclose(file);
                printf("Exiting Operations Menu.\n");
                return ;

            default:
                printf("Error: Invalid option.\n");
        }
    }
}