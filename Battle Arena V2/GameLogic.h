#pragma once

#include "Structs.h"
#include "Spells.h"

const char* levelColor(Player& player)
{
	if (player.level > 8) return magenta;
	if (player.level > 3) return silver;
	if (player.level > 1) return bronze;
	return reset;
}

int bossSelection(vector<Boss>& bosses)
{
	int bossPick;
	bool bossSelect = false;

	while (!bossSelect)
	{
		clear();

		cout << "[1] -> Trespasser (" << bosses[0].health << "HP)" << endl;

		if (bosses[0].isDefeated == false) cout << "[2] -> Gravebound [ LOCKED ]" << endl;
		else cout << "[2] -> Gravebound (" << bosses[1].health << "HP)" << endl;

		if (bosses[1].isDefeated == false) cout << "[3] -> Nightbound [ LOCKED ]" << endl;
		else cout << "[3] -> Nightbound (" << bosses[2].health << "HP)" << endl;
		cout << "> ";
		cin >> bossPick;

		if (input())
		{
			continue;
		}

		switch (bossPick)
		{
		case 1:
			return 0;
			break;

		case 2:
			
			if (bosses[0].isDefeated == false)
			{
				clear();
				cout << "You have not unlocked " << bosses[1].name << " yet!" << endl;
				pause();
				break;
			}

			bossSelect = true;
			return 1;
			break;

		case 3:

			if (bosses[1].isDefeated == false)
			{
				clear();
				cout << "You have not unlocked " << bosses[2].name << " yet!" << endl;
				pause();
				break;
			}

			bossSelect = true;
			return 2;
			break;

		default:
			clear();
			invalid();
			break;
		}

	}
}

int bossDamage(int bossType)
{
	if (bossType == 0) return rand() % 37 + 19;
	if (bossType == 1) return rand() % 70 + 35;
	if (bossType == 2) return rand() % 100 + 45;
}

bool bloodDrink(const Player& player)
{
	return player.health > player.maxHealth;
}

void playerAttack(Boss& target, Player& attacker, const vector<Weapon>& weapons, vector<Potion>& potion)
{
	clear();

	if (castIronFist(attacker, target, potion, weapons))
	{
		const int healthSnapshot = target.health;
		const int doubleDamage = weapons[attacker.equippedWeapon].damage * 2;
		target.health -= doubleDamage;

		cout << attacker.name << " Striking -> " << target.name << endl;
		battlePause();

		cout << target.name << " Health: " << healthSnapshot << " -> "
			<< target.health << "(" << red << "-" << doubleDamage << reset << ")" << endl;
		battlePause();
		space();

		potion[IronFist].isEquipped = false;
		potion[IronFist].isOwned = false;
	}
	
	else
	{
		const int healthSnapshot = target.health;
		target.health -= weapons[attacker.equippedWeapon].damage;

		cout << attacker.name << " Striking -> " << target.name << " | ";
		battlePause();

		cout << target.name << " Health: " << healthSnapshot << " -> "
			<< target.health << " (" << red << "-" << weapons[attacker.equippedWeapon].damage << reset << ")" << endl;
		battlePause();
		space();
	}
}

bool isDead(const Boss& boss)
{
	return boss.health <= 0;
}

void bossAttack(Player& target, const Boss& attacker)
{
	const int healthSnapshot = target.health;
	target.health -= attacker.damage;

	cout << attacker.name << " Striking -> " << target.name << " | ";
	battlePause();

	cout << target.name << " Health: " << healthSnapshot << " -> "
		<< target.health << " (" << red << "-" << attacker.damage << reset << ")" << endl;
	getKey();
	space();
}

bool isDead(const Player& player)
{ 
	 return player.health <= 0;
}

int giveRewards(const int bossType, Player& player)
{
	if (bossType == 0) return player.gold += 750;
	if (bossType == 1) return player.gold += 1750;
	if (bossType == 2) return player.gold += 3500;
	return 0;
}

int loseRewards(const int bossType, Player& player)
{
	if (bossType == 0) return player.gold -= 750;
	if (bossType == 1) return player.gold -= 1750;
	if (bossType == 2) return player.gold -= 3500;
	return 0;
}

int returnGold(const int bossType)
{
	if (bossType == 0) return 750;
	if (bossType == 1) return 1750;
	if (bossType == 2) return 3500;
	return 0;
}

void runPenalty(Player& player, Boss& boss)
{
	int result = MessageBoxA(NULL, "Running away will result in a penalty.", "Warning!", MB_YESNO);

	if (result == IDYES)
	{
		clear();
		player.flask--;
		player.gold -= 500;

		if (player.gold < 0) player.gold = 0;
		if (player.flask < 0) player.flask = 0;
		boss.health = boss.maxHealth;
		player.health = player.maxHealth;

		cout << "Coward! | - 1 Blood Drink & -500 Gold." << endl;
		cout << "Blood Drink Remaining: " << player.flask << " | Gold: " << player.gold << endl;
		getKey();
	}

	else if (result == IDNO)
	{
		cout << "Good Choice, Return to the battle." << endl;
		pause();
	}
}


void listStats(Player& player, vector<Weapon>& weapons)
{
	clear();

	cout << player.name << " | " << "lvl " << levelColor(player) << player.level << reset << endl;
	space();

	cout << left << setw(10) << "Health" << brightGreen << player.health << reset << "/" << green << player.maxHealth << reset << endl;
	cout << left << setw(10) << "Gold" << yellow << player.gold << reset << endl;
	cout << left << setw(10) << "Flask" << player.flask << endl;
	cout << left << setw(10) << "Weapon" << bloodRed << weapons[player.equippedWeapon].name << reset << endl;

	space();
	while (true)
	{
		cout << "[L] Level Up  [I] Information  [R] Return" << endl;
		char key = _getch();

		switch (tolower(key))
		{
		case 'l':
		{
			int buyingLevels;

			clear();
			cout << "Each level cost 500 Virtue | you can afford " << player.gold / 500 << " Levels!" << endl;
			space();

			cout << "Amount:";
			cin >> buyingLevels;

			if (input())
			{
				continue;
			}

			if (buyingLevels < 0)
			{
				space();
				cout << "[!] You cannot buy negative levels" << endl;
				pause();
				break;
			}

			if (player.gold < 500 * buyingLevels)
			{
				space();
				cout << "[!] You do not have enough virtue" << endl;
				pause();
				break;
			}

			cout << "[+] " << green << "Successfully " << reset << "Purchased " << buyingLevels << " Levels!" << endl;
			player.gold -= 500 * buyingLevels;
			player.level += buyingLevels;
			player.flask += buyingLevels / 2;
			weapons[player.equippedWeapon].damage += 2;
			getKey();

			return;
		}

		case 'i':
			MessageBoxA(NULL,
				"1. Blood Drinks will cap at 14, regardless of what level you are.\n"
				"2. There is no level cap, every level will grant a +2 weapon damage boost.\n"
				"3. For every 2 levels you purchase you will recive +1 Blood Drink",
				"Information",
				MB_OK | MB_ICONINFORMATION);
			break;

		case 'r':
			pause();
			return;
			
		default:
			invalid();
			break;
		}
	}
}

void equipWeapon(Player& player, const vector<Weapon>& weapons)
{
	int index;

	while (true)
	{
		clear();


		for (size_t i = 0; i < weapons.size(); i++)
		{
			if (weapons[i].isOwned == false) continue;

			if (i < weapons.size() - 1) cout << "------------" << endl;
			cout << "[ " << i << " ] " << weapons[i].name;
			if (i == player.equippedWeapon) cout << " [EQUIPPED] ";
			cout << endl;
		}

		cout << "Select an index: ";
		cin >> index;

		if (input())
		{
			continue;
		}

		if (index >= weapons.size() || index < 0)
		{
			invalid();
			break;
		}

		if (weapons[index].isOwned == false)
		{
			space();
			cout << "You do not own this weapon." << endl;
			pause();
			break;
		}

		player.equippedWeapon = index;

		space();
		cout << "[+] " << green << "Successfully" << reset << " Equipped " << weapons[index].name << endl;
		getKey();
		break;

	}

}