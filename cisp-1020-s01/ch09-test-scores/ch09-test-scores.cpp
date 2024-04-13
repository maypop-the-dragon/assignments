// ch9-test-scores.cpp by Blaine between 2024-02-06 and 2024-02-07
//
// It prompts you for a number of test scores, has you enter that many test
// scores, then displays the scores in ascending order as well as their average
// with the lowest score being dropped. If you enter an invalid value, it exits.
//
// The instructions say to "use pointer notation rather than array notation
// whenever possible," and I did just that. Unfortunately, that means that this
// code is probably harder to maintain because of it. Not that it matters.
// I have officially used malloc() now. It's actually easier than I expected.
// It's good to learn something new!
//
// I realized after writing this that my calculations would have been slightly
// more efficient if I had stored the start and end addresses rather than the
// base address and length.
// I'll probably follow your advice more in the future.
//
// I used G++ as my compiler so I hope it also works on Visual Studio. :P

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>

// Attempt to read an integer within a certain range from std::cin
// and crash the program if the value is invalid.
inline int readIntegerOrExit(int minimum, int maximum) {
	int parsed_input = 0;

	try {
		// Read a line of input.
		std::string unparsed_input;
		std::getline(std::cin, unparsed_input);

		// Attempt to parse it. (After using Option and Result in Rust, this
		// feels bad, and it is, but I guess this is how things are done.)
		int parsed_input = std::stoi(unparsed_input);

		// Exit if it's outside the correct range.
		if (parsed_input < minimum || parsed_input > maximum) {
			std::cerr << "That's out of range!\n";
			exit(2);
		}

		// If we have not exited, the value is valid.
		return parsed_input;
	} catch (...) {
		// Exit if it was not a valid integer.
		std::cerr << "That's not a valid integer!\n";
		exit(1);
	}
}

// Prompt the user for test scores, stores them in memory,
// and return the length and base address of that list.
//
// I used a tuple because, coming from Rust, I don't like creating an entire new
// type with a name and everything just to return it from one function, and I
// used uint8_t for the scores because it's easy and memory-efficient.
inline std::tuple<int, uint8_t*> readScoresOrExit() {
	std::cout
		<< "Enter the number of test scores.\n"
		<< "This must be between 1 and 250.\n"
		<< "> " << std::flush;
	int length = readIntegerOrExit(1, 250);

	std::cout
		<< "\nEnter all " << length << " test scores.\n"
		<< "Scores are usually between 0 and 100,\n"
		<< "but are allowed to go up to 200 for \"extra credit.\"\n";

	uint8_t *base_address = (uint8_t*)malloc(length);

	for (int i = 0; i < length; ++i) {
		std::cout << "> " << std::flush;
		*(base_address + i) = readIntegerOrExit(0, 200);
	}

	return std::make_tuple(length, base_address);
}

// Sort the scores with bubble sort, because I'm too tired to think hard.
// If this program were updated, this could be a good second step.
// A good first step would probably just be to switch to
// using array notation rather than pointer notation.
inline void bubbleSortScores(int length, uint8_t* base_address) {
	for (int i = 0; i < length - 1; ++i) {
		bool swapped = false;

		for (uint8_t *j = base_address; j < base_address + length - i - 1; ++j)
			if (*j > *(j + 1)) {
				uint8_t old_j = *j;
				*j = *(j + 1);
				*(j + 1) = old_j;

				swapped = true;
			}

		if (!swapped)
			break;
	}
}

// Average the scores in a list, dropping a certain number of the lowest ones.
// I know you had an entire talk about using the appropriate types for the job
// and specifically mentioned doubles, but this allocates maybe three doubles
// so I think it's fine, plus I want the precision in this case.
inline double averageScores(int length, uint8_t* base_address, int drop_count = 0) {
	double total = 0.0;

	for (int i = drop_count; i < length; ++i)
		total += (double)*(base_address + i);

	return total / (double)length;
}

int main() {
	int length = 0;
	uint8_t *base_address = 0;
	// Execute the score-reader-routine-inator.
	std::tie(length, base_address) = readScoresOrExit();

	// If this was an absurdly slow computer, printing this heading first would
	// let the user know what the program is doing before it finishes doing it.
	// I used `std::endl` specifically so that this would definitely be
	// displayed rather than buffered.
	std::cout << "\n- Sorted Scores -" << std::endl;

	// Sort the scores in ascending order.
	bubbleSortScores(length, base_address);

	// Now display the scores.
	std::cout << std::right;
	for (int i = 0; i < length; ++i)
		std::cout << std::setw(3) << (int)*(base_address + i) << '\n';

	std::cout
		<< "\nAverage (Lowest Dropped): " << std::flush
		<< std::setprecision(4) << averageScores(length, base_address, 1)
		<< std::endl;

	return 0;
}

