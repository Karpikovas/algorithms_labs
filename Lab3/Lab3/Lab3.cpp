#include "stdafx.h"


int main()
{
	setlocale(LC_ALL, "russian");
	int command;

	char menu[256] = "1 - Поиск вершин с разным количеством потомков\n" \
		"2 - Высота дерева\n" \
		"3 - Поиск листа дерева слева направо \n" \
		"4 - Удаление \n" \
		"0 - Сохранить \n" \
		": ";

	BinarySearchTree<int> obj;
	try {
		if (obj.fileIn("testin1.txt") == 1)
			throw "Can't open the file";
	}
	catch (const char* msg) {
		cout << msg << endl;
	}

	while (1) {
		
		obj.paintTree();
		cout << endl << menu << endl;
		cin >> command;

		switch (command)
		{
		case 1:
			system("cls");
			cout << "Список вершин: ";
			obj.count();
			cout << endl << endl;
			break;
		case 2:
			system("cls");
			cout << "Высота дерева: " << obj.getHeight() << endl << endl;
			break;
		case 3:
		{
			int k;
			cout << "Введите номер листа: ";
			cin >> k;
			system("cls");
			obj.find(k);
			cout << endl << endl;
		}
			break;
		case 4:
		{
			int k;
			cout << "Введите лист: ";
			cin >> k;
			system("cls");
			obj.remove(k);
		}
			break;
		case 0:
			obj.Out("testout.txt");
			break;

		default:
			obj.Out("testout.txt");
			break;
		}
	}
	// obj.remove(20);
	//obj.paintTree();
	// obj.find(3);
	obj.count();
	obj.Out("testout.txt");
	system("pause");

    return 0;
}

