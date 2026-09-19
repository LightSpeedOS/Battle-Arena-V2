#include "Includes.h"
#include "GameLogic.h"

using namespace std;

auto main() -> int
{
	initConsole();

	Player player = {};
	Boss boss = {};
	vector<Boss>Bosses;

	player.name = string(playerColour) +"Zork" + reset;
	player.health = 100;
	player.flask = 1;
	player.maxHealth = player.health;
	player.weapon.damage;
	player.gold = 100;
	player.level = 1;

	boss.name = string(bloodRed) + "Trespasser" + reset;
	boss.health = 135;
	boss.damage = bossDamage();
	Bosses.push_back(boss);

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