#pragma once

enum mainMenu
{
	Battle = 1,
	Shop,
	Equip,
	Stats,
	Exit
};

enum fightMenu
{
	Fight = 1,
	Spell,
	Run
};

enum Bosses
{
	Trespasser, // 0
	Gravebound, // 1
	Nightbound  // 2
};

struct Weapon
{
	string name;
	int damage;
	bool isOwned = false;
};

struct Potion
{
	string name;
	int gold;
	bool isOwned = false;
	bool isEquipped = false;
};

struct Player
{
	string name;
	int health;
	int flask;
	int maxHealth;
	int gold;
	int level;

	Weapon weapon;
	Potion potion;
};

struct Boss
{
	string name;
	int health;
	int damage;
	bool isDefeated = false;
};

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

void playerAttack(Boss& target, const Player& attacker)
{
	const int healthSnapshot = target.health;
	target.health -= attacker.weapon.damage;

	cout << attacker.name << " Striking ->" << target.name << endl;
	battlePause();

	cout << target.name << " Health: " << healthSnapshot << " -> "
		<< target.health << "(" << red << "-" << attacker.weapon.damage << reset << ")" << endl;
	battlePause();
	space();
}

void bossAttack(Player& target, const Boss& attacker)
{
	const int healthSnapshot = target.health;
	target.health -= attacker.damage;

	cout << attacker.name << " Striking ->" << target.name << endl;
	battlePause();

	cout << target.name << " Health: " << healthSnapshot << " -> "
		<< target.health << "(" << red << "-" << attacker.damage << reset << ")" << endl;
	battlePause();
	space();
}

bool isDead(const Boss& boss)
{
	return boss.health <= 0;
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

void runPenalty(Player& player)
{
	int result = MessageBoxA(NULL, "Running away will result in a penalty.", "Warning!", MB_YESNO);

	if (result == IDYES)
	{
		clear();
		player.flask--;
		player.gold -= 500;

		if (player.gold < 0) player.gold = 0;
		if (player.flask < 0) player.flask = 0;

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

void battleSequence(vector<Boss>& bosses, Player& player)
{
	bool inBattle = true;
	int bossPick = bossSelection(bosses);
	Boss& boss = bosses[bossPick];

	clear();
	SetConsoleTitleA("Battle Arena (Battle)");

	while (true)
	{ 

		int fightMenu;

		cout << "[1] Fight" << endl;
		cout << "[2] Spells" << endl;
		cout << "[3] Run" << endl;
		cout << "> ";
		cin >> fightMenu;

		if (input())
		{
			continue;
		}

		switch (fightMenu)
		{

		case Fight:

			while (inBattle)
			{
				cout << "[F] Fight  [H] Heal (" << player.flask << ") " << "[R] Run" << endl;
				cout << "> ";

				char key = _getch();

				switch (tolower(key))
				{
				case 'f':
					clear();
					break;

				case 'h':
					clear();

					if (player.flask <= 0)
					{
						clear();
						cout << "You do not have any flask remaining." << endl;
						pause();
						break;
					}

					if (bloodDrink(player))
					{
						int healthSnapshot = player.health;
						player.health = player.maxHealth;
						player.flask--;

						cout << "Health: " << healthSnapshot << " -> " << player.health << " (+0)" << endl;
						cout << "Remaining Blood Drink: " << player.flask << endl;
						pause();
					}

					else
					{
						int healthSnapshot = player.health;
						player.health += player.maxHealth * 0.35;
						player.flask--;
						cout << "Health: " << healthSnapshot << " -> " << player.health << " (" << green << "+" << player.maxHealth * 0.35 << reset << ")" << endl;
						cout << "Remaining Blood Drink: " << player.flask << endl;
						pause();
					}
					break;

				case 'r':
					runPenalty(player);
					return;

				}

				playerAttack(boss, player);
				if (isDead(boss))
				{
					inBattle = false;
					int goldSnapshot = player.gold;
					boss.isDefeated = true;

					giveRewards(bossPick, player);

					cout << "You " << green << "Win!" << reset << " · " << player.name << " defeated " << boss.name << endl;
					space();

					cout << "Gold: " << goldSnapshot << " -> " << player.gold << " (" << green << "+" << returnGold(bossPick) << reset << ")" << endl;

					getKey();
					return;
				}

				bossAttack(player, boss);
				if (isDead(player))
				{
					inBattle = false;
					int goldSnapshot = player.gold;
					loseRewards(bossPick, player);

					cout << "You " << red << "Lose!" << reset << " · " << boss.name << " defeated " << player.name << endl;
					space();

					cout << "Gold: " << goldSnapshot << " -> " << player.gold << " (" << red << "-" << returnGold(bossPick) << reset << ")" << endl;
					getKey();
					return;
				}
			}
			break;


		default:
			invalid();
			break;

		}
	}
}
