#include <iostream>

enum State {
	IA,
	PLAYER,
	EXIT,
	INIT,
};
State state = INIT;

class Character {

public:
	Character(int basic_attack, int defense, int live, int mana, int magic_attack, int magic_defense, int speed, const char* name)
		: basic_attack(basic_attack), defense(defense), live(live), mana(mana), magic_attack(magic_attack), 
		magic_defense(magic_defense), speed(speed), name(name) {}

	bool IsAlive() {
		return live > 0;
	}
	static Character* CompareSpeed(Character* c1, Character* c2) {
		return (c1->speed >= c2->speed) ? c1 : c2;
	}
	const char* GetName() {
		return name.data();
	}
	void PrintStats() {
		printf(" ---------------%s Stats---------------\n", name.data());
		printf(" ---------------%s Stats---------------\n\n", name.data());
	}

private:

	int basic_attack = 0;
	int defense = 0;
	int live = 0;
	int mana = 0;
	int magic_attack = 0;
	int magic_defense = 0;
	int speed = 0;

	std::string name;
};

void BattleIA()
{

}

void BattlePlayer()
{
	system("cls");
	printf("-----------------------------------------------------------------------\n");
	printf("----------------------------Player vs IA-------------------------------\n");
	printf("-----------------------------------------------------------------------\n\n");

	Character player(10, 5, 100, 60, 8, 4, 10, "Player");
	Character enemy(10, 5, 100, 60, 8, 4, 8, "Enemy");
	Character* active = Character::CompareSpeed(&player, &enemy);

	int round = 1;

	player.PrintStats();
	enemy.PrintStats();
	
	while (player.IsAlive() && enemy.IsAlive()) {
		char intro_input = getchar();
		printf("ROUND NUMEBER %i\n", round);
		printf("%s turn\n", active->GetName());
	}


	// TOOD: return to main menu
}

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

	while (state != EXIT) {
		char intro_input = getchar();
		switch (intro_input) {
		case '1': {
			state = IA;
			BattleIA();
			break; }
		case '2': {
			state = PLAYER;
			BattlePlayer();
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