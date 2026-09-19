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

bool inBattle = false;

const char* levelColor(Player& player)
{
	if (player.level == 1) return reset;
	if (player.level > 1) return bronze;
	if (player.level > 3) return silver;
	if (player.level > 8) return magenta;
}

int bossDamage()
{
	int bDamage = rand() % 37 + 19;
	return bDamage;
}

bool bloodDrink(Player& player)
{
	return player.health > 100;
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

int giveRewards(const Bosses bossType, Player& player)
{
	if (bossType == 0) return player.gold += 750;
	if (bossType == 1) return player.gold += 1750;
	if (bossType == 2) return player.gold += 3500;
}

int loseRewards(const Bosses bossType, Player& player)
{
	if (bossType == 0) return player.gold -= 750;
	if (bossType == 1) return player.gold -= 1750;
	if (bossType == 2) return player.gold -= 3500;
}

int returnGold(const Bosses bossType)
{
	if (bossType == 0) return 750;
	if (bossType == 1) return 1750;
	if (bossType == 2) return 3500;
}

void runPenalty(Player& player)
{

}

void battleSequence(Player& player, Boss& boss)
{
	inBattle = true;
	clear();
	SetConsoleTitleA("Battle Arena (in Battle)");

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

				playerAttack(boss, player);
				if (isDead(boss))
				{
					inBattle = false;
					int goldSnapshot = player.gold;
					giveRewards(Trespasser, player);

					cout << "You " << green << "Win!" << reset << " · " << player.name << " defeated " << boss.name << endl;
					space();

					cout << "Gold: " << goldSnapshot << " -> " << player.gold << " (" << green << "+" << returnGold(Trespasser) << reset << ")" << endl;

					getKey();
					return;
				}

				bossAttack(player, boss);
				if (isDead(player))
				{
					inBattle = false;
					int goldSnapshot = player.gold;
					loseRewards(Trespasser, player);

					cout << "You " << red << "Lose!" << reset << " · " << boss.name << " defeated " << player.name << endl;
					space();

					cout << "Gold: " << goldSnapshot << " -> " << player.gold << " (" << red << "-" << returnGold(Trespasser) << reset << ")" << endl;
					getKey();
					return;
				}

				cout << "[F] Fight  [H] Heal  [R] Run" << endl;

				char key = _getch();

				switch (tolower(key))
				{
				case 'f':
					clear(); 
					break;

				case 'h':
					clear();

					if (bloodDrink(player))
					{
						int healthSnapshot = player.health;
						player.health = player.maxHealth;

						cout << "Health: " << healthSnapshot << " -> " << player.health << " (+0)" << endl;
					}

					else
					{
						int healthSnapshot = player.health;
						player.health += player.maxHealth * 0.35;
						cout << "Health: " << healthSnapshot << " -> " << player.health << " (" << green << "+" << player.maxHealth * 0.35 << reset << ")" << endl;
					}

					break;
				}
			}
		}
	}
}
