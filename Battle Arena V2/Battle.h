#pragma once

#include "Structs.h"
#include "Spells.h"

void battleSequence(vector<Boss>& bosses, Player& player, const vector<Weapon>& weapons, vector<Potion>& potion)
{
	bool inBattle = true;
	int bossPick = bossSelection(bosses);
	Boss& boss = bosses[bossPick];

	clear();
	SetConsoleTitleA("Battle Arena (Battle)");

	while (true)
	{
		clear();

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
						runPenalty(player, boss);
						return;

					default:
						invalid();
						while (_kbhit()) _getch();
						break;
					}
				

				playerAttack(boss, player, weapons, potion);
				if (isDead(boss))
				{
					inBattle = false;
					int goldSnapshot = player.gold;
					boss.health = boss.maxHealth;
					player.health = player.maxHealth;
					boss.isDefeated = true;

					giveRewards(bossPick, player);

					clear();
					cout << "You " << green << "Win!" << reset << " - " << player.name << " defeated " << boss.name << endl;
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
					boss.health = boss.maxHealth;
					player.health = player.maxHealth;
					loseRewards(bossPick, player);

					clear();
					cout << "You " << red << "Lose!" << reset << " - " << boss.name << " defeated " << player.name << endl;
					space();

					cout << "Gold: " << goldSnapshot << " -> " << player.gold << " (" << red << "-" << returnGold(bossPick) << reset << ")" << endl;
					getKey();
					return;
				}
			}
			break;

		case Spell:
		{

			clear();

			if (potion.empty())
			{
				cout << "[!] You currently have no spells to use" << endl;
				pause();
				break;
			}

			cout << "Equip Potions To Assist You in Battle!" << endl;
			space();

			int index;

			for (size_t i = 0; i < potion.size(); i++)
			{
				if (i < potion.size() - 1) cout << "------------" << endl;
				if (potion[i].isOwned == false) continue;
				cout << " [ " << i << " ] " << potion[i].name;
				if (potion[i].isEquipped) cout << " [EQUIPPED] " << endl;
			}

			space();
			cout << "Select an Index: ";
			cin >> index;

			if (input())
			{
				continue;
			}

			if (index >= potion.size() || index < 0)
			{
				invalid();
				break;
			}

			if (potion[index].isOwned == false)
			{
				space();
				cout << "You do not own " << potion[index].name << "!" << endl;
				pause();
				break;
			}

			cout << "[+] " << green << "Successfully" << reset << " Equipped " << potion[index].name << "!" << endl;
			getKey();

			break;
		}

		case Run:
			runPenalty(player, boss);
			return;


		default:
			invalid();
			break;

		}
	}
}
