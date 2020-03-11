#pragma once

#include <iostream>
#include <string>

template <typename K, typename T>
class CMap {
	struct Pair {
		K key; // ����
		T value; // ��������
	};

	Pair *pairs; // ������ ���
	int capacity; // ������� �������
	int size; // ����� ���������

	int IndexOf(const K& key) const; // ������ ����� � �������

public:
	CMap(); // �����������
	CMap(const CMap& cmap); // ����������� �����������

	void Insert(const K& key, const T& value); // ������� � �������
	void Remove(const K& key); // �������� �� �����
	void Clear(); // ������� �������

	CMap& operator=(const CMap& cmap); // ������������
	CMap operator+(const CMap& cmap); // ��������
	CMap operator-(const CMap& cmap); // ��������

	~CMap(); // ����������

	template <typename K1, typename T1>
	friend std::ostream& operator<<(std::ostream& os, const CMap<K1, T1> &cmap); // ����� � �����
};

// ������ ����� � �������
template <typename K, typename T>
int CMap<K, T>::IndexOf(const K& key) const {
	for (int i = 0; i < size; i++) // ��� �� ���� ���������
		if (pairs[i].key == key) // ���� ����� ����
			return i; // ���������� ��� ������

	return -1; // �� ����� ����� ����
}

// �����������
template <typename K, typename T>
CMap<K, T>::CMap() {
	pairs = new Pair[1]; // �������� ������ ��� ���� �������
	capacity = 1; // ������� ����� ������
	size = 0; // ��������� ��� ���
}

// ����������� �����������
template <typename K, typename T>
CMap<K, T>::CMap(const CMap& cmap) {
	capacity = cmap.capacity; // �������� �������
	size = cmap.size; // �������� ������
	pairs = new Pair[capacity]; // �������� ������ ��� ����� ������

	// �������� ��������
	for (int i = 0; i < size; i++)
		pairs[i] = cmap.pairs[i];
}

// ������� � �������
template <typename K, typename T>
void CMap<K, T>::Insert(const K& key, const T& value) {
	int index = IndexOf(key); // ���� ��� �������� � �������

	// ���� ��� ��� ����
	if (index != -1) {
		pairs[index].value = value; // ��������� ��������
		return; // � �������
	}

	pairs[size].key = key; // ��������� ����
	pairs[size].value = value; // ��������� ��������
	size++; // ����������� ������

	if (size >= capacity) {
		capacity *= 2; // ����������� ������� � ��� ����
		Pair *tmp = new Pair[capacity]; // �������� ����� ��� ����� ������

		// �������� �������� � ����� ������
		for (int i = 0; i < size; i++)
			tmp[i] = pairs[i];

		delete[] pairs; // ����������� ������
		pairs = tmp; // ��������� ���������
	}
}

// �������� �� �����
template <typename K, typename T>
void CMap<K, T>::Remove(const K& key) {
	int index = IndexOf(key); // ���� ���� � �������

	if (index == -1)
		return; // �������, ���� �� �����

	size--; // ��������� ������

	// �������� ���� �� 1 �����
	for (int i = index; i < size; i++)
		pairs[i] = pairs[i + 1];
}

// ������� �������
template <typename K, typename T>
void CMap<K, T>::Clear() {
	size = 0; // �������, ��� ��������� ���
}

// ������������
template <typename K, typename T>
CMap<K, T>& CMap<K, T>::operator=(const CMap& cmap) {
	if (this == &cmap)
		return *this;

	delete[] pairs; // ����������� ������� ������
	capacity = cmap.capacity; // �������� �������
	size = cmap.size; // �������� ������
	pairs = new Pair[capacity]; // �������� ������ ��� ����� ������

	// �������� ��������
	for (int i = 0; i < size; i++)
		pairs[i] = cmap.pairs[i];

	return *this; // ���������� ������
}

// ��������
template <typename K, typename T>
CMap<K, T> CMap<K, T>::operator+(const CMap& cmap) {
	CMap result;

	for (int i = 0; i < size; i++)
		result.Insert(pairs[i].key, pairs[i].value);

	for (int i = 0; i < cmap.size; i++)
		result.Insert(cmap.pairs[i].key, cmap.pairs[i].value);

	return result;
}

// ��������
template <typename K, typename T>
CMap<K, T> CMap<K, T>::operator-(const CMap& cmap) {
	CMap result;

	for (int i = 0; i < size; i++)
		if (cmap.IndexOf(pairs[i].key) == -1)
			result.Insert(pairs[i].key, pairs[i].value);
	
	return result; // ���������� ���������
}

// ����������
template <typename K, typename T>
CMap<K, T>::~CMap() {
	delete[] pairs; // ����������� ���������� ������
}

// ����� � �����
template <typename K, typename T>
std::ostream& operator<<(std::ostream& os, const CMap<K, T> &cmap) {
	os << "{ ";
	for (int i = 0; i < cmap.size; i++) {
		os << cmap.pairs[i].key << " : " << cmap.pairs[i].value;

		if (i < cmap.size - 1)
			os << ", ";
	}
	os << "}" << std::endl;

	return os; // ���������� �����
}