#include "DataFrame.h"
#include "Menu.h"
#include <map>

void Interacción()
{
	ListadoDF* Listado = new ListadoDF;
	int Opcion = 0;
	int Opcion2, Indice, Filtro, f2;
	string Busqueda;
	Menu(Opcion);
	string c1, c2, c3, c4;
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
				cout << "Desea crear un nuevo DataFrame?(Si:1/No:0): "; cin >> Opcion2;
				if (Opcion2 == 0)
				{
					break;
				}
			}
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

				Listado->Guardar(i);
				cout << "DATAFRAME GUARDADO EXITOSAMENTE";
				system("pause>0");

			}
			else { cout << "No ha igresado datos al DataFrame"; }
			break;
		case 4:
			do {
				cout << "Ingresa el Data Frame que quieres filtrar: "; cin >> Indice;
			} while (!(Indice >= 0 && Indice < Listado->getsize()));
			do {
				cout << "Ingresa el criterio por el cual quieres filtrar: " << endl;
				cout << "1. Mayor " << endl;
				cout << "2. Menor " << endl;
				cout << "3. Inicia con " << endl;
				cout << "4. Termina con " << endl;
				cout << "5. Igual a " << endl;
				cout << "6. Contenido en " << endl;
				cout << "7. No Contenido en " << endl;
				cin >> Filtro;
				
			} while (!(Filtro >= 1 && Filtro < 7));
			do {
				cout << "Numero de Columnas por las que quieres realizar el filtro: "; cin >> f2;

			} while (!(f2 >= 1 && f2 <= 2));
			switch (Filtro) {
			case 5:
				if (f2 == 1) {
					cin >> c1;
					cin >> c2;
					Listado->Filtrado(Indice, c1, c2, "", "");
				}
				break;
			default: break;
			}
			
			break;
			/*case 4:

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
			case 1: cin >> Busqueda;
				Listado->GenerarColumnas(Busqueda);
				break;
			default:
				break;*/
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