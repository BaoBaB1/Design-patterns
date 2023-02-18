#pragma once

#include "Vehicle.h"
#include "Shape.h"

class AbstractFactory {
public:
	virtual Vehicle* create_vehicle() = 0;
	virtual Shape* create_shape() = 0;
};

class ConcreteFactory : public AbstractFactory {
public:
	Vehicle* create_vehicle() override { return new Car(); }
	Shape* create_shape() override { return new Circle(); }
};

class ConcreteFactory2 : public AbstractFactory {
public:
	Vehicle* create_vehicle() override { return new Airplane(); }
	Shape* create_shape() override { return new Square(); }
};
