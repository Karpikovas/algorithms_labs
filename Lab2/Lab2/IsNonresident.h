#pragma once
#include "List.h"
#define LOCATION "Орел"

class IsNonresident : public List
{
public:
	IsNonresident();
	~IsNonresident();
	bool insert(Enrollee *item);
	bool del(char* surname);
	void clear();
	Enrollee* getArray();
	bool isInclude(Enrollee *item);
};

