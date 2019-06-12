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
		while (j> 0 && key(columnas->at(j-1)) > key(aux))
		{
			filas->at(j) = filas->at(j - 1);
			columnas->at(j) = columnas->at(j - 1);
			j--;
		}
		if (i != j)
		{
			filas->at(j) = temp;
			columnas->at(j) = aux;
		}
	}
}