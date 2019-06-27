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

	void setDatos(vector<string>* ptr) {
		Data = ptr;
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

template <typename T, typename R = T>
class Tree
{
	struct Node
	{
		T elem;
		Node* left;
		Node* right;
		int h;

		Node(T elem, Node* left = nullptr, Node* rigth = nullptr) :elem(elem), left(left), right(right) {}

		static int height(Node* n)
		{
			if (n == nullptr)
			{
				return -1;
			}
			else
			{
				n->h;
			}
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
		else {
			if (key(elem) < key(node->elem)) {
				add(node->left, elem);
			}
			else {
				add(node->right, elem);
			}
		}
		node->updateH();
	}

	void InOrder(Node* node, std::function<void(T)> doSomething) {
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

	Tree(std::function<R(T)> key = [](T a) {return a; }) :root(nullptr), length(0), key(key) {}
	~Tree() { borrar(root); }

	int Height() {
		return Node::height(root);
	}
	int size() {
		return length;
	}

	void add(T elem) { add(root, elem); length++; }

	void InOrder(std::function<void(T)>doSomething)
	{
		InOrder(root, doSomething);
	}

	string Mayor() {
		Node* node = Mayor(root);
		if (node != nullptr) {
			return node->elem;
		}
	}
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
	Tree<Fila*, string>* T;
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
		else extension = "";
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
				cout << Filas->at(j)->getID() << "\t\t\t";

				if (contColumnas > 3)
				{
					for (int i = 0; i < 4; i++)
					{
						cout << Filas->at(j)->getData(Columnas, etiquetas->at(i)) << "\t\t\t";
					}
				}
				else
				{
					for (int i = 0; i < contColumnas; i++)
					{
						cout << Filas->at(j)->getData(Columnas, etiquetas->at(i)) << "\t\t\t";
					}
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

	void GuardarDatos(string fileName, string extension)
	{
		string nombreArchivo = fileName;
		ofstream file;
		nombreArchivo += "." + extension;

		file.open(nombreArchivo);

		for (int j = 0; j < contRow; j++)
		{
			for (int i = 0; i < contColumnas; i++)
			{
				if (extension == "csv") {
					if (i+1 <= contColumnas)
					{
						file << Columnas[etiquetas->at(i)]->getDatos()->at(Filas->at(j)->getID()); file << ",";
					}
					else
					{
						file << Columnas[etiquetas->at(i)]->getDatos()->at(Filas->at(j)->getID());
					}
				}
				else
				{
					if (i + 1 <= contColumnas)
					{
						file << Columnas[etiquetas->at(i)]->getDatos()->at(Filas->at(j)->getID()); file << "\t";
					}
					else
					{
						file << Columnas[etiquetas->at(i)]->getDatos()->at(Filas->at(j)->getID());
					}
				}
			}
			if(j + 1 < contRow)
			file << "\n";
		}
		file.close();
	}

	void Index(string _etiqueta) {
		T = new Tree<Fila*, string>([&](Fila* R) {return R->getData(Columnas, _etiqueta); });
		for (int i = 1; i < Filas->size();i++) {
			T->add(Filas->at(i));
		}
	}

	bool Comparar(int a, string c1, string c2, int i) {
		switch (a) {
		case 1:
			if (Columnas[c1]->getDatos()->at(i) >= c2)
				return true;
			else return false;
			break;
		case 2:
			if (Columnas[c1]->getDatos()->at(i) <= c2)
				return true;
			else return false;
			break;
		case 3:
				if (Columnas[c1]->getDatos()->at(i).at(0) == c2.at(0))
					return true;
			
			else return false;
			break;
		case 4:
			if (Columnas[c1]->getDatos()->at(i).at(Columnas[c1]->getDatos()->at(i).size()-1) == c2.at(0))
				return true;
			else return false;
			break;
		case 5:
			if (Columnas[c1]->getDatos()->at(i) == c2) 
				return true;
			else return false;
			break;
		case 6:
			if (Columnas[c1]->getDatos()->at(i).find(c2) != std::string::npos)
				return true;
			else return false;
			break;
		case 7:
			if (Columnas[c1]->getDatos()->at(i).find(c2) == std::string::npos)
				return true;
			else return false;
			break;
		default:
		
			break;
		}
	}

	DataFrame* Filtrar(int a, string F1, string F2, int b,string F3, string F4) {
		DataFrame* NDF = new DataFrame();
		NDF->Columnas = this->Columnas;
		NDF->setContCols(contColumnas);
		NDF->IniEtiqueta(etiquetas);
		for (int i = 0; i < contRow; i++) {
			
			if (Comparar(a,F1,F2,i)) {
				if (F3 == "" && F4 == "") {
					NDF->Filas->push_back(new Fila(i));
					NDF->SumarRow();
				}
				else if (Comparar(b,F3,F4,i) ){
					NDF->Filas->push_back(new Fila(i));
					NDF->SumarRow();
				}
			}
		}
		return NDF;
	}

	DataFrame* Select(vector<string> Nombres) {
		int x = 0;
		Colmap Ncol;
		for (int i = 0; i < Nombres.size(); i++) {
			Ncol.insert({ Nombres.at(i), new Columna(Nombres.at(i)) });
			x++;
		}
		for (int i = 0; i < Nombres.size(); i++) {
			Ncol[Nombres.at(i)]->setDatos(Columnas[Nombres.at(i)]->getDatos());
		}
		DataFrame* NDF = new DataFrame;
		NDF->Columnas = Ncol;
		*NDF->Filas = *Filas;
		NDF->contRow = contRow;
		NDF->contColumnas = x;
		*NDF->etiquetas = Nombres;
		NDF->setIsEmpty();
		return NDF;
	}

	//********************************************Ordenamiento**************************************
	template<typename T,typename R = T>
	void InsertionSort(DataFrame* NDF, vector<double>* aux, function<R(T)> key = [](T a) {return a; })
	{		
		if (key(NDF->Filas->at(1)).at(0) >= 48 && (key(NDF->Filas->at(1)).at(0)) <= 57)
		{
			for (int i = 2; i < contRow; i++)
			{
				double e = aux->at(i);
				T temp = NDF->Filas->at(i);
				int j = i;

				while (j > 1 && aux->at(j-1) > e)
				{
					NDF->Filas->at(j) = NDF->Filas->at(j - 1);
					aux->at(j) = aux->at(j - 1);
					j--;
				}
				if (i != j)
				{
					NDF->Filas->at(j) = temp;
					aux->at(j) = e;
				}
			}
		}
		else
		{
			for (int i = 2; i < contRow; i++)
			{
				T temp = NDF->Filas->at(i);
				int j = i;

				while (j > 1 && key(NDF->Filas->at(j-1)) > key(temp))
				{
					NDF->Filas->at(j) = NDF->Filas->at(j - 1);
					j--;
				}
				if (i != j)
				{
					NDF->Filas->at(j) = temp;
				}
			}
		}
	}

	template <typename T, typename R = T>
	int Pivot(DataFrame* NDF, vector<double>* aux, int i, int f, function<R(T)> key = [](T a) {return a; }) {
		if (key(NDF->Filas->at(1)).at(0) >= 48 && (key(NDF->Filas->at(1)).at(0)) <= 57)
		{
			double e = aux->at(i);
			T piv = NDF->Filas->at(i);
			int izq = i + 1;
			int der = f;
			while (der >= izq) {
				if (aux->at(izq) <= e) izq++;
				else if (aux->at(der) >= e) der--;
				else {
					T t = NDF->Filas->at(der);
					double y = aux->at(der);
					NDF->Filas->at(der) = NDF->Filas->at(izq);
					aux->at(der) = aux->at(izq);
					NDF->Filas->at(izq) = t;
					aux->at(izq) = y;
					der--;
					izq++;
				}
			}
			if (der != i) {
				double y = aux->at(der);
				T t = NDF->Filas->at(der);
				aux->at(der) = aux->at(i);
				NDF->Filas->at(der) = NDF->Filas->at(i);
				aux->at(i) = y;
				NDF->Filas->at(i) = t;
			}
			return der;
		}
		else
		{
			T piv = NDF->Filas->at(i);
			int izq = i + 1;
			int der = f;
			while (der >= izq) {
				if (key(NDF->Filas->at(izq)) <= key(piv)) izq++;
				else if (key(NDF->Filas->at(der)) >= key(piv)) der--;
				else {
					T t = NDF->Filas->at(der);
					NDF->Filas->at(der--) = NDF->Filas->at(izq);
					NDF->Filas->at(izq++) = t;
				}
			}
			if (der != i) {
				T t = NDF->Filas->at(der);
				NDF->Filas->at(der) = NDF->Filas->at(i);
				NDF->Filas->at(i) = t;
			}
			return der;
		}
	}

	template <typename T, typename R = T>
	void Quick(DataFrame* NDF, vector<double>* aux, int i, int f, function<R(T)> key = [](T a) {return a; }) {
		if (i < f) {
			int p = Pivot(NDF, aux, i, f, key);
			Quick(NDF, aux, i, p - 1, key);
			Quick(NDF, aux, p + 1, f, key);
		}
	}

	template <typename T, typename R = T>
	void QuickSort(DataFrame* NDF, vector<double>* aux, function<R(T)> key = [](T a) {return a; }) {
		Quick(NDF, aux,  1, contRow - 1, key);
	}

	template<typename T, typename R=T>
	void ConvertirDatos(vector<double>* aux, function<R(T)> key = [](T a) {return a; })
	{
		if (key(Filas->at(1)).at(0) >= 48 && key(Filas->at(1)).at(0) <= 57)
		{
			aux->push_back(0);
			for (int i = 1; i < contRow; i++)
			{
				string temp = key(Filas->at(i));
				aux->push_back(atof(temp.c_str()));
			}
		}
	}

	DataFrame* Ordenar(string _etiqueta)
	{
		vector<double>* aux;
		aux = new vector<double>;

		DataFrame *NDF = new DataFrame();
		NDF->Columnas = this->Columnas;
		NDF->setContCols(contColumnas);
		NDF->IniEtiqueta(etiquetas);
		*NDF->Filas = *Filas;
		NDF->setContRow(contRow);
		NDF->setIsEmpty();

		auto lmb = [&](Fila* row) {return row->getData(Columnas, _etiqueta); }; 
		ConvertirDatos<Fila*, string>(aux,lmb);
		//InsertionSort<Fila*, string>(NDF,aux,lmb);
		QuickSort<Fila*, string>(NDF, aux, lmb);
		return NDF;
	}

	//*************************************************************************************************
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
void setIsEmpty() { isEmpty = false; }
int getContCols() { return contColumnas; }
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

	void Guardar(int i, string fileName, string extension)
	{
		Listado->at(i)->GuardarDatos(fileName, extension);
	}

	bool getIsEmpty(int i) { return Listado->at(i)->getIsEmpty(); }

	int getsize() {
		return Listado->size();
	}

	void Filtrado(int i, int a, string c1, string c2, int b, string c3, string c4) {
		Listado->push_back(Listado->at(i)->Filtrar(a, c1, c2, b, c3, c4));
	}

	void Index(int i, string _etiqueta)
	{
		Listado->at(i)->Index(_etiqueta);
	}

	vector<DataFrame*>* getDFS() {
		return this->Listado;
	}

	void OrdenarXAtributo(string B, int n) {
		Listado->push_back(Listado->at(n)->Ordenar(B));
	}

	void Seleccionar(int i, vector<string> N)
	{
		Listado->push_back(Listado->at(i)->Select(N));
	}
};
