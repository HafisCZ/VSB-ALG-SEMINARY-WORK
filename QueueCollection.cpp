#include "QueueCollection.h"

#include <iostream>
#include <ctime>

namespace MQ 
{
	/*!
		Get value from top of queue.
		@return Value on top.
	*/
	Car* MQStorage::CarryPair::peek() const {
		return begin->_car;
	}

	/*!
		Deallocate pair content.
	*/
	void MQStorage::Carry::clear() {
		if (_next != nullptr) {
			_next->clear();
		}
		delete _car;
		delete this;
	}

	/*!
		Add carry node to queue.
		@param carry Pointer to carry node.
	*/
	void MQStorage::CarryPair::add(Carry *carry) {
		if (begin == nullptr || end == nullptr) {
			begin = carry;
		}
		else {
			end->_next = carry;
		}
		end = carry;
	}

	/*!
		Remove value from queue.
		@return Removed value.
	*/
	Car* MQStorage::CarryPair::remove() {
		Carry *follow = begin->_next;
		Car *removed = begin->_car;
		delete begin;
		begin = follow;
		return removed;
	}

	/*!
		Create new MQStorage.
		@param size Amount of internal queues, must be 1 or higher.
	*/
	MQStorage::MQStorage(unsigned int size) :
		_size(size),
		_carry(new CarryPair[size]()) 
	{

	}

	/*!
		Destroy all internal queues and deallocate their remaining content.
	*/
	MQStorage::~MQStorage() {
		for (unsigned int i = 0; i < _size; i++) {
			if (_carry[i].begin != nullptr) {
				_carry[i].begin->clear();
			}
		}
		delete[] _carry;
	}

	/*!
		Add new car into the queues.
		@param car Pointer to new car.
	*/
	void MQStorage::add(Car *car) {
		int destQueue = 0;
		for (unsigned int i = 1; i <= _size; i++) {
			if (car->getTotalCost() - Car::C1 <= static_cast<int>(i * (Car::getMaxCost() - Car::C1) / _size)) {
				destQueue = i - 1;
				break;
			}
		}
		std::cout << "F" << car->_id << "[" << destQueue << "]" << std::endl;
		_carry[destQueue].add(new Carry(car));
	}

	/*!
		Update whole MQStorage.
	*/
	void MQStorage::update() {
		for (unsigned int i = 0; i < _size; i++) {
			update(i);
		}
	}

	/*!
		Update one internal queue.
		@param queue Selected queue.
	*/
	void MQStorage::update(unsigned int queue) {
		if (_carry[queue].hasContent() && !_carry[queue].peek()->unload()) {
			Car *removedCar = _carry[queue].remove();
			std::cout << "X" << removedCar->_id << "[" << queue << "]" << std::endl;
			delete removedCar;
		}
	}

	/*!
		If any internal queue has value stored inside.
		@return True if value is stored.
	*/
	const bool MQStorage::hasContent() {
		for (unsigned int i = 0; i < _size; i++) {
			if (_carry[i].hasContent()) return true;
		}
		return false;
	}

	/*!
		Generate new randomized car.
		@param id Id of new car.
	*/
	Car* MQStorage::generate(unsigned int id) {
		static bool initialized = false;
		if (!initialized) {
			srand(static_cast<unsigned int>(time(0)));
			initialized = true;
		}

		return new Car(id, (rand() % (Car::C2 - Car::C1 + 1) + Car::C1), (rand() % Car::P + 1));
	}

}