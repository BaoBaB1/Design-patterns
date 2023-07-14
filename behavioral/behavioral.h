#pragma once

#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include "Entity.h"
#include "Shape.h"

namespace responsibility_chain {
  
  class IDispenser {
  public:
    virtual bool dispense(int amount) = 0;
    virtual IDispenser* set_next(IDispenser* next) = 0;
    virtual ~IDispenser() {}
  };

  class Dispenser : public IDispenser {
  public:
    int currency_amount() const { return m_currency_amount; }
    IDispenser* set_next(IDispenser* next) {
      m_next_handler = next;
      return next;
    }
  protected:
    Dispenser(int currency_amount) : m_currency_amount(currency_amount), m_next_handler(nullptr) {}
    bool dispense(int amount, int banknote_value);
  protected:
    IDispenser* m_next_handler;
    int m_currency_amount;
  };

  class Dispenser50 : public Dispenser {
  public:
    Dispenser50(int currency_amount) : Dispenser(currency_amount) {}
    bool dispense(int amount) override;
  };

  class Dispenser10 : public Dispenser {
  public:
    Dispenser10(int currency_amount) : Dispenser(currency_amount) {}
    bool dispense(int amount) override;
  };

  class ATM {
  public:
    ATM() {
      m_10_disp = new Dispenser10(5);
      m_50_disp = new Dispenser50(3);
      m_50_disp->set_next(m_10_disp);
    }
    int dispense(int amount) const;

    const Dispenser10* dispenser10() const { return m_10_disp; }
    const Dispenser50* dispenser50() const { return m_50_disp; }

    ~ATM() {
      delete m_10_disp;
      delete m_50_disp;
    }
  private:
    Dispenser10* m_10_disp;
    Dispenser50* m_50_disp;
  };
};

namespace observer {

  class IObserver {
  public:
    virtual void notify() = 0;
    virtual ~IObserver() {}
  };

  class ConcreteObserver : public IObserver {
  public:
    void notify() override { std::cout << "ConcreteObserver::notify()\n"; }
  };

  class ConcreteObserver2 : public IObserver {
  public:
    void notify() override { std::cout << "ConcreteObserver2::notify()\n"; }
  };

  class Subject {
  public:
    void add_observer(IObserver* obs) { m_observers.push_back(obs); }
    void remove_observer(IObserver* obs) {  
      auto it = std::find(m_observers.begin(), m_observers.end(), obs);
      if (it != m_observers.end())
        m_observers.erase(it);
    }
    void notify_all() {
      for (IObserver* obs : m_observers) {
        obs->notify();
      }
    }
    ~Subject() {
      for (auto obs : m_observers)
        delete obs;
    }
  private:
    std::vector<IObserver*> m_observers;
  };
};

namespace strategy {

  class IPaymentStrategy {
  public:
    virtual void pay(int amount) = 0;
    virtual ~IPaymentStrategy() {}
  };

  class VisaPayment : public IPaymentStrategy {
  public:
    void pay(int amount) override { std::cout << "Visa payment\n"; }
  };

  class MastercardPayment : public IPaymentStrategy {
  public:
    void pay(int amount) override { std::cout << "Mastercard payment\n"; }
  };

  class ShoppingCart {
  public:
    void pay(IPaymentStrategy* strategy, int amount) { strategy->pay(amount); }
  };
};

namespace visitor {

  class IShapeVisitor {
  public:
    virtual void visit(const Circle& circle) const = 0;
    virtual void visit(const Square& square) const = 0;
    virtual ~IShapeVisitor() = default;
  };

  class ShapeVisitor : public IShapeVisitor {
  public:
    void visit(const Circle& circle) const override {
      std::cout << "ShapeVisitor::visit(const Circle&)\n";
    }
    void visit(const Square& square) const override {
      std::cout << "ShapeVisitor::visit(const Square&)\n";
    }
  };
};
