#pragma once

#include "Entity.h"
#include "creational.h"

#define PI 3.14159265358979323846

class Shape : public Entity, prototype::IClonable<Shape> {
public:
	virtual float area() const = 0;
};

class Circle : public Shape {
public:
	Circle() : m_radius(1.f) {}
	Circle(float radius) : m_radius(radius) {}
	std::string me() const override { return "Circle"; }
	float area() const override { return static_cast<float>(PI * m_radius * m_radius); }
	Circle* clone() const override { return new Circle(*this); }
	float radius() const { return m_radius; }
private:
	float m_radius;
};

class Square : public Shape {
public:
	Square() : m_side(1.f) {}
	Square(float side) : m_side(side) {}
	std::string me() const override { return "Square"; }
	float area() const override { return m_side * m_side; }
	Square* clone() const override { return new Square(*this); }
private:
	float m_side;
};

