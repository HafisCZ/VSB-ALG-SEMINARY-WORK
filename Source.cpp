#include <iostream>

#include <vld.h>

#include "Car.h"
#include "QueueCollection.h"

using namespace MQ;

int main(int argc, char ** argv) {
	MQStorage mqs(3);

	unsigned int count = 1;
	do {
		if (count <= Car::N) mqs.add(MQStorage::generate(count++));
		mqs.update();
	} while (mqs.hasContent() || count <= Car::N);

	std::cin.get();
	return 0;
}