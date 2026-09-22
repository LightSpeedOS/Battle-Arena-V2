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

		if (player.gold < potions[index].gold)
		{
			space();
			cout << "[!] You do not have enough gold. " << potions[index].name << endl;
			pause();
			return;
		}

		if (index >= potions.size() || index < 0)
		{
			invalid();
			return;
		}

		space();
		const int goldSnapshot = player.gold;
		player.gold -= potions[index].gold;
		cout << "[+] Successfully Purchased " << potions[index].name << endl;
		cout << "Gold: " << goldSnapshot << " -> " << player.gold << " (" << red << "-" << potions[index].gold << reset << ")" << endl;
		getKey();
		return;
	}
}




void castFortunesDemise(Player& player, Boss& boss, vector<Potion>& potions)
{
	const float stolenHealth = boss.maxHealth * 0.20;
	const int healthSnapshot = boss.health;
	boss.health -= stolenHealth;

	space();
	cout << player.name << " has cast Fortune's Demise onto " << boss.name << " stealing " << stolenHealth << "!" << endl;
	cout << boss.name << brightGreen << boss.health << reset << "/" << green << boss.maxHealth << reset << endl;

	potions[0].isEquipped = false;
	potions[0].isOwned = false;
	getKey();
}
