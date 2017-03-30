#pragma once

#include <iostream>

const int C1 = 100; // cost min
const int C2 = 1000; // cost max
const int N = 500, P = 15;

class NakladniAuto {
	private:
		size_t cislo_;
		int pocet_polozek_;
		int cena_;
	public:
		NakladniAuto(size_t cislo, int pocet_polozek, int cena);
		inline const size_t cislo() const;
		inline const int pocetPolozek() const;
		inline const int cenaNakladu() const;
		inline const int maximalniCena() const;
		bool vyskladnitPolozku();
};

class Car {
	friend class Queue;
	private:
		NakladniAuto *car_;
		Car *next_;
	private:
		Car(NakladniAuto *car);
		void unalloc();
};

class Queue {
	private:
		Car *base_, *terminal_;
	public:
		Queue();
		~Queue();
		void add(NakladniAuto *car);
		NakladniAuto* remove();
		inline NakladniAuto* peek() const;
		inline const bool hasContent() const;
};

void splitIntoQueues(NakladniAuto* nove_auto, Queue &q1, Queue &q2, Queue &q3);
void processQueue(Queue &q, size_t num);