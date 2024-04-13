#include <cstdint>
#include <iostream>
#include <string>

namespace employees_lib {
	enum Shift {
		DAY = 1,
		NIGHT = 2
	};

	void printDate(std::ostream &out, uint16_t year, uint8_t month, uint8_t day) {
		const char *MONTHS[12] = {
			"January",
			"February",
			"March",
			"April",
			"May",
			"June",
			"July",
			"August",
			"September",
			"October",
			"November",
			"December"
		};

		out << (int)day << ' ';

		if (month > 12)
			out << "ERROR";
		else
			out << MONTHS[month - 1];

		out << ", " << year;
	}

	void printDollarAmount(std::ostream &out, uint16_t dollar_amount) {
		out << '$' << dollar_amount / 100 << '.';

		uint16_t cents = dollar_amount % 100;

		if (cents < 10)
			out << '0';
		out << cents;
	}

	void printShift(std::ostream &out, Shift shift) {
		switch (shift) {
			case Shift::DAY:
				out << "DAY";
				break;
			case Shift::NIGHT:
				out << "NIGHT";
				break;
			default:
				out << "INVALID";
				break;
		}
	}

	class Employee {
		public:
			std::string name;
			std::uint64_t id_number;
			std::int16_t hire_year;
			std::uint8_t hire_month;
			std::uint8_t hire_day;

			Employee(
				std::string name,
				std::uint64_t id_number,
				std::int16_t hire_year,
				std::uint8_t hire_month,
				std::uint8_t hire_day
			) {
				this->name = name;
				this->id_number = id_number;
				this->hire_year = hire_year;
				this->hire_month = hire_month;
				this->hire_day = hire_day;
			}
	};

	class ProductionWorker : public Employee {
		public:
			float hourly_pay;
			Shift shift;

			ProductionWorker(
				std::string name,
				std::uint64_t id_number,
				std::int16_t hire_year,
				std::uint8_t hire_month,
				std::uint8_t hire_day,
				float hourly_pay,
				Shift shift
			) : Employee(
				name,
				id_number,
				hire_year,
				hire_month,
				hire_day
			) {
				this->hourly_pay = hourly_pay;
				this->shift = shift;
			}
	};

	class TeamLeader : public ProductionWorker {
		public:
			float monthly_bonus;
			std::uint8_t yearly_training_hours_required;
			std::uint8_t yearly_training_hours_attended;

			TeamLeader(
				std::string name,
				std::uint64_t id_number,
				std::int16_t hire_year,
				std::uint8_t hire_month,
				std::uint8_t hire_day,
				float hourly_pay,
				float monthly_bonus,
				Shift shift,
				std::uint8_t yearly_training_hours_required,
				std::uint8_t yearly_training_hours_attended
			) : ProductionWorker(
				name,
				id_number,
				hire_year,
				hire_month,
				hire_day,
				hourly_pay,
				shift
			) {
				this->monthly_bonus;
				this->yearly_training_hours_required = yearly_training_hours_required;
				this->yearly_training_hours_attended = yearly_training_hours_attended;
			}
	};
}
