#pragma once
#include <map>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>


struct Attributes
{
	std::map<std::string, std::string> inventory;
	std::map<std::string, std::string> globalItems;
};

class SaveFileHandler
{
public:
	SaveFileHandler(std::string path, std::string name);
	~SaveFileHandler();

	void load();
	void save();
	void add(short choice, std::string attr, std::string value);
	void del(short choice, std::string attr);
	void edit(short choice, std::string attr, std::string value);
	std::string getElement(short choice, std::string attr);

private:
	Attributes _attributes;
	std::string _fileName;
	std::string _path;

	bool strToBool(std::string str);
};

