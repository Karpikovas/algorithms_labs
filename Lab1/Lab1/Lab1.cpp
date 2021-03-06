#include "stdafx.h"
#include "QueueLinks.cpp"


using namespace std;

void printTable(Queue <Detail> &queue, int size);

int main()
{
	setlocale(LC_ALL, "russian");
	
	Queue <Detail> queue; //очередь деталей
	Detail currentDetail; //текущая деталь на обработке
	
	int countOfDetails = 0;
	currentDetail.time = NULL;

	char command[10];
	char menu[256] = "1 - Поставить деталь на обработку\n" \
		"2 - Снять деталь с обработки \n" \
		"3 - Сброс\n" \
		": ";
	

	while(1) {
		system("cls");
		
		/*---------------- Деталь была снята с обработки ---------------------*/
		if (currentDetail.time == -1) {

			/*--------------- Вывод сообщения о снятии детали ---------------*/
			cout << "Деталь " << currentDetail.name << " снята с обработки!" << endl << endl;
			currentDetail.time = NULL;

			/*--------------- Исключение детали из очереди -----------------*/
			queue.deQueue();
			countOfDetails--;

			/* --------------- Получение следующей детали на обработку -----------------*/
			queue.front(currentDetail);
		}


		if (!queue.isEmpty()) {	

			/*-------------- Обработка детали окончена --------------------------*/
			if (currentDetail.time == 0) {

				/*--------------- Исключение детали из очереди -----------------*/
				queue.deQueue();
				countOfDetails--;

				/*--------------- Вывод сообщения о снятии детали ---------------*/
				cout << "Обработка детали " << currentDetail.name << " завершена!" << endl << endl;

				/* --------------- Получение следующей детали на обработку -----------------*/
				queue.front(currentDetail);
			}
			
			/* --------------- Вывод информации о процессе обработки текущей детали -----------------*/
			if (!queue.isEmpty()) {
				
				cout << setw(20) << "Текущая деталь#";
				cout << setw(20) << "Оставшееся время" << endl;

				cout << setw(20) << currentDetail.name;
				cout << setw(20) << currentDetail.time << endl << endl;
			}
		}


		printTable(queue, countOfDetails);


		cout << menu << endl;
		cin.getline(command, 10, '\n');

		switch (command[0])
		{
			/*-------------- Процесс обработки -----------*/
		case ' ':
			currentDetail.time--;
			break;

			/*------------------Включение детали в очередь-------------*/
		case '1':
		{
			Detail *detail = new Detail;

			cout << "Название: ";
			cin >> detail->name;
			cout << endl << "Время: ";
			cin >> detail->time;

			if (queue.isEmpty()) {
				currentDetail = *detail;
			}
			queue.enQueue(detail);
			countOfDetails++;
		}
			break;
			/*--------------------Снятие детали с обработки -------------------*/
		case '2': 
			currentDetail.time = -1;
			break;

			/*-----------------Начальная инициализация-------------------------*/
		case '3':
			queue.clear();
			break;
		default:
			break;
		}
	};
	return 0;
}

/*--------------------Вывод очереди деталей на экран--------------------*/
void printTable(Queue <Detail> &queue, int size) {
	Detail *queueArray;

	if (queue.isEmpty()) {
		cout << "Очередь пуста" << endl << endl;
	}
	else {
		queueArray = queue.getArray();

		cout << "Очередь на обработку:" << endl;
		cout << setiosflags(ios::left);

		cout << setw(20) << "Название#";
		cout << setw(20) << "Время обработки" << endl;


		for (int i = 0; i < size; i++) {

			cout << setw(20) << (queueArray + i)->name;
			cout << setw(20) << (queueArray + i)->time << endl;
		}
		cout << endl;
	}
}