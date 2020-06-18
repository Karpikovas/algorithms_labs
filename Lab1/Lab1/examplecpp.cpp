// Lab1.cpp: определяет точку входа для консольного приложения.
//
/*
#include "stdafx.h"
#include<Windows.h>
#include <iomanip>
#include <stdlib.h>
#include "QueueLinks.cpp"


using namespace std;

bool KEY[256];
void GetKEY()
{
	int i = 0;
	while (i < 256)
	{
		if (GetAsyncKeyState(i)) KEY[i] = 1; else KEY[i] = 0;
		i++;
	}
}

void printTable(Queue <Detail> &queue) {
	if (queue.isEmpty()) {
		cout << "Очередь пуста" << endl << endl;
	}
	else {
		cout << "Очередь на обработку:" << endl;
		cout << setiosflags(ios::left);

		cout << setw(20) << "Название#";
		cout << setw(20) << "Время обработки" << endl;

		int i = (queue.head % MAXLENGTH);

		while (i != queue.tail) {

			cout << setw(20) << queue.queue[i - 1].name;
			cout << setw(20) << queue.queue[i - 1].time << endl;

			i = (i % MAXLENGTH + 1);
		}
		cout << endl;
	}
}




int main()
{
	setlocale(LC_ALL, "russian");

	Queue <Detail> queue;
	char cancelName[20] = "";

	char menu[256] = "1 - Поставить делать на обработку\n" \
		"2 - Снять деталь с обработки \n" \
		"3 - Сброс\n" \
		": ";

	char command[10];


	while (1) {
		system("cls");

		if (strcmp(cancelName, "")) {
			cout << "Деталь " << cancelName << " снята с обработки!" << endl << endl;
			strcpy_s(cancelName, "");
		}

		if (!queue.isEmpty()) {

			int head = (queue.head % MAXLENGTH);

			if (queue.queue[head - 1].time == 0) {
				Detail detail;
				queue.deQueue(detail);
				cout << "Обработка детали " << detail.name << " завершена!" << endl << endl;

				head = (queue.head % MAXLENGTH);
			}

			if (!queue.isEmpty()) {
				Detail currentDetail = queue.queue[head - 1];
				cout << setw(20) << "Текущая деталь#";
				cout << setw(20) << "Оставшееся время" << endl;

				cout << setw(20) << currentDetail.name;
				cout << setw(20) << currentDetail.time << endl << endl;
			}
		}


		printTable(queue);
		cout << menu << endl;

		cin.getline(command, 10, '\n');

		switch (command[0])
		{
		case ' ':
		{
			if (!queue.isEmpty()) {
				int head = (queue.head % MAXLENGTH);
				queue.queue[head - 1].time--;
			}
		}
		break;
		case '1':
		{
			Detail detail;

			cout << "Название: ";
			cin >> detail.name;
			cout << endl << "Время: ";
			cin >> detail.time;

			queue.enQueue(detail);
		}
		break;
		case '2':
		{
			Detail detail;
			queue.deQueue(detail);
			strcpy_s(cancelName, detail.name);
		}
		break;
		case '3':
			queue.clear();
			break;
		default:
			break;
		}


	};
	return 0;
}

*/