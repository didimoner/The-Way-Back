#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "tinyxml\tinyxml2.h"
#include "Item.h"

struct SaveElement 
{
	char* name;
	std::map<std::string, std::string> attributes;
	std::pair<std::string, std::string> attrForSearch;
};

class SaveFileHandler
{
public:
	SaveFileHandler(char* path);
	~SaveFileHandler();

	void addElement(SaveElement parent, SaveElement child);
	bool deleteElement(char* parentElement, char* childElement, std::pair<std::string, std::string> search);
	std::string getElement(char* parentElement, char* childElement, std::pair<std::string, std::string> search, char* target);

private:
	bool save();

	char* _fileName;
	char* _path;
	const char* _charPath;
	tinyxml2::XMLElement* _pRootElement;
	tinyxml2::XMLDocument _document;
};

