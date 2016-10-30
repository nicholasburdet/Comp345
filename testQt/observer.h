#pragma once
class observer
{
public:
	observer();
	virtual ~observer();


	void virtual notify() = 0;
};

