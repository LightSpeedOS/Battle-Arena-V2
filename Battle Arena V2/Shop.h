#pragma once

#include "Structs.h"

void listWeapons(vector<Weapon>& weapons, Player& player)
{

	int shopChoice;
	int choice;

	while (true)
	{
	
		cout << "[1] -> Weapon Shop" << endl;
		cout << "[2] -> Potion Shop" << endl;
		cout << "[0] -> Return" << endl;
		cout << "> ";
		cin >> shopChoice;

		if (input())
		{
			continue;
		}

		switch (shopChoice)
		{
		case Swords:
		{
			clear();

			cout << "Gold: " << player.gold << endl;
			space();

			for (size_t i = 0; i < weapons.size(); i++)
			{
				if (weapons[i].isOwned == true)
				{
					continue;
				}

				cout << "[ " << i << " ] -> Name: " << weapons[i].name << " | Price:" << weapons[i].gold << endl;

				if (i < weapons.size() - 1) cout << "-----------" << endl;
			}

			cout << "Select an Index" << endl;
			cout << "> ";
			cin >> choice;

			if (choice >= weapons.size() || choice < 0)
			{
				space();
				cout << "[!] Invalid Index" << endl;
				pause();
				break;
			}

			if (weapons[choice].gold > player.gold)
			{
				space();
				cout << "You do not have enough gold to purchase " << weapons[choice].name << "!" << endl;
				pause();
				break;
			}

			if (weapons[choice].isOwned == true)
			{
				clear();
				cout << "[!] This weapon is alredy owned." << endl;
				pause();
				break;
			}

			player.equippedWeapon = choice;
			int goldSnapshot = player.gold;
			player.gold -= weapons[choice].gold;
			weapons[choice].isOwned = true;

			cout << "Successfully purchased " << weapons[choice].name << "!" << endl;
			cout << player.name << "'s Gold: " << goldSnapshot << " -> " << player.gold << "(" << red << "-" << weapons[choice].gold << reset << ")" << endl;
			getKey();
			return;
		}

		case Spells:
			clear();
			cout << "Coming soon :)" << endl;
			pause();
			return;

		case 0:

			return;

		default:
			invalid();
			return;
			
		}

	}
}