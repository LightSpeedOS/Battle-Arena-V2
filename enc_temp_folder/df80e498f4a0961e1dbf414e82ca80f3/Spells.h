#pragma once


void listPotions(vector<Potion>& potions, Player& player)
{
	int index;

	while (true)
	{
		clear();

		cout << player.name << " | Gold: " << player.gold << endl;

		for (size_t i = 0; i < potions.size(); i++)
		{

			cout << "[ " << i << " ] -> " << potions[i].name << " | Gold:" << potions[i].gold << endl;
			if (i < potions.size() - 1) cout << "-----------" << endl;
		}

		cout << "Select an Index: ";
		cin >> index;

		if (input())
		{
			continue;
		}

		if (index >= potions.size() || index < 0)
		{
			invalid();
			return;
		}

		if (player.gold < potions[index].gold)
		{
			space();
			cout << "[!] You do not have enough gold. " << potions[index].name << endl;
			pause();
			return;
		}

		if (potions[index].isOwned == true)
		{
			space();
			cout << "[!] You already own" << potions[index].name << "!" << endl;
			pause();
			return;
		}

		space();
		const int goldSnapshot = player.gold;
		player.gold -= potions[index].gold;
		potions[index].isOwned = true;

		cout << "[+] Successfully Purchased " << potions[index].name << endl;
		cout << "Gold: " << goldSnapshot << " -> " << player.gold << " (" << red << "-" << potions[index].gold << reset << ")" << endl;
		getKey();
		return;
	}
}

bool castFortunesDemise(Player& player, Boss& boss, vector<Potion>& potion)
{
	return potion[FortunesDemise].isEquipped == true;
}

bool castIronFist(Player& player, Boss& boss, vector<Potion>& potion, vector<Weapon> weapons)
{
	return potion[IronFist].isEquipped == true;
}
