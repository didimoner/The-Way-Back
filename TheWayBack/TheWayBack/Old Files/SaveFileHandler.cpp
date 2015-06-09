#include "SaveFileHandler.h"

SaveFileHandler::SaveFileHandler(std::string path, std::string name)
{
	_path = path;
	_fileName = name;
}


SaveFileHandler::~SaveFileHandler()
{
}

void SaveFileHandler::load()
{
	std::ifstream iFile;

	iFile.open(_path + _fileName + ".tws");

	if (!iFile)
	{
		std::ofstream oFile;
		oFile.open(_path + _fileName + ".tws", std::ios_base::out);
		oFile.close();

		if (!oFile)
			std::cout << "Can not open file: " << _path + _fileName + ".twr" << std::endl;
	}
	else
	{
		std::string data;

		std::string tempAttr;
		std::string tempValue;
		std::string switcher = "";
		bool selector = 0;

		bool readyFirst = false;
		bool readySecond = false;

		while (!iFile.eof())
		{
			iFile >> data;

			if (data == "-")
			{
				iFile >> data;
				switcher = data;
				continue;
			}
			if (data == "=")
			{
				selector = 1;
				iFile >> data;
			}
			else
			{
				selector = 0;
			}
			
			if (selector)
			{
				tempValue = data;
				readySecond = true;
			}
			else
			{
				tempAttr = data;
				readyFirst = true;
			}

			if (readyFirst && readySecond)
			{
				if (switcher == "inventory")
				{
					_attributes.inventory[tempAttr] = tempValue;
				}
				else if (switcher == "globalItems")
				{
					_attributes.globalItems[tempAttr] = tempValue;
				}

				readyFirst = false;
				readySecond = false;
			}
		}

		iFile.close();
	}

	// ------------------

	//std::cout << std::endl;

	//std::cout << "inventory size: " << _attributes.inventory.size() << std::endl;
	//std::cout << "globalItems size: " << _attributes.globalItems.size() << std::endl;

	//std::cout << "-" << " " << "inventory" << std::endl;
	//for (std::map<std::string, std::string>::iterator it = _attributes.inventory.begin(); it != _attributes.inventory.end(); ++it)
	//{
	//	std::cout << it->first << " = " << it->second << std::endl;
	//}

	//std::cout << "-" << " " << "globalItems" << std::endl;
	//for (std::map<std::string, std::string>::iterator it = _attributes.globalItems.begin(); it != _attributes.globalItems.end(); ++it)
	//{
	//	std::cout << it->first << " = " << it->second << std::endl;
	//}
}

void SaveFileHandler::save()
{
	std::ofstream oFile;

	oFile.open(_path + _fileName + ".tws");

	if (!oFile)
	{
		oFile.open(_path + _fileName + ".tws", std::ios_base::out);
		oFile.close();

		if (!oFile)
			std::cout << "Can not open file: " << _path + _fileName + ".twr" << std::endl;
	}
	else
	{
		oFile << "-" << " " << "inventory" << std::endl;
		for (std::map<std::string, std::string>::iterator it = _attributes.inventory.begin(); it != _attributes.inventory.end(); ++it)
		{
			oFile << it->first << " = " << it->second << std::endl;
		}

		oFile << "-" << " " << "globalItems" << std::endl;
		for (std::map<std::string, std::string>::iterator it = _attributes.globalItems.begin(); it != _attributes.globalItems.end(); ++it)
		{
			oFile << it->first << " = " << it->second << std::endl;
		}
	}

	oFile.close();
}

void SaveFileHandler::add(short choice, std::string attr, std::string value)
{
	switch (choice)
	{
	case 1:
		_attributes.inventory[attr] = value;
		break;
	case 2:
		_attributes.globalItems[attr] = value;
		break;
	default:
		break;
	}
}

void SaveFileHandler::del(short choice, std::string attr)
{
	switch (choice)
	{
	case 1:
		_attributes.inventory.erase(attr);
		break;
	case 2:
		_attributes.globalItems.erase(attr);
		break;
	default:
		break;
	}
}

void SaveFileHandler::edit(short choice, std::string attr, std::string value)
{
	switch (choice)
	{
	case 1:
		_attributes.inventory[attr] = value;
		break;
	case 2:
		_attributes.globalItems[attr] = value;
		break;
	default:
		break;
	}
}

std::string SaveFileHandler::getElement(short choice, std::string attr)
{
	std::map<std::string, std::string>::const_iterator it_i = _attributes.inventory.find(attr);
	std::map<std::string, std::string>::const_iterator it_g = _attributes.globalItems.find(attr);

	switch (choice)
	{
	case 1:
		if (it_i == _attributes.inventory.end())
			return "0";
		else
			return _attributes.inventory[attr];
	case 2:
		if (it_g == _attributes.globalItems.end())
			return "0";
		else
			return _attributes.globalItems[attr];
	default:
		break;
	}

	return 0;
}

bool SaveFileHandler::strToBool(std::string str)
{
	if (str == "1" || str == "true" || str == "TRUE")
	{
		return true;
	}

	return false;
}