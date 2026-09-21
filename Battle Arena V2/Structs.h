#pragma once

using namespace std;

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

enum shopMenu
{
	Swords = 1,
	Spells
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
	int gold;
	bool isOwned = false;
};

struct Potion
{
	string name;
	int gold;
	bool isEquipped = false;
	bool isOwned = false;
};

struct Player
{
	string name;
	int health;
	int flask;
	int maxHealth;
	int gold;
	int level;
	int equippedWeapon;

	Weapon weapon;
	Potion potion;
};

struct Boss
{
	string name;
	int health;
	int maxHealth;
	int damage;
	bool isDefeated = false;
};