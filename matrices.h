#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <map>

std::vector<std::vector<double>> MatricesMultiplication(const std::vector<std::vector<double>> &firstMatrix, const std::vector<std::vector<double>> &secondMatrix);
std::vector<std::vector<double>> GaussAlgoInverseMatrix(const std::vector<std::vector<double>> &A);
std::vector<std::vector<double>> ReturnUnitMatrix(size_t size);
std::vector<std::vector<double>> ReturnHilbertMatrix(size_t size);
std::vector<std::vector<double>> ReturnLeftMatrix(const std::vector<std::vector<double>> &H);
std::vector<std::vector<double>> ReturnRightMatrix(const std::vector<std::vector<double>> &H);
double MatrixRowsNorm(const std::vector<std::vector<double>> &M);
void PrintMatrix(const std::vector<std::vector<double>> &M);