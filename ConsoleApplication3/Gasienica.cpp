// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#define maxi 50000

using namespace std;



class Gasienica
{
public:
	int a[maxi];
	int f, r;
	


public:
	void initialize();
	void enqueue(int val);
	void enqueue2(int val);
	void dequeue();
	void display();
	void display2();

	
};

int remember_f;
int dlugosc_Edka;
char **gMapa;
int szerokosc, wysokosc;
char memory_lokacja;
int x_Edka = 1;
int y_Edka = 1;
char next_przeszkoda;
int suma_krokow = 0;
int test = 0;
char remember_kolor;


void intro();
void start();
void wymiary_mapy();		//Wysokoœæ i szerokoœæ mapy bêd¹ dodatnie i nie przekrocz¹ 4000 (szerokoœæ) i 1000 (wysokoœæ). Krotnoœæ ¿adnego ruchu nie bêdzie wiêksza ni¿ 5000.

void create_Edek();			//utwórz Edka
void add_segment();
void delete_segment();

void zawartosc_mapy();

void drzewa_do_okola();


void drzewo();
void kolec();
void grzyb();
void kaluza();
void zostaw_slad();
void showMapa();

void start_Edka();
void poruszanie_Edka();
void move_right();
void move_left();
void move_up();
void move_down();
void sprawdz_przeszkode();

void aktywacja_pola();
void load_test_map();
void refresh_test_map();

void edek_death();
void zakoncz();

void kolejka_cykl();
void edek_krok();
void koloruj();



Gasienica q;


int main()
{
	char x;
	int ch, val;
	
	intro();
	
}

void intro() {

	system("cls");
	cout << "Witaj w swiece Edka :)" << endl << endl;
	start();
	}

void zakoncz(){
	
	system("cls");
	cout << "Zegnaj" << endl;
	Sleep(3000);
	
	}

void start(){

	cout << "Instrukcja: " << endl;
	wymiary_mapy();
}

void create_Edek(){

	int dlugosc;
	cout << "Podaj dlugosc Edka: ";
	cin >> dlugosc;														
	dlugosc_Edka = dlugosc;
	cout << endl;

	q.initialize();
	for (int i = 0; i < dlugosc; i++)
	{
		q.enqueue(0);
	}
}
void wymiary_mapy(){
																		//char **mapa

	char **mapa;
	cout << "Podaj szerokosc mapy: [max 4000]";
	cin >> szerokosc;
	if (szerokosc >= 4001)
		do
		{
			system("cls");
			cout << "!!Max 4000!!" << endl; 
			cout << "Podaj szerokosc mapy:" << endl;
			cin >> szerokosc;
		}
			while (szerokosc <= 4000);
	else
	{
		cout << "Twoja szerokosc: " << szerokosc << endl;
		szerokosc++;
		szerokosc++;

	}
	cout << endl;

	cout << "Podaj wysokosc mapy: [max 1000]";
	cin >> wysokosc;
	if (szerokosc >= 1001)
		do
		{
			system("cls");
			cout << "!!Max 1000!!" << endl;
			cout << "Podaj wysokosc mapy:" << endl;
			cin >> wysokosc;
		} while (wysokosc <= 1000);
	else
	{
		cout << "Twoja wysokosc: " << wysokosc << endl;
		wysokosc++;
		wysokosc++;
	}
	cout << endl;

	system("cls");
	create_Edek();											// just making EDEK
	
	cout << "Startowy Edek: " << dlugosc_Edka << endl;

															// tworzenie tablicy
	mapa = new char *[wysokosc];	
	for (int i = 0; i < wysokosc; i++)
		mapa[i] = new char[szerokosc];
	
	gMapa = mapa;
	zawartosc_mapy();

	system("pause");

															//zwolnienie pamiêci
/*	for (int i = 0; i<wysokosc; i++)
		delete[] mapa[i];

	delete[] * mapa;
*/
}

void zawartosc_mapy(){

	cout << "Wymiary mapy to: " << wysokosc -2 << " x " << szerokosc -2 << endl;
	cout << "Utworz mape: " << endl;
	
	drzewa_do_okola();


	char rodzaj_lokacji;
	int licznik = 0;

		for (int j = 1; j < wysokosc-1; j++)							
		{

			for (int i = 1; i < szerokosc-1; i++)
			{																						
				
				if (licznik == 0)
				{
					cin >> licznik;			start_Edka();
					cin >> rodzaj_lokacji;
				}
				gMapa[i][j] = rodzaj_lokacji;
	
				licznik--;
			}
		}
		cout << endl;
		
		showMapa();

			start_Edka();

	refresh_test_map();
	poruszanie_Edka();



}


void drzewa_do_okola(){

	char drzewo = 'T';
	int licznik = 0;

	for (int j = 0; j < wysokosc ; j++)							//tworzenie tablicy
	{

		for (int i = 0; i < szerokosc; i++)
		{


			gMapa[i][j] = drzewo;

			licznik--;
		}
	}


}

void showMapa(){

	cout << "Oto mapa wygenerowana przez Ciebie:" << endl;

	for (int j = 0; j < wysokosc; j++)								//wypisywanie tablicy
	{

		for (int i = 0; i < szerokosc; i++)
		{
			cout << gMapa[i][j];

		}
		cout << endl;
	}

	cout << endl;

}

void start_Edka(){

	x_Edka = 1;
	y_Edka = 1;

	memory_lokacja = gMapa[1][1];
	gMapa[x_Edka][y_Edka] = 'o';


	cout << endl << memory_lokacja << endl;
}

void refresh_test_map(){

	system("cls");

	for (int j = 0; j < wysokosc; j++)
	{

		for (int i = 0; i < szerokosc; i++)
		{
			cout << gMapa[i][j];

		}
		cout << endl;
	}

	cout << endl;

}


void sprawdz_przeszkode(){

	next_przeszkoda = gMapa[x_Edka][y_Edka];
	
}

void move_right(){

		
	x_Edka++;
	y_Edka;
	sprawdz_przeszkode();
	x_Edka--;
	y_Edka;

	if (next_przeszkoda == 'T')
	{
		drzewo();
		
	}
	else{
		suma_krokow++;
		edek_krok();
		gMapa[x_Edka][y_Edka] = memory_lokacja;
		memory_lokacja = gMapa[x_Edka + 1][y_Edka];
		x_Edka++;
		y_Edka;
		gMapa[x_Edka][y_Edka] = 'o';							
		refresh_test_map();

		if (next_przeszkoda == 'K')
		{
			kolec();

		}
		else if (next_przeszkoda == 'G')
		{
			
			grzyb();
		}
		else if (next_przeszkoda >=97 && next_przeszkoda <=122)		
		{
			kaluza();
		}
		else if (next_przeszkoda == '.')
		{
			koloruj();
			
		}
		else
		{
			
			refresh_test_map();

		}
	}


}
void move_left(){

	x_Edka--;
	y_Edka;
	sprawdz_przeszkode();
	x_Edka++;
	y_Edka;

	if (next_przeszkoda == 'T')
	{
		drzewo();

	}
	else{
		suma_krokow++;
		edek_krok();
		gMapa[x_Edka][y_Edka] = memory_lokacja;
		memory_lokacja = gMapa[x_Edka - 1][y_Edka];
		x_Edka--;
		y_Edka;
		gMapa[x_Edka][y_Edka] = 'o';
		refresh_test_map();

		if (next_przeszkoda == 'K')
		{
			kolec();

		}
		else if (next_przeszkoda == 'G')
		{

			grzyb();
		}
		else if (next_przeszkoda >= 97 && next_przeszkoda <= 122)		
		{
			kaluza();
		}
		else if (next_przeszkoda == '.')
		{
			koloruj();
			
		}
		else
		{
			
			refresh_test_map();

		}
	}
}
void move_up(){

	x_Edka;
	y_Edka--;
	sprawdz_przeszkode();
	x_Edka;
	y_Edka++;

	if (next_przeszkoda == 'T')
	{
		drzewo();

	}
	else{
		suma_krokow++;
		edek_krok();
		gMapa[x_Edka][y_Edka] = memory_lokacja;
		memory_lokacja = gMapa[x_Edka][y_Edka - 1];
		x_Edka;
		y_Edka--;
		gMapa[x_Edka][y_Edka] = 'o';
		refresh_test_map();

		if (next_przeszkoda == 'K')
		{
			kolec();

		}
		else if (next_przeszkoda == 'G')
		{

			grzyb();
		}
		else if (next_przeszkoda >= 97 && next_przeszkoda <= 122)		
		{
			kaluza();
		}
		else if (next_przeszkoda == '.')
		{
			koloruj();
			
		}
		else
		{
			
			refresh_test_map();

		}
	}
}
void move_down(){

	x_Edka;
	y_Edka++;
	sprawdz_przeszkode();
	x_Edka;
	y_Edka--;

	if (next_przeszkoda == 'T')
	{
		drzewo();

	}
	else{
		suma_krokow++;
		edek_krok();
		gMapa[x_Edka][y_Edka] = memory_lokacja;
		memory_lokacja = gMapa[x_Edka][y_Edka + 1];
		x_Edka;
		y_Edka++;
		gMapa[x_Edka][y_Edka] = 'o';
		refresh_test_map();

		if (next_przeszkoda == 'K')
		{
			kolec();

		}
		else if (next_przeszkoda == 'G')
		{

			grzyb();
		}
		else if (next_przeszkoda >= 97 && next_przeszkoda <= 122)	
		{
			kaluza();
		}
		else if (next_przeszkoda == '.')
		{
			koloruj();
			
		}
		else
		{
			
			refresh_test_map();

		}
	}
}

bool jestLiczba(string znaki){
	std::string::const_iterator it = znaki.begin();
	while (it != znaki.end() && isdigit(*it)) ++it;
	return !znaki.empty() && it == znaki.end();
}

void poruszanie_Edka(){

	char move;
	int liczba_krokow;
	int licznik = 0;
	string znak;


	do
	{
		cin >> znak;
		if (jestLiczba(znak))
		{
			liczba_krokow = stoi(znak);
			if (liczba_krokow <= 5000 && liczba_krokow > 0)
			{
				cin >> move;
			}
			else
			{
				
				liczba_krokow = 1;
				
			}
		}
	else{
			liczba_krokow = 1;
			move = znak[0];

		}
		
		for (int i = 0; i < liczba_krokow; i++)
		{
					if (move == 'p') 
					{
						move_right();
					}
					else if (move == 'l') 
					{
						move_left();
					}
					else if (move == 'g') 
					{
						move_up();
					}
					else if (move == 'd') 
					{
						move_down();
					}
			
		}
		
		cout << suma_krokow << endl;
		cout << remember_f << "   "  << test;
		q.display();


	
	} while (0 == 0);
}
void drzewo(){

	refresh_test_map();
}
void kolec(){
	
	delete_segment();
}
void grzyb(){

	add_segment();
	memory_lokacja = '.';
}
void kaluza(){

	test = 1;
	
	remember_kolor = next_przeszkoda;
	cout << endl << "kolor " << remember_kolor << endl;

}

void koloruj(){
	
	
	cout << q.a[1] << "!!!!!!!!!!!!    " << char(remember_f) << x_Edka << y_Edka;

	if (remember_f >= 97 && remember_f <= 122)
	{
		char set_kolor;
		set_kolor = char(remember_f);
		gMapa[x_Edka][y_Edka] = set_kolor;
		//refresh_test_map();
		cout << "koloruje!!";

	}
}
void add_segment(){

	q.enqueue(0);
	cout << "added";
}
void delete_segment(){

	q.dequeue();
	cout << "deleted";
}







void Gasienica::initialize()
{
	cout << "Empty Queue is created :D";
	f = r = -1;
}
void Gasienica::enqueue(int val)
{
	val = remember_f;
	if (r == maxi - 1)
	{
		cout << "\nQueue Overflow..";
	}
	else if (f == -1 && r == -1)
	{
		f = r = 1;
		
		a[r] = val;
	}
	else
	{
		r++;
		a[r] = val;
	}
	
}

void Gasienica::enqueue2(int val)
{

	
	if (test = 0)
	{
		val = remember_f;
	}
	else
	{
		val = remember_kolor;
	}
	test = 0;
	if (r == maxi - 1)
	{
		cout << "\nQueue Overflow..";
	}
	else if (f == -1 && r == -1)
	{
		f = r = 1;

		a[r] = val;
	}
	else
	{
		r++;
		a[r] = val;
	}
}
void Gasienica::dequeue()
{
	if (f == -1 && r == -1)
	{
		cout << "\nQueue is already empty..";
	}
	else if (f == r)
	{
		cout << "\nThe dequeued element is.." << a[f];
		remember_f = a[f];
		f = r = -1;
	}
	else
	{
		cout << "\nThe dequeued element is.." << a[f];
		remember_f = a[f];
		f++;
	}
}
void Gasienica::display()
{
	int x;
	if (f == -1 && r == -1)
	{
		cout << "\nThe Queue is empty..";
		return;
	}
	cout << "\nThe Contents of the Queue is..";
	for (x = f; x <= r; x++)
	{
		cout << a[x] << " ";
	}
}

void Gasienica::display2()
{
	int x = 0;

	{

		cout << a[x] << " kolororek ";
	}
}


void edek_krok(){

	q.dequeue();
	q.enqueue2(0);
	
	

}