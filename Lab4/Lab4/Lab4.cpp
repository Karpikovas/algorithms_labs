#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h> 
#include <fstream>
#include <string>

#define COUNT_OF_KEYS 500
#define KEY_LENGTH 6


using namespace std;

struct Address
{
	int cnt_keys = 0;
	int cnt_collision = 0;
};

/*-------------------- Хэш-функция метод деления -----------------*/

int HashFunctionDivision(int k, int M)
{
	return (k % M);
}

/*--------------------- Хэш-функция метод умножения -----------------*/

int HashFunctionMultiplication(int k, int M)
{
	double A = (sqrt(5.0) - 1.0) / 2.0;
	double i;

	return int(M * modf(k * A, &i));
}

/*---------------------- Аддитивный метод ----------------------------*/

int AdditiveMethod(string key)
{
	int intKey = 0;
	for (int i = 0; i < KEY_LENGTH; i++) {
		intKey += (int)key[i];
	}
	return intKey;
}

/*---------------------- Метод исключающего ИЛИ ------------------------------*/

int XORMethod(string key)
{
	int intKey = 0;
	int Rand8[6] = { 192, 171, 462, 293, 52, 36 };

	for (int i = 0; i < KEY_LENGTH; i++) {
		intKey += (int)key[i] ^ Rand8[i];
	}
	return intKey;
}

/*---------------------------- Вывод в файл -----------------------------*/

void fileOut(string filename, Address* addresses, int M)
{
	unsigned int general_collision = 0;
	ofstream OutFile(filename);
	

	if (!OutFile) cout << "Error" << endl;
	else {
		for (int i = 0; i < M; i++) {
			OutFile << i << '.'<< '\t' << addresses[i].cnt_keys << '\t' << addresses[i].cnt_collision << endl;
			general_collision += addresses[i].cnt_collision;
		}
		OutFile << "Общая коллизия = " << general_collision << endl;
	}
	OutFile.close();
}

/*--------------------------- Генерация ключей ------------------------------*/

void GenerateRandomKeys(int num)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	string res;

	ofstream keys("keys.txt");

	if (keys) {
		for (int i = 0; i < num; ++i) {
			for (int j = 0; j < 6; ++j) {
				res += alphanum[rand() % (sizeof(alphanum) - 1)];
			}
			keys << res << endl;
			res = "";
		}
	}
}

int main()
{
	srand(time(nullptr));
	setlocale(LC_ALL, "russian");


	int M = 0; //размер таблицы

	/*------------- Результаты аддитивного метода -----------------*/

	Address* additiveDivision;
	Address* additiveMultiplication;
	
	/*-------------- Результаты метода исключающего или ----------------------*/

	Address* XORDivision;
	Address* XORMultiplication;


	cout << "Введите размер таблицы: ";
	cin >> M;
	
	/*--------------- Инициализация результирующих таблиц -------------------*/

	additiveDivision = new Address[M];
	XORDivision = new Address[M];
	additiveMultiplication = new Address[M];
	XORMultiplication = new Address[M];

	/*--------------------------- Генерация ключей ------------------------------*/

	GenerateRandomKeys(COUNT_OF_KEYS);
	ifstream in("keys.txt");

	string key;
	int i = 0;


	while (i != COUNT_OF_KEYS) {

		getline(in, key);

		/*---------------- Преобразование строковых ключей ---------------------*/

		int additiveKey = AdditiveMethod(key);
		int XORKey = XORMethod(key);

		/*------------------ Получение численных ключей -----------------------*/

		int idxAdditiveDivision = HashFunctionDivision(additiveKey, M);
		int idxXORDivision = HashFunctionDivision(XORKey, M);
		int idxAdditiveMultiplication = HashFunctionMultiplication(additiveKey, M);
		int idxXORMultiplication = HashFunctionMultiplication(XORKey, M);;

		/*------------------- Добавление ключей, добавлений коллизий --------------------*/

		additiveDivision[idxAdditiveDivision].cnt_keys++;
		if (additiveDivision[idxAdditiveDivision].cnt_keys > 1)
			additiveDivision[idxAdditiveDivision].cnt_collision++;

		XORDivision[idxXORDivision].cnt_keys++;
		if (XORDivision[idxXORDivision].cnt_keys > 1)
			XORDivision[idxXORDivision].cnt_collision++;

		additiveMultiplication[idxAdditiveMultiplication].cnt_keys++;
		if (additiveMultiplication[idxAdditiveMultiplication].cnt_keys > 1)
			additiveMultiplication[idxAdditiveMultiplication].cnt_collision++;

		XORMultiplication[idxXORMultiplication].cnt_keys++;
		if (XORMultiplication[idxXORMultiplication].cnt_keys > 1)
			XORMultiplication[idxXORMultiplication].cnt_collision++;

		i++;
	}

	/*--------------------- Запись результатов в файл ------------------------------*/

	fileOut("additiveDivision.txt", additiveDivision, M);
	fileOut("XORDivision.txt", XORDivision, M);
	fileOut("additiveMultiplication.txt", additiveMultiplication, M);
	fileOut("XORMultiplication.txt", XORMultiplication, M);
	
	system("pause");
    return 0;
}

