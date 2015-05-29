#pragma once
#include "Entity.h"

class Item :
	public Entity
{
public:
	Item();
	Item(sf::Sprite sprite, std::string name, std::string desc);
	~Item();

	virtual void update(float gameTime);
	virtual void draw(sf::RenderWindow &window);

	virtual sf::FloatRect getBounds();

	std::string getName();
	std::string getDescription();
	sf::Sprite* getSprite();
	void setVisible(bool flag);
	bool getState();

private:
	sf::Sprite _sprite;
	std::string _name;
	std::string _description;
	bool _isVisible;
};

