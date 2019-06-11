#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
using namespace System;

class CDatos
{
	string Nombre;
	string Apellido;
	int Año;

public:
	CDatos() {
		Nombre = "";
		Apellido = "";
		Año = 0;
	}

	void MostrarDatos()
	{
		cout << Nombre << " " << Apellido << " nacio en " << Año;
	}

	void setNombre(string n) { Nombre = n; }
	void setApellido(string a) { Apellido = a; }
	void setAño(int año) { Año = año; }

};

class Filas
{
	vector<CDatos*>*d;
public:
	Filas() {
		d = new vector<CDatos*>;
	}
	void GenerarDatos()
	{
		for (int i = 0; i < 3; i++)
		{
			d->push_back(new CDatos());
		}
	}
	void Mostrar() {
		for (int i = 0; i < d->size(); i++)
		{
			d->at(i)->MostrarDatos(); cout << endl;
		}
	}
	bool LecturaDatos(string Archivo)
	{
		int i = 0;
		ifstream file;

		file.open(Archivo, ios::in);

		if (file.fail()) { cout << "ERROR AL ABRIR EL ARCHIVO" << endl; return false; }

		while (file.good() && i < d->size())
		{
			string nombre = "";
			string apellido = "";
			string año = "";
			if (Archivo.at(Archivo.size() - 3) == 'c')
			{
				getline(file, nombre, ',');
				getline(file, apellido, ',');
				getline(file, año, '\n');
			}
			else
			{
				getline(file, nombre, '\t');
				getline(file, apellido, '\t');
				getline(file, año, '\n');
			}
			d->at(i)->setNombre(nombre);
			d->at(i)->setApellido(apellido);
			d->at(i)->setAño(atoi(año.c_str()));
			i++;
		}
		file.close();
		return true;
	}
};
