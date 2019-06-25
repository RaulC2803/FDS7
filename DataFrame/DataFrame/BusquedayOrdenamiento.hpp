#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

template<typename T, typename R = T, typename U>
void InsertionSort(vector<T>* columnas, vector<U>* filas, function<R(T)> key = [](T a) {return a; })
{
	for (int i = 1; i < filas->size(); i++)
	{	
		T aux = columnas->at(i);
		U temp = filas->at(i);
		int j = i;
		while (j > 0 && key(columnas->at(j-1)) > key(aux))
		{
			filas->at(j) = filas->at(j - 1);
			j--;
		}
		if (i != j)
		{
			filas->at(j) = temp;
		}
	}
}

template<typename T, typename R = T, typename U>
void Marge(vector<T>*columna, int ini, int end, function<R(T)>key = [](T a) {return a; })
{
	int len = (end - ini) + 1;
	T* temp = new T[len];
	int mid = (end + ini) / 2;
	int i = ini;
	int j = mid + 1;
	for (int k = 0; i <= mid || j <= end; k++)
	{
		if (i > mid || j <= end && key(columna->at(i)) > key(columna->at(j))) temp[k] = columna->at(j++);
		else temp[k] = columna->at(i++);
	}
	for (int k = 0; k < len; k++)
	{
		columna->at(ini + k) = temp[k];
	}
}

template<typename T, typename R = T, typename U>
void sortMarge(vector<T>* columna, vector<U>* fila, int i, int f, function<R(T)> key = [](T a) {return a; })
{
	if (i < f)
	{
		Marge(columna, i, f, a);
		int mid = (i + f) / 2;
		sortMarge(columna, i, mid, a);
		sortMarge(columna, mid + 1, f, a);
	}
}
