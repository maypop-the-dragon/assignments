#include <iostream>
#include <optional>
#include <string>
#include "./ch17-dynamic-stack.h"

inline void printItem(const std::string& item) {
	std::cout << "+ " << item << '\n';
}

int main() {
	std::cout
		<< "Welcome to my dynamic string stack REPL!\n"
		<< "You may use the following commands:\n"
		<< "? pop\n"
		<< "  Pop a line from the stack and display it.\n"
		<< "? push ...\n"
		<< "  Push a line of text onto the stack.\n"
		<< "? show\n"
		<< "  Display the entire stack from top to bottom.\n"
		<< "Use Ctrl+C to terminate the program!\n" << std::endl;

	Stack<std::string> stack;

	while (true) {
		std::string command;

		std::cout << "? ";
		std::getline(std::cin, command);

		if (command == "show") {
			stack.forEach(printItem);
		} else if (command.rfind("push ", 0) == 0) {
			stack.push(command.substr(5));
		} else if (command == "pop") {
			std::optional<std::string> possible_value = stack.pop();

			if (possible_value.has_value())
				std::cout << "- " << possible_value.value() << '\n';
			else
				std::cout << "! The stack was already empty.\n";
		} else if (command == "push") {
			// This is a special case for when you didn't write a space.
			stack.push("");
		} else if (command == "backdoor") {
			std::cout
				<< "! That's not a valid command,\n"
				<< "  and I'm calling the cops on you.\n";
		} else {
			std::cout << "! That's not a valid command.\n";
		}
	}
}
