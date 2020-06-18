#pragma once
#define MAXLENGTH 5
using namespace std;


typedef struct Detail {
	char name[20];
	int time;
};

void printTable(Queue <Detail> &queue);

