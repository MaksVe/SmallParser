#include <iostream>
#include <fstream>
#include <sstream>

bool fileExists(std::string fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

int main()
{
	// Prompt for the file
	std::string fileName;
	std::fstream file;

	std::cout << "Please enter the file name (in the current directory): ";
	std::getline(std::cin, fileName);

	bool goodToGo = fileExists(fileName);
	while(!goodToGo)
	{
		std::cerr << "File doesn't not exist. Try again: ";
		std::getline(std::cin, fileName);
		goodToGo = fileExists(fileName);
	}

	// Prompt for the key
	std::string domain;
	std::cout << "Please enter the key you want to parse: ";
	std::getline(std::cin, domain);

	int counter = 0;

	std::fstream out;
	std::fstream temp;

	temp.open("temp.txt", std::fstream::out);
	out.open("out.txt", std::fstream::out);

	std::string line;

	file.open(fileName.c_str());

	// Copy the line with the key to the new file and remove this line from the old one
	while (getline(file, line))
	{
		if (line.find(domain) != std::string::npos)
		{
			counter++;
			std::cout << counter << " : " << line << std::endl;
			out << line;
			line.replace(0, line.length(), "");
		}
		else
			temp << line << std::endl;
	}

	remove(fileName.c_str());
	rename("temp.txt", fileName.c_str());

	return 0;
}

