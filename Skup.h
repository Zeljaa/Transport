#ifndef Skup_H
#define Skup_H

#include "Stajaliste.h"

#include <set>
#include <map>
class Skup {
public:
	~Skup();
	static Skup& skup() {
		static Skup s;
		return s;
	}
	void UbaciStajaliste(Stajaliste*);
	void UbaciLiniju(Linija*);

	Stajaliste* NadjiStajaliste(int sifra);
	Linija* NadjiLiniju(string naziv);
private:
	map<int, Stajaliste*> stajalista;
	map<string, Linija*> linije;


	Skup() { }
	Skup& operator=(const Skup&) = delete;
	Skup(const Skup&) = delete;
};

#endif // !Skup_H