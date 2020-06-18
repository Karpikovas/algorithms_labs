#pragma once
#include "List.h"

class HasDistinctionCertificate : public List
{
public:
	HasDistinctionCertificate();
	~HasDistinctionCertificate();
	bool insert(Enrollee *item);
	bool del(char* surname);
	void clear();
	Enrollee* getArray();
	bool isInclude(Enrollee *item);
};

