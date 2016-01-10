#pragma once
#include "Entity.h"

class Item :
	public Entity
{
public:
	Item();
	Item(sf::Sprite sprite, std::string name, std::string id, std::string desc, std::string dependence);
	~Item();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	virtual sf::FloatRect getBounds();
	virtual void setPosition(sf::Vector2f position);

	std::string getName();
	std::string getId();
	std::string getDescription();
	sf::Sprite* getSprite();
	std::vector<std::string>* getDependence();
	bool getState();
	
	void setState(bool flag);
	void setScale(float x, float y);

private:
	void Item::parseDependence(std::string dependence);

	sf::Sprite _sprite;
	std::string _name;
	std::string _id;
	std::string _description;
	std::vector<std::string> _dependence;
	bool _state;
};

