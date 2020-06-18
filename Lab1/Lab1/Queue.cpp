#include "stdafx.h"
#pragma once
#define MAXLENGTH 6

using namespace std;

/*--------------C�������� ������--------------*/
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

	/*-----------------��������� �������� � �������-------------*/

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

	/*-----------------���������� �������� �� �������-------------*/

	bool deQueue() {
		if (isEmpty()) {
			return false;
		}
		head = head % MAXLENGTH + 1;
		return true;
	};

	/*----------------- ��������� ������� �������� �� �������-------------*/

	bool front(type &elem) {
		if (isEmpty()) {
			return false;
		}
		elem = queue[head - 1];
		return true;
	};

	/*-----------------�������� ������� �� �������-----------------*/
	
	bool isEmpty() {
		if (head == tail) {
			return true;
		}
		else {
			return false;
		}
	};

	/*-----------------�������� ������� �� �������������-----------------*/

	bool isOwerflow() {
		if (head == (tail % MAXLENGTH + 1)) {
			return true;
		}
		else {
			return false;
		}
	}

	/*------------------------ ����� ������� ----------------------*/
	void clear() {
		head = 1;
		tail = 1;
		memset(queue, MAXLENGTH, sizeof(type));
	};

	/*-----------------��������� �������������� ������� ��������� �������---------------*/
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