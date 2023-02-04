#ifndef Stajaliste_H
#define Stajaliste_H


#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>

#include "Linija.h"
#include "Izuzeci.h"

using namespace std;

class Stajaliste{
public:
	Stajaliste(string);
	int vratiSifru();
	string vratNaziv();


	void vratiStajalista(set<Stajaliste*>&);// vraca vektor sa svim stajalistima na koja se moze stici sa jednim prevozom
	void vratiLinije(set<Linija*>&);// vraca vektor sa svim linijama koje prolaze kroz njega
	Linija* vratiLiniju(Stajaliste*);//vraca liniju sa kojom se moze doci do stajalista ili null ako ne moze
	void dodajSuseda(Stajaliste*, Linija*);

	void Minimum(vector < pair<int, pair<Stajaliste*, Linija*>>>&, int);//vraca minimalno vreme do svih suseda
	void InfoStajaliste(string&);
private:

	string naziv;
	int sifra;
	map<Stajaliste* ,set<Linija*>> susedi;

};

#endif // !Stajaliste_H