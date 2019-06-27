#include "DataFrame.h"
#include "Menu.h"
#include <map>

void Interacción()
{
	ListadoDF* Listado = new ListadoDF;
	int Opcion = 0;
	int Opcion2 = 0, Indice = 0, Filtro = 0, Filtro2 = 0, f2 = 0;
	int Validar = 0;
	int xd = 0;
	int find = 0;
	string Busqueda = "";
	Menu(Opcion);
	string c1 = "", c2 = "", c3 = "", c4 = "";
	string nombreArchivo = "";
	vector<string>ColNombres;

	while (true)
	{
		switch (Opcion)
		{
		case 1:
			while (true) {
				do {
					cout << "Ingresa el archivo que quiere abrir: "; cin >> nombreArchivo;
				} while (!Listado->GenerarDF(nombreArchivo));
				configurarColorTexto(Azul);
				cout << "DATAFRAME CREADO EXITOSAMENTE" << endl;
				configurarColorTexto(Verde);
				cout << "Desea crear un nuevo DataFrame?(Si:1/No:0): "; cin >> Opcion2;
				if (Opcion2 == 0)
				{
					break;
				}
			}
			nombreArchivo = ""; Opcion2 = 0;
			break;

		case 2:
			Listado->MostrarDF(); system("pause>0"); break;

		case 3: int i;
			do
			{
				cout << "¿Cual DataFrame quiere guardar?: "; cin >> i;
				cout << endl;

			} while (i >= Listado->getsize());

			if (!Listado->getIsEmpty(i)) {
				string fileName;
				string extension;
				cout << "Nombre para Guardar: "; cin >> fileName;
				do
				{
					cout << "Cual extension usara? csv o tsv: "; cin >> extension;

				} while (extension != "csv" && extension != "tsv");

				Listado->Guardar(i, fileName, extension);
				configurarColorTexto(Azul);
				cout << "DATAFRAME GUARDADO EXITOSAMENTE";
				configurarColorTexto(Verde);
				system("pause>0");

			}
			else { cout << "No ha igresado datos al DataFrame"; }
			
			break;
		case 4:
			do {
				cout << "Ingresa el Data Frame que quieres filtrar: "; cin >> Indice;
			} while (!(Indice >= 0 && Indice < Listado->getsize()));
			do {
				cout << "Numero de Columnas por las que quieres realizar el filtro: "; cin >> f2;

			} while (!(f2 >= 1 && f2 <= 2));
			do {
				//do {
					cout << "Ingresa el criterio por el cual quieres filtrar: " << endl;
					cout << "1. Mayor " << endl;
					cout << "2. Menor " << endl;
					cout << "3. Inicia con " << endl;
					cout << "4. Termina con " << endl;
					cout << "5. Igual a " << endl;
					cout << "6. Contenido en " << endl;
					cout << "7. No Contenido en " << endl;
					if (Validar == 0)
						cin >> Filtro;
					if (Validar == 1)
						cin >> Filtro2;
				//} while ();
					if ((Filtro >= 1 && Filtro <= 7) && (Filtro2 >= 0 && Filtro2 <= 7)) {
						if (Validar == 0) {
							cout << "Ingresa la columnas por la que quieres aplicar el filtro: ";
							cin >> c1;
							cout << "Ingresa el filtro: ";
							cin >> c2;
						}
						if (Validar == 1) {
							cout << "Ingresa la columnas por la que quieres aplicar el filtro: ";
							cin >> c3;
							cout << "Ingresa el filtro: ";
							cin >> c4;
						}
						Validar++;
					}
		       
			} while (!(Filtro >= 1 && Filtro <= 7) || !(Filtro2 >= 0 && Filtro2 <= 7) || (f2 == 2 && Validar <2) );
			Listado->Filtrado(Indice, Filtro, c1, c2, Filtro2, c3, c4);
			Filtro = 0; Filtro2 = 0; c1 = ""; c2 = ""; c3 = ""; c4 = ""; Validar = 0;
			break;
		case 5:
			do {
				cout << "Elige el Data Frame que quieres ordenar: ";
				cin >> Indice;
				cout << "Elige la etiqueta por la que quieres ordenar: ";
				cin >> Busqueda;
				cout << "Mayor a menor (1) Menor a Mayor (0): "; cin >> xd;
			} while (!(Indice >= 0 &&Indice < Listado->getsize()) || !(xd >= 0 && xd <=1));
			Listado->OrdenarXAtributo(Busqueda, Indice, xd);
			xd = 0; Busqueda = ""; Indice = 0;
			break;
		
		case 6:
			
			int Ncolumnas;
			do {
				cout << "Ingresa el Data Frame: "; cin >> Indice;
			} while (!(Indice >= 0 && Indice < Listado->getsize()));

			do {
				cout << "Elige el número de columnas que quieres mostrar: ";
				cin >> Ncolumnas;
			} while (!(Ncolumnas > 0 && Ncolumnas <= Listado->getDFS()->at(Indice)->getContCols()))
				;
			for (int i = 0; i < Ncolumnas; i++) {
				cout << "Seleccione una columna: ";
				cin >> c1;
				ColNombres.push_back(c1);
			}
			Listado->Seleccionar(Indice, ColNombres);
			Indice = 0; Ncolumnas = 0; c1 = "";
			break;

		case 7: 
			do {
				cout << "Ingrese el Data Frame: ";cin >> Indice;
			} while ((!(Indice >= 0) && Indice < Listado->getsize()));
			cout << "Ingrese la Columna en la que quiere buscar: "; cin >> c4;
			cout << "Ingrese el elemento que quiere buscar: "; cin >> Busqueda;
			find = Listado->Index(Indice, Busqueda, c4);
			if ( find != -1)
			{
				cout << "El elemento se encuentra en la Fila " << find;
			}
			else { configurarColorTexto(Rojo); cout << "NO MATCH"; configurarColorTexto(Verde); }
			system("pause>0");
			break;
		default:
			break;
		}
			
		if (Opcion == 27) break;
		
		system("cls");
		Opcion = 0;
		Menu(Opcion);
	}
}

int main()
{  
	Interacción();
	return 0;
}