#include <stdio.h>

int	main(void)
{
	int a, b, choice;

	// CALCULATOR HEADER
	printf("---------------------------------\n-- Welcome to Calculator in C! --\n---------------------------------\n\n");

	// GETS THE NUMBERS
	printf("Enter the first number: ");
	scanf("%i", &a);
	printf("\n");
	printf("Enter the second number: ");
	scanf("%i", &b);

	// CHOOSES THE OPERATION
	printf("\n---------------------------------\nWhich operation you want to do?\n\n 1 - Addition\n 2 - Subtraction\n 3 - Multiplication\n 4 - Division\n---------------------------------\nChoose your option: ");
	scanf("%i", &choice);

	printf("---------------------------------\n");
	switch (choice)
	{
		case 1:
		{
			printf("Result: %d + %d = %d", a, b, (a + b));
			break;
		}
		case 2:
		{
			printf("Result: %d - %d = %d", a, b, (a - b));
			break;
		}
		case 3:
		{
			printf("Result: %d x %d = %d", a, b, (a * b));
			break;
		}
		case 4:
		{
			if (b != 0)
				printf("Result: %d / %d = %i", a, b, (a / b));
			else
			{
				printf("Divising by zero is not allowed.");
				printf("\n---------------------------------");
				return (1);
			}
			break;
		}
		default:
		{
			printf("Invalid operation! Try again.");
			printf("\n---------------------------------");
			return (2);
		}
	}
	printf("\n---------------------------------\n");
	printf("Thanks for using the calculator!\n");
	return (0);
}
