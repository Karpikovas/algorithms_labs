#include "stdafx.h"
#pragma once

typedef struct Enrollee {
	char surname[50];

	int scoreFirst;
	int scoreSecond;
	int scoreThird;
	bool isDistinctionCertificate = false;

	char whereFrom[128];
	bool needHostel = false;

	Enrollee *next = NULL;
	Enrollee *nextBestScore = NULL;
	Enrollee *nextHasDistinctionCertificate = NULL;
	Enrollee *nextIsNonresident = NULL;
	Enrollee *nextNeedHostel = NULL;
};

class List {
protected:
	Enrollee * first;
	Enrollee *last;
	Enrollee *ptr;
public:
	List();
	~List();
	bool isEmpty();
	virtual void clear();
	virtual bool insert(Enrollee *item);
	virtual bool del(char* surname);
	virtual Enrollee* getArray();
	virtual bool isInclude(Enrollee *item);
};