#include "matrices.h"

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

std::vector<std::vector<double>> ReturnLeftMatrix(const std::vector<std::vector<double>> &H) {
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

std::vector<std::vector<double>> ReturnRightMatrix(const std::vector<std::vector<double>> &H) {
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

double MatrixRowsNorm(const std::vector<std::vector<double>> &M) {
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