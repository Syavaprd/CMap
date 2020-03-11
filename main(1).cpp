#include <iostream>
#include <string>
#include "CMap.hpp"

using namespace std;

// проверка на число
bool IsInteger(const string& s) {
	if (s.length() == 0 || s == "-")
		return false; // пустая строка или строка из минуса - не число

	int start = s[0] == '-' ? 0 : 1; // символ начала проверки

	// проверяем все символы на цифру
	for (int i = start; i < s.length(); i++)
		if (s[i] < '0' || s[i] > '9') // если не цифра
			return false; // то это и не число

	return s.length() - start < 10; // строка - число, ограничим ввод 9 цифрами
}

// ввод целого числа
int GetInteger(const string& msg, int max = -1) {
	string s; // строка для ввода
	cout << msg; // выводим сообщение
	getline(cin, s); // считываем строку

	// пока некорректное число
	while (!IsInteger(s) || (max != -1 && stoi(s) > max)) {
		cout << "Incorrect input, try again: ";
		getline(cin, s); // повторяем ввод
	}

	return stoi(s); // получаем число из строки
}

// выбор словаря для вставки
int Select() {
	string s;
	cout << "Enter dictionary (a/b): ";
	getline(cin, s); // считываем словарь

	// повторяем, пока не введём словарь корректно
	while (s != "a" && s != "b") {
		cout << "incorrect dictionary, try again: ";
		getline(cin, s); // считываем словарь заново
	}

	return s == "a" ? 0 : 1;
}

// вставка в словарь
void Insert(CMap<string, int> &map) {
	string key; // ключ
	int value; // значение

	cout << "Enter key: ";
	getline(cin, key); // считываем ключ
	value = GetInteger("Enter value: "); // считываем зачение

	map.Insert(key, value); // вставляем в словарь
}

// удаление из словаря
void Remove(CMap<string, int> &map) {
	string key; // ключ
	cout << "Enter key: ";
	getline(cin, key); // считываем ключ
	
	map.Remove(key); // удаляем значение по ключу
}

int main() {
	CMap<string, int> a;
	CMap<string, int> b;

	int item; // выбираемый пункт меню
	int dict; // выбираемый словарь

	do {
		// выводим меню
		cout << "What do you want to do?" << endl;
		cout << "1. Print" << endl;
		cout << "2. Insert" << endl;
		cout << "3. Remove" << endl;
		cout << "4. Add" << endl;
		cout << "5. Sub" << endl;
		cout << "6. Clear" << endl;
		cout << "7. Quit" << endl;
		item = GetInteger(">", 7);
		
		// в зависимости от выбранного пункта выполняем действие
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
	} while (item != 7); // повторяем, пока не решим выйти

	return 0;
}