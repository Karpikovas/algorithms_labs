#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h> 
#include <fstream>
#include <string>

#define COUNT_OF_KEYS 250
#define KEY_LENGTH 6


using namespace std;

struct Table
{
	int cntKeys = 0;
	float searchLength = 0;
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

/*---------------------- Метод открытой адресации с линейным опробованием -----------------------*/

int CheckLinear(int key, int i, int M)
{
	int c = 73;
	return (key + c * i) % M;
}

/*-------------------- Метод открытой адресации с квадратичным опробованием --------------------*/

int CheckSquare(int key, int i, int M)
{
	int c = 73;
	int d = 3;
	return (key + c * i + d * i * i) % M;
}

/*---------------------------- Вывод в файл -----------------------------*/


void fileOut(string filename, Table* tables)
{
	ofstream OutFile(filename);


	if (!OutFile) cout << "Error" << endl;
	else {
		for (int i = 10; i < COUNT_OF_KEYS; i += 10) {
			OutFile << tables[i / 10 - 1].cntKeys << '\t' << tables[i / 10 - 1].searchLength << endl;
		}
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

/*----------------------- Формирование таблиц и подсчет средней длины пути ------------------------*/

float GenerateTable(int(*HashFunction)(int, int), int(*StategyType)(int, int, int), int M, int cntOfKeys)
{
	string key;
	ifstream in("keys.txt");

	string table[1024];
	vector<int> res;

	int j = 0;

	while (j != cntOfKeys)
	{
		getline(in, key);
		int i = 0;

		while (i != M)
		{
			int a = StategyType(HashFunction(XORMethod(key), M), i, M);

			if (table[a].empty()) {
				table[a] = key;
				res.push_back(i);
				break;
			}
			else if (table[a] == key) {
				res.push_back(i);
				break;
			}
			else {
				i++;
			}
		}
		res.push_back(i);
		j++;
	}

	int sum = 0;
	for (int k = 0; k < res.size(); ++k)
	{
		sum += res[k];
	}

	return float(sum) / cntOfKeys;
}

int main()
{
	srand(time(nullptr));
	setlocale(LC_ALL, "russian");
	setlocale(LC_NUMERIC, "RUS");


	int M = 256;

	/*------------- Результаты метода открытой адресации с линейным опробованием -----------------*/

	Table* linearDivision;
	Table* linearMultiplication;

	/*------------- Результаты метода открытой адресации с квадратичным опробованием -----------------*/

	Table* squareDivision;
	Table* squareMultiplication;


	/*--------------- Инициализация результирующих таблиц -------------------*/

	linearDivision = new Table[COUNT_OF_KEYS / 10];
	linearMultiplication = new Table[COUNT_OF_KEYS / 10];
	squareDivision = new Table[COUNT_OF_KEYS / 10];
	squareMultiplication = new Table[COUNT_OF_KEYS / 10];

	/*--------------------------- Генерация ключей ------------------------------*/

	GenerateRandomKeys(COUNT_OF_KEYS);
	ifstream in("keys.txt");

	string key;


	for (int cntKeys = 10; cntKeys < COUNT_OF_KEYS; cntKeys += 10) {

		/*------------------ Заполняем текущее значение ключей -----------------------------*/

		linearDivision[cntKeys / 10 - 1].cntKeys = cntKeys;
		linearMultiplication[cntKeys / 10 - 1].cntKeys = cntKeys;
		squareDivision[cntKeys / 10 - 1].cntKeys = cntKeys;
		squareMultiplication[cntKeys / 10 - 1].cntKeys = cntKeys;

		/*------------------- Заполняем средние показатели длины пути -----------------------------*/

		linearDivision[cntKeys / 10 - 1].searchLength = GenerateTable(HashFunctionDivision, CheckLinear, M, cntKeys);		
		linearMultiplication[cntKeys / 10 - 1].searchLength = GenerateTable(HashFunctionMultiplication, CheckLinear, M, cntKeys);
		squareDivision[cntKeys / 10 - 1].searchLength = GenerateTable(HashFunctionDivision, CheckSquare, M, cntKeys);
		squareMultiplication[cntKeys / 10 - 1].searchLength = GenerateTable(HashFunctionMultiplication, CheckSquare, M, cntKeys);

	}

	/*--------------------- Запись результатов в файл ------------------------------*/

	fileOut("linearDivision.txt", linearDivision);
	fileOut("linearMultiplication.txt", linearMultiplication);
	fileOut("squareDivision.txt", squareDivision);
	fileOut("squareMultiplication.txt", squareMultiplication);

	system("pause");
	return 0;
}

