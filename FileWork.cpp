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

std::vector<size_t> FileWork::Input() {
	std::vector<size_t> result;
	std::ifstream file;
	file.open(path);
	std::string row;
	if (file.is_open()) {
		for (int i = 0; i <= 1; i++) { // need only 2 params, so only 2 iterations
			row = "";
			getline(file, row, ';');
			int value = std::stoi(row);
			if (value <= 0) {
				throw "Error";
			}
			result.push_back(static_cast<size_t>(value));
		}
	} else {
		std::cout << "Can`t access the file.";
		throw "Error";
	}
	if (result[0] > result[1]) {
		throw "Error";
	}
	file.close();
	return result;
}

void FileWork::OutputSave(void(*function)(std::vector<int>, std::vector<double>, std::ostream &), std::vector<int> x, std::vector<double> y1, std::vector<double> y2) {
	std::ofstream file;
	file.open(path);
	file << "Chart for Left matrix:" << std::endl << std::endl;
	function(x, y1, file);
	file << std::endl << "Chart for Right matrix:" << std::endl << std::endl;
	function(x, y2, file);
	file.close();
}

void FileWork::InputSave(size_t left, size_t right) {
	std::ofstream file;
	file.open(path);
	file << left << ";" << right << std::endl;
	file.close();
}

void FileWork::Rename(std::string newPath) {
	path = newPath;
}