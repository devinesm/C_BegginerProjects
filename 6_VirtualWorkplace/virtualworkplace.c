#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_TITLE_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 80
#define MAX_DATE 12

void create_new_user(void);
int user_login(char *logged_in_user);
void second_menu(const char *username);
void create_new_task(const char *username);
void view_tasks(const char *username);
void send_message(const char *sender);
void view_messages(const char *username);
int user_exists(const char *username);
void flush_input(void);

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

typedef struct
{
    char title[MAX_TITLE_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char date[MAX_DATE];
    int priority;
    char owner[MAX_USERNAME_LENGTH];
} Task;

typedef struct
{
    char sender[MAX_USERNAME_LENGTH];
    char receiver[MAX_USERNAME_LENGTH];
    char text[200];
} Message;

int main(void)
{
    int choice;
    int logged_in = 0;
    char logged_in_user[MAX_USERNAME_LENGTH] = {0};

    printf("========================================\n");
    printf("       VIRTUAL WORKPLACE SYSTEM\n");
    printf("========================================\n");

    while (1)
    {
        printf("\n1. Create new user\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%i", &choice);
        flush_input();

        switch (choice)
        {
            case 1:
                create_new_user();
                break;
            case 2:
                logged_in = user_login(logged_in_user);
                if (logged_in)
                {
                    second_menu(logged_in_user);
                }
                break;
            case 3:
                printf("Exiting program...\n");
                return (0);
            default:
                printf("Error: Invalid choice.\n");
                break;   
        }
    }
    return (0);
}

void flush_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void create_new_user(void)
{
    User new_user;
    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        file = fopen("accounts.txt", "w");
        if (file == NULL)
        {
            printf("Error: Cannot open file to create\n");
            return ;
        }
        fclose(file);
        file = fopen("accounts.txt", "r");
    }

    int username_exists = 0;
    char username_in_file[MAX_USERNAME_LENGTH];
    char password_in_file[MAX_PASSWORD_LENGTH];

    printf(">>> Create New User\n");
    while (1)
    {
        printf("Enter a username: ");
        fgets(new_user.username, MAX_USERNAME_LENGTH, stdin);
        new_user.username[strcspn(new_user.username, "\n")] = '\0';

        username_exists = 0;
        rewind(file);
        while (fscanf(file, "%s %s", username_in_file, password_in_file) != EOF)
        {
            if (strcmp(username_in_file, new_user.username) == 0)
            {
                printf("Username already exists. Please choose another username\n");
                username_exists = 1;
                break;
            }
        }

        if (!username_exists)
        {
            break;
        }
    }

    printf("Enter your password: ");
    fgets(new_user.password, MAX_PASSWORD_LENGTH, stdin);
    new_user.password[strcspn(new_user.password, "\n")] = '\0';

    FILE *file_append = fopen("accounts.txt", "a");
    if (file_append == NULL)
    {
        printf("Error: Cannot open file to create account\n");
        fclose(file);
        return ;
    }

    fprintf(file_append, "%s %s\n", new_user.username, new_user.password);
    fclose(file);
    fclose(file_append);

    printf("User created successfully!\n");
    printf("----------------------------------------\n");
}

int user_login(char *logged_in_user)
{
    User user_account;
    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        printf("Error: No accounts found. Please create an account first.\n");
        return (0);
    }

    char entered_username[MAX_USERNAME_LENGTH];
    char entered_password[MAX_PASSWORD_LENGTH];
    int found = 0;

    printf(">>> Login\n");
    printf("Username: ");
    fgets(entered_username, MAX_USERNAME_LENGTH, stdin);
    entered_username[strcspn(entered_username, "\n")] = '\0';

    printf("Password: ");
    fgets(entered_password, MAX_PASSWORD_LENGTH, stdin);
    entered_password[strcspn(entered_password, "\n")] = '\0';

    while (fscanf(file, "%s %s", user_account.username, user_account.password) != EOF)
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
        printf("Login successful! Welcome, %s\n", user_account.username);
        printf("----------------------------------------\n");
        return (1);
    }
    else
    {
        printf("Invalid username or password.\n");
        printf("----------------------------------------\n");
        return (0);
    }
}

void second_menu(const char *username)
{
    int choice;

    while (1)
    {
        printf("\nMAIN MENU\n");
        printf("1. Create new task\n");
        printf("2. View my tasks\n");
        printf("3. Send message\n");
        printf("4. View messages\n");
        printf("5. Logout\n");
        printf("\nEnter your choice: ");
        scanf("%i", &choice);
        flush_input();

        switch (choice)
        {
            case 1:
                create_new_task(username);
                break;
            case 2:
                view_tasks(username);
                break;
            case 3:
                send_message(username);
                break;
            case 4:
                view_messages(username);
                break;
            case 5:
                printf("Logging out... See you soon!\n");
                return ;
            default:
                printf("Error: Invalid choice.\n");
                break;
        }
    }
}

void create_new_task(const char *username)
{
    Task new_task;
    FILE *file = fopen("tasks.txt", "a");
    
    if (file == NULL)
    {
        printf("Error: Cannot open the file to add tasks.\n");
        return ;
    }

    printf(">>> Create New Task\n");
    printf("Task title: ");
    fgets(new_task.title, MAX_TITLE_LENGTH, stdin);
    new_task.title[strcspn(new_task.title, "\n")] = '\0';

    printf("Description: ");
    fgets(new_task.description, MAX_DESCRIPTION_LENGTH, stdin);
    new_task.description[strcspn(new_task.description, "\n")] = '\0';

    printf("Due date (DD/MM/YYYY): ");
    fgets(new_task.date, MAX_DATE, stdin);
    new_task.date[strcspn(new_task.date, "\n")] = '\0';

    printf("Priority (1 = High, 2 = Medium, 3 = Low): ");
    scanf("%i", &new_task.priority);
    flush_input();

    strcpy(new_task.owner, username);

    fprintf(file, "%s|%s|%s|%i|%s\n", new_task.title, new_task.description, new_task.date, new_task.priority, new_task.owner);
    
    printf("Task created successfully!\n");
    printf("----------------------------------------\n");

    fclose(file);
}

void view_tasks(const char *username)
{
    Task tasks_info;
    char owner[MAX_USERNAME_LENGTH];
    const char *priority[] = {"High", "Medium", "Low"};
    FILE *file = fopen("tasks.txt", "r");

    if (file == NULL)
    {
        printf("Error: No tasks found.\n");
        return ;
    }

    printf(">>> My Tasks\n\n");

    int i = 1;
    while (fscanf(file, "%49[^|]|%79[^|]|%11[^|]|%d|%49[^\n]\n",
                  tasks_info.title, tasks_info.description,
                  tasks_info.date, &tasks_info.priority, owner) == 5)
    {
        if (strcmp(owner, username) == 0)
        {
            printf("[%i] %s\n", i, tasks_info.title);
            printf("Description: %s\n", tasks_info.description);
            printf("Due date: %s\n", tasks_info.date);

            if (tasks_info.priority >= 1 && tasks_info.priority <= 3)
            {
                printf("Priority: %s\n", priority[tasks_info.priority - 1]);
            }
            else
            {
                printf("Priority: Unknown\n");
            }
            printf("----------------------------------------\n\n");
            i++;
        }
    }

    fclose(file);
}

int user_exists(const char *username)
{
    FILE *file = fopen("accounts.txt", "r");
    
    if (file == NULL)
    {
        return (0);
    }

    char entered_username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while (fscanf(file, "%s %s", entered_username, password) != EOF)
    {
        if (strcmp(username, entered_username) == 0)
        {
            fclose(file);
            return (1);
        }
    }
    fclose(file);
    return (0);
}

void send_message(const char *sender)
{
    Message message;
    FILE *file = fopen("messages.txt", "a");

    if (file == NULL)
    {
        printf("Error: Cannot open file to send message.\n");
        return ;
    }

    printf(">>> Send Message\n");
    printf("To (username): ");
    fgets(message.receiver, MAX_USERNAME_LENGTH, stdin);
    message.receiver[strcspn(message.receiver, "\n")] = '\0';

    if (!user_exists(message.receiver))
    {
        printf("Error: User '%s' does not exist.\n", message.receiver);
        fclose(file);
        return ;
    }

    strcpy(message.sender, sender);
    printf("Message text: ");
    fgets(message.text, sizeof(message.text), stdin);
    message.text[strcspn(message.text, "\n")] = '\0';

    fprintf(file, "%s|%s|%s\n", message.sender, message.receiver, message.text);
    fclose(file);

    printf("Message sent successfully!\n");
    printf("----------------------------------------\n");
}

void view_messages(const char *username)
{
    Message message;
    FILE *file = fopen("messages.txt", "r");

    if (file == NULL)
    {
        printf("No messages found.\n");
        return ;
    }

    printf(">>> Your Messages\n\n");

    int found = 0;

    while (fscanf(file, "%49[^|]|%49[^|]|%199[^\n]\n",
                  message.sender, message.receiver, message.text) == 3)
    {
        if (strcmp(message.receiver, username) == 0)
        {
            printf("From: %s\n", message.sender);
            printf("Message: %s\n", message.text);
            printf("----------------------------------------\n");
            found = 1;
        }
    }

    if (!found)
    {
        printf("No messages for you.\n");
    }

    fclose(file);
}
