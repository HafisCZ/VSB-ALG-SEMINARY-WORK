#include "Truck.h"

/**
	@param cislo Number of our car.
	@param pocet_polozek Number of items in shipment.
	@param cena Cost of one item.
*/
NakladniAuto::NakladniAuto(size_t cislo, int pocet_polozek, int cena) {
	this->cislo_ = cislo;
	this->pocet_polozek_ = (pocet_polozek < 1 ? 1 : (pocet_polozek > P ? P : pocet_polozek));
	this->cena_ = (cena < C1 ? C1 : (cena > C2 ? C2 : cena));
	std::cout << "G" << this->cislo_ << "[" << this->pocet_polozek_ << "][" << this->cena_ << "]" << std::endl;
}

/**
	@return Number of our car.
*/
inline const size_t NakladniAuto::cislo() const {
	return this->cislo_;
}

/**
	@return Number of items in the car.
*/
inline const int NakladniAuto::pocetPolozek() const {
	return this->pocet_polozek_;
}

/**
	@return Total cost of shipment.
*/
inline const int NakladniAuto::cenaNakladu() const {
	return this->pocet_polozek_ * this->cena_;
}

/**
	@return Maximum value of our cars shipment.
*/
inline const int NakladniAuto::maximalniCena() const {
	return P * C2;
}

/**
	Removed one item from the shipment.

	@return If there are any items left.
*/
inline bool NakladniAuto::vyskladnitPolozku() {
	this->pocet_polozek_--;
	std::cout << "V" << this->cislo_ << "[" << this->pocet_polozek_ << "]" << std::endl;
	return this->pocet_polozek_ > 0;
}

/**
	Insert new car into proper queue.

	@param nove_auto New car instance.
	@param q1 Queue #1.
	@param q2 Queue #2.
	@param q3 Queue #3.
*/
void splitIntoQueues(NakladniAuto* nove_auto, Queue &q1, Queue &q2, Queue &q3) {
	int queue = (nove_auto->cenaNakladu() <= nove_auto->maximalniCena() / 3 ? 1 : (nove_auto->cenaNakladu() <= 2 * nove_auto->maximalniCena() / 3 ? 2 : 3));
	(queue == 1 ? q1 : (queue == 2 ? q2 : q3)).add(nove_auto);
	std::cout << "F" << nove_auto->cislo() << "[" << queue << "]" << std::endl;
}

/**
	Removed item from front car. If car is empty, removes it from the queue and deletes it.

	@param q Queue.
*/
void processQueue(Queue &q, size_t num) {
	if (q.hasContent() && !q.peek()->vyskladnitPolozku()) {
		NakladniAuto* del_auto = q.remove();
		std::cout << "X" << del_auto->cislo() << "[" << num << "]" << std::endl;
		delete del_auto;
	}
}

/**
	Create new carry node for Car.

	@deprecated Only for use with Queue.
*/
Car::Car(NakladniAuto* car) {
	this->car_ = car;
	this->next_ = NULL;
}

/**
	Dealocate used memory.
*/
void Car::unalloc() {
	if (this->next_ != NULL) this->next_->unalloc();
	delete this->car_;
	delete this;
}

/**
	Create new instance of Queue.
*/
Queue::Queue() {
	this->base_ = NULL;
	this->terminal_ = NULL;
}

/**
	Destroy car queue and deallocate remaining nodes. Eliminates memory leaks when values remain inside after exiting scope with queue.
*/
Queue::~Queue() {
	if (this->base_ != NULL) this->base_->unalloc();
}

/**
	Add new car into the queue.

	@param car New car to be inserted.
*/
void Queue::add(NakladniAuto *car) {
	Car *new_car = new Car(car);
	if (this->base_ == NULL || this->terminal_ == NULL) {
		this->terminal_ = new_car;
		this->base_ = this->terminal_;
	} else {
		this->terminal_->next_ = new_car;
		this->terminal_ = new_car;
	}
}

/**
	Removes car from the queue.

	@return Removed car.
*/
NakladniAuto* Queue::remove() {
	Car *follow = this->base_->next_;
	NakladniAuto *car = this->base_->car_;
	delete this->base_;
	this->base_ = follow;
	return car;
}

/**
	@return Next car to be removed.
*/
inline NakladniAuto* Queue::peek() const {
	return this->base_->car_;
}

/**
	@param If some cars are still inside the queue.
*/
inline const bool Queue::hasContent() const {
	return this->base_ != NULL;
}