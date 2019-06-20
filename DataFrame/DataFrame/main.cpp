#include "DataFrame.h"
#include "Menu.h"
#include <map>

void Interacción()
{
	ListadoDF* Listado = new ListadoDF;
	int Opcion = 0;
	int Opcion2, Indice;
	string Busqueda;
	Menu(Opcion);

	string nombreArchivo;

	while (true)
	{
		switch (Opcion)
		{
		case 1:
			while (true) {
				do {
					cout << "Ingresa el archivo que quiere abrir: "; cin >> nombreArchivo;
				} while (!Listado->GenerarDF(nombreArchivo));

				cout << "DATAFRAME CREADO EXITOSAMENTE" << endl;
				cout << "Desea crear un nuevo DataFrame?(Si:1/No:0) ";
				cin >> Opcion2;
				if (Opcion2 == 0)
					break;
			}
			break;

		case 2:
			Listado->MostrarDF(); break;

		case 3: int i;
			do
			{
				cout << "¿Cual DataFrame quiere guardar?: "; cin >> i;
				cout << endl;

			} while (i >= Listado->getsize());

			if (!Listado->getIsEmpty(i)) {

				Listado->Guardar(i);
				cout << "DATAFRAME GUARDADO EXITOSAMENTE";
			}
				else { cout << "No ha igresado datos al DataFrame"; }
				break;
				
		case 4:

			do {
				cout << "Ingresa el Data Frame que quiere mostrar: "; cin >> Indice;
			} while (!(Indice >= 0 && Indice < Listado->getsize()));

			Listado->MostrarDFpos(Indice);
			break;

		case 5:
			do{
			cout << "Elige el Data Frame que quieres ordenar: ";
			cin >> Indice;
		   
			cout << "Elige la etiqueta por la que quieres ordenar: ";

			cin >> Busqueda;
			} while (!(Indice >= 0 && Indice < Listado->getsize()) || !Listado->OrdenarXAtributo(Busqueda, Indice));
		
			break;
		default:
			break;
		}
		if (Opcion == 27) break;
		system("pause>0");
		system("cls");
		
		Opcion = 0;
		Menu(Opcion);
	}
	
}

int main()
{  
	map<string, float> m;
	m["hola"] = 10.5;
	
	Interacción();
	return 0;
}