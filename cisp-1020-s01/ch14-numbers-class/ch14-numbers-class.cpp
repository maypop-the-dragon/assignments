#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdlib.h>

// A dollar amount.
// Also, this is a terrible class name but the instructions say to use it.
class Numbers {
	std::int64_t amount;

	// This internal method prints a description of a non-negative number below
	// 1,000, but the number is passed negative.
	inline static void printHundred(std::ostream& out, int64_t number) {
		// Like the -illion strings, these names are also a list.
		const char* NUMBER_NAMES[20] = {
			"zero",
			"one",
			"two",
			"three",
			"four",
			"five",
			"six",
			"seven",
			"eight",
			"nine",
			"ten",
			"eleven",
			"twelve",
			"thirteen",
			"fourteen",
			"fifteen",
			"sixteen",
			"seventeen",
			"eighteen",
			"nineteen"
		};
		// The -ty names are also a list.
		const char* TY_NAMES[8] = {
			"twenty",
			"thirty",
			"forty",
			"fifty",
			"sixty",
			"seventy",
			"eighty",
			"ninety"
		};

		// Zero is a special case.
		if (!number)
			out << NUMBER_NAMES[0];

		if (number < -99) {
			// Print the hundreds value and remove that digit.
			out << NUMBER_NAMES[number / -100];
			out << " hundred";
			number %= -100;

			if (!number)
				// If there are no more digits, stop!
				return;
			else
				// Otherwise, print a space before the remaining values.
				out << ' ';
		}

		if (number > -20)
			// Print preset names for numbers less than 20.
			out << NUMBER_NAMES[-number];
		else {
			// Print the appropriate tens value.
			out << TY_NAMES[number / -10 - 2];

			// Print the ones value if necessary.
			if (number % -10)
				out << ' ' << NUMBER_NAMES[-number % 10];
		}
	}

	public:
		Numbers(std::int64_t amount):
			amount(amount) {};

		// Write an English description of the amount to the given stream.
		void print(std::ostream& out) {
			// Zero is a special case.
			if (this->amount == 0) {
				out << "zero dollars";
				return;
			}

			// This copy of the amount will have digits removed
			// as they are printed.
			std::int64_t copy = this->amount;

			if (copy < 0)
				out << "negative ";
			else
				// The copy value is actually inverted to become negative
				// if it is positive, because doing it the other way around
				// risks an overflow if the value is the minimum possible one.
				copy = -copy;

			// I have stored the -illion strings in a list. This way, my code
			// can be a bit shorter and it's easier to add more if necessary.
			// So, if anyone wants to use a larger integer type, you MUST add
			// add all of the necessary -illions or there will be issues.
			const int ILLION_COUNT = 6;
			const char* ILLIONS[ILLION_COUNT] = {
				"thousand",
				"million",
				"billion",
				"trillion",
				"quadrillion",
				"quintillion"
			};

			// Keep track of the numerical place-value of the current -illion.
			// This is used for the calculations in the loop.
			int64_t current_illion = std::pow(1000, ILLION_COUNT);
			// Test each of the possible -illions...
			for (int i = ILLION_COUNT - 1; i > -1; i--) {
				// If this -illion group has any non-zero digits, print it.
				if (copy / current_illion) {
					printHundred(out, copy / current_illion);
					out << ' ' << ILLIONS[i] << ' ';
				}

				// Remove these digits and go down one -illion.
				copy %= current_illion;
				current_illion /= 1000;
			}

			// If there are more digits or nothing was printed yet,
			// print the hundreds, tens, and ones values.
			if (copy) {
				printHundred(out, copy);
				out << ' ';
			}

			// Finally, print the word "dollar",
			// making it plural if there are multiple dollars.
			out << "dollar";
			if (this->amount != 1 && this->amount != -1)
				out << 's';
		}
};

int main(int argc, char* argv[]) {
	if (argc < 2) {
		// Print a message and quit if no amounts were supplied.
		std::cout
			<< "Supply the amount(s) as argument(s).\n"
			<< "Do not include the dollar signs.\n"
			<< "There is unfortunately no proper error handling\n"
			<< "Extremely large numbers will not be parsed correctly.\n";
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		// Parse the number.
		int64_t amount = strtoll(argv[i], NULL, 10);

		// Display the amount in base-10 form for reference,
		// mostly in case the input value overflowed.
		std::cout << '$' << amount << " is ";

		// Actually describe the amount.
		Numbers(amount).print(std::cout);
		std::cout << '\n';
	}

	return 0;
}
