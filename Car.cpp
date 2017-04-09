#include "Car.h"

#include <iostream>

/*!
	Create new instance of car.
	@param id Id of new car.
	@param cost Cost of one item.
	@param count Amount of items inside.
*/
Car::Car(unsigned int id, int cost, unsigned int count) :
	m_id(id)
{
	m_itemCount = (count < MIN_P ? MIN_P : (count > MAX_P ? MAX_P : count));
	m_itemCost = (cost < MIN_C ? MIN_C : (cost > MAX_C ? MAX_C : cost));

	std::cout << "G" << m_id << "[" << m_itemCount << "][" << m_itemCost << "]\n";
}

/*!
	Remove one item from the car.
	@return True if car still contains some items.
*/
bool Car::unload() {
	m_itemCount--;
	std::cout << "\t\tV" << m_id << "[" << m_itemCount << "]\n";
	return m_itemCount > 0;
}