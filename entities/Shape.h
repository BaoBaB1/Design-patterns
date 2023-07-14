#pragma once

#include "Entity.h"
#include "creational.h"
#include <iostream>

#define PI 3.14159265358979323846

namespace visitor {
	class IShapeVisitor;
}

class Shape : public Entity, public prototype::IClonable<Shape> {
public:
	virtual float area() const = 0;
	virtual void visit(visitor::IShapeVisitor*) const = 0;
	virtual void draw() const = 0;
	virtual ~Shape() = default;
};

class Circle : public Shape {
public:
	Circle() : m_radius(1.f) {}
	Circle(float radius) : m_radius(radius) {}
	std::string me() const override { return "Circle"; }
	void draw() const override { std::cout << "Drawing circle\n"; }
	float area() const override { return static_cast<float>(PI * m_radius * m_radius); }
	Circle* clone() const override { return new Circle(*this); }
	float radius() const { return m_radius; }
	void visit(visitor::IShapeVisitor*) const override;
private:
	float m_radius;
};

class Square : public Shape {
public:
	Square() : m_side(1.f) {}
	Square(float side) : m_side(side) {}
	std::string me() const override { return "Square"; }
	void draw() const override { std::cout << "Drawing square\n"; }
	float area() const override { return m_side * m_side; }
	Square* clone() const override { return new Square(*this); }
	void visit(visitor::IShapeVisitor*) const override;
private:
	float m_side;
};

