#include <iostream>
#include "BattleSimulator.h"

enum State {
	IA,
	PLAYER,
	EXIT,
	INIT,
};
State state = INIT;

class Character {

public:
	Character(int basic_attack, int defense, int live, int mana, int special_attack, int speed, const char* name, 
		int cost_mana_special_attack, int cost_mana_buff)
		: basic_attack(basic_attack), defense(defense), live(live), mana(mana), speed(speed), name(name),
		special_attack(special_attack), cost_mana_buff(cost_mana_buff), cost_mana_special_attack(cost_mana_special_attack) {}

	bool IsAlive() {
		return live > 0;
	}
	static Character* CompareSpeed(Character* c1, Character* c2) {
		return (c1->speed >= c2->speed) ? c1 : c2;
	}
	const char* GetName() {
		return name.data();
	}
	int CostBuff() {
		return cost_mana_buff;
	}
	int CostSpecialAttack() {
		return cost_mana_special_attack;
	}
	bool CanDoSpecialAttack() {
		return mana >= cost_mana_special_attack;
	}
	bool CanDoBuff() {
		return mana >= cost_mana_buff;
	}

	void PrintStats() {
		printf("---------------%s Stats---------------\n", name.data());
		printf("---------------HEALTH: %i\n", live);
		printf("---------------MANA: %i\n", mana);
		printf("---------------BASIC ATTACK DAMAGE: %i\n", basic_attack);
		printf("---------------SPECIAL ATTACK DAMAGE: %i\n", special_attack);
		printf("---------------DEFENSE: %i\n", defense);
		printf("---------------SPEED: %i\n", speed);
		printf("---------------%s Stats---------------\n\n", name.data());
	}

private:

	int basic_attack = 0;
	int special_attack = 0;
	int defense = 0;
	int live = 0;
	int mana = 0;
	int speed = 0;

	int cost_mana_special_attack = 0;
	int cost_mana_buff = 0;

	std::string name;
};

void BattleIA()
{

}

void PrintPlayerIATitle()
{
	printf("-----------------------------------------------------------------------\n");
	printf("----------------------------Player vs IA-------------------------------\n");
	printf("-----------------------------------------------------------------------\n\n");
}

void BattlePlayer()
{
	system("cls");
	PrintPlayerIATitle();

	Character player(10, 4, 100, 60, 20, 10, "Player", 15, 10);
	Character enemy(10, 4, 100, 60, 20, 10, "Enemy", 15, 10);
	Character* active = Character::CompareSpeed(&player, &enemy);

	int round = 1;

	player.PrintStats();
	enemy.PrintStats();
	
	while (player.IsAlive() && enemy.IsAlive()) {
		printf("----------------------------ROUND NUMEBER %i----------------------------\n", round);
		printf("---------------%s turn---------------\n\n", active->GetName());

		if (active == &player) {
			printf(" Choose your action:\n");
			printf("	A) Basic Attack (a)\n");
			printf("	B) Special Attack (%i mana) (b)\n", active->CostSpecialAttack());
			printf("	C) Buff Attack (%i mana) (c)\n", active->CostBuff());
			printf("	D) Buff Defense (%i mana) (d)\n", active->CostBuff());

			bool next_turn = false;
			while (!next_turn) {
				char action = getchar();
				switch (action)
				{
				case 'a': {

					break; }
				case 'b': {
					if (active->CanDoSpecialAttack()) {

					}
					else {
						printf("You don't have enough mana\n");
					}
					break; }
				case 'c': {
					if (active->CanDoBuff()) {

					}
					else {
						printf("You don't have enough mana\n");
					}
					break; }
				case 'd': {
					if (active->CanDoBuff()) {

					}
					else {
						printf("You don't have enough mana\n");
					}
					break; }
				case '\n': {
					break; }
				default: {
					printf("Choose a correct action\n");
					break; }
				}
			}
		}
		else {

		}
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