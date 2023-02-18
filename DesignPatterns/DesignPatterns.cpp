#include <iostream>
#include <assert.h>
#include "Factory.h"
#include "AbstractFactory.h"
#include "Builder.h"

void test_factory();
void test_abstract_factory();
void test_builder();

int main()
{
    //test_factory();
    //test_abstract_factory();
    //test_builder();
}

void test_factory() {
    Vehicle* car = VehicleFactory::create_vehicle(Vehicle::VehicleType::Car);
    Vehicle* airplane = VehicleFactory::create_vehicle(Vehicle::VehicleType::Airplane);
    car->move();
    assert(car->state() == "Car is moving");
    airplane->move();
    assert(airplane->state() == "Airplane is moving");
    delete car;
    delete airplane;
}

void test_abstract_factory() {
    for (int i = 0; i < 2; ++i) {
        AbstractFactory* factory = nullptr;
        if (i == 0)
            factory = new ConcreteFactory();
        else
            factory = new ConcreteFactory2();
        Vehicle* v = factory->create_vehicle();
        Shape* s = factory->create_shape();
        v->move();
        s->render();
        if (i == 0) {
            assert(v->state() == "Car is moving");
            assert(s->state() == "Circle is rendering");
        }
        else {
            assert(v->state() == "Airplane is moving");
            assert(s->state() == "Square is rendering");
        }
        delete factory;
        delete v;
        delete s;
    }
}

void test_builder() {
    HouseBuilder* builder = new PrivateHouseBuilder();
    HouseBuilder* builder2 = new FlatBuilder();
    Director d(builder);
    House* private_house = d.construct_house(); // PrivateHouse
    d.set_builder(builder2);
    House* flat = d.construct_house(); // Flat
    delete builder;
    delete builder2;
}

