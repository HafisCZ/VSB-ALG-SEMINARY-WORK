#pragma once

#include "Car.h"

//! Queue using pair of carry nodes
class CarryPair {
	private:
		//! Carry node to store value
		class Carry;
	public:
		// Constr
		CarryPair() { }
		//~CarryPair() { }

		// Ops
		void add(Car *car);
		Car* remove();
		Car* peek() const;

		//! Getters
		inline const bool hasContent() { return m_begin != nullptr; }

		//! Vars
		Carry* m_begin = nullptr;
		Carry* m_end = nullptr;
};

class CarryPair::Carry {
	public:
		// Constr
		Carry(Car *car) : m_car(car) { }
		~Carry() { }

		//! Ops
		void clear();

		//! Vars
		Carry* m_next = nullptr;
		Car* m_car = nullptr;
};

//! Manages and provides access methods for internal queues stored within.
class MQStorage {
	public:
		//! Constr
		MQStorage(unsigned int size);
		~MQStorage();

		//! Ops
		void add(Car* car);
		void update();

		//! Static Ops
		static Car* generate(unsigned int id);

		//! Getters
		const bool hasContent();
	private:
		//! Ops
		void update(unsigned int queue);

		//! Vars
		CarryPair* m_carry;
		unsigned int m_size;
};