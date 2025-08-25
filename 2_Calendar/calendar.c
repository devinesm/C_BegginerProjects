#include <stdio.h>

int is_leap_year(int year);
int calculate_first_day(int year, int month);
void fill_calendar(int calendar[6][7], int first_day, int month_days);
void print_calendar(int calendar[6][7]);

int main(void)
{
    printf("---------------------------------\n-- Welcome to Calendar in C! --\n---------------------------------\n\n");

    int year, month, first_day;

    printf("Enter the year: ");
    scanf("%i", &year);
    printf("\nEnter the month (1 - 12): ");
    scanf("%i", &month);
    printf("\n---------------------------------\n");

    int february_days = 28;
    if (is_leap_year(year))
        february_days = 29;

    int month_days[12] = { 31, february_days, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    first_day = calculate_first_day(year, month);

    int calendar[6][7];
    fill_calendar(calendar, first_day, month_days[month - 1]);

    char *months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    printf("Month: %s | Year: %i\n", months[month - 1], year);

    print_calendar(calendar);
    return (0);
}


int is_leap_year(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return (1);
            else
                return (0);
        }
        else
            return (1);
    }
    else
        return (0);
}

int calculate_first_day(int year, int month)
{
    int k, j, f, week_day;

    if ((month == 1) || (month == 2))
    {
        month += 12;
        year -= 1;
    }
    
    k = year % 100;
    j = year / 100;

    f = 1 + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j);

    week_day = f % 7;

    week_day = (week_day + 6) % 7;

    return (week_day);
}

void fill_calendar(int calendar[6][7], int first_day, int month_days)
{
    int line, row;
    int counter = 1;

    for (line = 0; line < 6; line++)
    {
        for (row = 0; row < 7; row++)
        {
            calendar[line][row] = 0;
        }
    }

    line = 0;
    row = first_day;

    while (counter <= month_days)
    {
        calendar[line][row] = counter;
        counter++;
        row++;

        if (row == 7)
        {
            row = 0;
            line++;
        }
    }
}

void print_calendar(int calendar[6][7])
{
    int line, row;

    printf("\nSu Mo Tu We Th Fr Sa\n");
    for (line = 0; line < 6; line++)
    {
        for (row = 0; row < 7; row++)
        {
            if (calendar[line][row] != 0)
                printf("%2d ", calendar[line][row]);
            else
                printf("   ");
        }
        printf("\n");
    }
    printf("---------------------------------\n");
}