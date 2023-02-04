#ifndef Linija_H
#define Linija_H

#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Stajaliste;

class Linija{
public:
	Linija(string red);
	string vratiNaziv();
	void vratiStajalista(Stajaliste*, Stajaliste*, set<Stajaliste*>&);
	void vratiStajalista(Stajaliste*, Stajaliste*, vector<Stajaliste*>&);
	bool ImaStajaliste(Stajaliste*);
	int PotrebnoVreme(int vreme, Stajaliste* od, Stajaliste* ka); 
	// racuna kada ce se biti na drugom stajalistu ako se na prvom(mora biti sused drugog) nalazi u dato vreme 


	void InfoLinije(string& putanja);
	void StatistikaLinije(string& putanja);
private:
	string naziv;
	int pocetni, krajnji, razmak;
	vector<Stajaliste*> stajalista;
};

#endif //!Linija_H