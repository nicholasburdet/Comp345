#pragma once
/*!
	Abstract class for implementation of observer pattern
*/



class observer
{
public:
	observer();
	virtual ~observer();


	void virtual notify() = 0;
};

