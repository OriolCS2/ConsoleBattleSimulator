#include <iostream>
#include <time.h>
#include "BattleSimulator.h"

enum State {
	BOSS_BOSS,
	MINION_MINION,
	BOSS_MINON,
	PLAYER_BOSS,
	PLAYER_MINION,
	EXIT,
	INIT,
};
State state = INIT;

class Character {

public:
	Character() {}
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
	void DoSpecialAttack(Character* against) {
		mana -= cost_mana_special_attack;
		if (time_buff_attack != 0) {
			against->DecreaseHealth(special_attack + buff_attack);
		}
		else {
			against->DecreaseHealth(special_attack);
		}
		printf(" %s was hitted with a special attack and has %i health\n", against->name.data(), against->GetHealth());
	}
	void DoBasicAttack(Character* against) {
		if (time_buff_attack != 0) {
			against->DecreaseHealth(basic_attack + buff_attack);
		}
		else {
			against->DecreaseHealth(basic_attack);
		}
		printf(" %s was hitted with a basic attack and has %i health\n", against->name.data(), against->GetHealth());
	}
	void DecreaseHealth(int damage) {
		if (time_buff_defense != 0) {
			if (damage > defense + buff_defense) {
				live -= abs((defense + buff_defense) - damage);
			}
		}
		else {
			if (damage > defense) {
				live -= abs(defense - damage);
			}
		}
	}
	int GetHealth() {
		return live;
	}
	int GetMana() {
		return mana;
	}
	void BuffAttack() {
		mana -= cost_mana_buff;
		time_buff_attack = buff_duration;
		printf(" %s Attack and special attack increased by %i points for %i rounds\n", name.data(), Character::buff_attack, Character::buff_duration - 1);
	}
	void BuffDefense() {
		mana -= cost_mana_buff;
		time_buff_defense = buff_duration;
		printf(" %s Defense increased by %i points for %i rounds\n", name.data(), Character::buff_defense, Character::buff_duration - 1);
	}
	void CheckBuffs() {
		if (time_buff_attack != 0) {
			--time_buff_attack;
			if (time_buff_attack == 0) {
				printf(" %s Attack has return to the normal state\n", name.data());
			}
		}
		if (time_buff_defense != 0) {
			--time_buff_defense;
			if (time_buff_defense == 0) {
				printf(" %s Defense has return to the normal state\n", name.data());
			}
		}
	}
	void DoRandomAttack(Character* against) {
		bool do_buff_attack = false;
		bool do_buff_defense = false;
		bool basic = false;
		bool special = false;
		
		if (time_buff_attack != 0 && time_buff_defense != 0) { // 2 buffs
			int r = rand() % 2;
			switch (r) {
			case 0: {
				basic = true;
				break; }
			case 1: {
				if (CanDoSpecialAttack()) {
					special = true;
				}
				else {
					basic = true;
				}
				break; }
			}
		}
		else if (time_buff_attack != 0 && time_buff_defense == 0) { // attack buff
			int r = rand() % 3;
			switch (r) {
			case 0: {
				basic = true;
				break; }
			case 1: {
				if (CanDoSpecialAttack()) {
					special = true;
				}
				else {
					basic = true;
				}
				break; }
			case 2: {
				if (CanDoBuff()) {
					do_buff_defense = true;
				}
				else {
					basic = true;
				}
				break; }
			}
		}
		else if (time_buff_attack == 0 && time_buff_defense != 0) { // defense buff
			int r = rand() % 3;
			switch (r) {
			case 0: {
				basic = true;
				break; }
			case 1: {
				if (CanDoSpecialAttack()) {
					special = true;
				}
				else {
					basic = true;
				}
				break; }
			case 2: {
				if (CanDoBuff()) {
					do_buff_attack = true;
				}
				else {
					basic = true;
				}
				break; }
			}
		}
		else { // no buff
			int r = rand() % 4;
			switch (r) {
			case 0: {
				basic = true;
				break; }
			case 1: {
				if (CanDoSpecialAttack()) {
					special = true;
				}
				else {
					basic = true;
				}
				break; }
			case 2: {
				if (CanDoBuff()) {
					do_buff_attack = true;
				}
				else {
					basic = true;
				}
				break; }
			case 3: {
				if (CanDoBuff()) {
					do_buff_defense = true;
				}
				else {
					basic = true;
				}
				break; }
			}
		}

		if (basic) {
			DoBasicAttack(against);
		}
		else if (special) {
			DoSpecialAttack(against);
		}
		else if (do_buff_attack) {
			BuffAttack();
		}
		else if (do_buff_defense) {
			BuffDefense();
		}
	}

	void PrintStats() {
		printf("---------------%s Stats---------------\n", name.data());
		printf("---------------HEALTH: %i\n", live);
		printf("---------------MANA: %i\n", mana);
		printf("---------------BASIC ATTACK DAMAGE: %i\n", (time_buff_attack == 0) ? basic_attack : basic_attack + buff_attack);
		printf("---------------SPECIAL ATTACK DAMAGE: %i\n", (time_buff_attack == 0) ? special_attack : special_attack + buff_attack);
		printf("---------------DEFENSE: %i\n", (time_buff_defense == 0) ? defense : defense + buff_defense);
		printf("---------------SPEED: %i\n", speed);
		printf("---------------%s Stats---------------\n", name.data());
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

	int time_buff_attack = 0;
	int time_buff_defense = 0;

public:

	static const int buff_attack = 5;
	static const int buff_defense = 4;
	static const int buff_duration = 4; // the turn you buff counts here too
};

void PrintMainMenu()
{
	printf("-----------------------------------------------------------------------\n");
	printf("--------------------Welcome to the Battle Simulator--------------------\n");
	printf("-----------------------------------------------------------------------\n\n");
	printf(" What do you want to do?\n\n");

	// first menu inputs
	printf(" 1- Boss vs Boss (1)\n");
	printf(" 2- Boss vs Minion (2)\n");
	printf(" 3- Minion vs Minion (3)\n");
	printf(" 4- Player vs Minion (4)\n");
	printf(" 5- Player vs Boss (5)\n");
	printf(" 6- Simulate 100 Boss vs Boss (6)\n");
	printf(" 7- Simulate 100 Boss vs Minion (7)\n");
	printf(" 8- Simulate 100 Minion vs Minion (8)\n");
	printf(" 9- Exit (9)\n");
	printf("\n");
}

void BattleIAx100()
{
	int total_win_1 = 0;
	int total_win_2 = 0;

	Character enemy1, enemy2;

	for (int i = 0; i < 100; ++i) {
		switch (state) {
		case BOSS_BOSS: {
			enemy1 = { 12, 7, 120, 100, 30, 11, "Boss1", 20, 10 };
			enemy2 = { 12, 7, 120, 100, 30, 11, "Boss2", 20, 10 };
			break; }
		case BOSS_MINON: {
			enemy1 = { 12, 7, 120, 60, 30, 11, "Boss", 20, 10 };
			enemy2 = { 9, 3, 50, 45, 12, 6, "Minion", 15, 15 };
			break; }
		case MINION_MINION: {
			enemy1 = { 9, 3, 50, 45, 12, 6, "Minion1", 15, 15 };
			enemy2 = { 9, 3, 50, 45, 12, 6, "Minion2", 15, 15 };
			break; }
		default: {
			break; }
		}

		Character* active = Character::CompareSpeed(&enemy1, &enemy2);

		int turn = 0;
		bool round_finished = true;
		int round = 1;
		while (enemy1.IsAlive() && enemy2.IsAlive()) {
			if (round_finished) {
				printf("----------------------------ROUND NUMBER %i----------------------------\n", round);
				round_finished = false;
			}
			printf("---------------%s turn---------------\n\n", active->GetName());

			if (active == &enemy1) {
				++turn;
				active->DoRandomAttack(&enemy2);
				active = &enemy2;
			}
			else {
				++turn;
				active->DoRandomAttack(&enemy1);
				active = &enemy1;
			}
			printf("\n");
			if (turn == 2) {
				++round;
				turn = 0;
				round_finished = true;
			}
		}

		if (enemy1.IsAlive()) {
			printf(" \n%s won the battle\n", enemy1.GetName());
			++total_win_1;
		}
		else {
			printf(" \n%s won the battle\n", enemy2.GetName());
			++total_win_2;
		}
		if (i != 99) {
			printf(" \nNEXT BATTLE!!\n");
		}
	}
	printf("\n---------------100 simulations finished---------------\n");
	printf("---------%s won: %i\n", enemy1.GetName(), total_win_1);
	printf("---------%s won: %i\n", enemy2.GetName(), total_win_2);
	printf(" \nClick enter to return main menu\n");
	getchar();
	getchar();
	state = INIT;
	system("cls");

	PrintMainMenu();
}

void BattleIA()
{
	Character enemy1, enemy2;
	switch (state) {
	case BOSS_BOSS: {
		enemy1 = { 12, 7, 120, 100, 30, 11, "Boss1", 20, 10 };
		enemy2 = { 12, 7, 120, 100, 30, 11, "Boss2", 20, 10 };
		break; }
	case BOSS_MINON: {
		enemy1 = { 12, 7, 120, 60, 30, 11, "Boss", 20, 10 };
		enemy2 = { 9, 3, 50, 45, 12, 6, "Minion", 15, 15 };
		break; }
	case MINION_MINION: {
		enemy1 = { 9, 3, 50, 45, 12, 6, "Minion1", 15, 15 };
		enemy2 = { 9, 3, 50, 45, 12, 6, "Minion2", 15, 15 };
		break; }
	default: {
		break; }
	}
	Character* active = Character::CompareSpeed(&enemy1, &enemy2);

	int turn = 0;
	bool round_finished = true;
	int round = 1;
	while (enemy1.IsAlive() && enemy2.IsAlive()) {
		if (round_finished) {
			printf("----------------------------ROUND NUMBER %i----------------------------\n", round);
			round_finished = false;
		}
		printf("---------------%s turn---------------\n\n", active->GetName());

		if (active == &enemy1) {
			++turn;
			active->DoRandomAttack(&enemy2);
			active = &enemy2;
		}
		else {
			++turn;
			active->DoRandomAttack(&enemy1);
			active = &enemy1;
		}
		printf("\n");
		if (turn == 2) {
			++round;
			turn = 0;
			round_finished = true;
		}
	}

	if (enemy1.IsAlive()) {
		printf(" \n%s won the battle\n", enemy1.GetName());
	}
	else {
		printf(" \n%s won the battle\n", enemy2.GetName());
	}
	printf(" \nClick enter to return main menu\n");
	getchar();
	getchar();
	state = INIT;
	system("cls");

	PrintMainMenu();
}

void BattlePlayer()
{
	system("cls");
	printf("-----------------------------------------------------------------------\n");
	printf("----------------------------Player vs IA-------------------------------\n");
	printf("-----------------------------------------------------------------------\n\n");

	Character player(14, 6, 100, 90, 20, 10, "Player", 15, 10);
	Character enemy;

	switch (state) {
	case PLAYER_BOSS: {
		enemy = { 12, 7, 120, 60, 30, 11, "Boss", 20, 10 };
		break; }
	case PLAYER_MINION: {
		enemy = { 9, 3, 50, 45, 12, 6, "Minion", 15, 15 };
		break; }
	default: {
		break; }
	}

	Character* active = Character::CompareSpeed(&player, &enemy);

	int round = 1;

	player.PrintStats();
	printf("\n");
	enemy.PrintStats();
	printf("\n");
	printf(" Press Enter to start the battle\n");
	getchar();
	getchar();
	system("cls");

	int turn = 0;
	bool round_finished = true;
	while (player.IsAlive() && enemy.IsAlive()) {
		if (round_finished) {
			printf("----------------------------ROUND NUMBER %i----------------------------\n", round);
			round_finished = false;
		}
		printf("---------------%s turn---------------\n\n", active->GetName());

		if (active == &player) {
			++turn;
			printf("--------Current Health: %i\n", player.GetHealth());
			printf("--------Current Mana: %i\n", player.GetMana());
			printf("--------Enemy Health: %i\n\n", enemy.GetHealth());

			printf(" Choose your action:\n");
			printf("	A) Basic Attack (a)\n");
			printf("	B) Special Attack (%i mana) (b)\n", active->CostSpecialAttack());
			printf("	C) Buff Attack (%i mana) (c)\n", active->CostBuff());
			printf("	D) Buff Defense (%i mana) (d)\n", active->CostBuff());
			printf("	E) See Player Stats (e)\n");
			printf("	F) See Enemy Stats (f)\n");

			bool next_turn = false;
			while (!next_turn) {
				char action = getchar();
				printf("\n");
				switch (action)
				{
				case 'a': {
					active->DoBasicAttack(&enemy);
					next_turn = true;
					active = &enemy;
					break; }
				case 'b': {
					if (active->CanDoSpecialAttack()) {
						active->DoSpecialAttack(&enemy);
						next_turn = true;
						active = &enemy;
					}
					else {
						printf(" You don't have enough mana\n");
					}
					break; }
				case 'c': {
					if (active->CanDoBuff()) {
						active->BuffAttack();
						next_turn = true;
						active = &enemy;
					}
					else {
						printf(" You don't have enough mana\n");
					}
					break; }
				case 'd': {
					if (active->CanDoBuff()) {
						active->BuffDefense();
						next_turn = true;
						active = &enemy;
					}
					else {
						printf(" You don't have enough mana\n");
					}
					break; }
				case 'e': {
					player.PrintStats();
					break; }
				case 'f': {
					enemy.PrintStats();
					break; }
				case '\n': {
					break; }
				default: {
					printf(" Choose a correct action\n");
					break; }
				}
			}
			player.CheckBuffs();
			printf("\n----------------------------------------\n");
			if (enemy.IsAlive()) {
				printf("\n Press Enter to finish turn\n");
				getchar();
				getchar();
			}
		}
		else {
			++turn;
			active->DoRandomAttack(&player);
			enemy.CheckBuffs();
			printf("\n----------------------------------------\n");
			if (player.IsAlive()) {
				printf("\n Press Enter to start your turn\n");
				getchar();
			}
			active = &player;
		}
		if (turn == 2) {
			++round;
			turn = 0;
			round_finished = true;
		}
	}
	if (enemy.IsAlive()) {
		printf(" \n%s won the battle :(\n", enemy.GetName());
	}
	else {
		printf(" \n%s won the battle :)\n", player.GetName());
	}
	printf(" \nClick enter to return main menu\n");
	getchar();
	getchar();
	state = INIT;
	system("cls");
	
	PrintMainMenu();
}

int main()
{
	srand(time(NULL));
	PrintMainMenu();
	while (state != EXIT) {
		char intro_input = getchar();
		switch (intro_input) {
		case '1': {
			state = BOSS_BOSS;
			BattleIA();
			break; }
		case '2': {
			state = BOSS_MINON;
			BattleIA();
			break; }
		case '3': {
			state = MINION_MINION;
			BattleIA();
			break; }
		case '4': {
			state = PLAYER_MINION;
			BattlePlayer();
			break; }
		case '5': {
			state = PLAYER_BOSS;
			BattlePlayer();
			break; }
		case '6': {
			state = BOSS_BOSS;
			BattleIAx100();
			break; }
		case '7': {
			state = BOSS_MINON;
			BattleIAx100();
			break; }
		case '8': {
			state = MINION_MINION;
			BattleIAx100();
			break; }
		case '9': {
			state = EXIT;
			break; }
		case '\n': {
			break; }
		default: {
			PrintMainMenu();
			break; }
		}
	}
}