#pragma once

#include "Vehicle.h"

class House {
public:
	virtual void build_kitchen() = 0;
	virtual void build_pool() = 0;
	virtual void build_balcony() = 0;
	virtual void build_bathroom() = 0;
	virtual void build_garage() = 0;
	// ...
};

class PrivateHouse : public House {
public:
	void build_kitchen() override { std::cout << "Building kitchen for private house\n"; };
	void build_pool() override { std::cout << "Building pool for private house\n"; };
	void build_balcony() override { std::cout << "Building balcony for private house\n"; };
	void build_bathroom() override { std::cout << "Building bathroom for private house\n"; };
	void build_garage() override { std::cout << "Building garage for private house\n"; };
};

class Flat : public House {
public:
	void build_kitchen() override { std::cout << "Building kitchen for flat\n"; };
	void build_pool() override {};
	void build_balcony() override { std::cout << "Building balcony for flat\n"; };
	void build_bathroom() override { std::cout << "Building bathroom for flat\n"; };
	void build_garage() override {};
};

class HouseBuilder {
public:
	virtual ~HouseBuilder() { delete m_house; }
	House* build() {
		House* tmp = m_house;
		reset();
		return tmp;
	}
	virtual void add_kitchen() = 0;
	virtual void add_pool() = 0;
	virtual void add_balcony() = 0;
	virtual void add_bathroom() = 0;
	virtual void add_garage() = 0;
protected:
	virtual void reset() = 0;
protected:
	House* m_house;
};

class PrivateHouseBuilder : public HouseBuilder {
public:
	PrivateHouseBuilder() { reset(); }
	void add_kitchen() override { m_house->build_kitchen(); };
	void add_pool() override { m_house->build_pool(); };
	void add_balcony() override { m_house->build_balcony(); };
	void add_bathroom() override { m_house->build_bathroom(); };
	void add_garage() override { m_house->build_garage(); };
protected:
	void reset() override { m_house = new PrivateHouse(); }
};

class FlatBuilder : public HouseBuilder {
public:
	FlatBuilder() { reset(); }
	void add_kitchen() override { m_house->build_kitchen(); };
	void add_pool() override { m_house->build_pool(); };
	void add_balcony() override { m_house->build_balcony(); };
	void add_bathroom() override { m_house->build_bathroom(); };
	void add_garage() override { m_house->build_garage(); };
protected:
	void reset() override { m_house = new Flat(); }
};

class Director {
public:
	Director(HouseBuilder* builder) {
		m_builder = builder;
	}
	void set_builder(HouseBuilder* builder) { m_builder = builder; }
	// other way is to create separate methods for different types of houses
	House* construct_house() {
		m_builder->add_balcony();
		m_builder->add_bathroom();
		m_builder->add_garage();
		m_builder->add_kitchen();
		m_builder->add_pool();
		return m_builder->build();
	}
private:
	HouseBuilder* m_builder;
};
