#pragma once
#include <vector>
#include <iostream>
class Tests {
public:
	Tests();
	~Tests();

	void MakeTests();

private:
	std::vector<std::vector<std::vector<double>>> testingData;
};