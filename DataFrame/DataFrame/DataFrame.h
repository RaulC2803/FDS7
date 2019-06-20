#include "BusquedayOrdenamiento.hpp"
#include <fstream>
#include "Menu.h"
#include <algorithm>
#include <functional>

using namespace std;
using namespace System;

class CDatos
{
	vector<string>*Dato;

public:
	CDatos() {
		Dato = new vector<string>;
	}

	void agregarDato(string dato) {
		Dato->push_back(dato);
	}

	void setDato(string t, int i) { Dato->at(i) = t; }
	
	string getDato(int i) { return Dato->at(i); }

	int getContador() { return Dato->size(); }
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
	void AgregarDato(string dato) {
		Datos->agregarDato(dato);
	}
	void MostrarFila()
	{
		cout << id;
		for (int i = 0; i < 3; i++)
		{
			cout << "\t\t" << Datos->getDato(i);
		}
	}
	void setDato(string n, int i) { Datos->setDato(n,i); }
	string getDato(int i) { return Datos->getDato(i); }
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
	vector<ColumnaString*>* Columnas;
	ifstream file;
	int contColumnas;
	bool isEmpty;
public:

	DataFrame() {
		isEmpty = true;
		Filas = new vector<Fila*>;
		contColumnas = 0;
		Columnas = new vector<ColumnaString*>;
	}

	~DataFrame()
	{
		Filas->clear();
		Columnas->clear();
	}

	void ContarColumnas(string n_file)
	{
		int i = 0;
		bool finish = false;

		string n_columna;
		string f;

		file.open(n_file, ios::in);

		if (!file.fail()) {

			while (finish != true)
			{
				getline(file, f, '\n');

				for (int i = 0; i < f.size(); i++)
				{
					if (f.at(i) == ',')
					{
						contColumnas++;
					}

				}
				contColumnas++;
				finish = true;
			}
		}
		file.close();

		for (int i = 0; i < contColumnas; i++)
		{
			cout << "Ingrese el nombre de la columna " << i << ": "; cin >> n_columna;
			Columnas->push_back(new ColumnaString(n_columna));
		}
	}

	void MostrarData() {
		cout << "ID\t\t";
		for (int i = 0; i < 3; i++)
		{
			cout << Columnas->at(i)->getEtiqueta() << "\t\t  ";
		}
		 
		cout << endl << endl;

		for (int i = 0; i < Filas->size(); i++)
		{
			if ((i < 9 || i >= Filas->size() - 9) && i < Filas->size())
			{
				Filas->at(i)->MostrarFila(); cout << endl;
			}
		}
	}
	bool LecturaDatos(string Archivo)
	{
		ContarColumnas(Archivo);

		isEmpty = false;
		int j = 0;
	
		file.open(Archivo, ios::in);

		if (file.fail()) { configurarColorTexto(10); cout << "ERROR AL ABRIR EL ARCHIVO" << endl; configurarColorTexto(5); return false;  }

		while (file.good())
		{
			Filas->push_back(new Fila(j, new CDatos));
		
			string dato = "";
			if (Archivo.at(Archivo.size() - 3) == 'c')
			{
				for (int i = 0; i < contColumnas-1; i++)
				{
					getline(file, dato, ',');
					Columnas->at(i)->AgregarDatos(dato);
					Filas->at(j)->AgregarDato(dato);
				}
				getline(file, dato, '\n');
				Columnas->at(contColumnas-1)->AgregarDatos(dato);
				Filas->at(j)->AgregarDato(dato);
			}
			else
			{
				for (int i = 0; i < contColumnas-1; i++)
				{
					getline(file, dato, '\t');
					Columnas->at(i)->AgregarDatos(dato);
					Filas->at(j)->AgregarDato(dato);
				}
				getline(file, dato, '\n');
				Columnas->at(contColumnas - 1)->AgregarDatos(dato);
				Filas->at(j)->AgregarDato(dato);
			}
			j++;
		}
		Filas->pop_back();
		file.close();
		return true;
	}
	void GuardarDatos()
	{
		string nombreArchivo = "";
		string extension = "";
		ofstream file;

		cout << "Nombre para Guardar: "; cin >> nombreArchivo;
		do
		{
			cout << "Cual extension usara? csv o tsv: "; cin >> extension;

		} while (extension != "csv" && extension != "tsv");
		
		nombreArchivo += "." + extension;
		file.open(nombreArchivo);

		for (int i = 0; i < Filas->size(); i++)
		{
			for (int j = 0; j < contColumnas; j++)
			{
				if (j != contColumnas - 1)
				{
					if (extension == "csv") {
						file << Filas->at(i)->getDato(j); file << ",";
					}
					else
					{
						file << Filas->at(i)->getDato(j); file << "\t";
					}
				}
				else
				{
					file << Filas->at(i)->getDato(j); file;
				}
			}
			file << "\n";
		}
		file.close();
	}
	void Ordenar(string busqueda)
	{
		if (busqueda == "Nombre" || "nombre")
		{
			auto lmb = [](string C) {return C; }; // El lambda obtiene un string

			//Se pasa por parametro, el vector Dato de la Columna Nombres, el vector de Filas, y el lambda

			/*InsertionSort<string, string, Fila*>(Nombres->getDato(),Filas, lmb); */
																		
		}
	}
	bool getIsEmpty() { return isEmpty; }
};

class ListadoDF {
	vector<DataFrame*>* Listado;
public:
	ListadoDF() {
		Listado = new vector<DataFrame*>;
	}
	~ListadoDF() {
		Listado->clear();
	}

	void MostrarDF() {
		for (int i = 0; i < Listado->size(); i++) {
			cout << "DATA FRAME #" << i << endl << endl;
			Listado->at(i)->MostrarData();
				cout << endl;
		}
	}

	bool GenerarDF(string Archivo) {
		
		Listado->push_back(new DataFrame());
		if (!Listado->at(Listado->size() - 1)->LecturaDatos(Archivo)) {
			Listado->pop_back();
			return false;
		}
		else return true;
	}

	void MostrarDFpos(int i) {
		cout << "DATA FRAME #" << i << endl << endl;
		Listado->at(i)->MostrarData();
		cout << endl;
	}

	void Guardar(int i)
	{
		Listado->at(i)->GuardarDatos();
	}

	bool getIsEmpty(int i) { return Listado->at(i)->getIsEmpty(); }

	int getsize() {
		return Listado->size();
	}
};

template <typename T, typename R=T>
class Tree
{
	struct Node
	{
		float elem;
		Node* left;
		Node* right;
		int h;

		Node(float elem, Node* left = nullptr, Node* rigth = nullptr) :elem(elem), left(left), right(right) {}

		static int height(Node* n)
		{
			return n == nullptr ? -1 : n->h;
		}
		void updateH() {
			h = std::max(Node::height(left), Node::height(right)) + 1;
		}
	};

	Node* root;
	int length;
	std::function<R(T)> key;

	void borrar(Node* node)
	{
		if (node != nullptr) {
			borrar(node->left);
			borrar(node->right);
			delete node;
		}
	}

	void rotAB(Node*& node)
	{
		Node* aux = node->left;
		node->left = aux->right;
		node->updateH();
		aux->right = node;
		node = aux;
		node->updateH();
	}

	void rotBA(Node*& node)
	{
		Node* aux = node->right;
		n->right = aux->left;
		node->updateH();
		aux->left = node;
		node = aux;
		node->updateH;
	}

	void balance(Node*& n)
	{
		int delta = Node::height(n->left) - Node::height(n->right);
		if (delta < -1) {
			if (Node::height(n->right->left) > Node::height(n->right->right)) {
				rotAB(n->right);
			}
			rotBA(n);
		}
		else if (delta > 1) {
			if (Node::height(n->left->right) > Node::height(n->left->left))
			{
				rotBA(n->left);
			}
			rotAB(n);
		}
	}

	void add(Node*& node, T elem) {
		if (node == nullptr)
		{
			node = new Node(elem);
		}
		else if (key(elem) < key(node->elem)) {
			add(node->left, elem);
		}
		else {
			add(node->right, elem);
		}
		node->updateH();
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

	Tree(std::function<R(T)>key = [](T a) {return a;}) :root(nullptr), length(0), key(key) {}
	~Tree() { borrar(root); }

	int Height() {
		return Node::height(root);
	}
	int size() {
		return length;
	}

	void add(T elem) { add(root, elem); length++; }

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
