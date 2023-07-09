#include <iostream>
#include "creational.h"

void builder::PrivateHouse::set_kitchen(int val) {
	std::cout << "Building kitchen for private house\n"; 
	m_kitchen = val;
}

void builder::PrivateHouse::set_balcony(int val) {
	std::cout << "Building balcony for private house\n";
	m_balcony = val;
}

void builder::PrivateHouse::set_bathroom(int val) {
	std::cout << "Building bathroom for private house\n";
	m_bathroom = val;
}

void builder::Flat::set_kitchen(int val) {
	std::cout << "Building kitchen for flat\n";
	m_kitchen = val;
}

void builder::Flat::set_balcony(int val) {
	std::cout << "Building balcony for flat\n";
	m_balcony = val;
}

void builder::Flat::set_bathroom(int val) {
	std::cout << "Building bathroom for flat\n";
	m_bathroom = val;
}

std::unique_ptr<builder::Dwelling> builder::PrivateHouseBuilder::build() const {
	auto up = std::make_unique<PrivateHouse>();
	up->set_balcony(1);
	up->set_kitchen(2);
	up->set_bathroom(3);
	return up;
}

std::unique_ptr<builder::Dwelling> builder::FlatBuilder::build() const {
	auto up = std::make_unique<Flat>();
	up->set_balcony(4);
	up->set_kitchen(5);
	up->set_bathroom(6);
	return up;
}
