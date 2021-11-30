#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>

#include "FileSystem.h"

class GameObject
{
public:
	GameObject();

	// getters
	std::string getName(); // get the name of this object
	int getX(); // get x position
	int getY(); // get y position

	void setPosition(int x, int y); // set new position
	void Renderer(); // show current position of this object

	void Draw(); // draw this object drawing

protected:
	std::string m_name;
	int m_x;
	int m_y;

	std::string m_drawing; // string variable to store the drawing of this object
};
#endif // !GAMEOBJECT