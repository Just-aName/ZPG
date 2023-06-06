#include "Subject.h"

const void Subject::attach(Observer* obs) {
	this->obs.insert(obs);
	//this->obs.emplace_back(obs);
}

const void Subject::notify() const {
	for (const auto& item : obs) {
		item->update();
	}
}

const void Subject::remove(Observer* obs)
{
	this->obs.erase(obs);
}
