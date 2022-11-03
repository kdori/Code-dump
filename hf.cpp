/*Készítette: 
Szakács Enikõ
SQLS3Z
Adatnyilvántartó beadandó házi feladat
*/


#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define MAX 50

using namespace std;

void fomenu();
int m = 1;

class adat{
	int id;
	char nev[MAX];
	char neptunkod[MAX];
	int ezh;
	int mzh;
	int vizsga;
	int jegy;
	adat *kovetkezo;
	public:
	static adat* uj(adat*);
	static void keres(adat*);
	static void modosit(adat*);
	static adat* torles(adat*);
	static void lista(adat*);
};


int main (){
	setlocale(LC_ALL,"");
	int szam = 0;
	adat *elso = NULL;
	while(szam!=6)	{
	system ("cls");
	fomenu();
	cin >> szam;
	switch (szam){
			case 1: elso = adat::uj(elso); break;
			case 2: adat::keres(elso); break;
			case 3: adat::modosit(elso); break;
			case 4: elso = adat::torles(elso); break;
			case 5: adat::lista(elso); break;
			default: break;
		}
	}
	system("cls");
}


void fomenu(){	
	cout << "\t| Tanulók félévi jegyei (adatnyilvántartó) |" << endl << "\t|\t\t\t\t\t   |"<< endl;
	cout << "\t| \t     1.Új adat bevitele\t\t   |" << endl;
	cout << "\t|\t\t 2.Keresés\t\t   |" << endl;
	cout << "\t|\t      3.Adatmódosítás\t\t   |" << endl;
	cout << "\t|\t\t  4.Törlés\t\t   |" << endl;
	cout << "\t|\t\t 5.Listázás\t\t   |" << endl;
	cout << "\t|\t\t 6.Kilépés\t\t   |" << endl << "\t____________________________________________"<< endl;
	cout << endl << "Válasszon egy opciót: ";
}


adat* adat::uj(adat* elso){
	system ("cls");
	
	int az, db=0;
	float atl;
	int j;
	int h = 1;
	
	adat* uj = new adat;
	
	if(!uj){
		cout << "Hibás foglalás";
		system("pause");
		return NULL;
	}
	
	cout << "\tÚj adat bevitele" << endl << endl;
	
	while(h == 1){
	cout << "Azonosító: ";
	cin >> uj->id;
	while(cin.fail()){
			cout << endl << "Hiba: az azonosítónak egész számnak kell lennie" << endl << endl;
			system("pause");
			system("cls");
			cin.clear();
			cin.ignore(256,'\n');
			cout << "\tÚj adat bevitele" << endl << endl;
			cout << "Azonosító: ";
			cin >> uj->id;
		}	
	h = 0;
	adat *aktualis = elso, *elozo = NULL;
	while(aktualis && aktualis->id <= uj->id){
		if(aktualis->id == uj->id){
			cout << "Hiba: Ez az azonosító már létezik." << endl << endl;
			h = 1;
			break;
		}
		else{
		elozo = aktualis;
		aktualis = aktualis->kovetkezo;	
		}
	}
	if (h == 0){
		if(!elozo) elso = uj; 
		else elozo->kovetkezo = uj; 
		uj->kovetkezo = aktualis;
		}
	}
	
	cin.clear();
	cin.ignore(1000,'\n');
	
	cout << "Név: ";
	cin.getline(uj->nev, MAX);
	cout <<"Neptun kód: ";
	cin.getline(uj->neptunkod, MAX);
	while (m){
		cout << "Elsõ zh eredménye(kerekített jegy): ";
		cin >> uj->ezh;
		if (uj->ezh < 1 || uj->ezh > 5) {
		cout << "Hiba: Ilyen jegy nem létezik!" << endl << endl;
	    }
		else break;
	}
	while (m){
		cout << "Második zh eredménye(kerekített jegy): ";
		cin >> uj->mzh;
		if (uj->mzh < 1 || uj->mzh > 5) {
		cout << "Hiba: Ilyen jegy nem létezik!" << endl << endl;
	    }
		else break;
	}
	while (m){
		cout << "Vizsga eredménye(kerekített jegy): ";
		cin >> uj->vizsga;
		if (uj->vizsga < 1 || uj->vizsga > 5) {
		cout << "Hiba: Ilyen jegy nem létezik!" << endl << endl;
	    }
		else break;
	}
	
	atl = (uj->ezh*0.25)+(uj->mzh*0.25)+(uj->vizsga*0.5);
	j = (int)(atl+0.5);
	if (uj->ezh == 1 || uj->mzh == 1 || uj->vizsga == 1) j = 1;
	
	cout << "Jegy: " << j << endl << endl;
	uj->jegy = j;
	
	cin.clear();
	cin.ignore(1000,'\n');
	cout << "Adatbevitel megtörtént." << endl << endl;
	system ("pause");
	return elso;
}


void adat::keres(adat* elso){
	system ("cls");
	
	int az;
	adat *aktualis = elso;
	
	cout << "\tKeresés" << endl << endl;
	
	cout << "Azonosító: ";
	cin >> az;
	
	while(aktualis){
		if (aktualis->id == az) {
			cout << endl << "Név: " << aktualis->nev << endl;
			cout << "Neptun kód: " << aktualis->neptunkod << endl;
			cout << "Elsõ zh eredménye: " << aktualis->ezh << endl;
			cout << "Második zh eredménye: " << aktualis->mzh << endl;
			cout << "Vizsga eredménye: " << aktualis->vizsga << endl;
			cout << "Jegy: " << aktualis->jegy << endl << endl;
			break;
		}
		else aktualis = aktualis->kovetkezo;
	}
	if(!aktualis) cout << endl << "Nincs ilyen azonosító" << endl << endl;
	
	system("pause");
}


void adat::modosit(adat* elso){
	system ("cls");
	
	int az;
	float atl;
	int j;
	adat *aktualis = elso;
	
	cout << "\tAdat módosítás" << endl << endl;
	
	cout << "Azonosító: ";
	cin >> az;
	
	while(aktualis){
		if (aktualis->id == az) {
			cout << endl << "Név: " << aktualis->nev << endl;
			cout << "Neptun kód: " << aktualis->neptunkod << endl;
			cout << "Elsõ zh eredménye: " << aktualis->ezh << endl;
			cout << "Második zh eredménye: " << aktualis->mzh << endl;
			cout << "Vizsga eredménye: " << aktualis->vizsga << endl;
			cout << "Jegy: " << aktualis->jegy << endl;
			break;
		}
		else aktualis = aktualis->kovetkezo;
	}
	
	if(!aktualis) {
	cout << endl << "Nincs ilyen azonosító" << endl << endl;
	system("pause");
	}
	
	else{
	cin.clear();
	cin.ignore(1000,'\n');
	
	cout <<  endl << "Új Név: ";
	cin.getline(aktualis->nev, MAX);
	cout << "Új Neptun kód: ";
	cin >> aktualis->neptunkod;
	while (m){
		cout << "Új elsõ zh eredménye(kerekített jegy): ";
		cin >> aktualis->ezh;
		if (aktualis->ezh < 1 || aktualis->ezh > 5) {
		cout << "Hiba: Ilyen jegy nem létezik!" << endl << endl;
	    }
		else break;
	}
	while (m){
		cout << "Új második zh eredménye(kerekített jegy): ";
		cin >> aktualis->mzh;
		if (aktualis->mzh < 1 || aktualis->mzh > 5) {
		cout << "Hiba: Ilyen jegy nem létezik!" << endl << endl;
	    }
		else break;
	}
	while (m){
		cout << "Új vizsga eredménye(kerekített jegy): ";
		cin >> aktualis->vizsga;
		if (aktualis->vizsga < 1 || aktualis->vizsga > 5) {
		cout << "Hiba: Ilyen jegy nem létezik!" << endl << endl;
	    }
		else break;
	}
	
	atl = (aktualis->ezh*0.25)+(aktualis->mzh*0.25)+(aktualis->vizsga*0.5);
	j = (int)(atl+0.5);
	
	cout << "Új Jegy: " << j << endl << endl;
	aktualis->jegy = j;
	
	cin.clear();
	cin.ignore(1000,'\n');
	
	cout  << "Az adatmódosítás megtörtént." << endl << endl;
	
	system("pause");
	}
}


adat* adat::torles(adat* elso){
	system ("cls");
	
	int az;
	string valasz;
	adat *aktualis = elso, *elozo = NULL;
	
	cout << "\tTörlés" << endl << endl;
	
	cout <<"Azonosító: ";
	cin >> az;
	
	while(aktualis){
		if (aktualis->id == az) {
			cout << endl << "Név: " << aktualis->nev << endl;
			cout << "Neptun kód: " << aktualis->neptunkod << endl;
			cout << "Elsõ zh eredménye: " << aktualis->ezh << endl;
			cout << "Második zh eredménye: " << aktualis->mzh << endl;
			cout << "Vizsga eredménye: " << aktualis->vizsga << endl;
			cout << "Jegy: " << aktualis->jegy << endl;
			break;
		}
		else{
		elozo = aktualis;
		aktualis = aktualis->kovetkezo;
		}
	}
	if(!aktualis) {
	cout << endl << "Nincs ilyen azonosító" << endl << endl; 
	system("pause");
	return elso;
	}
	
	while (valasz != "0"){
		cout << endl << "Biztosan törli az adatokat? igen / nem" << endl;
		cin >> valasz;
	
		if ( valasz=="nem" ) {
			system("pause");
			return elso;
		}
		else if (valasz == "igen"){
			if(elozo) elozo->kovetkezo = aktualis->kovetkezo;
			else elso = aktualis->kovetkezo;
			free(aktualis);
			cout  << endl << "Az adatok törlése megtörtént." << endl << endl;
			system("pause"); 
			return elso;
		}
		else cout << endl << "Nem egyértelmû válasz" << endl;
	}
}


void adat::lista(adat* elso){
	system ("cls");
	
	adat* aktualis = elso;
	
	printf("%10s|%25s|%11s|%15s|%15s|%17s|%6s|\n", "Azonosító", "Név", "Neptun kód", "1.zh eredménye", "2.zh eredménye", "Vizsga eredménye", "Jegy");
	
	while(aktualis){
		printf("%10d|%25s|%11s|%15d|%15d|%17d|%6d|\n", aktualis->id, aktualis->nev, aktualis->neptunkod, aktualis->ezh, aktualis->mzh, aktualis->vizsga, aktualis->jegy);
		aktualis = aktualis->kovetkezo;
	}
	system("pause");
}










