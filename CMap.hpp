#pragma once

#include <iostream>
#include <string>

template <typename K, typename T>
class CMap {
	struct Pair {
		K key; // ключ
		T value; // значение
	};

	Pair *pairs; // массив пар
	int capacity; // ёмкость словаря
	int size; // число элементов

	int IndexOf(const K& key) const; // индекс ключа в массиве

public:
	CMap(); // конструктор
	CMap(const CMap& cmap); // конструктор копирования

	void Insert(const K& key, const T& value); // вставка в словарь
	void Remove(const K& key); // удаление по ключу
	void Clear(); // очистка словаря

	CMap& operator=(const CMap& cmap); // присваивание
	CMap operator+(const CMap& cmap); // сложение
	CMap operator-(const CMap& cmap); // разность

	~CMap(); // деструткор

	template <typename K1, typename T1>
	friend std::ostream& operator<<(std::ostream& os, const CMap<K1, T1> &cmap); // вывод в поток
};

// индекс ключа в массиве
template <typename K, typename T>
int CMap<K, T>::IndexOf(const K& key) const {
	for (int i = 0; i < size; i++) // идём по всем значениям
		if (pairs[i].key == key) // если нашли ключ
			return i; // возвращаем его индекс

	return -1; // не нашли такой ключ
}

// конструктор
template <typename K, typename T>
CMap<K, T>::CMap() {
	pairs = new Pair[1]; // выделяем память под один элемент
	capacity = 1; // ёмкость равна одному
	size = 0; // элементов ещё нет
}

// конструктор копирования
template <typename K, typename T>
CMap<K, T>::CMap(const CMap& cmap) {
	capacity = cmap.capacity; // копируем ёмкость
	size = cmap.size; // копируем размер
	pairs = new Pair[capacity]; // выделяем память под новый массив

	// копируем значения
	for (int i = 0; i < size; i++)
		pairs[i] = cmap.pairs[i];
}

// вставка в словарь
template <typename K, typename T>
void CMap<K, T>::Insert(const K& key, const T& value) {
	int index = IndexOf(key); // ищем это значение в массиве

	// если оно уже есть
	if (index != -1) {
		pairs[index].value = value; // обновляем значение
		return; // и выходим
	}

	pairs[size].key = key; // сохраняем ключ
	pairs[size].value = value; // сохраняем значение
	size++; // увеличиваем размер

	if (size >= capacity) {
		capacity *= 2; // увеличиваем ёмкость в два раза
		Pair *tmp = new Pair[capacity]; // выделяем памть под новый массив

		// копируем значения в новый массив
		for (int i = 0; i < size; i++)
			tmp[i] = pairs[i];

		delete[] pairs; // освобождаем память
		pairs = tmp; // подменяем указатели
	}
}

// удаление по ключу
template <typename K, typename T>
void CMap<K, T>::Remove(const K& key) {
	int index = IndexOf(key); // ищем ключ в словаре

	if (index == -1)
		return; // выходим, если не нашли

	size--; // уменьшаем размер

	// сдвигаем пары на 1 влево
	for (int i = index; i < size; i++)
		pairs[i] = pairs[i + 1];
}

// очистка словаря
template <typename K, typename T>
void CMap<K, T>::Clear() {
	size = 0; // считаем, что элементов нет
}

// присваивание
template <typename K, typename T>
CMap<K, T>& CMap<K, T>::operator=(const CMap& cmap) {
	if (this == &cmap)
		return *this;

	delete[] pairs; // освобождаем текущую память
	capacity = cmap.capacity; // копируем ёмкость
	size = cmap.size; // копируем размер
	pairs = new Pair[capacity]; // выделяем память под новый массив

	// копируем значения
	for (int i = 0; i < size; i++)
		pairs[i] = cmap.pairs[i];

	return *this; // возвращаем объект
}

// сложение
template <typename K, typename T>
CMap<K, T> CMap<K, T>::operator+(const CMap& cmap) {
	CMap result;

	for (int i = 0; i < size; i++)
		result.Insert(pairs[i].key, pairs[i].value);

	for (int i = 0; i < cmap.size; i++)
		result.Insert(cmap.pairs[i].key, cmap.pairs[i].value);

	return result;
}

// разность
template <typename K, typename T>
CMap<K, T> CMap<K, T>::operator-(const CMap& cmap) {
	CMap result;

	for (int i = 0; i < size; i++)
		if (cmap.IndexOf(pairs[i].key) == -1)
			result.Insert(pairs[i].key, pairs[i].value);
	
	return result; // возвращаем результат
}

// деструктор
template <typename K, typename T>
CMap<K, T>::~CMap() {
	delete[] pairs; // освобождаем выделенную память
}

// вывод в поток
template <typename K, typename T>
std::ostream& operator<<(std::ostream& os, const CMap<K, T> &cmap) {
	os << "{ ";
	for (int i = 0; i < cmap.size; i++) {
		os << cmap.pairs[i].key << " : " << cmap.pairs[i].value;

		if (i < cmap.size - 1)
			os << ", ";
	}
	os << "}" << std::endl;

	return os; // возвращаем поток
}