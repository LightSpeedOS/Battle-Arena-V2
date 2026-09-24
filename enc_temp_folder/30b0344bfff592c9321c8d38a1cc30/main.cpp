#include "Includes.h"
#include "GameLogic.h"
#include "Structs.h"
#include "Battle.h"
#include "Shop.h"
#include "Spells.h"

using namespace std;

auto main() -> int
{
	initConsole();

	Player player = {};
	Boss tBoss = {};
	Boss gBoss = {};
	Boss nBoss = {};
	vector<Boss>Entites;
	vector<Weapon> weapons;
	vector<Potion> potion;

	player.name = string(playerColour) + "Zork" + reset;
	player.health = 100;
	player.flask = 1;
	player.maxHealth = player.health;
	player.gold = 10000;
	player.level = 1;
	player.equippedWeapon = 0;

	tBoss.name = string(bloodRed) + "Trespasser" + reset;
	tBoss.health = 135;
	tBoss.maxHealth = tBoss.health;
	tBoss.damage = bossDamage(Trespasser);
	tBoss.isDefeated = false;
	Entites.push_back(tBoss);

	gBoss.name = string(bloodRed) + "Gravebound" + reset;
	gBoss.health = 220;
	gBoss.maxHealth = gBoss.health;
	gBoss.damage = bossDamage(Gravebound);
	gBoss.isDefeated = false;
	Entites.push_back(gBoss);

	nBoss.name = string(bloodRed) + "NightBound" + reset;
	nBoss.health = 380;
	nBoss.maxHealth = nBoss.health;
	nBoss.damage = bossDamage(Nightbound);
	nBoss.isDefeated = false;
	Entites.push_back(nBoss);

	Weapon Undersea;
	Undersea.name = "Undersea Cable";
	Undersea.damage = 19;
	Undersea.gold = 0;
	Undersea.isOwned = true;
	weapons.push_back(Undersea);

	Weapon fullMoon;
	fullMoon.name = "Full Moon Blade";
	fullMoon.damage = 31;
	fullMoon.gold = 600;
	fullMoon.isOwned = false;
	weapons.push_back(fullMoon);
	 
	Weapon Bloodthirsty;
	Bloodthirsty.name = "Bloodthirsty Axe";
	Bloodthirsty.damage = 87;
	Bloodthirsty.gold = 1500;
	Bloodthirsty.isOwned = false;
	weapons.push_back(Bloodthirsty);

	Potion lifeSteal;
	lifeSteal.name = "Fortune's Demise";
	lifeSteal.gold = 1200;
	lifeSteal.isOwned = false;
	potion.push_back(lifeSteal);

	Potion ironFist;
	ironFist.name = "Iron Fist";
	ironFist.gold = 300;
	ironFist.isOwned = false;
	potion.push_back(ironFist);



	int mainOptions;

	while (true)
	{
		clear();
		SetConsoleTitleA("Battle Arena (Main Menu)");

		cout << "--MENU---------------------------" << endl;
		space();

		cout << player.name << "  HP " << brightGreen << player.health << reset << "/" << green << player.maxHealth << reset
			<< "  Gold " << gold << player.gold << reset << "  Lvl " << levelColor(player) << player.level << reset <<
			"  Weapon " << bloodRed << weapons[player.equippedWeapon].name << reset << " (" << green << weapons[player.equippedWeapon].damage << reset << ")" << endl;
		space();

		cout << "[1] -> Battle" << endl;
		cout << "[2] -> Shop" << endl;
		cout << "[3] -> Equip a Weapon" << endl;
		cout << "[4] -> Stat's" << endl;
		cout << "[5] -> " << red << "Quit" << reset << endl;
		cout << "> ";
		cin >> mainOptions;

		if (input())
		{
			continue;
		}

		switch (mainOptions)
		{

		case Battle:
			battleSequence(Entites, player, weapons, potion);
			break;

		case Shop:
			listWeapons(weapons, potion, player);
			break;

		case Equip:
			equipWeapon(player, weapons);
			break;

		case Stats:
			listStats(player, weapons);
			break;

		case Exit:
			shutDown();
			break;

		default:
			invalid();
			break;

		}
	}
	
}