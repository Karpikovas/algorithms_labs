#include "stdafx.h"
#include "HasDistinctionCertificate.h"


HasDistinctionCertificate::HasDistinctionCertificate(){}


HasDistinctionCertificate::~HasDistinctionCertificate(){}

bool HasDistinctionCertificate::insert(Enrollee *item) {
	item->nextHasDistinctionCertificate = NULL;
	if (isEmpty()) {
		first = item;
		last = item;
	}
	else {
		last->nextHasDistinctionCertificate = item;
		last = item;
	}
	return true;
};

bool HasDistinctionCertificate::del(char* surname) {
	if (isEmpty()) {
		return false;
	}

	ptr = first;

	while (1) {
		if (ptr->nextHasDistinctionCertificate == NULL) {
			if (!strcmp(ptr->surname, surname)) {
				clear();
				return true;
			}
			else {
				return false;
			}
		}

		if (!strcmp(ptr->surname, surname)) {
			first = ptr->nextHasDistinctionCertificate;
			return true;
		}

		if (!strcmp(ptr->nextHasDistinctionCertificate->surname, surname)) {
			Enrollee *tmp = ptr->nextHasDistinctionCertificate->nextHasDistinctionCertificate;
			ptr->nextHasDistinctionCertificate = tmp;
			if (tmp == NULL) {
				last = ptr;
			}
			return true;
		}
		ptr = ptr->nextHasDistinctionCertificate;
	}

	return false;
}
void HasDistinctionCertificate::clear() {
	if (isEmpty()) {
		return;
	}
	ptr = first;

	while (1) {
		if (ptr->nextHasDistinctionCertificate == NULL) {
			break;
		}
		Enrollee *tmp = ptr->nextHasDistinctionCertificate;
		ptr = tmp;
	}

	first = NULL;
	last = NULL;
}

Enrollee* HasDistinctionCertificate::getArray() {
	Enrollee queueArray[128];

	ptr = first;
	int i = 0;

	while (1) {
		queueArray[i] = *ptr;
		if (ptr->nextHasDistinctionCertificate == NULL) {
			break;
		}
		ptr = ptr->nextHasDistinctionCertificate;
		i++;
	}

	return queueArray;
};

bool HasDistinctionCertificate::isInclude(Enrollee *item) {
	return item->isDistinctionCertificate;
};