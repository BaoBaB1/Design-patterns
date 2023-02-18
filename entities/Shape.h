#pragma once

#include <iostream>
#include <string>

class Shape {
public:
	virtual ~Shape() {}
	virtual void render() = 0;
	std::string state() { return m_state; }
protected:
	std::string m_state;
};

class Circle : public Shape {
public:
	void render() override { m_state = "Circle is rendering"; }
};

class Square : public Shape {
public:
	void render() override { m_state = "Square is rendering"; }
};