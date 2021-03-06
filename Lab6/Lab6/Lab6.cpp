#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h> 
#include <fstream>
#include <string>
#include <algorithm> 
#define _CRT_SECURE_NO_WARNINGS

#define MAX_REC_COUNT 10

using namespace std;

struct ExtFile
{
	fstream File;
	int currentElem = -1; // текущий элемент в файле
	char eor; // индикатор конца отрезка
};

struct Record
{
	int waysCount;
	int stepsCount;
	double time;
};


ExtFile fileArray[MAX_REC_COUNT * 2];
int L;
int t[MAX_REC_COUNT * 2];
int ta[MAX_REC_COUNT * 2];



void copy(ExtFile *x, ExtFile *y)
{
	string key;

	y->currentElem = x->currentElem;
	y->File << &y->currentElem << endl;
	getline(x->File, key);
	x->currentElem = atoi(key.c_str());
	x->eor = x->currentElem<y->currentElem;
}

void initIndexMap(int waysCount) {
	for (int i = 0; i < waysCount * 2; i++) {
		t[i] = i;
	}
}

/*----------------------- Начальное распределение отрезков ------------------------*/

void SegmentDistribution(string fileName, int waysCount) {

	string key;
	ifstream in(fileName);

	for (int i = 0; i < waysCount; i++) {
		string fileName = to_string(waysCount) + "/" + to_string(i) + ".txt";
		fileArray[i].File.open(fileName, fstream::out);
	}

	L = 0;
	int i = 0;

	while (!in.eof()) {
		
		getline(in, key);

		if (key.length() > 0) {
			fileArray[i].File << key << endl;
			L++;
		}

		i = (i + 1) % waysCount;
	}

	for (int i = 0; i < waysCount; i++) {
		fileArray[i].File.close();
	}

	in.close();
}

/*-------------------------- Сортировка ----------------------------------*/

int BalancedMergeSort(int waysCount) {
	int stepCount = 0; // количество проходов
	string key;

	/*----------------- Вызываем начальное распределение отрезков ----------------*/

	SegmentDistribution("input.txt", waysCount);

	/*--------------- Выполняем начальную инициализацию индексной карты ----------*/

	initIndexMap(waysCount);	


	do {
		stepCount++;
		int af = min(L, waysCount);// количество активных файлов

		/*---------------- Открываем файлы на чтение/запись --------------*/

		for (int i = 0; i < af; i++) {
			string fileName = to_string(waysCount) + "/" + to_string(t[i]) + ".txt";
			fileArray[t[i]].File.open(fileName, fstream::in );
		}

		for (int i = waysCount; i < waysCount * 2; i++) {
			string fileName = to_string(waysCount) + "/" + to_string(t[i]) + ".txt";
			fileArray[t[i]].File.open(fileName, fstream::out);
		}

		/*----------- Инициализация массива ta и определение первого элемента отрезков в файлах --------*/

		for (int i = 0; i < af; i++) {
			ta[i] = t[i];

			fileArray[t[i]].File.clear();
			fileArray[t[i]].File.seekg(0);
			getline(fileArray[t[i]].File, key);
			fileArray[t[i]].currentElem = atoi(key.c_str());
		}

		L = 0;
		int j = waysCount;

		do {
			L++;
			int ao = af;// количество активных файлов с активными отрезками

			do {

				/*-------------- Поиск индекса файла с минимальным ключом -----------*/

				int m = 0;
				int minValue = fileArray[ta[0]].currentElem;
				int i = 1;
				while (i < ao) {

					if (fileArray[ta[i]].currentElem < minValue) {
						minValue = fileArray[ta[i]].currentElem;
						m = i;
					}
					i++;
				}

				/*------------------ Копирование записи ----------------------*/

				fileArray[t[j]].currentElem = fileArray[ta[m]].currentElem;
				fileArray[t[j]].File << fileArray[t[j]].currentElem << endl;

				getline(fileArray[ta[m]].File, key);
				fileArray[ta[m]].currentElem = atoi(key.c_str());

				fileArray[ta[m]].eor = fileArray[ta[m]].currentElem < fileArray[t[j]].currentElem;

				/*----------------- Если файл закончился ----------------*/

				if (fileArray[ta[m]].File.eof()) {
					fileArray[ta[m]].eor = 0;
					ta[m] = ta[ao-1];
					ta[ao-1] = ta[af-1];
					af--;
					ao--;
				}
				/*---------------- Если в файле конец отрезка ------------*/

				else if (fileArray[ta[m]].eor) {
					int tx = ta[m];
					ta[m] = ta[ao - 1];
					ta[ao - 1] = tx;
					ao--;
				}


			} while (ao > 0);
			if (j < waysCount * 2 - 1) j++; else j = waysCount;
		} while (af > 0);

		/*------------ Переключение индексной карты и закрытие файлов ------------*/

		for (int i = 0; i< waysCount; i++)
		{
			int tx = t[i];
			t[i] = t[i + waysCount];
			t[i + waysCount] = tx;
		}
		for (int i = 0; i < waysCount * 2; i++) {
			fileArray[i].File.close();
		}

	} while (L != 1);

	/*------------------- Запись результата сортировки --------------------*/

	ofstream OutFile(to_string(waysCount) + "/" + "Result.txt");

	string fileName = to_string(waysCount) + "/" + to_string(t[0]) + ".txt";
	fileArray[t[0]].File.open(fileName, fstream::in);
	fileArray[t[0]].File.clear();
	fileArray[t[0]].File.seekg(0);

	while (!fileArray[t[0]].File.eof()) {
		getline(fileArray[t[0]].File, key);
		OutFile << key << endl;
	}

	OutFile.close();
	fileArray[t[0]].File.close();

	return stepCount;
}


/*--------------------------- Генерация ключей ------------------------------*/

void GenerateRandomKeys()


{
	static const char alphanum[] =
		"0123456789";
	string res;

	fstream keys("input.txt", fstream::out);

	if (keys) {
		for (int i = 0; i < 10000; ++i) {
			int key = 1 + rand() % (10000 - 1);
			for (int j = 0; j < 195; ++j) {
				res += alphanum[rand() % (sizeof(alphanum) - 1)];
			}
			keys << key << endl;
			res = "";

		}
	}
}

void fileOut(Record* records)
{
	ofstream OutFile("output.txt");


	if (!OutFile) cout << "Error" << endl;
	else {

		for (int waysCount = 2; waysCount <= MAX_REC_COUNT; waysCount++) {
			OutFile << records[waysCount - 2].waysCount << '\t' << records[waysCount - 2].time << '\t' << records[waysCount - 2].stepsCount  << endl;
		}
	}
	OutFile.close();
}


int main()
{
	srand(time(nullptr));
	setlocale(LC_ALL, "russian");
	setlocale(LC_NUMERIC, "RUS");

	
	Record* records;
	records = new Record[9];

	GenerateRandomKeys();


	int ways = 2;

	cout << "Количество путей" << '\t' << "Время сек" << '\t' << "Количество шагов" << endl;

	for (int waysCount = 2; waysCount <= MAX_REC_COUNT; waysCount++) {
		records[waysCount - 2].waysCount = waysCount;

		clock_t t = clock();
		records[waysCount - 2].stepsCount = BalancedMergeSort(waysCount);
		records[waysCount - 2].time = (static_cast<double>(clock() - t) / CLOCKS_PER_SEC);

		cout << '\t' << records[waysCount - 2].waysCount << "\t\t" << records[waysCount - 2].time << "\t\t\t" << records[waysCount - 2].stepsCount << endl;
	}

	fileOut(records);
	
	system("pause");


	return 0;
}

