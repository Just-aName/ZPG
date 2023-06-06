#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

#include "Observer.h"


class Subject {
public:
	unordered_set <class Observer*> obs;
	const void attach(Observer* obs);
	const void notify() const;
	const void remove(Observer* obs);
};

