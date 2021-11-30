#include "GameObject.h"

GameObject::GameObject()
{
	// prevent warning
	m_x = 0; // assign 0 initially
	m_y = 0;
}

std::string GameObject::getName()
{
	return m_name;
}

int GameObject::getX()
{
	return m_x;
}

int GameObject::getY()
{
	return m_y;
}

void GameObject::setPosition(int x, int y)
{
	m_x = x; // occupy the x position passed
	m_y = y; // occupy the y position passed
}

void GameObject::Renderer()
{
	// print to the screen the name and position (x, y) 
	std::cout << m_name << " current position is -> x: " << m_x << " y: " << m_y << "\n";
}

void GameObject::Draw()
{
	std::cout << "\n" << m_drawing; // print the drawing
}