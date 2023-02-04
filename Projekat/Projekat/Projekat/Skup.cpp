#include "Skup.h"

Skup::~Skup(){
	for (auto i : linije)
		delete i.second;
	linije.clear();
	for (auto i : stajalista)
		delete i.second;	
	stajalista.clear();
}

void Skup::UbaciStajaliste(Stajaliste* stajaliste){
	stajalista.insert({ stajaliste->vratiSifru(),stajaliste });
}

void Skup::UbaciLiniju(Linija* linija){
	linije.insert({ linija->vratiNaziv(),linija });
}

Stajaliste* Skup::NadjiStajaliste(int sifra){
	if (stajalista.find(sifra) == stajalista.end())
		return nullptr;
	return stajalista.find(sifra)->second;
}

Linija* Skup::NadjiLiniju(string naziv){
	if(linije.find(naziv) == linije.end())
		return nullptr;
	return linije.find(naziv)->second;
}
