#pragma once

namespace MQ 
{
	class Car {
		friend class MQStorage;
		public:
			Car(unsigned int id, int cost, unsigned int count);
			bool unload();

			inline const unsigned int getID() const { return _id; }
			inline const unsigned int getCount() const { return _count; }
			inline const int getCostPerItem() const { return _cost; }
			inline const int getTotalCost() const { return (_cost * _count); }

			static const int C1 = 100;
			static const int C2 = 1000;
			static const int N = 50;
			static const int P = 10;
			static inline const int getMaxCost() { return P * C2; }
		private:
			unsigned int _id, _count;
			int _cost;
	};

}