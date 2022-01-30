/*
Kristian Kerrigan
Subject.hpp
This file contains the Subject class for the observer pattern.
*/

#pragma once
#include <set>
#include "View.hpp"

class Subject {
	std::set<View*> views;
public:
	virtual ~Subject() {}
	void attach(View* p) { views.insert(p); }
	void detach(View* p) { views.erase(p); }
	void notify() {
		for (auto view : views)
			view->update();
	}
};