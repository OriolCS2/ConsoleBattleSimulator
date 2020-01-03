#include <iostream>

enum State {
	IA,
	PLAYER,
	EXIT,
	INIT,
};

int main()
{
	printf("-----------------------------------------------------------------------\n");
	printf("--------------------Welcome to the Battle Simulator--------------------\n");
	printf("-----------------------------------------------------------------------\n\n");
	printf(" What do you want to do?\n\n");

	// first menu inputs
	printf(" 1- IA vs IA (1)\n");
	printf(" 2- Player vs IA (2)\n");
	printf(" 3- Exit (3)\n");

	State state = INIT;

	while (state != EXIT) {
		char intro_input = getchar();

		switch (intro_input) {
		case '1': {
			state = IA;
			break; }
		case '2': {
			state = PLAYER;
			break; }
		case '3': {
			state = EXIT;
			break; }
		case '\n': {
			break; }
		default: {
			printf(" Choose a valid input, %c is not valid\n", intro_input);
			printf(" 1- IA vs IA (1)\n");
			printf(" 2- Player vs IA (2)\n");
			printf(" 3- Exit (3)\n");
			break; }
		}

	}
}
