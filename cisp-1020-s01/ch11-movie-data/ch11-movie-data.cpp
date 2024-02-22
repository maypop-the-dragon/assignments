// ch11-movie-data.cpp by Blaine Hargett on 2024-02-19 through 20
//
// "Movie" barely looks like a real word at this point.
// It looks like it should be mohvie instead of moovie...

#include <iostream>
#include <string>

struct MovieData {
	// The movie's title. ASCII with no control codes.
	char const *title;
	// The director(s') name(s), separated by ", ". ASCII with no control codes.
	char const *director;
	// The movie's full release year (i.e. 2024, NOT just 24).
	int release_year;
	// The movie's running time in minutes.
	unsigned int runtime;
};

inline void printFunMarqueePart(
	bool& is_lit,

	char const* first_line_left,
	char const* subsequent_line_left,
	unsigned int left_width,

	char const* text,

	char const* right,
	unsigned int right_width
) {
	unsigned int index = 0;

	while (text[index] != 0) {
		if (is_lit)
			std::cout << "\x1B[93m\x1B[41m@\x1B[30m\x1B[107m";
		else
			std::cout << "\x1B[41m \x1B[30m\x1B[47m";

		if (index == 0)
			std::cout << first_line_left;
		else
			std::cout << subsequent_line_left;

		unsigned int character_count = left_width + right_width;
		while (character_count < 50 && text[index] != 0) {
			std::cout << text[index];
			character_count++;
			index++;
		}
		while (character_count < 50) {
			std::cout << ' ';
			character_count++;
		}

		std::cout << right;

		if (is_lit)
			std::cout << "\x1B[93m\x1B[41m@\x1B[0m\n";
		else
			std::cout << "\x1B[41m \x1B[0m\n";

		is_lit = !is_lit;
	}
}

// Print a fun "marquee" that describes the given movies.
void printFunMarquee(MovieData movies[], unsigned int length) {
	std::cout
		<< "\n\x1B[31m\x1B[1m"
		<< "                    NOW  SHOWING\n\x1B[93m\x1B[41m\x1B[22m"
		<< "@  @  @  @  @  @  @  @  @  @  @  @  @  @  @  @  @  @\x1B[0m\n";

	bool is_lit = false;

	unsigned int i = 0;
	while (true) {
		printFunMarqueePart(
			is_lit,
			" \x1B[1m", " \x1B[1m", 1,
			movies[i].title,
			"\x1B[22m ", 1
		);

		printFunMarqueePart(
			is_lit,
			"     directed by    \x1B[1m", "                    \x1B[1m", 20,
			movies[i].director,
			"\x1B[22m ", 1
		);

		{
			std::string runtime_text = std::to_string(movies[i].runtime / 60);
			runtime_text += ':';

			if (movies[i].runtime % 60 < 10)
				runtime_text += '0';
			runtime_text += std::to_string(movies[i].runtime % 60);

			printFunMarqueePart(
				is_lit,
				"     runtime        \x1B[1m", "                    \x1B[1m", 20,
				runtime_text.c_str(),
				"\x1B[22m ", 1
			);
		}

		printFunMarqueePart(
			is_lit,
			"     released       \x1B[1m", "                    \x1B[1m", 20,
			std::to_string(movies[i].release_year).c_str(),
			"\x1B[22m ", 1
		);

		i++;

		// Print an extra line if there is another movie after this
		// or if the last line would be lit otherwise.
		if (i < length || !is_lit) {
			printFunMarqueePart(
				is_lit,
				"", "", 0,
				" ",
				"", 0
			);
		}

		if (i >= length)
			break;
	}

	std::cout << "\x1B[93m\x1B[41m"
		<< "@  @  @  @  @  @  @  @  @  @  @  @  @  @  @  @  @  @\x1B[0m\n\n";
}

int main() {
	unsigned int MOVIE_COUNT = 2;
	MovieData movies[MOVIE_COUNT] = {
		{
			"Monty Python and the Holy Grail",
			"Terry Gillam, Terry Jones",
			1975,
			89
		},
		{
			"Night of the Day of the Dawn of the Son of the Bride of the Return of the Terror",
			"James Riffel",
			1991,
			96
		}
	};

	printFunMarquee(movies, MOVIE_COUNT);

	return 0;
}
