#pragma once
#include <iostream>

enum class InputType {
	MANUAL = 0,
	FILE = 1,
};

enum class Answer {
	NO = 0,
	YES = 1
};

class Menu {
public:
	template <typename ElementType>
	static ElementType GetInput(void) {
		ElementType input;
		std::cin >> input;
		while (std::cin.fail()) {
			std::cout << "Incorrect input!" << std::endl << "Input: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> input;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl;
		return input;
	}

	void StartInformation(void);

	Answer ModularTestsAsk(void);

	InputType InputAsk(void);

	Answer SaveInputAsk(void);

	Answer OutputFileAsk(void);

	Answer RewriteAsk(void);

	Answer RepeatAsk(void);

	static Answer Ask(void);
private:
	static bool isAnswerCorrect(Answer input);

	bool isInputTypeCorrect(InputType input);
};