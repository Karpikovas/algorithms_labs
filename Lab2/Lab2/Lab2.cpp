// Lab2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "List.h"
#include "BestScore.h"
#include "HasDistinctionCertificate.h"
#include "IsNonresident.h"
#include "NeedHostel.h"
#define ARRAYLENGTH 5

void printTable(List *list, int size);
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); 

	List* lists[] = { new List, new BestScore, new HasDistinctionCertificate, new IsNonresident, new NeedHostel };
	int size[5];

	memset(size, 0, sizeof(size));


	int command;
	char menu[356] = "1 - Добавить абитуриента\n" \
		"2 - Список всех абитуриентов \n" \
		"3 - Список абитуриентов, имеющих по всем экзаменам результат \"отлично\"\n" \
		"4 - Список абитуриентов, имеющих аттестат с отличием\n"	\
		"5 - Список иногородних абитуриентов\n"	\
		"6 - Список нуждающихся в общежитии\n" \
		"7 - Удалить информацию об абитуриенте (по фамилии)\n" \
		"8 - Очистка БД\n" \
		": ";

	while (1) {

		cout << menu << endl;
		cin >> command;

		switch (command)
		{
			/*-------------- Добавить абитуриента -----------*/
		case 1: 
		{
			system("cls");
			Enrollee *enrolle = new Enrollee;
			char flag[100];

			cout << "Фамилия: ";
			cin >> enrolle->surname;

			cout << endl << "Первая оценка: ";
			cin >> enrolle->scoreFirst;
			cout << endl << "Вторая оценка: ";
			cin >> enrolle->scoreSecond;
			cout << endl << "Третья оценка: ";
			cin >> enrolle->scoreThird;

			cout << endl << "Аттестат с отличием (да/Нет): ";
			cin >> flag;

			if (!strcmp(flag, "да")) {
				enrolle->isDistinctionCertificate = true;
			}

			cout << endl << "Населенный пункт: ";
			cin >> enrolle->whereFrom;

			cout << endl << "Необходимость общежития (да/Нет): ";
			cin >> flag;

			if (!strcmp(flag, "да")) {
				enrolle->needHostel = true;
			}

			for (int i = 0; i < ARRAYLENGTH; i++) {
				if (lists[i]->isInclude(enrolle)) {
					lists[i]->insert(enrolle);
					size[i]++;
				}
			}
			system("cls");
			cout << "Абитуриент успешно добавлен!" << endl << endl;
		}
			break;

			/*-----------------Список всех абитуриентов-------------*/
		case 2:
			system("cls");
			printTable(lists[0], size[0]);	
		break;
		/*--------------------Список абитуриентов, имеющих по всем экзаменам результат "отлично" -------------------*/
		case 3:
			system("cls");
			printTable(lists[1], size[1]);
			break;

			/*-----------------Список абитуриентов, имеющих аттестат с отличием-------------------------*/
		case 4:
			system("cls");
			printTable(lists[2], size[2]);
			break;
			/*-----------------Список иногородних абитуриентов-------------------------*/
		case 5:
			system("cls");
			printTable(lists[3], size[3]);
			break;
			/*-----------------Список нуждающихся в общежитии-------------------------*/
		case 6:
			system("cls");
			printTable(lists[4], size[4]);
			break;
			/*-----------------Удалить информацию об абитуриенте (по фамилии)-------------------------*/
		case 7: 
		{
			system("cls");
			char surname[100];
			bool flag = false;

			cout << "Фамилия: ";
			cin >> surname;

			for (int i = ARRAYLENGTH - 1; i >= 0; i--) {
				if (lists[i]->del(surname)) {
					size[i]--;
					flag = true;
				};
			}
			system("cls");
			if (flag) {
				cout << "Студент успешно удален!" << endl << endl;
			}
			else {
				cout << "Студент не найден!" << endl << endl;
			}
			
		}
			break;
			/*----------------------------Очистка БД---------------------------------*/
		case 8:
			system("cls");
			for (int i = ARRAYLENGTH - 1; i >= 0; i--) {
				lists[i]->clear();
			}
			cout << "Все данные стерты!" << endl << endl;
			break;
		default:
			break;
		}
	}


    return 0;
}

void printTable(List *list, int size) {
	Enrollee *listArray;

	if (list->isEmpty()) {
		cout << "Информация отсутствует" << endl << endl;
	}
	else {
		listArray = list->getArray();

		cout << setiosflags(ios::left);
		cout << setw(20) << "Фамилия#";
		cout << setw(10) << "Экзамены";
		cout << setw(20) << "Аттестат с отличием";
		cout << setw(20) << "Город";
		cout << setw(10) << "Общежитие" << endl;


		for (int i = 0; i < size; i++) {
			char str[128];
			sprintf_s(str, "%d %d %d", (listArray + i)->scoreFirst, (listArray + i)->scoreSecond, (listArray + i)->scoreThird);

			cout << setw(20) << (listArray + i)->surname;
			cout << setw(10) << str;
			(listArray + i)->isDistinctionCertificate ? cout << setw(20) << "да"  : cout << setw(20) << "нет";
			cout << setw(20) << (listArray + i)->whereFrom;
			(listArray + i)->needHostel ? cout << setw(10) << "да" << endl : cout << setw(210) << "нет" << endl;
		}
	}
}