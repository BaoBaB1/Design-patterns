#include "tests.h"
#include "Vehicle.h"
#include "Shape.h"
#include <cassert>
#include "../creational/creational.h"
#include "../structural/structural.h"
#include "../behavioral/behavioral.h"

void creationaltests::test_factory() {
  using namespace factorymethod;
  auto car = VehicleFactory::create_vehicle(Vehicle::VehicleType::Car);
  auto airplane = VehicleFactory::create_vehicle(Vehicle::VehicleType::Airplane);
  assert(car->me() == "Car");
  assert(airplane->me() == "Airplane");
}

void creationaltests::test_abstract_factory() {
  using namespace abstractfactory;
  std::unique_ptr<AbstractFactory> factory;
  for (int i = 0; i < 2; ++i) {
    if (i == 0)
      factory = std::make_unique<ConcreteFactory>();
    else
      factory = std::make_unique<ConcreteFactory2>();
    auto vehicle = factory->create_vehicle();
    auto exception = factory->create_exception();
    if (i == 0) {
      assert(vehicle->me() == "Car");
      assert(dynamic_cast<std::runtime_error*>(exception.get()) && std::string(exception->what()) == "Runtime error");
    }
    else {
      assert(vehicle->me() == "Airplane");
      assert(dynamic_cast<std::range_error*>(exception.get()) && std::string(exception->what()) == "Range error");
    }
  }
}

void creationaltests::test_builder() {
  using namespace builder;
  std::cout << "\nBuilder test\n";
  Director d(std::make_unique<PrivateHouseBuilder>());
  auto house = d.construct_dwelling();
  assert(house->balcony() == 1 && house->kitchen() == 2 && house->bathroom() == 3);
  assert(dynamic_cast<PrivateHouse*>(house.get()));
  d.set_builder(std::make_unique<FlatBuilder>());
  auto flat = d.construct_dwelling();
  assert(flat->balcony() == 4 && flat->kitchen() == 5 && flat->bathroom() == 6);
  assert(dynamic_cast<Flat*>(flat.get()));
}

void creationaltests::test_singleton() {
  using namespace singleton;
  Car& car = Singleton<Car>::instance();
  Car& car2 = Singleton<Car>::instance();
  assert(&car == &car2);
}

void creationaltests::test_prototype() {
  // class Shape inherits IClonable interface
  std::unique_ptr<Circle> circle = std::make_unique<Circle>(2.f);
  std::unique_ptr<Circle> circle_clone(circle->clone());
  assert(circle->radius() == 2.f && circle_clone->radius() == 2.f);
  std::unique_ptr<Square> sq = std::make_unique<Square>();
  std::unique_ptr<Square> sq_clone(sq->clone());
  assert(sq.get() != sq_clone.get());
}

void creationaltests::test_all() {
  test_factory();
  test_abstract_factory();
  test_builder();
  test_singleton();
  test_prototype();
}

void structuraltests::test_adapter() {
  using namespace adapter;
  std::cout << "\nAdapter test\n";
  Pigeon p;
  Seal s;
  FlyableToSwimmableAdapter adapter(&p);
  p.fly();                       // pigeon is flying
  s.swim();                      // seal is swimming
  adapter.swim();                // now pigeon is swimming
}

void structuraltests::test_decorator() {
  using namespace decorator;
  std::cout << "\nDecorator test\n";
  Circle c;
  ColoredShape cs(&c, "yellow");
  cs.paint();                   // paint circle in yellow
  Square sq;
  ColoredShape cs2(&sq);
  cs2.paint();                  // paint square in red
}

void structuraltests::test_proxy() {
  using namespace proxy;
  std::cout << "\nProxy test\n";
  ServiceProxy _proxy;
  _proxy.do_some_work();
}

void structuraltests::test_facade() {
  using namespace facade;
  std::cout << "\nFacade test\n";
  SceneRenderer sc;
  sc.render_scene();
}

void structuraltests::test_all() {
  test_adapter();
  test_decorator();
  test_proxy();
  test_facade();
}

void behavioraltests::test_responsibility_chain() {
  using namespace responsibility_chain;
  std::cout << "\nChain of responsibility test\n";
  // 10 banknotes - 5
  // 50 banknotes - 3
  // sum - 200
  const ATM atm;
  auto cp10 = atm.dispenser10();
  auto cp50 = atm.dispenser50();
  int val = atm.dispense(75);
  assert(cp10->currency_amount() == 5 && cp50->currency_amount() == 3);
  val = atm.dispense(100);
  assert(val == 100 && cp10->currency_amount() == 5 && cp50->currency_amount() == 1);
  val = atm.dispense(40);
  assert(val == 40 && cp10->currency_amount() == 1 && cp50->currency_amount() == 1);
  val = atm.dispense(20);
  assert(val == 0 && cp10->currency_amount() == 1 && cp50->currency_amount() == 1);
  val = atm.dispense(60);
  assert(val == 60 && cp10->currency_amount() == 0 && cp50->currency_amount() == 0);
  val = atm.dispense(10);
  assert(val == 0 && cp10->currency_amount() == 0 && cp50->currency_amount() == 0);
  val = atm.dispense(50);
  assert(val == 0 && cp10->currency_amount() == 0 && cp50->currency_amount() == 0);
  const ATM atm2;
  val = atm2.dispense(-100);
  assert(val == 0);
  val = atm2.dispense(0); 
  assert(val == 0);
}

void behavioraltests::test_observer() {
  using namespace observer;
  std::cout << "\nObserver test\n";
  ConcreteObserver* obs = new ConcreteObserver();
  ConcreteObserver2* obs2 = new ConcreteObserver2();
  Subject s;
  s.add_observer(obs);
  s.add_observer(obs2);
  s.notify_all();
  s.remove_observer(obs2);
  s.notify_all();
}

void behavioraltests::test_strategy() {
  using namespace strategy;
  std::cout << "\nStrategy test\n";
  ShoppingCart cart;
  VisaPayment vp;
  cart.pay(&vp, 210);
  ShoppingCart cart2;
  MastercardPayment mp;
  cart2.pay(&mp, 300);
}

void behavioraltests::test_visitor() {
  using namespace visitor;
  std::cout << "\nVisitor test\n";
  ShapeVisitor visitor;
  Circle c;
  Square sq;
  c.visit(&visitor);
  sq.visit(&visitor);
}

void behavioraltests::test_all() {
  test_responsibility_chain();
  test_observer();
  test_strategy();
  test_visitor();
}