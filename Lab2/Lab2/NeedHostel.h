#pragma once
#include "List.h"

class NeedHostel : public List
{
public:
	NeedHostel();
	~NeedHostel();
	bool insert(Enrollee *item);
	bool del(char* surname);
	void clear();
	Enrollee* getArray();
	bool isInclude(Enrollee *item);
};

