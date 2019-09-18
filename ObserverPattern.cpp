// ObserverPattern.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

//abstract class Observable
class Observable {
public:
	virtual void Add() {}

	virtual void Remove() {}

	virtual void Notify() = 0;
};

//abstract class Observer
class Observer {
public:
	virtual void Update() = 0;
};

//concrete class below for observable
class Subject : public Observable {
public:
	std::vector<Observer*> observers;

	//add observers from this observable
	void Add(Observer& observer) {
		this->observers.push_back(&observer); //-> if pass argument as pointer
		//this->observers.push_back(&observer); //-> if pass argument by reference
	}

	//remove observer from this observable
	void Remove(Observer& observer) {
		//iterate for the position of the given observer
		//std::vector<Observer*>::iterator itr = std::find(this->observers.begin(), this->observers.end(), &observer); -> same as below
		auto itr = std::find(this->observers.begin(), this->observers.end(), &observer);
		this->observers.erase(itr);
	}

	//sample data
	int getData() {
		return 1;
	}

	//by calling this function - notify the observers
	void Notify() override {
		for (int i = 0; i < this->observers.size(); i++) {
			this->observers[i]->Update();
		}
	}
};

//concrete classes below for observer
class Subscriber : public Observer {
public:
	Subject& topic_;

	Subscriber(Subject& topic) : topic_(topic) {
	}

	void Update() override {
		std::cout << this->topic_.getData() << std::endl;
		std::cout << "Subscriber is notified" << std::endl;
	}
};

class Subscriber1 : public Observer {
public:
	Subject& topic_;

	Subscriber1(Subject& topic) : topic_(topic) {
	}

	void Update() override {
		std::cout << "Subscriber1 is notified" << std::endl;
		std::cout << this->topic_.getData() << std::endl;
	}
};

class Subscriber2 : public Observer {
public:
	Subject& topic_;

	Subscriber2(Subject& topic) : topic_(topic){
	}

	void Update() override {
		std::cout << "Subscriber2 is notified" << std::endl;
		std::cout << this->topic_.getData() << std::endl;
	}
};

int main()
{
	Subject subj;
	Subject subj1;
	Subscriber sub(subj);
	Subscriber1 sub1(subj);
	Subscriber2 sub2(subj);
	Subscriber1 sub3(subj);
	Subscriber2 sub4(subj1);

	subj.Add(sub);
	subj.Add(sub1);
	subj.Add(sub2);
	subj.Add(sub3);
	subj1.Add(sub4);

	subj.Remove(sub1);

	subj.Notify();
	subj1.Notify();

    return 0;
}

