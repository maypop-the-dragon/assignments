#include "./ch15-employees.h"
#include <iostream>
#include <random>

using employees_lib::printDate;
using employees_lib::printDollarAmount;
using employees_lib::ProductionWorker;
using employees_lib::Shift;
// This is the hard-coded sample data used for this program.
std::vector<ProductionWorker> workers = {
	ProductionWorker("John Doe", 1234567890, 2018, 5, 15, 1550, Shift::DAY),
	ProductionWorker("Jane Smith", 2345678901, 2019, 8, 3, 1675, Shift::NIGHT),
	ProductionWorker("Michael Johnson", 3456789012, 2017, 11, 20, 1425, Shift::DAY),
	ProductionWorker("Emily Brown", 4567890123, 2016, 2, 10, 1700, Shift::NIGHT),
	ProductionWorker("David Lee", 5678901234, 2020, 3, 8, 1575, Shift::DAY),
	ProductionWorker("Sarah Wilson", 6789012345, 2018, 9, 5, 1625, Shift::NIGHT),
	ProductionWorker("James Taylor", 7890123456, 2015, 7, 12, 1450, Shift::DAY),
	ProductionWorker("Jennifer Martinez", 8901234567, 2019, 1, 30, 1800, Shift::NIGHT),
	ProductionWorker("Christopher Garcia", 9012345678, 2017, 4, 25, 1525, Shift::DAY),
	ProductionWorker("Mary Martinez", 1234567890, 2016, 10, 17, 1675, Shift::NIGHT),
	ProductionWorker("Matthew Robinson", 2345678901, 2020, 12, 1, 1750, Shift::DAY),
	ProductionWorker("Patricia Lee", 3456789012, 2018, 2, 14, 1400, Shift::NIGHT),
	ProductionWorker("Daniel Harris", 4567890123, 2015, 6, 28, 1525, Shift::DAY),
	ProductionWorker("Laura Clark", 5678901234, 2019, 10, 9, 1650, Shift::NIGHT),
	ProductionWorker("Kevin Lewis", 6789012345, 2017, 3, 23, 1475, Shift::DAY),
	ProductionWorker("Elizabeth Walker", 7890123456, 2016, 11, 11, 1725, Shift::NIGHT),
	ProductionWorker("Brian King", 8901234567, 2020, 5, 7, 1600, Shift::DAY),
	ProductionWorker("Susan Young", 9012345678, 2018, 8, 19, 1575, Shift::NIGHT),
	ProductionWorker("Mark Allen", 1234567890, 2015, 2, 3, 1450, Shift::DAY),
	ProductionWorker("Barbara Hernandez", 2345678901, 2019, 7, 28, 1625, Shift::NIGHT),
	ProductionWorker("Robert Wright", 3456789012, 2017, 11, 14, 1500, Shift::DAY),
	ProductionWorker("Linda Lopez", 4567890123, 2016, 4, 5, 1775, Shift::NIGHT),
	ProductionWorker("William Hill", 5678901234, 2020, 1, 23, 1650, Shift::DAY),
	ProductionWorker("Margaret Scott", 6789012345, 2018, 6, 10, 1525, Shift::NIGHT),
	ProductionWorker("Joseph Green", 7890123456, 2015, 9, 18, 1475, Shift::DAY),
	ProductionWorker("Jessica Adams", 8901234567, 2019, 3, 5, 1600, Shift::NIGHT),
	ProductionWorker("David Baker", 9012345678, 2017, 5, 12, 1550, Shift::DAY),
	ProductionWorker("Karen Hall", 1234567890, 2016, 12, 30, 1725, Shift::NIGHT),
	ProductionWorker("Richard Gonzalez", 2345678901, 2020, 9, 14, 1675, Shift::DAY),
	ProductionWorker("Betty Perez", 3456789012, 2018, 4, 8, 1500, Shift::NIGHT)
};

int main() {
	std::cout << "Let's downsize from " << workers.size() << " workers!\n";

	unsigned int people_to_screw_over = workers.size() / 2;

	// Decrease the variable each time the loop runs,
	// and stop when it reaches zero.
	for (; people_to_screw_over; people_to_screw_over--) {
		// Decide on a random worker to fire.
		unsigned int index = (unsigned int)(
			float(rand()) / (float(RAND_MAX)) * float(workers.size())
		);

		std::cout << '\n'
			<< "Employee #" << workers[index].id_number << ",\n"
			<< "or as their \"family\" calls them, \"" << workers[index].name << ",\"\n"
			<< "has worked for us since ";
		printDate(
			std::cout,
			workers[index].hire_year,
			workers[index].hire_month,
			workers[index].hire_day
		);
		std::cout << ",\ncurrently on the ";
		printShift(std::cout, workers[index].shift);
		std::cout << " shift.\nThat's ";
		printDollarAmount(std::cout, workers[index].hourly_pay);
		std::cout << " per hour we don't have to pay them.\n";

		// Remove that worker from the list.
		workers.erase(workers.begin() + index);
	}

	std::cout << "\nWe now have " << workers.size() << " workers." << std::endl;

	return 0;
}
