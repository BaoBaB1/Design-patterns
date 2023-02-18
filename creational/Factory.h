#pragma once

#include "Vehicle.h"

class VehicleFactory {
public:
	static Vehicle* create_vehicle(Vehicle::VehicleType type) {
		if (type == Vehicle::VehicleType::Car)
			return new Car();
		else if (type == Vehicle::VehicleType::Airplane)
			return new Airplane();
		return nullptr;
	}
};