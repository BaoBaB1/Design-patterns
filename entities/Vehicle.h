#pragma once

#include <iostream>
#include <string>

class Vehicle {
public:
	enum VehicleType {
		Car,
		Airplane
	};
public:
	virtual ~Vehicle() {}
	virtual void move() = 0;
	std::string state() { return m_state; }
protected:
	std::string m_state;
};

class Car : public Vehicle {
public:
	void move() override { m_state = "Car is moving"; }
};

class Airplane : public Vehicle {
public:
	void move() override { m_state = "Airplane is moving"; }
};