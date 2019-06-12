#pragma once

#include <iostream>
#include <conio.h>
#include <functional>

using namespace System;
using namespace std;

#define Negro     0
#define Amarillo  1
#define Marron    2
#define Naranja   3
#define Azul      4
#define Verde     5
#define AzulOS    6
#define GrisOS    7
#define Gris      8
#define VerdeOS   9
#define Rojo      10
#define Cian      11
#define Blanco    12
#define CianOS    13
#define Violeta   14
#define VioletaOS 15

#define ARRIBA 72
#define ABAJO 80
#define DERECHA 77
#define IZQUIERDA 75
#define SALIR      27

void configurarColorFondo(short color) {
	switch (color)
	{
	case Negro:      Console::BackgroundColor = ConsoleColor::Black; break;
	case Amarillo:   Console::BackgroundColor = ConsoleColor::Yellow; break;
	case Marron:     Console::BackgroundColor = ConsoleColor::DarkRed; break;
	case Naranja:    Console::BackgroundColor = ConsoleColor::DarkYellow; break;
	case Azul:       Console::BackgroundColor = ConsoleColor::Blue; break;
	case Verde:      Console::BackgroundColor = ConsoleColor::Green; break;
	case AzulOS:     Console::BackgroundColor = ConsoleColor::DarkBlue; break;
	case GrisOS:     Console::BackgroundColor = ConsoleColor::DarkGray; break;
	case Gris:       Console::BackgroundColor = ConsoleColor::Gray; break;
	case VerdeOS:    Console::BackgroundColor = ConsoleColor::DarkGreen; break;
	case Rojo:       Console::BackgroundColor = ConsoleColor::Red; break;
	case Cian:       Console::BackgroundColor = ConsoleColor::Cyan; break;
	case CianOS:     Console::BackgroundColor = ConsoleColor::DarkCyan; break;
	case Blanco:     Console::BackgroundColor = ConsoleColor::White; break;
	case Violeta:    Console::BackgroundColor = ConsoleColor::Magenta; break;
	case VioletaOS:  Console::BackgroundColor = ConsoleColor::DarkMagenta; break;
	}
}

void configurarColorTexto(short color) {
	switch (color)
	{
	case Negro:      Console::ForegroundColor = ConsoleColor::Black; break;
	case Amarillo:   Console::ForegroundColor = ConsoleColor::Yellow; break;
	case Marron:     Console::ForegroundColor = ConsoleColor::DarkRed; break;
	case Naranja:    Console::ForegroundColor = ConsoleColor::DarkYellow; break;
	case Azul:       Console::ForegroundColor = ConsoleColor::Blue; break;
	case Verde:      Console::ForegroundColor = ConsoleColor::Green; break;
	case AzulOS:     Console::ForegroundColor = ConsoleColor::DarkBlue; break;
	case GrisOS:     Console::ForegroundColor = ConsoleColor::DarkGray; break;
	case Gris:       Console::ForegroundColor = ConsoleColor::Gray; break;
	case VerdeOS:    Console::ForegroundColor = ConsoleColor::DarkGreen; break;
	case Rojo:       Console::ForegroundColor = ConsoleColor::Red; break;
	case Cian:       Console::ForegroundColor = ConsoleColor::Cyan; break;
	case CianOS:     Console::ForegroundColor = ConsoleColor::DarkCyan; break;
	case Blanco:     Console::ForegroundColor = ConsoleColor::White; break;
	case Violeta:    Console::ForegroundColor = ConsoleColor::Magenta; break;
	case VioletaOS:  Console::ForegroundColor = ConsoleColor::DarkMagenta; break;
	}
}

void Menu(int &Opcion) {
	Console::SetWindowSize(115, 50);
	while (!(Opcion == 1)) {
		configurarColorTexto(Cian);
	     cout << "\t  _______                             __                             ______                      " << endl;
		 cout << "\t /       \                           /  |                           /      \       __        __    " << endl;
		 cout << "\t $$$$$$$  |  ______   _______    ____$$ |  ______    _______       /$$$$$$  |   /  |      /  |   " << endl;
		 cout << "\t $$ |__$$ | /      \ /       \  /      $$ | /      \  /       |       $$ |  $$/  __$$ |__  __$$ |__ " << endl;
		 cout << "\t $$    $$/  $$$$$$  |$$$$$$$  |/$$$$$$$ | $$$$$$  |/$$$$$$$/       $$ |      /  $$    |/  $$    |" << endl;
		 cout << "\t $$$$$$$/   /    $$ |$$ |  $$ |$$ |  $$ | /    $$ |$$      \        $$ |   __ $$$$$$$$/ $$$$$$$$/ " << endl;
		 cout << "\t $$ |      /$$$$$$$ |$$ |  $$ |$$ \__ $$ |/$$$$$$$ | $$$$$$  |      $$ \__/  |    $$ |      $$ |   " << endl;
		 cout << "\t $$ |      $$    $$ |$$ |  $$ |$$    $$ |$$    $$ |/     $$/       $$    $$/    $$/       $$/    " << endl;
		 cout << "\t $$/        $$$$$$$/ $$/   $$/  $$$$$$$/  $$$$$$$/ $$$$$$$/         $$$$$$/                      " << endl;
		 cout << "\t                                                                                              	" << endl;
		
		cout << "\n\n\t\t\t\t\t\t  ,*   ^;     ;'   *," << endl;
		cout << "\t\t\t\t\t\t  ;   s$$$$$$$s     ;" << endl;
		cout << "\t\t\t\t\t\t  ',ss$$$$$$$$$$s, ' " << endl;
		cout << "\t\t\t\t\t\t  ;s$$$$$$$$$$$$$$$  " << endl;
		cout << "\t\t\t\t\t\t  $$$$$$$$$$$$$$$$$$ " << endl;
		cout << "\t\t\t\t\t\t $$$$P**Y$$$Y**W$$$$$" << endl;
		cout << "\t\t\t\t\t\t $$$$  p*$$$*q  $$$$$" << endl;
		cout << "\t\t\t\t\t\t  $$$$$.$$$$$.$$$$$$ " << endl;
		cout << "\t\t\t\t\t\t   $$$$$$$$$$$$$$$   " << endl;
		cout << "\t\t\t\t\t\t    *Y$$$***$$$Y*    " << endl;
		cout << "\t\t\t\t\t\t       *$b.$$*       " << endl;
	
		configurarColorTexto(Rojo);
		cout << "\n\n\t\t\t\t      " << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
		cout << "\t\t\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "\t\t       MENU\t\t    " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "    1. Mostrar Dataframe\t\t    " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t\t\t      " << char(186) << "\t\t\t\t\t    " << char(186);
		cout << "\n\t\t\t\t      " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;

		configurarColorTexto(Verde);
		do {
			Console::SetCursorPosition(18, 40);
			cout << "ELIJA UNA OPCION: ";
			cin >> Opcion;
		} while (!(Opcion >= 1 && Opcion <= 9));
		configurarColorTexto(Verde);
		configurarColorFondo(Negro);
		system("cls");
	}

}