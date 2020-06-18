#include "stdafx.h"
#include "NeedHostel.h"


NeedHostel::NeedHostel(){}
NeedHostel::~NeedHostel(){}

bool NeedHostel::insert(Enrollee *item) {
	item->nextNeedHostel = NULL;
	if (isEmpty()) {
		first = item;
		last = item;
	}
	else {
		last->nextNeedHostel = item;
		last = item;
	}
	return true;
};

bool NeedHostel::del(char* surname) {
	if (isEmpty()) {
		return false;
	}

	ptr = first;

	while (1) {
		if (ptr->nextNeedHostel == NULL) {
			if (!strcmp(ptr->surname, surname)) {
				clear();
				return true;
			}
			else {
				return false;
			}
		}

		if (!strcmp(ptr->surname, surname)) {
			first = ptr->nextNeedHostel;
			return true;
		}

		if (!strcmp(ptr->nextNeedHostel->surname, surname)) {
			Enrollee *tmp = ptr->nextNeedHostel->nextNeedHostel;
			ptr->nextNeedHostel = tmp;
			if (tmp == NULL) {
				last = ptr;
			}
			return true;
		}
		ptr = ptr->nextNeedHostel;
	}

	return false;
}

void NeedHostel::clear() {
	if (isEmpty()) {
		return;
	}
	ptr = first;

	while (1) {
		if (ptr->nextNeedHostel == NULL) {
			break;
		}
		Enrollee *tmp = ptr->nextNeedHostel;
		ptr = tmp;
	}

	first = NULL;
	last = NULL;
}

Enrollee* NeedHostel::getArray() {
	Enrollee queueArray[128];

	ptr = first;
	int i = 0;

	while (1) {
		queueArray[i] = *ptr;
		if (ptr->nextNeedHostel == NULL) {
			break;
		}
		ptr = ptr->nextNeedHostel;
		i++;
	}

	return queueArray;
};
bool NeedHostel::isInclude(Enrollee *item) {
	return item->needHostel;
};
