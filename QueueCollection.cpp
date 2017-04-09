#include "QueueCollection.h"

#include <iostream>	//< cout
#include <random>	//< mt19937_64(), uniform_int_distribution()
#include <ctime>	//< time()

//! 
//! Carry Pair
//! 

/*!
	Deallocate carry content.
*/
void CarryPair::Carry::clear() {
	if (m_next != nullptr) {
		m_next->clear();
	}
	
	delete m_car;
	delete this;
}

/*!
	Get value from top of queue.
	@return Value on top.
*/
Car* CarryPair::peek() const {
	return m_begin->m_car;
}

/*!
	Add carry node to queue.
	@param carry Pointer to carry node.
*/
void CarryPair::add(Car *car) {
	Carry *newCarry = new Carry(car);

	if (m_begin == nullptr || m_end == nullptr) {
		m_begin = newCarry;
	} else {
		m_end->m_next = newCarry;
	}

	m_end = newCarry;
}

/*!
	Remove value from queue.
	@return Removed value.
*/
Car* CarryPair::remove() {
	Carry *follow = m_begin->m_next;
	Car *removed = m_begin->m_car;
	delete m_begin;
	m_begin = follow;
	return removed;
}

//! 
//! QueueSet
//!

/*!
	Create new MQStorage.
	@param size Amount of internal queues, must be 1 or higher.
*/
MQStorage::MQStorage(unsigned int size) : m_size(size), m_carry(new CarryPair[size]()) { 

}

/*!
	Destroy all internal queues and deallocate their remaining content.
*/
MQStorage::~MQStorage() {
	for (unsigned int i = 0; i < m_size; i++) {
		if (m_carry[i].m_begin != nullptr) m_carry[i].m_begin->clear();
	}
	delete[] m_carry;
}

/*!
	Add new car into the queues.
	@param car Pointer to new car.
*/
void MQStorage::add(Car *car) {
	int selectedQueue = (car->getTotalCost() - Car::MIN_C - 1) / ((Car::getMaxCost() - Car::MIN_C) / m_size);
	std::cout << "\tF" << car->getID() << "[" << selectedQueue << "]\n";
	m_carry[selectedQueue].add(car);
}

/*!
	Update whole MQStorage.
*/
void MQStorage::update() {
	for (unsigned int i = 0; i < m_size; i++) update(i);
}

/*!
	Update one internal queue.
	@param queue Selected queue.
*/
void MQStorage::update(unsigned int queue) {
	if (m_carry[queue].hasContent() && !m_carry[queue].peek()->unload()) {
		Car *removedCar = m_carry[queue].remove();
		std::cout << "\t\t\tX" << removedCar->getID() << "[" << queue << "]\n";
		delete removedCar;
	}
}

/*!
	If any internal queue has value stored inside.
	@return True if value is stored.
*/
const bool MQStorage::hasContent() {
	for (unsigned int i = 0; i < m_size; i++) {
		if (m_carry[i].hasContent()) return true;
	}
	return false;
}

/*!
	Generate new randomized car.
	@param id Id of new car.
	@param range Range of generator.
*/
Car* MQStorage::generate(unsigned int id) {
	static std::mt19937_64 engine(time(nullptr));
	std::uniform_int_distribution<int> randP(Car::MIN_P, Car::MAX_P);
	std::uniform_int_distribution<int> randC(Car::MIN_C, Car::MAX_C);

	return new Car(id, randC(engine), randP(engine));
}