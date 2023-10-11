#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <map>
#include "menu.h"
#include "FileWork.h"

void ManualInput(size_t* a, size_t* b);
std::vector<std::vector<double>> MatricesMultiplication(const std::vector<std::vector<double>> &firstMatrix, const std::vector<std::vector<double>> &secondMatrix);
std::vector<std::vector<double>> GaussAlgoInverseMatrix(const std::vector<std::vector<double>> &A);
std::vector<std::vector<double>> ReturnUnitMatrix(size_t size);
std::vector<std::vector<double>> ReturnHilbertMatrix(size_t size);
std::vector<std::vector<double>> ReturnLeftMatrix(const std::vector<std::vector<double>>& H);
std::vector<std::vector<double>> ReturnRightMatrix(const std::vector<std::vector<double>>& H);
double MatrixRowsNorm(const std::vector<std::vector<double>> &M);
void PrintMatrix(const std::vector<std::vector<double>> &M);
void DrawChart(std::vector<int> x, std::vector<double> y);

int main() {
	size_t leftBorder = 0;
	size_t rightBorder = 0;

    Menu menu{};
    menu.StartInformation();
    bool isExit = false;
    if (menu.ModularTestsAsk() == Answer::YES) {
        //Add tests
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
            FileWork inputFile{ path };
            //Add input
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
		DrawChart(x, leftMatrixNorms);
		std::cout << std::endl << "Chart for Right matrix:" << std::endl << std::endl;
		DrawChart(x, rightMatrixNorms);
		

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
            //Add input saving
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
            //Add output saving
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

std::vector<std::vector<double>> MatricesMultiplication(const std::vector<std::vector<double>> &firstMatrix, const std::vector<std::vector<double>> &secondMatrix) {
	std::vector<std::vector<double>> result;
	for (int i = 0; i < firstMatrix.size(); i++) { // rows
		std::vector<double> empty;
		result.push_back(empty);
		for (int j = 0; j < secondMatrix[0].size(); j++) { //columns
			result[i].push_back(0);
			for (int k = 0; k < secondMatrix.size(); k++) {
				result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}
	return result;
}

std::vector<std::vector<double>> GaussAlgoInverseMatrix(const std::vector<std::vector<double>> &A) {
	std::vector<std::vector<double>> enteredMatrix = A;
	std::vector<std::vector<double>> result = ReturnUnitMatrix(enteredMatrix.size());
	for (int j = 0; j < enteredMatrix[0].size(); j++) { //column cycle
		double maxAbs = 0;
		int rowWithMaxAbs = 0;
		for (int i = j; i < enteredMatrix.size(); i++) {
			if (std::abs(enteredMatrix[i][j]) > maxAbs) {
				maxAbs = std::abs(enteredMatrix[i][j]);
				rowWithMaxAbs = i;
			}
		}
		if (maxAbs == 0) {
			//std::cout << "Entered matrix is singular and the inverse matrix can`t be calculated.";
			throw "Singular matrix";
		}
		//rows swap
		std::vector<double> tempRow = enteredMatrix[j];
		enteredMatrix[j] = enteredMatrix[rowWithMaxAbs];
		enteredMatrix[rowWithMaxAbs] = tempRow;
		tempRow = result[j];
		result[j] = result[rowWithMaxAbs];
		result[rowWithMaxAbs] = tempRow;

		//division of elements
		double divisor = enteredMatrix[j][j];
		for (int i = 0; i < enteredMatrix[j].size(); i++) {
			enteredMatrix[j][i] /= divisor;
			result[j][i] /= divisor;
		}

		//subtractions of elements
		for (int i = 0; i < enteredMatrix.size(); i++) {
			if (i == j) {
				continue;
			}
			double multiplier = enteredMatrix[i][j];
			for (int k = j; k < enteredMatrix[0].size(); k++) {
				enteredMatrix[i][k] -= multiplier * enteredMatrix[j][k];
			}
			for (int k = 0; k < enteredMatrix[0].size(); k++) {
				result[i][k] -= multiplier * result[j][k];
			}
		}
	}
	return result;
}

std::vector<std::vector<double>> ReturnUnitMatrix(size_t size) {
	std::vector<std::vector<double>> result;
	for (int i = 0; i < size; i++) {
		std::vector<double> empty;
		result.push_back(empty);
		for (int j = 0; j < size; j++) {
			if (i == j) {
				result[i].push_back(1);
			} else {
				result[i].push_back(0);
			}
		}
	}
	return (result);
}

std::vector<std::vector<double>> ReturnHilbertMatrix(size_t size) {
	std::vector<std::vector<double>> result;
	for (int i = 0; i < size; i++) {
		std::vector<double> empty;
		result.push_back(empty);
		for (int j = 0; j < size; j++) {
			double divisor = static_cast<double>((i + 1) + (j + 1) - 1);
			result[i].push_back(1.0 / divisor);
		}
	}
	return result;
}

std::vector<std::vector<double>> ReturnLeftMatrix(const std::vector<std::vector<double>>& H) {
	std::vector<std::vector<double>> invH = GaussAlgoInverseMatrix(H);
	std::vector<std::vector<double>> result = MatricesMultiplication(invH, H);
	std::vector<std::vector<double>> unit = ReturnUnitMatrix(H.size());
	for (int i = 0; i < H.size(); i++) {
		for (int j = 0; j < H[0].size(); j++) {
			result[i][j] -= unit[i][j];
		}
	}
	return result;
}

std::vector<std::vector<double>> ReturnRightMatrix(const std::vector<std::vector<double>>& H) {
	std::vector<std::vector<double>> invH = GaussAlgoInverseMatrix(H);
	std::vector<std::vector<double>> result = MatricesMultiplication(H, invH);
	std::vector<std::vector<double>> unit = ReturnUnitMatrix(H.size());
	for (int i = 0; i < H.size(); i++) {
		for (int j = 0; j < H[0].size(); j++) {
			result[i][j] -= unit[i][j];
		}
	}
	return result;
}

double MatrixRowsNorm(const std::vector<std::vector<double>>& M) {
	std::vector<double> eachRowSum;
	for (int i = 0; i < M.size(); i++) {
		double sum = 0;
		for (int j = 0; j < M[0].size(); j++) {
			sum += std::abs(M[i][j]);
		}
		eachRowSum.push_back(sum);
	}
	return *std::max_element(eachRowSum.begin(), eachRowSum.end());
}

void PrintMatrix(const std::vector<std::vector<double>> &M) {
	for (int i = 0; i < M.size(); i++) {
		for (int j = 0; j < M[0].size(); j++) {
			std::cout << (j == 0 ? "\n| " : "") << std::setw(10) << M[i][j] << (j == M[0].size() - 1 ? " |" : " ") << "\t";
		}
		std::cout << std::endl;
	}
}

void DrawChart(std::vector<int> x, std::vector<double> y) {
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
			std::cout << table[i][j];
		}
		std::cout << std::endl;
	}
}