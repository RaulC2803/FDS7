#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include "Menu.h"


using namespace std;
using namespace System;

template <typename T, typename R = T>
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

	Tree(std::function<R(T)>key = [](T a) {return a; }) :root(nullptr), length(0), key(key) {}
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
	string getData(Colmap &Col, string name) {
		return Col[name]->getDatos()->at(id);
	}
	int getID() { return id; }
};

class DataFrame
{
	vector<Fila*>* Filas;
	vector<string>*etiquetas;
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
		etiquetas = new vector<string>;
		contColumnas = 0;
		contRow = 0;
		extension = "";
	}

	~DataFrame()
	{
		Filas->clear();
	}

	void verificarExtension(string n_file)
	{
		if (n_file.size() >= 3)
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
	}

	void ContarColumnas(string n_file)
	{
		int k = 0;
		bool finish = false;
		string n_columna;
		string f;
		string x;

		file.open(n_file, ios::in);

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
	}

	void MostrarData() {

		for (int j = 0; j < contRow; j++)
		{
			if (j < 9 || j >= contRow - 9)
			{
				cout << Filas->at(j)->getID() << "\t";

				for (int i = 0; i < 3; i++)
				{
					cout << Filas->at(j)->getData(Columnas,etiquetas->at(i)) << "\t\t";
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
				for (int i = 0; j < contColumnas ;i++)
				{
					if (j + 1 < contColumnas) {
						getline(file, dato, ',');
						Columnas[etiquetas->at(j)]->AgregarDatos(dato);
					}
					else
					{
						getline(file, dato, '\n');
						if (dato.at(dato.size() - 1) == ',')
						{
							dato.erase(dato.size() - 1);
						}
						Columnas[etiquetas->at(j)]->AgregarDatos(dato);
						Filas->push_back(new Fila(contRow));
						contRow++;
					}
					j++;
				}
			}
			else
			{
				if (extension == "tsv") {
					for (int i = 0; j < contColumnas; i++)
					{
						if (j + 1 < contColumnas) {
							getline(file, dato, '\t');
							Columnas[etiquetas->at(j)]->AgregarDatos(dato);
						}
						else
						{
							getline(file, dato, '\n');
							if (dato.at(dato.size() - 1) == '\t')
							{
								dato.erase(dato.size() - 1);
							}
							Columnas[etiquetas->at(j)]->AgregarDatos(dato);
							Filas->push_back(new Fila(contRow));
							contRow++;
						}
						j++;
					}
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

		for (int j = 0; j < k->second->getDatos()->size(); j++)
		{
			for (int i = 0; i < contColumnas; i++)
			{
				if (extension == "csv") {
					if (i+1 <= contColumnas)
					{
						file << Columnas[etiquetas->at(i)]->getDatos()->at(j); file << ",";
					}
					else
					{
						file << Columnas[etiquetas->at(i)]->getDatos()->at(j);
					}
				}
				else
				{
					if (i + 1 <= contColumnas)
					{
						file << Columnas[etiquetas->at(i)]->getDatos()->at(j); file << "\t";
					}
					else
					{
						file << Columnas[etiquetas->at(i)]->getDatos()->at(j);
					}
				}
			}
			if(j + 1 < k->second->getDatos()->size())
			file << "\n";
		}
		file.close();
	}

	/*void Index(string Columna) {
		Tree<Fila*, string>* T = new Tree<Fila*, string>(
			[=](Fila* R) {return R->getData(Columna); });
		for (int i = 0; i < Filas->size();i++) {
			T->add(Filas->at(i));
		}
	}*/

	DataFrame* FiltrarIguala(string F1, string F2) {
		DataFrame* NDF = new DataFrame();
		NDF->Columnas = this->Columnas;
		NDF->setContCols(contColumnas);
		NDF->IniEtiqueta(etiquetas);
		for (int i = 0; i < contRow; i++) {
			if (Columnas[F1]->getDatos()->at(i) == F2) {
				NDF->Filas->push_back(new Fila(i));
				NDF->SumarRow();
			}
		}
		return NDF;
	}

	template<typename T,typename R = T>
	void InsertionSort(DataFrame* NDF, string _etiqueta, function<R(T)> key = [](T a) {return a; })
	{
		/*if (NDF->Filas->at(1)->getData(Columnas, _etiqueta).at(1) <= 48 && NDF->Filas->at(1)->getData(Columnas, _etiqueta).at(1) <= 57)
		{
			for (int i = 1; i < contRow; i++)
			{
				atoi(NDF->Filas->at(i)->getData(Columnas, _etiqueta).c_str());
			}
		}
*/
		for (int i = 0; i < contRow; i++)
		{
			NDF->Filas->push_back(new Fila(Filas->at(i)->getID()));
			NDF->SumarRow();
		}

		for (int i = 1; i < contRow; i++)
		{

			Fila* aux = NDF->Filas->at(i);
			T temp = NDF->Filas->at(i)->getData(Columnas, _etiqueta);
			int j = i;
			while (j > 0 && key(NDF->Filas->at(j - 1)->getData(Columnas, _etiqueta)) > key(temp))
			{
				NDF->Filas->at(j) = NDF->Filas->at(j - 1);
				j--;
			}
			if (i != j)
			{
				NDF->Filas->at(j) = aux;
			}
		}
	}

	DataFrame* Ordenar(string busqueda)
	{
		DataFrame *NDF = new DataFrame();
		NDF->Columnas = this->Columnas;
		NDF->setContCols(contColumnas);
		NDF->IniEtiqueta(etiquetas);
		auto lmb = [](string c) {return c; };
		InsertionSort<string, string>(NDF,busqueda,lmb);
		return NDF;
	}

	bool getIsEmpty() { return isEmpty; }

	vector<Fila*>* getFila() {
		return this->Filas;
	}

Colmap getColumnas() {
	return this->Columnas;
}
void setContCols(int _cont) { contColumnas = _cont; }
void setContRow(int _cont) { contRow = _cont; }
void SumarRow() { contRow++; }
void SumarCols() { contColumnas++; }
void IniEtiqueta(vector<string>*_etiquetas) { etiquetas = _etiquetas; }
};


//////////////////////Listado///////////////////////////


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

	void Filtrado(int i,string c1, string c2, string c3, string c4) {
		Listado->push_back(Listado->at(i)->FiltrarIguala(c1, c2));
	}

	vector<DataFrame*>* getDFS() {
		return this->Listado;
	}

	void OrdenarXAtributo(string B, int n) {
		Listado->push_back(Listado->at(n)->Ordenar(B));
	}
};


