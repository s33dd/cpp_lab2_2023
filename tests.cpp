#include "tests.h"
#include "matrices.h"

bool IsUnit(const std::vector<std::vector<double>> &M);

void Tests::MakeTests() {
	const int testsQuantity = 5;
	int count = 0;

	for (int i = 0; i < testsQuantity; i++) {
		std::vector<std::vector<double>> inverted = GaussAlgoInverseMatrix(testingData[i]);
		std::vector<std::vector<double>> checkMatrix = MatricesMultiplication(testingData[i], inverted);
		if (IsUnit(checkMatrix)) {
			count++;
		}
		else {
			std::cout << std::endl << "Tests failed on " << i + 1 << " attempt" << std::endl;
			std::cout << "Obtained: " << std::endl << std::endl;
			PrintMatrix(checkMatrix);
			std::cout << "Expected: " << std::endl << std::endl;
			PrintMatrix(ReturnUnitMatrix(checkMatrix.size()));
		}
	}

	if (count == testsQuantity) {
		std::cout << "Tests passed" << std::endl;
	}
}

Tests::Tests() {
	std::vector<std::vector<double>> matrix;

	matrix = { { 1, 2 }, { 3, 4 }};
	testingData.push_back(matrix);

	matrix = { { 3, 2 }, { 4, 4 } };
	testingData.push_back(matrix);

	matrix = { { 3, 2, 1 }, { 4, 4, 2 }, { 1, 1, 4} };
	testingData.push_back(matrix);

	matrix = { { 5, 2 }, { 4, 5 } };
	testingData.push_back(matrix);

	matrix = { { 4, 3 }, { 2, 1 } };
	testingData.push_back(matrix);
}

Tests::~Tests() {}

bool IsUnit(const std::vector<std::vector<double>> &M) {
	for (int i = 0; i < M.size(); i++) {
		for (int j = 0; j < M[0].size(); j++) {
			if (i == j) {
				if (round(M[i][j]) != 1.0) {
					return false;
				}
			} else {
				if (round(M[i][j]) != 0.0) {
					return false;
				}
			}
		}
	}
	return true;
}