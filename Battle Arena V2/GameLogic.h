#pragma once

enum mainMenu
{
	Battle = 1,
	Shop,
	Equip,
	Stats,
	Exit
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

void playerAttack(Boss& target, const Player& attacker)
{
	const int healthSnapshot = target.health;
	target.health -= attacker.weapon.damage;

	cout << attacker.name << " Striking ->" << target.name << endl;
	battlePause();

	cout << target.name << " Health: " << healthSnapshot << " -> "
		<< target.health << "(" << red << "-" << attacker.weapon.damage << reset << ")" << endl;
	battlePause();
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
}
