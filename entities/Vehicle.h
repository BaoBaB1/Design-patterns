#pragma once

#include "Entity.h"

class Vehicle : public Entity {
public:
	enum VehicleType {
		Car,
		Airplane
	};
public:
	float set_speed(float speed) { m_speed = speed; }
	float speed() const { return m_speed; }
protected:
	float m_speed;
};

class Car : public Vehicle {
public:
	std::string me() const override { return "Car"; }
};

class Airplane : public Vehicle {
public:
	std::string me() const override { return "Airplane"; }
};
