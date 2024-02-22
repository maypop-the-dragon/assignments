// ch10-string-length.cpp by Blaine Hargett on 2024-02-13
//
// This program can count UTF-8 codepoints too. Try emojis or something!

#include <iostream>
#include <stdlib.h>

// This function counts the number of bytes in a C-string.
unsigned int count_bytes_in_string(const char* string) {
	// Start at index zero.
	unsigned int index = 0;

	// Increment the index until we encounter a null character.
	while (string[index])
		++index;

	// The index of the null character is the same as the number of
	// bytes in the string.
	return index;
}

// This function counts the number of UTF-8 codepoints in a C-string.
// If the string is invalid, it returns -(index + 1),
// where index is the index of the error.
signed int count_codepoints_in_string(const char* string, unsigned int byte_count) {
	unsigned int index = 0;
	signed int count = 0;

	// The conditions under which the function exits are complex,
	// so I just used break statements instead of a loop condition.
	while (true) {
		// If we have reached the end, return the computed count.
		// If the index is greater than the byte count, something has gone
		// horribly wrong, so I opted to let it loop forever in that case,
		// rather than silently returning a wrong answer.
		if (index == byte_count)
			return count;

		if (string[index] & 0b10000000) {
			// The uppermost bit is 1, so this should be a multi-byte codepoint.

			// Determine the length of this codepoint based on its first byte,
			// and use that to calculate the index after its last byte.
			// There might be a cleaner way to do this.
			unsigned int codepoint_end = 0;
			if ((string[index] & 0b11111000) == 0b11110000)
				codepoint_end = index + 4;
			else if ((string[index] & 0b11110000) == 0b11100000)
				codepoint_end = index + 3;
			else if ((string[index] & 0b11100000) == 0b11000000)
				codepoint_end = index + 2;
			else
				return -(signed int)index - 1; // Nothing else is valid.

			// Step through the remaining bytes to check for errors.
			for (++index; index < codepoint_end; ++index) {
				// If the string ends in the middle of this character
				// or the uppermost bits aren't 10,
				// that's an error!
				if (index == byte_count || (string[index] & 0b11000000) != 0b10000000)
					return -(signed int)index - 1;
			}
		} else
			// Otherwise, it's a basic ASCII character, so advance one byte.
			++index;

		// We have just advanced by one codepoint, so increase the count.
		++count;
	}
}

int main(int argc, char* argv[]) {
	// // This line is no longer necessary because the program no longer needs
	// // to directly read the string from standard input as I remembered that
	// // command-line arguments are a thing late into writing this.
	// //
	// // It was here to enable UTF-8 on Windows, though I am on Linux so cannot
	// // test if it works or not.
	// //
	// // You might still need to actually execute that command manually.
	// #ifdef WIN32
	// system("chcp 65001");
	// #endif

	// Exit with a helpful message if no strings were supplied.
	if (argc < 2) {
		std::cout
			<< "Pass any number of valid UTF-8 strings as arguments to this\n"
			<< "program to measure their length in bytes and codepoints! <3\n";
		return 0;
	}

	// Process all of the strings.
	int invalid_count = 0;
	for (unsigned int i = 1; i < argc; ++i) {
		std::cout << "String #" << i << '\n'
			<< "     Bytes:   " << std::flush;

		unsigned int byte_count = count_bytes_in_string(argv[i]);

		std::cout << byte_count << '\n'
			<< "  Codepoints: " << std::flush
			<< std::flush;

		int codepoint_count = count_codepoints_in_string(argv[i], byte_count);

		if (codepoint_count < 0)
			std::cout << "INVALID UTF-8 AT STRING[" << -(codepoint_count + 1) << "]\n\n";
		else
			std::cout << codepoint_count << "\n\n";
	}
}
