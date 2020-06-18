#include "stdafx.h"
#pragma once
#define MAXLENGTH 6

using namespace std;

/*--------------Cтруктура Деталь--------------*/
typedef struct Detail {
	char name[20];
	int time;
};

template <class type> class Queue
{
public:
	int head;
	int tail;
	type queue[MAXLENGTH];

	Queue() {
		head = 1;
		tail = 1;
	};
	~Queue() {
		clear();
	};

	/*-----------------Включение элемента в очередь-------------*/

	bool enQueue(type *item) {
		if (isOwerflow()) {
			return false;
		}
		if (isEmpty()) {
			queue[head - 1] = *item;
			tail = tail % MAXLENGTH + 1;
		}
		else {
			queue[tail - 1] = *item;
			tail = tail % MAXLENGTH + 1;
		}
		return true;
	};

	/*-----------------Исключение элемента из очереди-------------*/

	bool deQueue() {
		if (isEmpty()) {
			return false;
		}
		head = head % MAXLENGTH + 1;
		return true;
	};

	/*----------------- Получение первого элемента из очереди-------------*/

	bool front(type &elem) {
		if (isEmpty()) {
			return false;
		}
		elem = queue[head - 1];
		return true;
	};

	/*-----------------Проверка очереди на пустоту-----------------*/
	
	bool isEmpty() {
		if (head == tail) {
			return true;
		}
		else {
			return false;
		}
	};

	/*-----------------Проверка очереди на наполненность-----------------*/

	bool isOwerflow() {
		if (head == (tail % MAXLENGTH + 1)) {
			return true;
		}
		else {
			return false;
		}
	}

	/*------------------------ Сброс очереди ----------------------*/
	void clear() {
		head = 1;
		tail = 1;
		memset(queue, MAXLENGTH, sizeof(type));
	};

	/*-----------------Получение упорядоченного массива элементов очереди---------------*/
	type* getArray() {
		type queueArray[128];
		int i = (head % MAXLENGTH);
		int j = 0;

		while (i != tail) {
			queueArray[j] = queue[i - 1];
			i = (i % MAXLENGTH + 1);
			j++;
		}
		return queueArray;
	}
};