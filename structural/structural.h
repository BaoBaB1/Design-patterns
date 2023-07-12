#pragma once

#include <iostream>
#include <vector>
#include "Shape.h"

namespace adapter {

  class IFlyable : public Entity {
  public:
    virtual void fly() = 0;
    virtual float speed() = 0;
    virtual ~IFlyable() = default;
  };

  class Pigeon : public IFlyable {
  public:
    void fly() override { std::cout << "Pigeon flies with speed " << speed() << '\n'; }
    float speed() override { return 1.5f; }
    std::string me() const override { return "Pigeon"; }
  };

  class ISwimmable : public Entity {
  public:
    virtual void swim() = 0;
    virtual float speed() = 0;
    virtual ~ISwimmable() = default;
  };

  class Seal : public ISwimmable {
  public:
    void swim() override { std::cout << "Seal swims with speed " << speed() << '\n'; }
    float speed() override { return 2.f; }
    std::string me() const override { return "Seal"; }
  };

  class FlyableToSwimmableAdapter : public ISwimmable {
  public:
    FlyableToSwimmableAdapter(IFlyable* flyable) : m_flyable(flyable) {}
    void swim() override { std::cout << m_flyable->me() << " now swims with speed " << m_flyable->speed() << '\n'; }
    float speed() override { return 0.f; }
    std::string me() const override { return "FlyableToSwimmableAdapter"; }
  private:
    IFlyable* m_flyable;
  };
};

namespace decorator {

  class ColoredShape {
  public:
    ColoredShape(Shape* sh, const std::string& color = "red") : m_wrapped(sh), m_color(color) {}
    void paint() { std::cout << "Painting " << m_wrapped->me() << " in " << m_color << " color\n"; }
  private:
    Shape* m_wrapped;
    std::string m_color;
  };
};

/*
  Decorator get reference for decorated object (usually through constructor) while Proxy responsible to do that by himself.
*/

namespace proxy {

  class IService {
  public:
    virtual void do_some_work() = 0;
    virtual ~IService() {}
  };

  class Service : public IService {
  public:
    Service(int val = 2) : m_val(val) {}
    int value() const { return m_val; }
    void do_some_work() override { std::cout << "Service is doing some work\n"; }
  private:
    int m_val;
  };

  class ServiceProxy : public Service {
  public:
    ServiceProxy() : m_service(new Service(1)), m_cached_data(0) {}
    ~ServiceProxy() { delete m_service; }
    void do_some_work() override {
      std::cout << "Proxy is caching data...\n";
      m_cached_data = m_service->value();
      m_service->do_some_work();
    }
  private:
    Service* m_service;
    int m_cached_data;
  };
};

namespace facade {

  class SceneRenderer {
  public:
    void render_scene() {
      create_scene();
      for (const auto& shape : m_shapes) {
        shape->draw();
      }
    }
  private:
    void create_scene() {
      for (int i = 0; i < 5; i++) {
        if (i & 1) {
          m_shapes.push_back(std::unique_ptr<Shape>(new Circle));
        }
        else {
          m_shapes.push_back(std::unique_ptr<Shape>(new Square));
        }
      }
    }
  private:
    std::vector<std::unique_ptr<Shape>> m_shapes;
  };

};
