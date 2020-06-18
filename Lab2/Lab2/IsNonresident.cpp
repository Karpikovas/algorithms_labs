#include "stdafx.h"
#include "IsNonresident.h"


IsNonresident::IsNonresident(){}


IsNonresident::~IsNonresident(){}

bool IsNonresident::insert(Enrollee *item) {
	item->nextIsNonresident = NULL;
	if (isEmpty()) {
		first = item;
		last = item;
	}
	else {
		last->nextIsNonresident = item;
		last = item;
	}
	return true;
};

bool IsNonresident::del(char* surname) {
	if (isEmpty()) {
		return false;
	}

	ptr = first;

	while (1) {
		if (ptr->nextIsNonresident == NULL) {
			if (!strcmp(ptr->surname, surname)) {
				clear();
				return true;
			}
			else {
				return false;
			}
		}

		if (!strcmp(ptr->surname, surname)) {
			first = ptr->nextIsNonresident;
			return true;
		}

		if (!strcmp(ptr->nextIsNonresident->surname, surname)) {
			Enrollee *tmp = ptr->nextIsNonresident->nextIsNonresident;
			ptr->nextIsNonresident = tmp;
			if (tmp == NULL) {
				last = ptr;
			}
			return true;
		}
		ptr = ptr->nextIsNonresident;
	}

	return false;
}

void IsNonresident::clear() {
	if (isEmpty()) {
		return;
	}
	ptr = first;

	while (1) {
		if (ptr->nextIsNonresident == NULL) {
			break;
		}
		Enrollee *tmp = ptr->nextIsNonresident;
		ptr = tmp;
	}

	first = NULL;
	last = NULL;
}

Enrollee* IsNonresident::getArray() {
	Enrollee queueArray[128];

	ptr = first;
	int i = 0;

	while (1) {
		queueArray[i] = *ptr;
		if (ptr->nextIsNonresident == NULL) {
			break;
		}
		ptr = ptr->nextIsNonresident;
		i++;
	}

	return queueArray;
};

bool IsNonresident::isInclude(Enrollee *item) {
	if (strcmp(item->whereFrom, LOCATION))
		return true;
	return false;
};