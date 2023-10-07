#include "menu.h"

void Menu::StartInformation(void) {
	std::cout << "________________________" << std::endl;
	std::cout << "The second lab" << std::endl;
	std::cout << "Created by student of 404th group Sukhoverikov Denis" << std::endl;
	std::cout << "________________________" << std::endl;
	std::cout << "Variant 6" << std::endl;
	std::cout << "________________________" << std::endl;
	std::cout << "Inverse square matrices calculation." << std::endl;
	std::cout << "________________________" << std::endl;
}

Answer Menu::ModularTestsAsk(void) {
	std::cout << "Do you want to perform tests?" << std::endl;
	std::cout << "1 - Yes / 0 - No: ";
	return Ask();
}

InputType Menu::InputAsk(void) {
	std::cout << "What type of input you would like to use?" << std::endl;
	std::cout << "1 - Input from file / 0 - Manual input: ";
	InputType choice = static_cast<InputType>(GetInput<int>());
	while (!isInputTypeCorrect(choice)) {
		choice = static_cast<InputType>(GetInput<int>());
	}
	return choice;
}

Answer Menu::SaveInputAsk(void) {
	std::cout << "Do you want to save input data in file?" << std::endl;
	std::cout << "1 - Yes / 0 - No: ";
	return Ask();
}

Answer Menu::OutputFileAsk(void) {
	std::cout << "Do you want to save output data in file?" << std::endl;
	std::cout << "1 - Yes / 0 - No: ";
	return Ask();
}

Answer Menu::RewriteAsk(void) {
	std::cout << "Do you want to rewrite file?" << std::endl;
	std::cout << "1 - Yes / 0 - No: ";
	return Ask();
}

Answer Menu::RepeatAsk(void) {
	std::cout << "Do you want to exit the program?" << std::endl;
	std::cout << "1 - Yes / 0 - No: ";
	return Ask();
}

Answer Menu::Ask(void) {
	Answer choice = static_cast<Answer>(GetInput<int>());
	while (!isAnswerCorrect(choice)) {
		choice = static_cast<Answer>(GetInput<int>());
	}
	return choice;
}

bool Menu::isAnswerCorrect(Answer input) {
	if ((input == Answer::NO) || (input == Answer::YES)) {
		return true;
	} else {
		std::cout << "Incorrect input!" << std::endl << "1 - Yes / 0 - No: ";
		return false;
	}
}

bool Menu::isInputTypeCorrect(InputType input) {
	if ((input == InputType::MANUAL) || (input == InputType::FILE)) {
		return true;
	} else {
		std::cout << "Incorrect input!" << std::endl << "1 — Input from file / 0 — Manual input: ";
		return false;
	}
}