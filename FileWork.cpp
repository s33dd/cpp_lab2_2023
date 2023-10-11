#include "FileWork.h"

FileWork::FileWork(std::string path) {
	this->path = path;
}

FileWork::~FileWork() {}

bool FileWork::NameForbidden(std::string path) {
	try {
		bool isNameNormal = false;
		isNameNormal = std::filesystem::is_regular_file(path);
	} catch (std::exception&) {
		std::cout << "Incorrect path!" << std::endl;
		return true;
	}
	return false;
}

bool FileWork::IsReadOnly(std::string path) {
	if (!std::filesystem::exists(path)) {
		return false;
	}
	DWORD attributes = GetFileAttributesA(path.c_str());
	if (attributes != INVALID_FILE_ATTRIBUTES) {
		bool isReadOnly = attributes & FILE_ATTRIBUTE_READONLY;
		return isReadOnly;
	} else {
		throw "Unexpected file error.";
	}
}

std::vector<std::string> FileWork::Input() {
	std::vector<std::string> result;
	std::ifstream file;
	file.open(path);
	std::string row;
	if (file.is_open()) {
		while (getline(file, row)) {
			result.push_back(row);
		}
	} else {
		std::cout << "Can`t access the file.";
	}
	file.close();
	return result;
}

void FileWork::Save(std::vector<std::string> data) {
	std::ofstream file;
	file.open(path);
	for (auto row : data) {
		file << row << std::endl;
	}
	file.close();
}

void FileWork::Rename(std::string newPath) {
	path = newPath;
}