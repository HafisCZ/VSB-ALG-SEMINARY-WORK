#pragma once

class Car {
	public:
		//! Constr
		Car(unsigned int id, int cost, unsigned int count);
		~Car() { }

		//! Ops
		bool unload();

		//! Getters
		inline const unsigned int getID() const { return m_id; }
		inline const unsigned int getCount() const { return m_itemCount; }
		inline const int getCostPerItem() const { return m_itemCost; }
		inline const int getTotalCost() const { return (m_itemCost * m_itemCount); }

		//! Static Getters
		static const int getMaxCost() { return MAX_P * MAX_C; }

		//! Static Vars
		static const int MIN_C = 100;	//< C1
		static const int MAX_C = 1000;	//< C2
		static const int MIN_P = 1;	
		static const int MAX_P = 10;	//< P
	private:
		//! Vars
		unsigned int m_id, m_itemCount;
		int m_itemCost;
};