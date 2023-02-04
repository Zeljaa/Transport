#include "Simulacija.h"

Cvor::~Cvor() {
	for (auto i : deca)
		delete i;
}


Stajaliste* Cvor::vratiNaziv() {
	return naziv;
}
Cvor* Cvor::vratiRoditelja() {
	return roditelj;
}
Linija* Cvor::vratiTrasnport() {
	return transport;
}
bool Cvor::dodajTransport(Linija* transport) {
	if (!this->transport) {
		this->transport = transport;
		return true;
	}
	return false;
}

void Cvor::dodajDete(Cvor* dete) {
	deca.insert(dete);
}
void Cvor::StampaStabla() {
	cout << naziv->vratiSifru() << ": ";
	for (auto i : deca) {
		cout << i->naziv->vratiSifru() << " ";
	}
	for (auto i : deca) {
		cout << endl;
		i->StampaStabla();
	}
}
Simulacija::Simulacija(){
	poslednja_sifra = 0;
}

void Simulacija::NajbrzeVreme(int pocetak, int kraj, int vreme){
	if (pocetak == kraj) {
		cout << "Stigli ste :-)";
	}

	Skup& skup = Skup::skup();
	Cvor* koren = new Cvor(skup.NadjiStajaliste(pocetak));
	UbacitiUQueue(koren, vreme);
	obidjeni.insert(koren->vratiNaziv());
	Cvor* cvor = nullptr;

	while (!pq.empty()) {
		pair<int, int> trenutni = pq.top();
		
		if (obidjeni.find(baza[trenutni.second].first.second) == obidjeni.end()) {
			cvor = new Cvor(baza[trenutni.second].first.second, baza[trenutni.second].first.first,baza[trenutni.second].second);

			baza[trenutni.second].first.first->dodajDete(cvor);
			if (cvor->vratiNaziv() == skup.NadjiStajaliste(kraj))
				break;
			UbacitiUQueue(cvor, trenutni.first);
			obidjeni.insert(cvor->vratiNaziv());
		}	
		pq.pop();
	}
	//koren->StampaStabla();
	if (cvor->vratiNaziv()->vratiSifru() != kraj || pq.top().first >= 1500) {
		cout << "Nije moguce doci sa pocetnog stajaliste na krajnje.";
		delete koren;
		obidjeni.clear();
		baza.clear();
		return;
	}
	
	vector<Cvor*> res;
	while (cvor) {
		res.push_back(cvor);
		cvor = cvor->vratiRoditelja();
	}
	koren->dodajTransport(res[res.size() - 2]->vratiTrasnport());
	ofstream izlaz("putanja_"+to_string(pocetak) + "_" + to_string(kraj) + ".txt");
	izlaz << "->" << res[res.size() - 1]->vratiTrasnport()->vratiNaziv() << endl;
	izlaz << res[res.size() - 1]->vratiNaziv()->vratiSifru();
	for (int i = res.size() - 2; i >= 0; i--) {		
		if (res[i]->vratiTrasnport() != res[i + 1]->vratiTrasnport()) {
			izlaz << endl << "->" << res[i]->vratiTrasnport()->vratiNaziv() << endl;
			izlaz << res[i + 1]->vratiNaziv()->vratiSifru() << " ";
			izlaz << res[i]->vratiNaziv()->vratiSifru();
		}
		else {
			izlaz << " " << res[i]->vratiNaziv()->vratiSifru();
		}
	}

	cout << "Generisan je fajl: " << "putanja_" + to_string(pocetak) + "_" + to_string(kraj) + ".txt" << " sa putanjom od stajalista " << pocetak << " ka stajalistu " << kraj << endl;
	//koren->StampaStabla();
	delete koren;
	obidjeni.clear();
	baza.clear();
}

void Simulacija::NajmanjePrevoza(int pocetak, int kraj){
	if (pocetak == kraj) {
		cout << "Stigli ste :-)";
	}
	Skup& skup = Skup::skup();
	Cvor* koren = new Cvor(skup.NadjiStajaliste(pocetak));
	obidjeni.insert(koren->vratiNaziv());
	UbacitiUQueueDva(koren, 0);
	
	Cvor* cvor = nullptr;
	while (!pq.empty()) {
		pair<int, int> trenutni = pq.top();

		if (obidjeni.find(baza[trenutni.second].first.second) == obidjeni.end()) {
			cvor = new Cvor(baza[trenutni.second].first.second, baza[trenutni.second].first.first, baza[trenutni.second].second);
			baza[trenutni.second].first.first->dodajDete(cvor);
			if (cvor->vratiNaziv() == skup.NadjiStajaliste(kraj))
				break;
			UbacitiUQueueDva(cvor, trenutni.first);
			obidjeni.insert(cvor->vratiNaziv());
		}
		pq.pop();
	}

	if (cvor->vratiNaziv()->vratiSifru() != kraj || pq.top().first >= 1500) {
		cout << "Nije moguce doci sa pocetnog stajaliste na krajnje.";
		delete koren;
		obidjeni.clear();
		baza.clear();
		return;
	}

	vector<Cvor*> res;
	while (cvor) {
		res.push_back(cvor);
		cvor = cvor->vratiRoditelja();
	}
	//koren->StampaStabla();
	ofstream izlaz("putanja_" + to_string(pocetak) + "_" + to_string(kraj) + ".txt");

	for (int i = res.size() - 1; i > 0; i--) {
		vector<Stajaliste*> pomocni;
		res[i]->vratiNaziv()->vratiLiniju(res[i - 1]->vratiNaziv())->vratiStajalista(res[i]->vratiNaziv(), res[i-1]->vratiNaziv(), pomocni);
		izlaz << "->" << res[i]->vratiNaziv()->vratiLiniju(res[i - 1]->vratiNaziv())->vratiNaziv() << endl;
		for (auto i : pomocni) {
			izlaz << i->vratiSifru() << " ";
		}
		izlaz << endl;
	}

	cout << "Generisan je fajl: " << "putanja_" + to_string(pocetak) + "_" + to_string(kraj) + ".txt" << " sa putanjom od stajalista " << pocetak << " ka stajalistu " << kraj << endl;
	//koren->StampaStabla();
	delete koren;
	poslednja_sifra = 0;
	obidjeni.clear();
	baza.clear();
}
     
void Simulacija::UbacitiUQueue(Cvor* roditelj, int vreme){
	vector < pair<int, pair<Stajaliste*, Linija*>>> m;
	roditelj->vratiNaziv()->Minimum(m, vreme);
	for (auto i : m) {
		if (obidjeni.find(i.second.first) != obidjeni.end())
			continue;
		pq.push({ i.first, poslednja_sifra++ });
		baza.push_back({ {roditelj,i.second.first},i.second.second });		
	}
}


void Simulacija::UbacitiUQueueDva(Cvor* roditelj, int vrednost) {
	set<Stajaliste*> stajalista;
	roditelj->vratiNaziv()->vratiStajalista(stajalista);
	for (auto i : stajalista) {
		if (obidjeni.find(i) != obidjeni.end())
			continue;
		pq.push({ vrednost + 1, poslednja_sifra++ });
		baza.push_back({ {roditelj,i}, nullptr });
	}

}


