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

int L;
int t[MAX_REC_COUNT * 2];
int ta[MAX_REC_COUNT * 2];

struct ExtFile
{
	fstream File;
	int currentElem = -1; // current element of this file
	char eor; // indicates end of series
};


//fstream fileArray[MAX_REC_COUNT * 2];

ExtFile fileArray[MAX_REC_COUNT * 2];


struct TSortRect
{
	int key;
	char data[196];
};

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

void SegmentDistribution(string fileName, int waysCount) {

	string key;
	string data;
	ifstream in(fileName);
	int lastKey = 1000000;

	for (int i = 0; i < waysCount; i++) {
		string fileName = to_string(i) + ".txt";
		fileArray[i].File.open(fileName, fstream::out);
	}

	L = 0;
	int i = 0;

	//getline(in, key);
	while (!in.eof()) {
		
		getline(in, key);

		if (key.length() > 0) {

			fileArray[i].File << key << endl;
			/*
			
			do {
				lastKey = atoi(key.c_str());
				fileArray[i].File << key << endl;
				getline(in, key);
			} while (!in.eof() && atoi(key.c_str()) >= lastKey);
			*/
			L++;
		}
		i = (i + 1) % waysCount;
	}

	for (int i = 0; i < waysCount; i++) {
		fileArray[i].File.close();
	}

	in.close();

}


/*
void SegmentDistribution(string fileName, int waysCount) {

	int arr[12] = { 31, 17, 05, 59, 13, 41, 67, 43, 11, 23, 29, 47 };
	string key;
	string data;
	ifstream in(fileName);
	int lastKey = 1000000;

	for (int i = 0; i < waysCount; i++) {
		string fileName = to_string(i) + ".txt";
		fileArray[i].File.open(fileName, fstream::out);
	}

	L = 0;
	int i = 0;

	//getline(in, key);
	for (int j = 0; j < 12; j++) {
		fileArray[i].File << arr[j] << endl;
		L++;
		i = (i + 1) % waysCount;
	}

	for (int i = 0; i < waysCount; i++) {
		fileArray[i].File.close();
	}

	in.close();

}

*/

void BalancedMergeSort(int waysCount) {
	string key;
	initIndexMap(waysCount);

	for (int i = waysCount; i < waysCount * 2; i++) {
		string fileName = to_string(i) + ".txt";
		fileArray[i].File.open(fileName, fstream::out);
		fileArray[i].File.close();
	}

	


	do {
		int af = min(L, waysCount);

		for (int i = 0; i < af; i++) {
			string fileName = to_string(t[i]) + ".txt";
			fileArray[t[i]].File.open(fileName, fstream::in );
		}

		for (int i = waysCount; i < waysCount * 2; i++) {
			string fileName = to_string(t[i]) + ".txt";
			fileArray[t[i]].File.open(fileName, fstream::out);
		}


		for (int i = 0; i < af; i++) {
			fileArray[t[i]].File.clear();
			fileArray[t[i]].File.seekg(0);
			ta[i] = t[i];
			getline(fileArray[t[i]].File, key);
			fileArray[t[i]].currentElem = atoi(key.c_str());
		}

		L = 0;
		int j = waysCount; //возможно тут не + 1

		do {
			L++;
			int ao = af;

			do {

				int m = 0;
				int minValue = fileArray[ta[0]].currentElem;
				int i = 0;
				while (i < ao) {

					if (fileArray[ta[i]].currentElem < minValue) {
						minValue = fileArray[ta[i]].currentElem;
						m = i;
					}
					i++;
				}

				fileArray[t[j]].currentElem = fileArray[ta[m]].currentElem;
				fileArray[t[j]].File << fileArray[t[j]].currentElem << endl;

				getline(fileArray[ta[m]].File, key);
				fileArray[ta[m]].currentElem = atoi(key.c_str());
				fileArray[ta[m]].eor = fileArray[ta[m]].currentElem < fileArray[t[j]].currentElem;


				if (fileArray[ta[m]].File.eof()) {
					//fileArray[ta[m]].File.close();
					fileArray[ta[m]].eor = 0;
					ta[m] = ta[ao-1];
					ta[ao-1] = ta[af-1];
					af--;
					ao--;
				}
				else if (fileArray[ta[m]].eor) {
					if (fileArray[ta[m]].currentElem == 0) {
						//fileArray[ta[m]].File.close();
						fileArray[ta[m]].eor = 0;
						ta[m] = ta[ao-1];
						ta[ao-1] = ta[af-1];
						af--;
						ao--;
					}
					else {
						int tx = ta[m];
						ta[m] = ta[ao - 1];
						ta[ao-1] = tx;
						ao--;
					}
					
				}


			} while (ao > 0); //возможно не то условие

			if (j < waysCount * 2 - 1) j++; else j = waysCount;
		} while (af > 0);

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

	ofstream OutFile("Result.txt");

	fileArray[0].File.clear();
	fileArray[0].File.seekg(0);
	while (!fileArray[0].File) {
		getline(fileArray[0].File, key);
		OutFile << key << endl;
	}

	OutFile.close();

	for (int i = 0; i < waysCount * 2; i++) {
		fileArray[i].File.close();
	}

}


/*--------------------------- Генерация ключей ------------------------------*/

void GenerateRandomKeys()


{
	static const char alphanum[] =
		"0123456789";
	string res;

	fstream keys("keys.txt", fstream::out);

	if (keys) {
		for (int i = 0; i < 20; ++i) {
			int key = 1 + rand() % (20 - 1);
			for (int j = 0; j < 195; ++j) {
				res += alphanum[rand() % (sizeof(alphanum) - 1)];
			}
			keys << key << endl;
			//keys << res << endl;

			res = "";

		}
	}
}


int main()
{
	//srand(time(nullptr));
	TSortRect rect;
	GenerateRandomKeys();

	int ways = 3;

	SegmentDistribution("keys.txt", ways);
	BalancedMergeSort(ways);

	cout << sizeof(rect);
	rect.key = 1;
	rect.key = 2;
	return 0;
}

