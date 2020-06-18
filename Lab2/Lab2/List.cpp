#include "stdafx.h"
#include "List.h"

List::List() {
	first = NULL;
	last = NULL;
}

List::~List()
{}

bool List::isEmpty() {
	if (first == NULL) {
		return true;
	}
	else {
		return false;
	}
};

bool List::insert(Enrollee *item) {
	item->next = NULL;
	if (isEmpty()) {
		first = item;
		last = item;
	}
	else {
		last->next = item;
		last = item;
	}
	return true;
};

bool List::del(char* surname) {
	if (isEmpty()) {
		return false;
	}

	ptr = first;

	while (1) {
		if (ptr->next == NULL) {
			if (!strcmp(ptr->surname, surname)) {
				clear();
				return true;
			}
		}

		if (!strcmp(ptr->surname, surname)) {
			first = ptr->next;
			free(ptr);
			return true;
		}

		if (!strcmp(ptr->next->surname, surname)) {
			Enrollee *tmp = ptr->next->next;
			free(ptr->next);
			ptr->next = tmp;
			if (tmp == NULL) {
				last = ptr;
			}
			return true;
		}	
		ptr = ptr->next;
	}

	return false;
}

void List::clear() {
	ptr = first;

	while (1) {
		if (ptr->next == NULL) {
			free(ptr);
			break;
		}
		Enrollee *tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}

	first = NULL;
	last = NULL;
}

Enrollee* List::getArray() {
	Enrollee queueArray[128];

	ptr = first;
	int i = 0;

	while (1) {
		queueArray[i] = *ptr;
		if (ptr->next == NULL) {
			break;
		}
		ptr = ptr->next;
		i++;
	}

	return queueArray;
};

bool List::isInclude(Enrollee *item) {
	return true;
}