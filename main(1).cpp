#include <iostream>
#include <string>
#include "CMap.hpp"

using namespace std;

// �������� �� �����
bool IsInteger(const string& s) {
	if (s.length() == 0 || s == "-")
		return false; // ������ ������ ��� ������ �� ������ - �� �����

	int start = s[0] == '-' ? 0 : 1; // ������ ������ ��������

	// ��������� ��� ������� �� �����
	for (int i = start; i < s.length(); i++)
		if (s[i] < '0' || s[i] > '9') // ���� �� �����
			return false; // �� ��� � �� �����

	return s.length() - start < 10; // ������ - �����, ��������� ���� 9 �������
}

// ���� ������ �����
int GetInteger(const string& msg, int max = -1) {
	string s; // ������ ��� �����
	cout << msg; // ������� ���������
	getline(cin, s); // ��������� ������

	// ���� ������������ �����
	while (!IsInteger(s) || (max != -1 && stoi(s) > max)) {
		cout << "Incorrect input, try again: ";
		getline(cin, s); // ��������� ����
	}

	return stoi(s); // �������� ����� �� ������
}

// ����� ������� ��� �������
int Select() {
	string s;
	cout << "Enter dictionary (a/b): ";
	getline(cin, s); // ��������� �������

	// ���������, ���� �� ����� ������� ���������
	while (s != "a" && s != "b") {
		cout << "incorrect dictionary, try again: ";
		getline(cin, s); // ��������� ������� ������
	}

	return s == "a" ? 0 : 1;
}

// ������� � �������
void Insert(CMap<string, int> &map) {
	string key; // ����
	int value; // ��������

	cout << "Enter key: ";
	getline(cin, key); // ��������� ����
	value = GetInteger("Enter value: "); // ��������� �������

	map.Insert(key, value); // ��������� � �������
}

// �������� �� �������
void Remove(CMap<string, int> &map) {
	string key; // ����
	cout << "Enter key: ";
	getline(cin, key); // ��������� ����
	
	map.Remove(key); // ������� �������� �� �����
}

int main() {
	CMap<string, int> a;
	CMap<string, int> b;

	int item; // ���������� ����� ����
	int dict; // ���������� �������

	do {
		// ������� ����
		cout << "What do you want to do?" << endl;
		cout << "1. Print" << endl;
		cout << "2. Insert" << endl;
		cout << "3. Remove" << endl;
		cout << "4. Add" << endl;
		cout << "5. Sub" << endl;
		cout << "6. Clear" << endl;
		cout << "7. Quit" << endl;
		item = GetInteger(">", 7);
		
		// � ����������� �� ���������� ������ ��������� ��������
		switch (item) {
			case 1:
				cout << "a: " << a;
				cout << "b: " << b;
				break;

			case 2:
				dict = Select();
				Insert(dict == 0 ? a : b);
				break;

			case 3:
				dict = Select();
				Remove(dict == 0 ? a : b);
				cout << "Done" << endl;
				break;

			case 4:
				cout << "a + b: " << (a + b);
				break;

			case 5:
				cout << "a - b: " << (a - b);
				break;

			case 6:
				dict = Select();
				if (dict == 0)
					a.Clear();
				else
					b.Clear();
				cout << "Cleared" << endl;
				break;
		}
	} while (item != 7); // ���������, ���� �� ����� �����

	return 0;
}