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

	active = 1;

	while (active)
	{
		printf("-----------\n"
			"1) Add\n"
			"2) Subtract\n"
			"3) Multiply\n"
			"4) Divide\n"
			"0) Quit\n");
		scanf("%d", &input);

		if (input == 0)
		{
			printf("Bye!\n");
			return (1);
		}
		else if (input > 4)
			printf("Invalid choice\n");

	}
	return (1);
}
