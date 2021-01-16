#pragma once
#include <fstream>
#include <sstream>
#include "Helper.h"

class FileReader
{

public:

	FileReader(const char * filepath, uint openMode);

	void Read(std::vector<std::vector <double>> & data);
	void Read(const char* lable, std::vector<std::vector <double>>& data, bool normalize = false);

	bool isEof() { file.eof(); }; 

	void Close() { file.close(); };
	

private:

	std::fstream file;
};

