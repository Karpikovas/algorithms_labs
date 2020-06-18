#pragma once
#include "List.h"
class BestScore : public List
{
public:
	BestScore();
	~BestScore();
	bool insert(Enrollee *item);
	bool del(char* surname);
	bool isInclude(Enrollee *item);
	void clear();
	Enrollee* getArray();
};

