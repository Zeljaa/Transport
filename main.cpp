#include <stdio.h>
#include <fstream>
#include <iostream>
#include <set>

#include "Skup.h"
#include "Linija.h"
#include "Simulacija.h"

using namespace std;
void Pocetak(int& opcija) {
	cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju:" << endl;
	cout << "1. Ucitavanje podataka o mrezi gradskog prevoza" << endl;
	cout << "0. Kraj rada" << endl;
	//cin >> opcija;
	opcija = 1;
	cout << 1 << endl;
	while (opcija != 1 && opcija != 0) {
		cout << "Uneli ste pogresnu opciju. Molimo Vas, pokusajte ponovo:" << endl;
		cout << "1. Ucitavanje podataka o mrezi gradskog prevoza" << endl;
		cout << "0. Kraj rada" << endl;
		cin >> opcija;
	}
}
int Unos() {
	Skup& skup = Skup::skup();
	int broj_reda = 0;
	string putanja;
	string red;
	try {
		cout << "Molimo Vas, unesite putanju do fajla sa stajalistima:" << endl;
		//cin >> putanja;
		putanja = "stajalista.txt";
		ifstream ulaz1(putanja);

		while (getline(ulaz1, red)) {
			skup.UbaciStajaliste(new Stajaliste(red));
			broj_reda++;
		}
	}
	catch (Error e) {
		cout << e.what() << " U liniji broj: " << broj_reda;
		return 0;
	}
	broj_reda = 0;

	try {
		cout << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza:" << endl;
		//cin >> putanja;
		putanja = "linije.txt";
		ifstream ulaz2(putanja);

		while (getline(ulaz2, red)) {
			skup.UbaciLiniju(new Linija(red));
			broj_reda++;
		}
	}
	catch (Error e) {
		cout << e.what() << " U liniji broj: " << broj_reda;
		return 0;
	}
	return 1;
}
int main() {

	int opcija;
	Pocetak(opcija);	
	if (opcija == 0)
		return 0;

	int provera = Unos();
	if (!provera)
		return 0;
	
	cout << "Mreza gradskog prevoza je uspesno ucitana.";
	while (1) {
		cout << "Molimo Vas, odaberite opciju : " << endl;
		cout << "1. Prikaz informacija o stajalistu" << endl;
		cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
		cout << "3. Prikaz statistickih informacija o liniji gradskog prevoza" << endl;
		cout << "4. Pronalazak najbrze putanje izmedju dva stajalista" << endl;
		cout << "5. Pronalazak putanje izmedju dva stajalista sa najmanjim brojem razlicitih prevoza" << endl;
		cout << "0. Kraj rada" << endl;

		cin >> opcija;
		Skup& skup = Skup::skup();
		if (!opcija)
			return 0;
		else if (opcija == 1) {
			cout << "Molimo Vas, unesite sifru stajalista cije osnovne informacije zelite da prikazete." << endl;
			int sifra;
			cin >> sifra;
			
			Stajaliste* stajaliste = skup.NadjiStajaliste(sifra);
			if (!stajaliste)
				cout << "Nepostojeca sifra stajalista." << endl;
			else {
				string putanja = "stajaliste_" + to_string(sifra) + ".txt";
				stajaliste->InfoStajaliste(putanja);
				cout << "Generisan je fajl " << putanja << " sa osnovnim informacijama o stajalistu " << sifra << endl;
			}		
		}
		else if (opcija == 2) {
			cout << "Molimo Vas, unesite naziv linije cije osnovne informacije zelite da prikazete." << endl;
			string naziv;
			cin >> naziv;
			Linija* linija = skup.NadjiLiniju(naziv);
			if (!linija)
				cout << "Nepostojeci naziv linije." << endl;
			else {
				string putanja = "linija_" + naziv + ".txt";
				linija->InfoLinije(putanja);
				cout << "Generisan je fajl " << putanja << " sa osnovnim informacijama o liniji " << naziv << endl;
			}
		}
		else if (opcija == 3) {
			cout << "Molimo Vas, unesite naziv linije cije statisticke informacije zelite da prikazete." << endl;
			string naziv;
			cin >> naziv;
			Linija* linija = skup.NadjiLiniju(naziv);
			if (!linija)
				cout << "Nepostojeci naziv linije." << endl;
			else {
				string putanja = "statistika_" + naziv + ".txt";
				linija->StatistikaLinije(putanja);
				cout << "Generisan je fajl " << putanja << " sa statistickim informacijama o liniji " << naziv << endl;
			}
		}
		else if (opcija == 4) {
			cout << "Molimo Vas, unesite sifru stajalista sa kog idete, ka kome idete i vreme u koje cete biti na stajalistu(hh:mm)" << endl;

			int od, ka;
			string vreme;
			cin >> od;
			cin >> ka;
			cin >> vreme;

			if (!skup.NadjiStajaliste(od) || !skup.NadjiStajaliste(ka))
				cout << "Pocetna ili krajnja stanica nisu pravilno unete." << endl;
			else if (vreme[2] != ':' || !isdigit(vreme[0]) || !isdigit(vreme[1]) || !isdigit(vreme[3]) || !isdigit(vreme[4]))
				cout << "Pogresno je vreme uneto." << endl;
			else {
				Simulacija sim;

				sim.NajbrzeVreme(od, ka, ((vreme[0] - '0') * 10 + vreme[1] - '0') * 60 + (vreme[3] - '0') * 10 + vreme[4] - '0');
			}
			
		}
		else if (opcija == 5) {
			cout << "Molimo Vas, unesite sifru stajalista sa kog idete i ka kom idete" << endl;

			int od, ka;
			cin >> od;
			cin >> ka;

			if (!skup.NadjiStajaliste(od) || !skup.NadjiStajaliste(ka))
				cout << "Pocetna ili krajnja stanica nisu pravilno unete." << endl;
			else {
				Simulacija sim;
				sim.NajmanjePrevoza(od, ka);
			}

		}
	}
	return 0;
}