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
	std::vector<std::string> Input();
	void Save(std::vector<std::string> data);
	void Rename(std::string newPath);
private:
	std::string path;
};