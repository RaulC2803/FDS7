#include "BusquedayOrdenamiento.hpp"
#include <fstream>

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

	void setNombre(string n) { Nombre = n; }
	void setApellido(string a) { Apellido = a; }
	void setAño(int año) { Año = año; }
	
	string getNombre() { return Nombre; }
	string getApellido() { return Apellido; }
	int getAño() { return Año; }

};

class Fila
{
	int id = 0;
	CDatos* Datos;
public:
	Fila(int _id, CDatos* data) {
		id = _id;
		Datos = data;
	}
	void MostrarFila()
	{
		cout << id << "\t\t" << Datos->getNombre() << "\t\t" << Datos->getApellido() << "\t\t" << Datos->getAño();
	}
	void setNombre(string n) { Datos->setNombre(n); }
	void setApellido(string a) { Datos->setApellido(a); }
	void setAño(int año) { Datos->setAño(año); }
	string getNombre() { return Datos->getNombre(); }
	string getApellido() { return Datos->getApellido(); }
	int getAño() { return Datos->getAño(); }
};

class Columna {
protected:
	string Etiqueta;
public:
	Columna() {
	}
	string getEtiqueta() { return Etiqueta; }
};

class ColumnaString : public Columna {
	vector<string>* Datos;
public:
	ColumnaString(string Etiqueta) : Columna() {
		Datos = new vector<string>;
		this->Etiqueta = Etiqueta;
	}
	void AgregarDatos(string n) {
		Datos->push_back(n);
	}
	vector<string>* getDato()
	{
		return Datos;
	}
};

class ColumnaInt : public Columna {
	vector<int>* Datos;
public:
	ColumnaInt(string Etiqueta) : Columna() {
		Datos = new vector<int>;
		this->Etiqueta = Etiqueta;
	}
	void AgregarDatos(int n) {
		Datos->push_back(n);
	}
	
};

class ColumnaLong : public Columna {
	vector<long>* Datos;
public:
	ColumnaLong(string Etiqueta) : Columna() {
		this->Etiqueta = Etiqueta;
		Datos = new vector<long>;
	}
	void AgregarDatos(long n) {
		Datos->push_back(n);
	}
};

class ColumnaDouble : public Columna {
	vector<double>* Datos;
public:
	ColumnaDouble(string Etiqueta) : Columna() {
		Datos = new vector<double>;
		this->Etiqueta = Etiqueta;
	}
	void AgregarDatos(double n) {
		Datos->push_back(n);
	}
};

class DataFrame
{
	vector<Fila*>* Filas;
	vector<Columna*>* Columnas;
	ColumnaString* Nombres;
	ColumnaString* Apellidos;
	ColumnaInt* Año;
	bool isEmpty;
public:

	DataFrame() {
		isEmpty = true;
		Filas = new vector<Fila*>;
		Columnas = new vector<Columna*>;
		Columnas->push_back(new ColumnaString("Nombre"));
		Columnas->push_back(new ColumnaString("Apellido"));
		Columnas->push_back(new ColumnaInt("Año"));
		Nombres = (ColumnaString*)Columnas->at(0);			   //Se convierte el Puntero Columnas a puntero ColumnasString
		Apellidos = (ColumnaString*)Columnas->at(1);		   //Se convierte el Puntero Columnas a puntero ColumnasString
		Año = (ColumnaInt*)Columnas->at(2);					   //Se convierte el Puntero Columnas a puntero ColumnasInt
	}

	~DataFrame()
	{
		delete Nombres;
		delete Apellidos;
		delete Año;
	}
	void MostrarData() {
		cout << "ID\t\t" <<Nombres->getEtiqueta() << "\t\t" << Apellidos->getEtiqueta() << "\t\t" << Año->getEtiqueta();
		cout << endl << endl;
		for (int i = 0; i < Filas->size(); i++)
		{
			Filas->at(i)->MostrarFila(); cout << endl;
		}
	}
	bool LecturaDatos(string Archivo)
	{
		isEmpty = false;
		int i = 0;
		ifstream file;

		file.open(Archivo, ios::in);

		if (file.fail()) { cout << "ERROR AL ABRIR EL ARCHIVO" << endl; return false; }

		while (file.good())
		{
			Filas->push_back(new Fila(i, new CDatos));
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

			Nombres->AgregarDatos(nombre);					
			Apellidos->AgregarDatos(apellido);				
			Año->AgregarDatos(atoi(año.c_str()));				

			Filas->at(i)->setNombre(nombre);
			Filas->at(i)->setApellido(apellido);
			Filas->at(i)->setAño(atoi(año.c_str()));
			i++;
		}
		Filas->pop_back();
		file.close();
		return true;
	}
	void GuardarDatos()
	{
		string nombreArchivo;
		ofstream file;

		cout << "Nombre para Guardar: "; cin >> nombreArchivo;
		nombreArchivo += ".cvs";
		file.open(nombreArchivo);

		for (int i = 0; i < Filas->size(); i++)
		{
			file << Filas->at(i)->getNombre(); file << ","; file << Filas->at(i)->getApellido(); 
			file << ","; file << Filas->at(i)->getAño(); file << "\n";
		}
		file.close();
	}
	void Ordenar(string busqueda)
	{
		if (busqueda == "Nombre" || "nombre")
		{
			auto lmb = [](string C) {return C; }; // El lambda obtiene un string

			//Se pasa por parametro, el vector Dato de la Columna Nombres, el vector de Filas, y el lambda

			InsertionSort<string, string, Fila*>(Nombres->getDato(),Filas, lmb); 
																		
		}
	}
	bool getIsEmpty() { return isEmpty; }
};

class Tree
{
	struct Node
	{
		float elem;
		Node* left;
		Node* right;

		Node(float elem, Node* left = nullptr, Node* rigth = nullptr) :elem(elem), left(left), right(right) {}
	};

	Node* root;
	int length;

	void borrar(Node* node)
	{
		if (node != nullptr) {
			borrar(node->left);
			borrar(node->right);
			delete node;
		}
	}

	void add(Node*& node, float elem) {
		if (node == nullptr)
		{
			node = new Node(elem);
		}
		else if (elem < node->elem) {
			add(node->left, elem);
		}
		else {
			add(node->right, elem);
		}
	}

	void InOrder(Node* node, std::function<void(float)> doSomething) {
		if (node != nullptr)
		{
			InOrder(node->left, doSomething);
			doSomething(node->elem);
			InOrder(node->right, doSomething);
		}
	}

	Node* Mayor(Node* node) {
		if (node != nullptr) {
			if (node->right == nullptr) {
				return node;
			}
			else {
				return node->right;
			}
		}
		return nullptr;
	}
public:

	Tree() :root(nullptr), length(0) {}
	~Tree() { borrar(root); }

	void add(float elem) { add(root, elem); length++; }

	void InOrder(std::function<void(float)>doSomething)
	{
		InOrder(root, doSomething);
	}

	float Mayor() {
		Node* node = Mayor(root);
		if (node != nullptr) {
			return node->elem;
		}
	}

};
