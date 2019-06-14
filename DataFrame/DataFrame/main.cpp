#include "DataFrame.h"
#include "Menu.h"
#include <map>

void Interacción()
{
	ListadoDF* Listado = new ListadoDF;
	int Opcion = 0;
	int Opcion2, Indice;
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

		/*case 3:
			if (!P->getIsEmpty()) {
				P->GuardarDatos();
				cout << "DATAFRAME GUARDADO EXITOSAMENTE";
			}
			else { cout << "No ha igresado datos al DataFrame"; }
			break;
			*/
		case 4: 
			
				do {
					cout << "Ingresa el Data Frame que quiere mostrar: "; cin >> Indice;
				} while (!(Indice >= 0 && Indice < Listado->getsize()));
				
				Listado->MostrarDFpos(Indice);
			break;
		
		default:
			break;
		}
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