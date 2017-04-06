#include "Car.h"

#include <iostream>

namespace MQ 
{
	/*!
		Create new instance of car.
		@param id Id of new car.
		@param cost Cost of one item.
		@param count Amount of items inside.
	*/
	Car::Car(unsigned int id, int cost, unsigned int count) :
		_id(id)
	{
		_count = (count < 1 ? 1 : (count > P ? P : count));
		_cost = (cost < C1 ? C1 : (cost > C2 ? C2 : cost));

		std::cout << "G" << _id << "[" << _count << "][" << _cost << "]" << std::endl;
	}

	/*!
		Remove one item from the car.
		@return True if car still contains some items.
	*/
	bool Car::unload() {
		_count--;
		std::cout << "V" << _id << "[" << _count << "]" << std::endl;
		return _count > 0;
	}

}