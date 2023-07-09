#pragma once

#include <string>

class Entity {
public:
	virtual std::string me() const = 0;
	virtual ~Entity() {}
};
