#pragma once

#include "Structs.h"

void battleSequence(vector<Boss>& bosses, Player& player, const vector<Weapon>& weapons)
{
	bool inBattle = true;
	int bossPick = bossSelection(bosses);
	Boss& boss = bosses[bossPick];
	boss.health = boss.maxHealth;
	player.health = player.maxHealth;

	clear();
	SetConsoleTitleA("Battle Arena (Battle)");

	while (true)
	{

		int fightMenu;

		cout << "[1] Battle" << endl;
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
				clear();

				cout << "[F] Fight  [H] Heal (" << player.flask << ") " << "[R] Run" << endl;
				cout << "> ";

				this_thread::sleep_for(chrono::milliseconds(500));
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

				playerAttack(boss, player, weapons);
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
