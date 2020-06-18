#include "stdafx.h"
#include "BestScore.h"


BestScore::BestScore(){}
BestScore::~BestScore(){}

bool BestScore::insert(Enrollee *item) {
	item->nextBestScore = NULL;
	if (isEmpty()) {
		first = item;
		last = item;
	}
	else {
		last->nextBestScore = item;
		last = item;
	}
	return true;
};

bool BestScore::del(char* surname) {
	if (isEmpty()) {
		return false;
	}

	ptr = first;

	while (1) {
		if (ptr->nextBestScore == NULL) {
			if (!strcmp(ptr->surname, surname)) {
				clear();
				return true;
			}
			else {
				return false;
			}
		}

		if (!strcmp(ptr->surname, surname)) {
			first = ptr->nextBestScore;
			return true;
		}

		if (!strcmp(ptr->nextBestScore->surname, surname)) {
			Enrollee *tmp = ptr->nextBestScore->nextBestScore;
			ptr->nextBestScore = tmp;
			if (tmp == NULL) {
				last = ptr;
			}
			return true;
		}
		ptr = ptr->nextBestScore;
	}

	return false;
}

void  BestScore::clear() {
	if (isEmpty()) {
		return;
	}
	ptr = first;

	while (1) {
		if (ptr->nextBestScore == NULL) {
			break;
		}
		Enrollee *tmp = ptr->nextBestScore;
		ptr = tmp;
	}

	first = NULL;
	last = NULL;
}

Enrollee* BestScore::getArray() {
	Enrollee queueArray[128];

	ptr = first;
	int i = 0;

	while (1) {
		queueArray[i] = *ptr;
		if (ptr->nextBestScore == NULL) {
			break;
		}
		ptr = ptr->nextBestScore;
		i++;
	}

	return queueArray;
};

bool BestScore::isInclude(Enrollee *item) {
	if (item->scoreFirst == 5 && item->scoreSecond == 5 && item->scoreThird == 5)
		return true;
	return false;
}