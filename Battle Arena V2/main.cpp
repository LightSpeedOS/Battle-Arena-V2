#include "Includes.h"
#include "GameLogic.h"
#include "Structs.h"
#include "Battle.h"

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

	player.name = string(playerColour) + "Zork" + reset;
	player.health = 100;
	player.flask = 1;
	player.maxHealth = player.health;
	player.gold = 100;
	player.level = 1;
	player.equppedWeapon = 0;

	tBoss.name = string(bloodRed) + "Trespasser" + reset;
	tBoss.health = 135;
	tBoss.damage = bossDamage(Trespasser);
	tBoss.isDefeated = false;
	Entites.push_back(tBoss);

	gBoss.name = string(bloodRed) + "Gravebound" + reset;
	gBoss.health = 220;
	gBoss.damage = bossDamage(Gravebound);
	gBoss.isDefeated = false;
	Entites.push_back(gBoss);

	nBoss.name = string(bloodRed) + "NightBound" + reset;
	nBoss.health = 380;
	nBoss.damage = bossDamage(Nightbound);
	nBoss.isDefeated = false;
	Entites.push_back(nBoss);

	Weapon weapon1;
	weapon1.name = "Undersea Cable";
	weapon1.damage = 19;

	int mainOptions;

	while (true)
	{

		SetConsoleTitleA("Battle Arena (Main Menu)");

		cout << "--MENU---------------------------" << endl;
		space();

		cout << player.name << "  HP " << brightGreen << player.health << reset << "/" << green << player.maxHealth << reset
			<< "  Gold " << gold << player.gold << reset << "  Lvl " << levelColor(player) << player.level << reset << endl;
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

			break;

		}
	}
	
}