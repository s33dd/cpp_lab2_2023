#include "menu.h"
#include "FileWork.h"
#include "tests.h"
#include "matrices.h"

void ManualInput(size_t* a, size_t* b);
void DrawChart(std::vector<int> x, std::vector<double> y, std::ostream &stream);

int main() {
	size_t leftBorder = 0;
	size_t rightBorder = 0;

    Menu menu{};
    menu.StartInformation();
    bool isExit = false;
    if (menu.ModularTestsAsk() == Answer::YES) {
		Tests t = Tests();
		t.MakeTests();
    }
    while (!isExit) {
        bool isFileInput = false;

        switch (menu.InputAsk()) {
        case InputType::FILE: {
            isFileInput = true;
            std::string path;
            bool isErrors = true;
            while (isErrors) {
                std::cout << "Input the filename: ";
                getline(std::cin, path);
                if (std::filesystem::exists(path)) {
                    isErrors = false;
                } else {
                    std::cout << "File doesn`t exist." << std::endl;
                }
            }
            FileWork inputFile{ path };\
			try {
				std::vector<size_t> input = inputFile.Input();
				leftBorder = input[0];
				rightBorder = input[1];
			}
			catch (...) {
				std::cout << std::endl << "There is error in values. Check if it is correct and in right format:" << std::endl;
				std::cout << "file: leftBorder;rightBorder" << std::endl;
				std::cout << "Make sure that left value is lower than right and both of them greater than zero." << std::endl << std::endl;
				continue;
			}
            break;
        }
        case InputType::MANUAL: {
			ManualInput(&leftBorder, &rightBorder);
            break;
        }
        }

        //Make work
		std::vector<int> x;
		std::vector<double> leftMatrixNorms;
		std::vector<double> rightMatrixNorms;
		for (size_t i = leftBorder; i <= rightBorder; i++) {
			x.push_back(static_cast<int>(i));

			std::vector<std::vector<double>> hilbert = ReturnHilbertMatrix(i);
			std::vector<std::vector<double>> left = ReturnLeftMatrix(hilbert);
			std::vector<std::vector<double>> right = ReturnRightMatrix(hilbert);
			
			double leftNorm = MatrixRowsNorm(left);
			double rightNorm = MatrixRowsNorm(right);

			leftMatrixNorms.push_back(leftNorm);
			rightMatrixNorms.push_back(rightNorm);
		}

		std::cout << "Chart for Left matrix:" << std::endl << std::endl;
		DrawChart(x, leftMatrixNorms, std::cout);
		std::cout << std::endl << "Chart for Right matrix:" << std::endl << std::endl;
		DrawChart(x, rightMatrixNorms, std::cout);
		

        //Ask about saves
        bool isInputSave = false;
        if (!isFileInput) {
            switch (menu.SaveInputAsk()) {
            case Answer::YES:
                isInputSave = true;
                break;
            case Answer::NO:
                break;
            }
        }
        if (isInputSave) {
            std::string path;
            bool isErrors = true;
            bool rewriteFlag = false;
            while (isErrors) {
                std::cout << "Input the filename: ";
                getline(std::cin, path);
                if (FileWork::NameForbidden(path)) {
                    std::cout << "Invalid filename." << std::endl;
                    continue;
                }
                if (std::filesystem::exists(path)) {
                    switch (menu.RewriteAsk()) {
                    case Answer::NO:
                        rewriteFlag = false;
                        break;
                    case Answer::YES:
                        rewriteFlag = true;
                        break;
                    }
                }
                if (std::filesystem::exists(path) and rewriteFlag == false) {
                    continue;
                }
                if (rewriteFlag == true and FileWork::IsReadOnly(path)) {
                    std::cout << "The file is readonly." << std::endl;
                    continue;
                }
                isErrors = false;
            }
            FileWork inputSaveFile{ path };
			inputSaveFile.InputSave(leftBorder, rightBorder);
        }

        switch (menu.OutputFileAsk()) {
        case Answer::NO:
            break;
        case Answer::YES: {
            std::string path;
            bool isErrors = true;
            bool rewriteFlag = false;
            while (isErrors) {
                std::cout << "Input the filename: ";
                getline(std::cin, path);
                if (FileWork::NameForbidden(path)) {
                    std::cout << "Invalid filename." << std::endl;
                    continue;
                }
                if (std::filesystem::exists(path)) {
                    switch (menu.RewriteAsk()) {
                    case Answer::NO:
                        rewriteFlag = false;
                        break;
                    case Answer::YES:
                        rewriteFlag = true;
                        break;
                    }
                }
                if (std::filesystem::exists(path) and rewriteFlag == false) {
                    continue;
                }
                if (rewriteFlag == true and FileWork::IsReadOnly(path)) {
                    std::cout << "The file is readonly." << std::endl;
                    continue;
                }
                isErrors = false;
            }
            FileWork outputSaveFile{ path };
			outputSaveFile.OutputSave(*DrawChart, x, leftMatrixNorms, rightMatrixNorms);
        }
        }

        if (menu.RepeatAsk() == Answer::YES) {
            isExit = true;
        } else {
            isExit = false;
        }
    }
}

void ManualInput(size_t* a, size_t* b) {
	bool isErrors = true;
	int input;
	while (isErrors) {
		std::cout << std::endl << "Enter left border (matrix dimension): ";
		input = Menu::GetInput<int>();
		if (input <= 0) {
			isErrors = true;
			std::cout << "Dimension can`t be less or equal zero";
		} else {
			isErrors = false;
		}
	}
	*a = static_cast<size_t>(input);
	isErrors = true;
	while (isErrors) {
		std::cout << std::endl << "Enter right border (matrix dimension): ";
		input = Menu::GetInput<int>();
		if (input <= 0) {
			isErrors = true;
			std::cout << std::endl << "Dimension can`t be less or equal zero";
		} else {
			if (input <= *a) {
				std::cout << std::endl << "Right border can`t be lower or equal left border";
			} else {
				isErrors = false;
			}
		}
	}
	*b = static_cast<size_t>(input);
}
void DrawChart(std::vector<int> x, std::vector<double> y, std::ostream &stream) {
	std::map<int, double> tableValues;
	size_t maxYValueSize = 0;
	size_t maxXValueSize = 0;

	for (int i = 0; i < x.size(); i++) {
		tableValues[x[i]] = y[i];
		std::stringstream ss;
		ss << std::scientific << y[i];
		if (ss.str().size() > maxYValueSize) {
			maxYValueSize = ss.str().size();
		}
		if (std::to_string(x[i]).size() > maxXValueSize) {
			maxXValueSize = std::to_string(x[i]).size();
		}
	}

	std::sort(x.begin(), x.end());
	std::sort(y.begin(), y.end(), std::greater<double>());
	y.erase(std::unique(y.begin(), y.end()), y.end());

	std::vector<std::vector<std::string>> table;

	for (int i = 0; i < y.size(); i++) {
		std::vector<std::string> row;
		std::stringstream ss;
		ss << std::scientific << y[i];
		std::string value = ss.str();
		std::string filler = "";

		filler.resize((maxYValueSize - value.size()), ' ');
		value.insert(0, filler);
		value += "|";
		row.push_back(value);

		for (int j = 0; j < x.size(); j++) {
			std::string mark = "*";
			filler = "";
			if (tableValues[x[j]] == y[i]) {
				filler.resize(maxXValueSize, ' ');
				mark.insert(0, filler);
				row.push_back(mark);
			} else {
				filler.resize(maxXValueSize + 1,' ');
				row.push_back(filler);
			}
		}
		table.push_back(row);
	}

	std::vector<std::string> row;
	std::string str = "";
	str.resize(maxYValueSize + 1, ' ');
	row.push_back(str);
	for (int i = 0; i < x.size(); i++) {
		std::string xValue = std::to_string(x[i]);
		std::string filler = "";
		filler.resize(maxXValueSize - xValue.size() + 1, ' ');
		xValue.insert(0, filler);
		row.push_back(xValue);
	}
	table.push_back(row);

	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[0].size(); j++) {
			stream << table[i][j];
		}
		stream << std::endl;
	}
}