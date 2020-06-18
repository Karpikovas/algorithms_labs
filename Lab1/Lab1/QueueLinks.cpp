#include "stdafx.h"
#pragma once

using namespace std;

/*--------------Cтруктура Деталь--------------*/
typedef struct Detail {
	char name[20];
	int time;
	Detail *next;
};

template <class type> class Queue
{
	type* first;
	type* last;
	type* ptr;
public:
	Queue() {
		first = NULL;
		last = NULL;
	};
	~Queue() {
		clear();
	};

	/*-----------------Включение элемента в очередь-------------*/
	bool enQueue(type *item) {
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

	/*-----------------Исключение элемента из очереди-------------*/

	bool deQueue() {
		if (isEmpty()) {
			return false;
		}
		if (first->next != NULL) {
			type* tmp = first;
			first = first->next;
			free(tmp);
		}
		else {
			free(first);
			first = NULL;
		}
		return true;
	};

	/*----------------- Получение первого элемента из очереди-------------*/

	bool front(type &elem) {
		if (isEmpty()) {
			return false;
		}
		elem = *first;
		return true;
	};

	/*-----------------Проверка очереди на пустоту-----------------*/

	bool isEmpty() {
		if (first == NULL) {
			return true;
		}
		else {
			return false;
		}
	};

	/*-----------------Получение упорядоченного массива элементов очереди---------------*/
	type* getArray() {
		type queueArray[128];

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

	/*------------------------ Сброс очереди ----------------------*/
	void clear() {
		ptr = first;

		while (1) {
			if (ptr->next == NULL) {
				free(ptr);
				break;
			}
			type *tmp = ptr->next;
			free(ptr);
			ptr = tmp;
		}

		first = NULL;
		last = NULL;
	};
};

