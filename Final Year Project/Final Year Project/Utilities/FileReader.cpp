#include "FileReader.h"
#include <iostream>


FileReader::FileReader(const char * filepath, uint openMode)
{
	
	file.open(filepath, openMode);

}

void FileReader::Read(std::vector<std::vector <double>>& data)
{
	std::string line;
	std::string l;

	std::vector<double> dataFromFile;
	std::stringstream ss;
	if (file && file.is_open())
	{
		while (!file.eof())
		{
			std::getline(file, line);
			ss.clear();
			ss.str(line);
			dataFromFile.clear();

			while (!ss.eof())
			{
				double n;
				std::string temp;
				ss >> temp;
				
				if (std::istringstream(temp) >> n)
				{
					dataFromFile.push_back(n);
				}
			}

			data.push_back(dataFromFile);
		}

		
	}
}

void FileReader::Read(const char* lable, std::vector < std::vector < double >> &data, bool normalize)
{
	std::string line;
	std::string l;

	std::vector<double> dataFromFile;
	std::istringstream ss;
	bool open = file.is_open();
	if (file && open)
	{
		while (!file.eof())
		{
			std::getline(file, line);
			ss.clear();
			ss.str(line);

			ss >> l;

			dataFromFile.clear();

			if (l.compare(lable) == 0)
			{
				while (!ss.eof())
				{
					double n;
					ss >> n;
					ss >> std::ws;

					if (normalize)
					{
						n = (n - 0) / (10 - 0);
					}

					dataFromFile.push_back(n);
				}
				data.push_back(dataFromFile);
			}
		}
	}

	file.clear();
	file.seekg(0, std::fstream::basic_ios::beg);

}
