#include <iostream>
#include <string>

std::string formatYear(int year) {
	if (year > 0)
		return std::to_string(year);
	else
		return std::to_string(-year + 1) + " BC";
}

class Car {
	// The car's full year number (2024, not 24).
	int yearModel;
	// The make of the car.
	std::string make;

	// The speed of the car in some mysterious unspecified unit.
	unsigned int speed;

	public:
		inline unsigned int getSpeed() { return this->speed; }
		inline std::string getMake() { return this->make; }
		inline int getYearModel() { return this->yearModel; }

		// Accelerate the car by 5 unspecified speed units.
		inline void accelerate() { this->speed += 5; }
		// Slow the car down by 5 unspecified speed units.
		// This function stops at zero and does not go any farther.
		inline void brake() {
			if (this->speed > 5)
				this->speed -= 5;
			else
				this->speed = 0;
		}

		inline Car(int yearModel, std::string make):
			yearModel(yearModel),
			make(make),
			speed(0) {};
};

int main() {
	// Flintstones reference.
	Car car = Car(-9999, "Canopysaurus");

	// First, display the make and model and go down two lines.
	std::cout << "- " << formatYear(car.getYearModel()) << ' ' << car.getMake() << " -\n" << std::endl;

	// Accelerate and display the speed while doing so.
	for (int i = 0; i < 5; i++) {
		std::cout << "Speed: " << car.getSpeed() << " \\ Accelerating!" << std::endl;
		car.accelerate();
	}

	// Brake and display the speed while doing so.
	while (car.getSpeed()) {
		std::cout << "Speed: " << car.getSpeed() << " / Braking!" << std::endl;
		car.brake();
	}

	// Display the speed one last time for the satisfaction of reaching zero.
	std::cout << "Speed: " << car.getSpeed() << std::endl;
}
