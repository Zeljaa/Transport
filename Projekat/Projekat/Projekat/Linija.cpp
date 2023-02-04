#include "Linija.h"
#include "Skup.h"


Linija::Linija(string red){
	int pom = red.find(' ');
	if (red[pom + 1] != '[' || red[pom + 16] != ']')
		throw Error("Pogresan unos reda voznji.");
	naziv = red.substr(0, pom);
	if(!(isdigit(red[pom+2]) && isdigit(red[pom + 3]) && isdigit(red[pom + 5]) && isdigit(red[pom + 6])))
		throw Error("Vreme prvog polaska nije dobro definisano.");
	if (!(isdigit(red[pom + 8]) && isdigit(red[pom + 9]) && isdigit(red[pom + 11]) && isdigit(red[pom + 12])))
		throw Error("Vreme poslednjeg polaska nije dobro definisano.");
	if (!(isdigit(red[pom + 14]) && isdigit(red[pom + 15])))
		throw Error("Razmak izmedju polazaka nije dobro definisan.");

	pocetni = stoi(red.substr(pom + 2, 2)) * 60 + stoi(red.substr(pom + 5, 2));
	krajnji = stoi(red.substr(pom + 8, 2)) * 60 + stoi(red.substr(pom + 11, 2));
	razmak = stoi(red.substr(pom + 14, red.find(']') - pom + 14));

	Skup& skup = Skup::skup();
	if(red[red.find(']') + 1] != ' ')
		throw exception();
	pom = 0;
	for (int i = red.find(']') + 2; i < red.size(); i++) {
		if (red[i] == ' ') {
			Stajaliste* trenutno = skup.NadjiStajaliste(pom);
			if (!trenutno)
				throw Error("Nepostojeca sifra stajalista uneta.");
			if (stajalista.size()) {
				stajalista.back()->dodajSuseda(trenutno, this);
				(trenutno)->dodajSuseda(stajalista.back(),this);
			}
			stajalista.push_back(trenutno);
			pom = 0;
			continue;
		}
		else if (!isdigit(red[i]))
			throw Error("Pogresan unos sifara stanica.");
		pom = pom*10 + (red[i] - '0');
	}
	if (pom) {
		Stajaliste* trenutno = skup.NadjiStajaliste(pom);
		if (!trenutno)
			throw Error("Nepostojeca sifra stajalista uneta.");
		if (stajalista.size()) {
			stajalista.back()->dodajSuseda(trenutno, this);
			(trenutno)->dodajSuseda(stajalista.back(), this);
		}
		stajalista.push_back(trenutno);
	}
	
}

string Linija::vratiNaziv(){
	return naziv;
}

void Linija::vratiStajalista(Stajaliste* prvo, Stajaliste* drugo, set<Stajaliste*>& res){
	for (int i = 0; i < stajalista.size(); i++) {
			res.insert(stajalista[i]);
	}
}

void Linija::vratiStajalista(Stajaliste* prvo, Stajaliste* drugo, vector<Stajaliste*>& res) {
	bool izmedju = false;
	bool obrni = false;
	for (int i = 0; i < stajalista.size(); i++) {
		if (stajalista[i] == prvo || stajalista[i] == drugo) {
			res.push_back(stajalista[i]);
			if (!izmedju) {
				izmedju = true;
				if (stajalista[i] == drugo)
					obrni = true;
				continue;
			}
			izmedju = false;
		}
		else if (izmedju)
			res.push_back(stajalista[i]);
	}

	if(obrni)
		reverse(res.begin(), res.end());
}

bool Linija::ImaStajaliste(Stajaliste* trazeno){
	for (auto i : stajalista) {
		if (i == trazeno)
			return true;
	}
	return false;
}

/*void Linija::LinijeZaPresedanje() {
	for (int i = 0; i < stajalista.size(); i++)
		for (auto j : stajalista[i]->linije)
			if(j->naziv != this->naziv)
				linije_presedanje.insert(j);

	for (auto i : linije_presedanje)
		cout << i->naziv << " ";
	//stajalista[0]->vratiLinije()[0]->razmak = 5;
}*/

int Linija::PotrebnoVreme(int vreme, Stajaliste* od, Stajaliste* ka){
	int i;
	for (i = 0; i < stajalista.size(); i++)
		if (od == stajalista[i])
			break;
	if (((vreme > krajnji + i * 3) && stajalista[i + 1] == ka) || ((vreme > krajnji + (stajalista.size() - 1 - i) * 3) && stajalista[i - 1] == ka))
		return 1500;

	if ((vreme < pocetni + i * 3) && stajalista[i + 1] == ka)
		return pocetni + i * 3 + 3;
	if ((vreme < pocetni + (stajalista.size() - 1 - i) * 3) && i>0 && stajalista[i - 1] == ka)
		return pocetni + (stajalista.size() - 1 - i) * 3 + 3;
	if (i != stajalista.size() - 1 && stajalista[i + 1] == ka)
		return pocetni + ceil((double)(vreme-i*3-pocetni)/razmak)*razmak + 3*i + 3;

	return pocetni + ceil((double)(vreme - (stajalista.size()-i-1) * 3 - pocetni) / razmak) * razmak + 3 * (stajalista.size() - i - 1) + 3;
}

void Linija::InfoLinije(string& putanja){
	ofstream izlaz(putanja);
	izlaz << naziv << " " << stajalista[0]->vratNaziv() << "->" << stajalista.back()->vratNaziv();
}

void Linija::StatistikaLinije(string& putanja){
	ofstream izlaz(putanja);
	set<Linija*> linije;
	for (auto stajaliste : stajalista) {
		stajaliste->vratiLinije(linije);
	}

	izlaz << naziv << endl;
	for (auto linija : linije) {
		if (linija == this)
			continue;
		izlaz << linija->naziv << " ";
	}
	izlaz << endl << (krajnji - pocetni) / razmak + 1;
}
