#include "Stajaliste.h"
#include "Skup.h"

Stajaliste::Stajaliste(string red){
	int pom = red.find(' ');
	if (pom == string::npos)
		throw Error("Pogresan unos");
	naziv = red.substr(pom + 1);
	for(auto c: red.substr(0,pom))
		if(!isdigit(c)) 
			throw Error("Pogresan unos sifre.");

	sifra = stoi(red.substr(0, pom));
	Skup& skup = Skup::skup();
	if (skup.NadjiStajaliste(sifra))
		throw Error("Postoje dve iste sifre.");
}

int Stajaliste::vratiSifru(){
	return sifra;
}

string Stajaliste::vratNaziv()
{
	return naziv;
}

void Stajaliste::vratiStajalista(set<Stajaliste*>& stajalista){
	set<Linija*> linije;
	vratiLinije(linije);
	for (set<Linija*>::iterator it = linije.begin(); it != linije.end(); it++) {
		(*it)->vratiStajalista(nullptr, nullptr, stajalista);
	}
}

void Stajaliste::vratiLinije(set<Linija*>& linije) {
	for (auto sused : susedi) {
		for (auto linija : sused.second)
			linije.insert(linija);
	}
}

Linija* Stajaliste::vratiLiniju(Stajaliste* stajaliste){
	set<Linija*> linije;
	vratiLinije(linije);
	for (auto i : linije) {
		if (i->ImaStajaliste(stajaliste))
			return i;
	}
}

void Stajaliste::dodajSuseda(Stajaliste* stajaliste, Linija* linija){
	susedi[stajaliste].insert(linija);
}

void Stajaliste::Minimum(vector < pair<int, pair<Stajaliste*, Linija*>>>& m, int vreme) {
	for (auto sused : susedi) {
		m.push_back({ 1500,{sused.first,*sused.second.begin()} });
		for (auto i : sused.second) {
			int potrebno_vreme = i->PotrebnoVreme(vreme, this, sused.first);
			if (m.back().first > potrebno_vreme) {
				m.back().first = potrebno_vreme;
				m.back().second.second = i;
			}
		}
	}
}

void Stajaliste::InfoStajaliste(string& putanja){
	ofstream izlaz(putanja);
	izlaz << sifra << " " << naziv << " [";
	set<Linija*> linije;
	vratiLinije(linije);
	izlaz << (*linije.begin())->vratiNaziv();
	linije.erase(linije.begin());
	for (auto linija : linije) {
		izlaz << " " << linija->vratiNaziv();
	}
	izlaz << "]";
}


