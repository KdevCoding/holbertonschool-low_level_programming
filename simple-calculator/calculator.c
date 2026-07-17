#include <stdio.h>

/** main - a basic calculator
 *
 *
 *
 */

int main(void)
{
	int active;
	int input;
	int Ain;
	int Bin;
	int result;

	active = 1;
	input = 5;
	Ain = 1;
	Bin = 1;
	result = 0;

	while (active)
	{
		printf("\n-----------\n"
				"1) Add\n"
				"2) Subtract\n"
				"3) Multiply\n"
				"4) Divide\n"
				"0) Quit\n"
				"Choice: ");
		scanf("%d", &input);

		if (input == 0)
		{
			printf("Bye!\n");
			return (1);
		}
		else if (input > 4)
			printf("Invalid choice\n");
		else if (input == 1)
		{
			printf("A: ");
			scanf("%d", &Ain);
			printf("B: ");
			scanf("%d", &Bin);
			result = (Ain + Bin);
			printf("\n###########\n"
				"Result: %d\n"
				"###########\n", result);

		}
		else if (input == 2)
		{
			printf("A: ");
			scanf("%d", &Ain);
			printf("B: ");
			scanf("%d", &Bin);
			result = (Ain - Bin);
			printf("\n###########\n"
				"Result: %d\n"
				"###########\n", result);

		}
	}
	return (1);
}
