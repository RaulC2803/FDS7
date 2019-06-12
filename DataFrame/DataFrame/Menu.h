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
	
	while (!(Opcion == 1)) {
		cout << "                              _,add8ba,										" << endl;
		cout << "                            ,d888888888b,									    " << endl;
		cout << "                           d8888888888888b                        _,ad8ba,_	" << endl;
		cout << "                          d888888888888888)                     ,d888888888b,  " << endl;
		cout << "                          I8888888888888888 _________          ,8888888888888b " << endl;
		cout << "                __________`Y88888888888888P***********baaa,__ ,888888888888888," << endl;
		cout << "            ,adP************9888888888P**^                 ^*Y8888888888888888I" << endl;
		cout << "         ,a8*^           ,d888P*888P^                           ^*Y8888888888P'" << endl;
		cout << "       ,a8^            ,d8888'                                     ^Y8888888P' " << endl;
		cout << "      a88'           ,d8888P'                                        I88P*^	" << endl;
		cout << "    ,d88'           d88888P'                                          *b,	    " << endl;
		cout << "   ,d88'           d888888'                                            `b,	    " << endl;
		cout << "  ,d88'           d888888I                                              `b,	" << endl;
		cout << "  d88I           ,8888888'            ___                                `b,   " << endl;
		cout << " ,888'           d8888888          ,d88888b,              ____            `b,  " << endl;
		cout << " d888           ,8888888I         d88888888b,           ,d8888b,           `b  " << endl;
		cout << ",8888           I8888888I        d8888888888I          ,88888888b           8, " << endl;
		cout << "I8888           88888888b       d88888888888'          8888888888b          8I " << endl;
		cout << "d8886           888888888       Y888888888P'           Y8888888888,        ,8b " << endl;
		cout << "88888b          I88888888b      `Y8888888^             `Y888888888I        d88," << endl;
		cout << "Y88888b         `888888888b,      `****^                `Y8888888P'       d888I" << endl;
		cout << "`888888b         88888888888b,                           `Y8888P^        d88888" << endl;
		cout << " Y888888b       ,8888888888888ba,_          _______        `**^        ,d888888" << endl;
		cout << " I8888888b,    ,888888888888888888ba,_     d88888888b               ,ad8888888I" << endl;
		cout << " `888888888b,  I8888888888888888888888b,    ^*Y888P*^      ____.,ad88888888888I" << endl;
		cout << "  88888888888b,`888888888888888888888888b,     **      ad888888888888888888888'" << endl;
		cout << "  8888888888888698888888888888888888888888b_,ad88ba,_,d88888888888888888888888 " << endl;
		cout << "  88888888888888888888888888888888888888888b,`***^ d8888888888888888888888888I " << endl;
		cout << "  8888888888888888888888888888888888888888888baaad888888888888888888888888888' " << endl;
		cout << "  Y8888888888888888888888888888888888888888888888888888888888888888888888888P  " << endl;
		cout << "  I888888888888888888888888888888888888888888888P^  ^Y8888888888888888888888'  " << endl;
		cout << "  `Y88888888888888888P88888888888888888888888888'     ^88888888888888888888I   " << endl;
		cout << "   `Y8888888888888888 `8888888888888888888888888       8888888888888888888P'   " << endl;
		cout << "    `Y888888888888888  `888888888888888888888888,     ,888888888888888888P'	" << endl;
		cout << "     `Y88888888888888b  `88888888888888888888888I     I888888888888888888'	    " << endl;
		cout << "       *Y8888888888888b  `8888888888888888888888I     I88888888888888888'	    " << endl;
		cout << "         *Y88888888888P   `888888888888888888888b     d8888888888888888'	    " << endl;
		cout << "            ^/*******^     `Y88888888888888888888,    888888888888888P'		" << endl;
		cout << "                             *8888888888888888888b,   Y888888888888P^		    " << endl;
		cout << "                              `Y888888888888888888b   `Y8888888P*^			    " << endl;
		cout << "                                *Y8888888888888888P     `****^				    " << endl;
		cout << "                                  `*YY88888888888P'							" << endl;
	
		configurarColorTexto(Rojo);
		cout << "\n\t\t      " << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
		cout << "\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t      " << char(186) << "\t\t       MENU\t\t    " << char(186) << endl;
		cout << "\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t      " << char(186) << "    1. Mostrar Dataframe\t\t    " << char(186) << endl;
		cout << "\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t      " << char(186) << "\t\t\t\t\t    " << char(186) << endl;
		cout << "\t\t      " << char(186) << "\t\t\t\t\t    " << char(186);
		cout << "\n\t\t      " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;

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