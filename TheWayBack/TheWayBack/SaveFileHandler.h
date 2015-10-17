#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "tinyxml\tinyxml2.h"
#include "Item.h"

class SaveFileHandler
{
public:
	SaveFileHandler(char* path);
	~SaveFileHandler();

	bool load();
	bool del(char* element, std::string  id);
	void inventoryItemChange(Item* item);
	void mapItemChange(Item* item, char* state);
	std::string getElement(char* element, std::string id, char* attr);

private:
	char* _fileName;
	char* _path;
	const char* _charPath;

	tinyxml2::XMLDocument _document;
	bool save();
};

