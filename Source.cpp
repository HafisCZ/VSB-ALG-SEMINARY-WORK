#include <iostream>
#include <string>
#include <ctime>

#include "vld.h" /* Visual Leak Detector */
#include "Truck.h"

int main() {
	srand(static_cast<size_t>(time(0)));
	Queue q1, q2, q3;
	size_t truck_count = 1;
	do {
		if (truck_count <= N) splitIntoQueues(new NakladniAuto(truck_count++, rand() % P + 1, rand() % (C2 - C1) + C1 + 1), q1, q2, q3);
		processQueue(q1, 1);
		processQueue(q2, 2);
		processQueue(q3, 3);
	} while (q1.hasContent() || q2.hasContent() || q3.hasContent());

	std::cin.get();
	return 0;
}