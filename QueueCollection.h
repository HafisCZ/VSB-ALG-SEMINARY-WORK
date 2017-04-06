#pragma once

#include "Car.h"

namespace MQ 
{
	class MQStorage {
		private:
			struct Carry {
				Carry *_next;
				Car *_car;
				Carry(Car *car) : _next(nullptr), _car(car) { }
				void clear();
			};

			struct CarryPair {
				Carry *begin;
				Carry *end;
				CarryPair() : begin(nullptr), end(nullptr) { }
				inline const bool hasContent() { return begin != nullptr; }
				
				void add(Carry *carry);
				Car* remove();
				Car* peek() const;
			} *_carry;

			unsigned int _size;
			void update(unsigned int queue);
		public:
			MQStorage(unsigned int size);
			~MQStorage();
			void add(Car *car);
			void update();
			const bool hasContent();

			static Car* generate(unsigned int id);
	};

}