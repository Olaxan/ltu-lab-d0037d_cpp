#include "pool.h"
#include "..\UtilsLib\menu.h"

#include <string>
#include <iostream>

efiilj::Pool pool = efiilj::Pool("Customers");

bool doAdd()
{
	pool.addVehicle();
	return false;
}

bool doFind()
{
	int capacity;
	float price;

	if (efiilj::IOUtils::Input<float>(price, '0', "Max price: ") && efiilj::IOUtils::Input<int>(capacity, "Min capacity: "))
	{
		vector<efiilj::PoolItem*> matches = pool.findVehicles(capacity, price);

		cout << "\n" << matches.size() << " matches:\n\n";

		if (matches.size() > 0)
		{
			int select, count;
			efiilj::Vehicle vehicle;

			for (unsigned int i = 0; i < matches.size(); i++)
			{
				cout << (i + 1) << ". " << matches[i]->to_string();
			}

			if (efiilj::IOUtils::Input<int>(select, '0', "\nRent vehicle?\n> ", 1, matches.size()) && efiilj::IOUtils::Input<int>(count, '0', "Quantity: ", 1)) {
				if (matches[select - 1]->rentVehicle(count))
					cout << "\nVehicle selected for rental.\n";
				else
					cout << "\nUnable to select vehicle for rental (not available).\n";

				cout << "Please speak with an AVIS representative for further assistance.\n";
			}
		}
	}
	return false;
}

bool doList()
{
	pool.to_string();

	return false;
}

int main()
{
	efiilj::Menu mainMenu = efiilj::Menu("=======[ Main Menu ]=======");
	mainMenu.AddItem("Register new vehicle", doAdd);
	mainMenu.AddItem("Search vehicle registry", doFind);
	mainMenu.AddItem("Print registry", doList);
	mainMenu.Show();
}