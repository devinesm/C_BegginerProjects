#include <stdio.h>

int main(void)
{
    printf("----------------------------------------\n");
    printf("       Welcome to Unit Converter\n");
    printf("----------------------------------------\n");

    int choice;

    while (1)
    {
        printf("Please select a conversion type:\n");
        printf("1. Temperature (Celsius <-> Fahrenheit)\n");
        printf("2. Length (Meters <-> Centimeters)\n");
        printf("3. Currency (Dollar <-> Rupees)\n");
        printf("4. Weight (Kilograms <-> Pounds)\n");
        printf("5. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%i", &choice);

        switch (choice)
        {
            case 1:
            {
                int schoice;
                float temp, ctemp;
                printf("You selected: Temperature Conversion\n");
                printf("Convert\n");
                printf("1. Celsius to Fahrenheit\n");
                printf("2. Fahrenheit to Celsius\n");
                printf("\nEnter your choice: ");
                scanf("%i", &schoice);

                switch (schoice)
                {
                    case 1:
                        printf("Enter temperature in Celsius: ");
                        scanf("%f", &temp);
                        ctemp = (temp * 1.8) + 32;
                        printf("Result: %.2f°C = %.2f°F\n", temp, ctemp);
                        break;

                    case 2:
                        printf("Enter temperature in Fahrenheit: ");
                        scanf("%f", &temp);
                        ctemp = (temp - 32) / 1.8;
                        printf("Result: %.2f°F = %.2f°C\n", temp, ctemp);
                        break;

                    default:
                        printf("Error: Invalid choice.\n");
                        break;
                }
                break;
            }

            case 2:
            {
                int schoice;
                float len, clen;

                printf("You selected: Length Conversion\n");
                printf("Convert:\n");
                printf("1. Meters to Centimeters\n");
                printf("2. Centimeters to Meters\n");
                printf("\nEnter your choice: ");
                scanf("%i", &schoice);

                switch (schoice)
                {
                    case 1:
                        printf("Enter length in Meters: ");
                        scanf("%f", &len);
                        clen = len * 100;
                        printf("Result: %.2f m = %.2f cm\n", len, clen);
                        break;

                    case 2:
                        printf("Enter length in Centimeters: ");
                        scanf("%f", &len);
                        clen = len / 100;
                        printf("Result: %.2f cm = %.2f m\n", len, clen);
                        break;

                    default:
                        printf("Error: Invalid choice.\n");
                        break;
                }
                break;
            }

            case 3:
            {
                int schoice;
                float dollar, rupees;

                printf("You selected: Currency Conversion\n");
                printf("Convert:\n");
                printf("1. Dollar to Rupees\n");
                printf("2. Rupees to Dollar\n");
                printf("\nEnter your choice: ");
                scanf("%i", &schoice);

                switch (schoice)
                {
                    case 1:
                        printf("Enter amount in Dollars: ");
                        scanf("%f", &dollar);
                        rupees = dollar * 83;
                        printf("Result: $%.2f = ₹%.2f\n", dollar, rupees);
                        break;

                    case 2:
                        printf("Enter amount in Rupees: ");
                        scanf("%f", &rupees);
                        dollar = rupees / 83;
                        printf("Result: ₹%.2f = $%.2f\n", rupees, dollar);
                        break;

                    default:
                        printf("Error: Invalid choice.\n");
                        break;
                }
                printf("(Note: Conversion rate used: 1 USD = 83.00 INR)\n");
                break;
            }

            case 4:
            {
                int schoice;
                float kg, pounds;

                printf("You selected: Weight Conversion\n");
                printf("Convert:\n");
                printf("1. Kilograms to Pounds\n");
                printf("2. Pounds to Kilograms\n");
                printf("\nEnter your choice: ");
                scanf("%i", &schoice);

                switch (schoice)
                {
                    case 1:
                        printf("Enter amount in Kilograms: ");
                        scanf("%f", &kg);
                        pounds = kg * 2.20462;
                        printf("Result: %.2f kg = %.2f lbs\n", kg, pounds);
                        break;

                    case 2:
                        printf("Enter amount in Pounds: ");
                        scanf("%f", &pounds);
                        kg = pounds / 2.20462;
                        printf("Result: %.2f lbs = %.2f kg\n", pounds, kg);
                        break;

                    default:
                        printf("Error: Invalid choice.\n");
                        break;
                }
                break;
            }

            case 5:
                printf("Thank you for using Unit Converter. Goodbye!\n");
                return (0);

            default:
                printf("Error: Invalid choice.\n");
        }
    }

    return (0);
}