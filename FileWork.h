#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <Windows.h>
#include <fstream>
#include <string>

class FileWork {
public:
	FileWork(std::string path);
	~FileWork();
	static bool NameForbidden(std::string path);
	static bool IsReadOnly(std::string path);
	std::vector<size_t> Input();
	void OutputSave(void(*function)(std::vector<int>, std::vector<double>, std::ostream &), std::vector<int> x, std::vector<double> y1, std::vector<double> y2);
	void InputSave(size_t left, size_t right);
	void Rename(std::string newPath);
private:
	std::string path;
};