#include "pool.h"
#include "..\UtilsLib\utilslib.h"

#include <iostream>
#include <algorithm>

using namespace std;

namespace efiilj
{

	Pool::Pool() : _name("Unnamed") { }
	Pool::Pool(std::string name) : _name(name) { }

	void Pool::addVehicle()
	{
		Vehicle v;
		int count;
		if (showAddVehicleDialog(v) && IOUtils::Input<int>(count, '0', "\nCount: ", 0))
		{
			addVehicle(v, count);
		}
	}

	void Pool::addVehicle(Vehicle vehicle, int count)
	{
		if (!templateExists(vehicle))
		{
			this->_vehicleTemplates.push_back(vehicle);
			cout << "\n'" << vehicle.model << "' added to vehicle templates.";
		}

		PoolItem* item = findSingleVehicle(vehicle);

		if (item == nullptr)
			this->_vehicles.push_back(PoolItem(vehicle, count));
		else
			(*item) += count;

		cout << "\n'" << vehicle.model << "' (" << count << ") added to pool.\n";
	}
	
	PoolItem* Pool::findSingleVehicle(Vehicle vehicle)
	{
		PoolItem* item = nullptr;

		for (unsigned int i = 0; i < _vehicles.size(); i++)
		{
			if (_vehicles[i].vehicle == vehicle)
			{
				item = &_vehicles[i];
				break;
			}
		}

		return item;
	}

	vector<PoolItem*> Pool::findVehicles(int capacity, float costPerHour)
	{
		vector<PoolItem*> matches;

		for (unsigned int i = 0; i < _vehicles.size(); i++)
		{
			if (_vehicles[i].vehicle.capacity >= capacity && _vehicles[i].vehicle.costPerHour <= costPerHour)
				matches.push_back(&_vehicles[i]);
		}
		return matches;
	}

	bool Pool::vehicleExists(const Vehicle & vehicle) const
	{
		for (unsigned int i = 0; i < _vehicles.size(); i++)
		{
			if (_vehicles[i].vehicle == vehicle)
				return true;
		}

		return false;
	}

	bool Pool::templateExists(const Vehicle& vehicle) const
	{
		for (unsigned int i = 0; i < _vehicleTemplates.size(); i++)
		{
			if (_vehicleTemplates[i] == vehicle)
				return true;
		}

		return false;
	}

	bool Pool::rentVehicle(PoolItem& item, int count)
	{
		return item.rentVehicle();
	}

	bool Pool::returnVehicle(PoolItem& item, int count)
	{
		return item.returnVehicle();
	}

	bool Pool::showAddVehicleDialog(Vehicle& vehicle)
	{

		cout << "Choose a pre-made vehicle template, or create a new: \n\n";

		listTemplates();

		cout << this->count() + 1 << ". Register New\n";
		cout << "0. Exit\n";

		int select;
		if (IOUtils::Input<int>(select, '0', "> ", 0, count() + 1) && select != 0)
		{

			std::string type;
			int capacity;
			float cost, fuel;

			if (select == this->count() + 1)
			{
				cout << "Type: ";
				getline(cin, type);

				IOUtils::Input<float>(cost, "Rental cost: ", 0);
				IOUtils::Input<float>(fuel, "Fuel efficiency: ", 0);
				IOUtils::Input<int>(capacity, "Seat capacity: ", 0);

				if (type.length() > 0)
				{
					vehicle = Vehicle(type, cost, fuel, capacity);
					return true;
				}
			}
			else
			{
				vehicle = _vehicleTemplates[select - 1];
				return true;
			}
		}

		return false;
	}

	std::string Pool::to_string()
	{
		std::stringstream ss;

		if (_vehicles.size() == 0)
			cout << "No vehicles available.\n";
		else
		{
			for (unsigned int i = 0; i < _vehicles.size(); i++)
			{
				cout << i + 1 << ". " << _vehicles[i].to_string();
			}
		}

		return ss.str();
	}


	void Pool::listTemplates()
	{
		if (_vehicleTemplates.size() == 0)
			cout << "No templates available.\n";
		else
		{
			for (unsigned int i = 0; i < _vehicleTemplates.size(); i++)
			{
				cout << i + 1 << ". " << _vehicleTemplates[i].to_string();
			}
		}
		cout << "\n";
	}

	int Pool::count()
	{
		return _vehicles.size();
	}



	Pool::~Pool() { }

}

