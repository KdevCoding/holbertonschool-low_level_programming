#include <stdio.h>

/** main - a basic calculator
 *
 *  The calculator uses int and no decimals, it uses def rounding of always down
 *
 */

int main(void)
{
	int active;
	int input;
	int Ain;
	int Bin;
	int result;
	int numberRead;

	active = 1;
	input = 5;
	Ain = 1;
	Bin = 1;
	result = 0;

	while (active)
	{
		numberRead = 0;

		printf("\n-----------\n"
				"1) Add\n"
				"2) Subtract\n"
				"3) Multiply\n"
				"4) Divide\n"
				"0) Quit\n"
				"Choice: ");

		if (scanf("%d", &input) != 1)
		{
			printf("!!**Invalid choice**!!");
			scanf("%*[^\n]"); /* clear scanf buffer, *: dont store, []: what to skip to */
		}
		else if (input == 0)
		{
			printf("Bye!\n");
			return (1);
		}
		else if (input > 4)
			printf("!!**Invalid choic**!!e\n");
		else if (input == 1)
		{
			printf("A: ");
			numberRead = scanf("%d", &Ain);
			while (numberRead != 1)
			{
				printf("!!**Invalid number**!!\n");
				scanf("%*[^\n]");
				printf("A: ");
				numberRead = scanf("%d", &Ain);
			}
			printf("B: ");
			numberRead = scanf("%d", &Bin);
			while (numberRead != 1)
			{
				printf("!!**Invalid number**!!\n");
				scanf("%*[^\n]");
				printf("B: ");
				numberRead = scanf("%d", &Bin);
			}
			result = (Ain + Bin);
			printf("\n###########\n"
					"Result: %d\n"
					"###########\n", result);

		}
		else if (input == 2)
		{
			printf("A: ");
			numberRead = scanf("%d", &Ain);
			while (numberRead != 1)
			{
				printf("!!**Invalid number**!!\n");
				scanf("%*[^\n]");
				printf("A: ");
				numberRead = scanf("%d", &Ain);
			}
			printf("B: ");
			numberRead = scanf("%d", &Bin);
			while (numberRead != 1)
			{
				printf("!!**Invalid number**!!\n");
				scanf("%*[^\n]");
				printf("B: ");
				numberRead = scanf("%d", &Bin);
			}
			result = (Ain - Bin);
			printf("\n###########\n"
					"Result: %d\n"
					"###########\n", result);

		}
		else if (input == 3)
		{
			printf("A: ");
			numberRead = scanf("%d", &Ain);
			while (numberRead != 1)
			{
				printf("!!**Invalid number**!!\n");
				scanf("%*[^\n]");
				printf("A: ");
				numberRead = scanf("%d", &Ain);
			}
			printf("B: ");
			numberRead = scanf("%d", &Bin);
			while (numberRead != 1)
			{
				printf("!!**Invalid number**!!\n");
				scanf("%*[^\n]");
				printf("B: ");
				numberRead = scanf("%d", &Bin);
			}

			result = (Ain * Bin);
			printf("\n###########\n"
				"Result: %d\n"
				"###########\n", result);

		}
		else if (input == 4)
		{
			printf("A: ");
			numberRead = scanf("%d", &Ain);
			while (numberRead != 1)
			{
				printf("!!**Invalid number**!!\n");
				scanf("%*[^\n]");
				printf("A: ");
				numberRead = scanf("%d", &Ain);
			}
			printf("B: ");
			numberRead = scanf("%d", &Bin);
			while (numberRead != 1)
			{
				printf("!!**Invalid number**!!\n");
				scanf("%*[^\n]");
				printf("B: ");
				numberRead = scanf("%d", &Bin);
			}
			if (Bin == 0)
			{
				printf("\n###########\n"
						"Error: division by zero\n"
						"###########\n");
			}
			else
			{
				result = (Ain / Bin);
				printf("\n###########\n"
						"Result: %d\n"
						"###########\n", result);
			}

		}
	}
	return (1);
}
