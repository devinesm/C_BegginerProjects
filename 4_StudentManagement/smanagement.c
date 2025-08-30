#include <stdio.h>
#include <string.h>

#define STUDENT_NAME_LENGTH 70
#define STUDENT_COURSE_LENGTH 70
#define ROLL_NUMBER 7

typedef struct
{
    char name[STUDENT_NAME_LENGTH];
    char rollnumber[ROLL_NUMBER];
    int age;
    char course[STUDENT_COURSE_LENGTH];
} Student;

void add_new_student(void);
void search_student(const char *roll_search);
void update_student(const char *roll_search);
void delete_student(const char *roll_search);
void show_all_students(void);

int main(void)
{
    int choice;
    char roll_search[ROLL_NUMBER];

    while (1)
    {
        printf("---------------------------------------------------\n");
        printf("|      Student Record Management System           |\n");
        printf("---------------------------------------------------\n");
        printf("1. Add New Student\n");
        printf("2. Search Student by Roll Number\n");
        printf("3. Update Student Information\n");
        printf("4. Delete Student\n");
        printf("5. Show All Students\n");
        printf("6. Exit\n");
        printf("---------------------------------------------------\n");
        printf("Please choose an option: ");
        scanf("%i", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                add_new_student();
                break;
            case 2:
                printf("Enter Roll Number to Search: ");
                fgets(roll_search, ROLL_NUMBER, stdin);
                roll_search[strcspn(roll_search, "\n")] = '\0';
                search_student(roll_search);
                break;
            case 3:
                printf("Enter Roll Number of the Student to Update: ");
                fgets(roll_search, ROLL_NUMBER, stdin);
                roll_search[strcspn(roll_search, "\n")] = '\0';
                update_student(roll_search);
                break;
            case 4:
                printf("Enter Roll Number of the Student to Delete: ");
                fgets(roll_search, ROLL_NUMBER, stdin);
                roll_search[strcspn(roll_search, "\n")] = '\0';
                delete_student(roll_search);
                break;
            case 5:
                show_all_students();
                break;
            case 6:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Error: Invalid choice\n");
                break;
        }
    }
    return 0;
}

void add_new_student(void)
{
    Student new_student;
    FILE *file = fopen("students.txt", "r+");

    if (file == NULL)
    {
        printf("Error: Cannot open file to read\n");
        return;
    }

    int student_exists = 0;
    char student_in_file[ROLL_NUMBER];

    printf("Add New Student\n");

    while (1)
    {
        printf("Enter Student's Roll Number: ");
        fgets(new_student.rollnumber, ROLL_NUMBER, stdin);
        new_student.rollnumber[strcspn(new_student.rollnumber, "\n")] = '\0';

        student_exists = 0;
        rewind(file);
        while (fscanf(file, "%s %s %i %s", student_in_file, new_student.name, &new_student.age, new_student.course) != EOF)
        {
            if (strcmp(student_in_file, new_student.rollnumber) == 0)
            {
                printf("Student already registered\n");
                student_exists = 1;
                break;
            }
        }

        if (!student_exists)
        {
            break;
        }
    }

    printf("Enter Student's Name: ");
    fgets(new_student.name, STUDENT_NAME_LENGTH, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = '\0';

    printf("Enter Student's Age: ");
    while (scanf("%i", &new_student.age) != 1)
    {
        printf("Invalid input. Please enter a valid age: ");
        while (getchar() != '\n');
    }
    getchar();

    printf("Enter Student's Course: ");
    fgets(new_student.course, STUDENT_COURSE_LENGTH, stdin);
    new_student.course[strcspn(new_student.course, "\n")] = '\0';

    FILE *file_append = fopen("students.txt", "a");
    if (file_append == NULL)
    {
        printf("Error: Cannot open file to create student.\n");
        return;
    }

    fprintf(file_append, "%s %s %i %s\n", new_student.rollnumber, new_student.name, new_student.age, new_student.course);
    fclose(file_append);

    printf("Student Added Successfully!\n");
}

void search_student(const char *roll_search)
{
    Student student_info;
    FILE *file = fopen("students.txt", "r");

    if (file == NULL)
    {
        printf("Error: No students found.\n");
        return;
    }

    int found = 0;
    while (fscanf(file, "%s %s %i %s", student_info.rollnumber, student_info.name, &student_info.age, student_info.course) != EOF)
    {
        if (strcmp(student_info.rollnumber, roll_search) == 0)
        {
            printf("Roll Number: %s\n", student_info.rollnumber);
            printf("Name: %s\n", student_info.name);
            printf("Age: %i\n", student_info.age);
            printf("Course: %s\n", student_info.course);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No student found with Roll Number %s.\n", roll_search);
    }

    fclose(file);
}

void update_student(const char *roll_search)
{
    int choice;
    Student user_student;
    FILE *file = fopen("students.txt", "r+");
    FILE *temp_file = fopen("temp.txt", "w");

    if (file == NULL || temp_file == NULL)
    {
        printf("Error: Cannot open files.\n");
        return;
    }

    int found = 0;

    while (fscanf(file, "%s %s %i %s", user_student.rollnumber, user_student.name, &user_student.age, user_student.course) != EOF)
    {
        if (strcmp(user_student.rollnumber, roll_search) == 0)
        {
            printf("Student Found! Choose the field to update:\n");
            printf("1. Name\n2. Age\n3. Course\n");
            printf("Enter your choice: ");
            scanf("%i", &choice);
            getchar();

            if (choice == 1)
            {
                printf("Enter the new Name: ");
                fgets(user_student.name, STUDENT_NAME_LENGTH, stdin);
                user_student.name[strcspn(user_student.name, "\n")] = '\0';
            }
            else if (choice == 2)
            {
                printf("Enter the new Age: ");
                scanf("%i", &user_student.age);
                getchar();
            }
            else if (choice == 3)
            {
                printf("Enter the new Course: ");
                fgets(user_student.course, STUDENT_COURSE_LENGTH, stdin);
                user_student.course[strcspn(user_student.course, "\n")] = '\0';
            }
            else
            {
                printf("Error: Invalid choice.\n");
                return;
            }

            found = 1;
        }

        fprintf(temp_file, "%s %s %i %s\n", user_student.rollnumber, user_student.name, user_student.age, user_student.course);
    }

    if (!found)
    {
        printf("Student with Roll Number %s not found.\n", roll_search);
    }
    else
    {
        printf("Information updated successfully!\n");
    }

    fclose(file);
    fclose(temp_file);

    remove("students.txt");
    rename("temp.txt", "students.txt");
}

void delete_student(const char *roll_search)
{
    Student user_student;
    FILE *file = fopen("students.txt", "r");
    FILE *temp_file = fopen("temp.txt", "w");

    if (file == NULL || temp_file == NULL)
    {
        printf("Error: Cannot open files.\n");
        return;
    }

    int found = 0;

    while (fscanf(file, "%s %s %i %s", user_student.rollnumber, user_student.name, &user_student.age, user_student.course) != EOF)
    {
        if (strcmp(user_student.rollnumber, roll_search) != 0)
        {
            fprintf(temp_file, "%s %s %i %s\n", user_student.rollnumber, user_student.name, user_student.age, user_student.course);
        }
        else
        {
            found = 1;
        }
    }

    if (!found)
    {
        printf("Student with Roll Number %s not found.\n", roll_search);
    }

    fclose(file);
    fclose(temp_file);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
    {
        printf("Student deleted successfully!\n");
    }
}

void show_all_students(void)
{
    Student student_info;
    FILE *file = fopen("students.txt", "r");

    if (file == NULL)
    {
        printf("Error: No students found.\n");
        return;
    }

    printf("List of All Students:\n");
    while (fscanf(file, "%s %s %i %s", student_info.rollnumber, student_info.name, &student_info.age, student_info.course) != EOF)
    {
        printf("Roll Number: %s\n", student_info.rollnumber);
        printf("Name: %s\n", student_info.name);
        printf("Age: %i\n", student_info.age);
        printf("Course: %s\n", student_info.course);
        printf("---------------------------------\n");
    }

    fclose(file);
}