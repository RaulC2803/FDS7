#include "BusquedayOrdenamiento.hpp"
#include <fstream>
#include "Menu.h"
#include <algorithm>
#include <functional>
#include <map>

using namespace std;
using namespace System;

class Columna {
	vector<string>* Data;
	string Etiqueta;
public:
	Columna(string Etiqueta) {
		this->Etiqueta = Etiqueta;
		Data = new vector<string>;
	}
	string getEtiqueta() { return Etiqueta; }

	void AgregarDatos(string Dato) {
		Data->push_back(Dato);
	}

	vector<string>* getDatos() {
		return Data;
	}
};

typedef map<string, Columna*> Colmap;

class Fila
{
	int id;
public:
	Fila(int id): id(id) {}
	string getData(Colmap &Cols, string name) {
		return Cols[name]->getDatos()->at(id);
	}
};

class DataFrame
{
	vector<Fila*>* Filas;
	Colmap Columnas;
	ifstream file;
	string extension;
	int contColumnas;
	int contRow;
	bool isEmpty;
public:
	
	DataFrame() {
		isEmpty = true;
		Filas = new vector<Fila*>;
		contColumnas = 0;
		contRow = 0;
	}

	~DataFrame()
	{
		Filas->clear();
	}

	void verificarExtension(string n_file)
	{
		if (n_file.at(n_file.size() - 3) == 'c')
		{
			extension = "csv";
		}
		else
		{
			extension = "tsv";
		}
	}

	void ContarColumnas(string n_file)
	{
		int k = 0;
		bool finish = false;
		vector<string>*etiquetas;
		string n_columna;
		string f;
		string x;

		file.open(n_file, ios::in);
		etiquetas = new vector<string>;

		verificarExtension(n_file);

		if (!file.fail()) {

			while (finish != true)
			{
				getline(file, f, '\n');

				for (int i = 0; i < f.size(); i++)
				{
					if (f.at(i) == ',')
					{
						etiquetas->push_back(x);
						Columnas.insert({ etiquetas->at(k) , new Columna(etiquetas->at(k))});
						contColumnas++;
						x = "";
						k++;
					}
					else {

						if (f.at(i) == '\t')
						{
							etiquetas->push_back(x);
							Columnas.insert({ etiquetas->at(k) , new Columna(etiquetas->at(k)) });
							contColumnas++;
							x = "";
							k++;
						}
						else {
							x += f.at(i);
						}
					}
				}
				if ((f.at(f.size() - 1) != ',' && extension == "csv") || (f.at(f.size() - 1) != '\t' && extension == "tsv"))
				{
					etiquetas->push_back(x);
					Columnas.insert({ etiquetas->at(k), new Columna(etiquetas->at(k)) });
					contColumnas++;
				}
				finish = true;
			}
		}
		file.close();
		etiquetas->clear();
		delete etiquetas;
	}

	void MostrarData() {
		/*Colmap::iterator k = Columnas.begin();
		for (int j = 0; j < k->second->getDatos()->size(); j++)
		{
			for (Colmap::iterator i = Columnas.begin(); i != Columnas.end(); i++)
			{
				cout << i->second->getDatos()->at(j) << "\t\t";
			}
			cout << endl;
		}*/
		for (int j = 0; j < contRow; j++)
		{
			int cont = 0;
			if (j < 9 || j > contRow - 9)
			{
				for (Colmap::iterator i = Columnas.begin(); cont < 3; i++)
				{
					cout << Filas->at(j)->getData(Columnas, i->first) << "\t\t";
					cont++;
				}
				cout << endl;
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
			int j = 0;
			string dato = "";
			if (extension == "csv")
			{
				for (Colmap::iterator i= Columnas.begin(); j < contColumnas ;i++)
				{
					if (j + 1 < contColumnas) {
						getline(file, dato, ',');
						i->second->AgregarDatos(dato);
					}
					else
					{
						getline(file, dato, '\n');
						if (dato.at(dato.size() - 1) == ',')
						{
							dato.erase(dato.size() - 1);
						}
						i->second->AgregarDatos(dato);
						Filas->push_back(new Fila(contRow));
						contRow++;
					}
					j++;
				}
			}
			else
			{
				for (Colmap::iterator i = Columnas.begin(); j < contColumnas; i++)
				{
					if (j + 1 < contColumnas) {
						getline(file, dato, '\t');
						i->second->AgregarDatos(dato);
					}
					else
					{
						getline(file, dato, '\n');
						i->second->AgregarDatos(dato);
						Filas->push_back(new Fila(contRow));
						contRow++;
					}
					j++;
				}
			}
		}
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

		Colmap::iterator k = Columnas.begin();

		for (int j = 0; j < k->second->getDatos()->size()-1; j++)
		{
			int o = 0;

			for (Colmap::iterator i = Columnas.begin(); i != Columnas.end(); i++)
			{
				if (extension == "csv") {
					if (o+1 <= contColumnas)
					{
						file << i->second->getDatos()->at(j); file << ",";
					}
					else
					{
						file << i->second->getDatos()->at(j);
					}
				}
				else
				{
					if (o +1 <= contColumnas)
					{
						file << i->second->getDatos()->at(j); file << "\t";
					}
					else
					{
						file << i->second->getDatos()->at(j);
					}
				}
				o++;
			}
			file << "\n";
		}
		file.close();
	}
	/*bool Ordenar(string busqueda)
	{
		
		int i;
		for (i = 0; i < contColumnas; i++) {
			if (Columnas->at(i)->getEtiqueta() == busqueda) {
				
				break;
			}
		}
		if (i == contColumnas) {
			return false;
		}
		auto lmb = [](string c) {return c; };
		InsertionSort<string, string, Fila*>(Columnas->at(i)->getDato(),Filas, lmb); 	
		return true;
	}*/

	bool getIsEmpty() { return isEmpty; }

	vector<Fila*>* getFila() {
		return this->Filas;
	}

Colmap getColumnas() {
	return this->Columnas;
}
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

	void GenerarColumnas(string Archivo) {
		Listado->push_back(new DataFrame());
		Listado->at(0)->ContarColumnas(Archivo);
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

	/*bool OrdenarXAtributo(string B, int n) {
		return Listado->at(n)->Ordenar(B);
	}*/
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
