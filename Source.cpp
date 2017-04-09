#include <iostream>

#include <vld.h>

#include "QueueCollection.h"

const int N = 50;		//< N

int main(int argc, char ** argv) {
	MQStorage mqs(3);
	
	unsigned int count = 1;
	do {
		if (count <= N) mqs.add(MQStorage::generate(count++));
		mqs.update();
	} while (mqs.hasContent() || count <= N);
	
	std::cin.get();
	return 0;
}