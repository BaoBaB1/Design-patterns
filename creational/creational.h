#pragma once

#include <exception>
#include <memory>
#include <stdexcept>
#include "Vehicle.h"

namespace factorymethod {

	class VehicleFactory {
	public:
		static std::unique_ptr<Vehicle> create_vehicle(Vehicle::VehicleType type) {
			if (type == Vehicle::VehicleType::Car)
				return std::make_unique<Car>();
			else if (type == Vehicle::VehicleType::Airplane)
				return std::make_unique<Airplane>();
			return nullptr;
		}
	};
};

namespace abstractfactory {

	class AbstractFactory {
	public:
		virtual std::unique_ptr<Vehicle> create_vehicle() = 0;
		virtual std::unique_ptr<std::exception> create_exception() = 0;
	};

	class ConcreteFactory : public AbstractFactory {
	public:
		std::unique_ptr<Vehicle> create_vehicle() override { return std::make_unique<Car>(); }
		std::unique_ptr<std::exception> create_exception() override { return std::make_unique<std::runtime_error>("Runtime error"); }
	};

	class ConcreteFactory2 : public AbstractFactory {
	public:
		std::unique_ptr<Vehicle> create_vehicle() override { return std::make_unique<Airplane>(); }
		std::unique_ptr<std::exception> create_exception() override { return std::make_unique<std::range_error>("Range error"); }
	};
};

namespace builder {

	class Dwelling {
	public:
		virtual void set_kitchen(int) = 0;
		virtual void set_balcony(int) = 0;
		virtual void set_bathroom(int) = 0;
		virtual ~Dwelling() {}
		int bathroom() const { return m_bathroom; }
		int balcony() const { return m_balcony; }
		int kitchen() const { return m_kitchen; }
	protected:
		int m_bathroom;
		int m_balcony;
		int m_kitchen;
	};

	class PrivateHouse : public Dwelling {
	public:
		void set_kitchen(int) override;
		void set_balcony(int) override;
		void set_bathroom(int) override;
	};

	class Flat : public Dwelling {
	public:
		void set_kitchen(int) override;
		void set_balcony(int) override;
		void set_bathroom(int) override;
	};

	class HouseBuilder {
	public:
		virtual std::unique_ptr<Dwelling> build() const = 0;
	};

	class PrivateHouseBuilder : public HouseBuilder {
	public:
		PrivateHouseBuilder() {}
		std::unique_ptr<Dwelling> build() const override;
	};

	class FlatBuilder : public HouseBuilder {
	public:
		FlatBuilder() {}
		std::unique_ptr<Dwelling> build() const override;
	};

	class Director {
	public:
		Director(std::unique_ptr<HouseBuilder>&& builder) : m_builder(std::move(builder)) {}
		void set_builder(std::unique_ptr<HouseBuilder>&& builder) {
			if (m_builder.get())
				m_builder.reset();
			m_builder = std::move(builder);
		}
		std::unique_ptr<Dwelling> construct_dwelling() const { return m_builder->build(); }
	private:
		std::unique_ptr<HouseBuilder> m_builder;
	};
};

namespace singleton {

	template<typename T>
	class Singleton {
	public:
		static T& instance() {
			static T var;
			return var;
		}
		Singleton() = delete;
		~Singleton() = delete;
		Singleton(const Singleton& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
	};
}

namespace prototype {

	template<typename T>
	class IClonable {
	public:
		virtual T* clone() const = 0;
	};
};
