#ifndef Simulacija_H
#define Simulacija_H

#include "Skup.h"
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;
class Cvor {
public:
	Cvor(Stajaliste* naziv, Cvor* roditelj = nullptr, Linija* transport = nullptr) :naziv(naziv),roditelj(roditelj),transport(transport){}
	~Cvor(); 
	Stajaliste* vratiNaziv();
	Cvor* vratiRoditelja();
	Linija* vratiTrasnport();
	
	bool dodajTransport(Linija* transport);
	void dodajDete(Cvor* dete);
	void StampaStabla();
private:
	Stajaliste* naziv;
	Linija* transport;
	Cvor* roditelj;
	set<Cvor*> deca;
};
class Simulacija {
public:
	Simulacija();
	void NajbrzeVreme(int pocetak, int kraj,int vreme);
	void NajmanjePrevoza(int pocetak, int kraj);
private:
	void UbacitiUQueue(Cvor*, int);
	void UbacitiUQueueDva(Cvor*, int);
	set<Stajaliste*> obidjeni;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
	//			   vreme, sifra
	vector<pair<pair<Cvor*,Stajaliste*>, Linija*>> baza;
	int poslednja_sifra;
};
#endif
