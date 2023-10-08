#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

std::vector<std::vector<double>> MatricesMultiplication(const std::vector<std::vector<double>>& firstMatrix, const std::vector<std::vector<double>>& secondMatrix);
std::vector<std::vector<double>> GaussAlgoInverseMatrix(const std::vector<std::vector<double>> &A);
std::vector<std::vector<double>> ReturnUnitMatrix(size_t size);
void PrintMatrix(const std::vector<std::vector<double>>& M);
int digitsQuantity(int number);

int main() {
	std::vector<std::vector<double>> test = { {1, 2}, {3, 4} };
	//std::vector<std::vector<double>> test2 = { {-2, 1}, {1.5, -0.5} };
	std::vector<std::vector<double>> inv = GaussAlgoInverseMatrix(test);
	std::cout << "Inverted:" << std::endl;
	PrintMatrix(inv);
	std::cout << "Check: (must be unit)" << std::endl;
	PrintMatrix(MatricesMultiplication(test, inv));
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


//Wrong algo, redo
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

void PrintMatrix(const std::vector<std::vector<double>> &M) {
	//std::vector<int> columnsLength;
	//for (int j = 0; j < M[0].size(); j++) {
	//	int length = 0;

	//	for (int i = 0; i < M.size(); i++) {
	//		int numLength = digitsQuantity(M[i][j]);
	//		if (numLength > length) {
	//			length = numLength;
	//		}
	//	}
	//	columnsLength.push_back(length);
	//}

	//for (int i = 0; i < M.size(); i++) {
	//	for (int j = 0; j < M[0].size(); j++) {
	//		std::cout << (j == 0 ? "\n| " : "") << std::setw(columnsLength[j]) << M[i][j] << (j == M[0].size() - 1 ? " |" : " ");
	//	}
	//}
	//std::cout << '\n';
	for (int i = 0; i < M.size(); i++) {
		for (int j = 0; j < M[0].size(); j++) {
			std::cout << (j == 0 ? "\n| " : "") << std::setw(8) << M[i][j] << (j == M[0].size() - 1 ? " |" : " ") << "\t";
		}
		std::cout << std::endl;
	}
}

int digitsQuantity(int number) {
	if (number / 10 == 0) {
		return 1;
	}
	return 1 + digitsQuantity(number / 10);
}