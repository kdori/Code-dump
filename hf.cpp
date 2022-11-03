/*K�sz�tette: 
Szak�cs Enik�
SQLS3Z
Adatnyilv�ntart� beadand� h�zi feladat
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
	cout << "\t| Tanul�k f�l�vi jegyei (adatnyilv�ntart�) |" << endl << "\t|\t\t\t\t\t   |"<< endl;
	cout << "\t| \t     1.�j adat bevitele\t\t   |" << endl;
	cout << "\t|\t\t 2.Keres�s\t\t   |" << endl;
	cout << "\t|\t      3.Adatm�dos�t�s\t\t   |" << endl;
	cout << "\t|\t\t  4.T�rl�s\t\t   |" << endl;
	cout << "\t|\t\t 5.List�z�s\t\t   |" << endl;
	cout << "\t|\t\t 6.Kil�p�s\t\t   |" << endl << "\t____________________________________________"<< endl;
	cout << endl << "V�lasszon egy opci�t: ";
}


adat* adat::uj(adat* elso){
	system ("cls");
	
	int az, db=0;
	float atl;
	int j;
	int h = 1;
	
	adat* uj = new adat;
	
	if(!uj){
		cout << "Hib�s foglal�s";
		system("pause");
		return NULL;
	}
	
	cout << "\t�j adat bevitele" << endl << endl;
	
	while(h == 1){
	cout << "Azonos�t�: ";
	cin >> uj->id;
	while(cin.fail()){
			cout << endl << "Hiba: az azonos�t�nak eg�sz sz�mnak kell lennie" << endl << endl;
			system("pause");
			system("cls");
			cin.clear();
			cin.ignore(256,'\n');
			cout << "\t�j adat bevitele" << endl << endl;
			cout << "Azonos�t�: ";
			cin >> uj->id;
		}	
	h = 0;
	adat *aktualis = elso, *elozo = NULL;
	while(aktualis && aktualis->id <= uj->id){
		if(aktualis->id == uj->id){
			cout << "Hiba: Ez az azonos�t� m�r l�tezik." << endl << endl;
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
	
	cout << "N�v: ";
	cin.getline(uj->nev, MAX);
	cout <<"Neptun k�d: ";
	cin.getline(uj->neptunkod, MAX);
	while (m){
		cout << "Els� zh eredm�nye(kerek�tett jegy): ";
		cin >> uj->ezh;
		if (uj->ezh < 1 || uj->ezh > 5) {
		cout << "Hiba: Ilyen jegy nem l�tezik!" << endl << endl;
	    }
		else break;
	}
	while (m){
		cout << "M�sodik zh eredm�nye(kerek�tett jegy): ";
		cin >> uj->mzh;
		if (uj->mzh < 1 || uj->mzh > 5) {
		cout << "Hiba: Ilyen jegy nem l�tezik!" << endl << endl;
	    }
		else break;
	}
	while (m){
		cout << "Vizsga eredm�nye(kerek�tett jegy): ";
		cin >> uj->vizsga;
		if (uj->vizsga < 1 || uj->vizsga > 5) {
		cout << "Hiba: Ilyen jegy nem l�tezik!" << endl << endl;
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
	cout << "Adatbevitel megt�rt�nt." << endl << endl;
	system ("pause");
	return elso;
}


void adat::keres(adat* elso){
	system ("cls");
	
	int az;
	adat *aktualis = elso;
	
	cout << "\tKeres�s" << endl << endl;
	
	cout << "Azonos�t�: ";
	cin >> az;
	
	while(aktualis){
		if (aktualis->id == az) {
			cout << endl << "N�v: " << aktualis->nev << endl;
			cout << "Neptun k�d: " << aktualis->neptunkod << endl;
			cout << "Els� zh eredm�nye: " << aktualis->ezh << endl;
			cout << "M�sodik zh eredm�nye: " << aktualis->mzh << endl;
			cout << "Vizsga eredm�nye: " << aktualis->vizsga << endl;
			cout << "Jegy: " << aktualis->jegy << endl << endl;
			break;
		}
		else aktualis = aktualis->kovetkezo;
	}
	if(!aktualis) cout << endl << "Nincs ilyen azonos�t�" << endl << endl;
	
	system("pause");
}


void adat::modosit(adat* elso){
	system ("cls");
	
	int az;
	float atl;
	int j;
	adat *aktualis = elso;
	
	cout << "\tAdat m�dos�t�s" << endl << endl;
	
	cout << "Azonos�t�: ";
	cin >> az;
	
	while(aktualis){
		if (aktualis->id == az) {
			cout << endl << "N�v: " << aktualis->nev << endl;
			cout << "Neptun k�d: " << aktualis->neptunkod << endl;
			cout << "Els� zh eredm�nye: " << aktualis->ezh << endl;
			cout << "M�sodik zh eredm�nye: " << aktualis->mzh << endl;
			cout << "Vizsga eredm�nye: " << aktualis->vizsga << endl;
			cout << "Jegy: " << aktualis->jegy << endl;
			break;
		}
		else aktualis = aktualis->kovetkezo;
	}
	
	if(!aktualis) {
	cout << endl << "Nincs ilyen azonos�t�" << endl << endl;
	system("pause");
	}
	
	else{
	cin.clear();
	cin.ignore(1000,'\n');
	
	cout <<  endl << "�j N�v: ";
	cin.getline(aktualis->nev, MAX);
	cout << "�j Neptun k�d: ";
	cin >> aktualis->neptunkod;
	while (m){
		cout << "�j els� zh eredm�nye(kerek�tett jegy): ";
		cin >> aktualis->ezh;
		if (aktualis->ezh < 1 || aktualis->ezh > 5) {
		cout << "Hiba: Ilyen jegy nem l�tezik!" << endl << endl;
	    }
		else break;
	}
	while (m){
		cout << "�j m�sodik zh eredm�nye(kerek�tett jegy): ";
		cin >> aktualis->mzh;
		if (aktualis->mzh < 1 || aktualis->mzh > 5) {
		cout << "Hiba: Ilyen jegy nem l�tezik!" << endl << endl;
	    }
		else break;
	}
	while (m){
		cout << "�j vizsga eredm�nye(kerek�tett jegy): ";
		cin >> aktualis->vizsga;
		if (aktualis->vizsga < 1 || aktualis->vizsga > 5) {
		cout << "Hiba: Ilyen jegy nem l�tezik!" << endl << endl;
	    }
		else break;
	}
	
	atl = (aktualis->ezh*0.25)+(aktualis->mzh*0.25)+(aktualis->vizsga*0.5);
	j = (int)(atl+0.5);
	
	cout << "�j Jegy: " << j << endl << endl;
	aktualis->jegy = j;
	
	cin.clear();
	cin.ignore(1000,'\n');
	
	cout  << "Az adatm�dos�t�s megt�rt�nt." << endl << endl;
	
	system("pause");
	}
}


adat* adat::torles(adat* elso){
	system ("cls");
	
	int az;
	string valasz;
	adat *aktualis = elso, *elozo = NULL;
	
	cout << "\tT�rl�s" << endl << endl;
	
	cout <<"Azonos�t�: ";
	cin >> az;
	
	while(aktualis){
		if (aktualis->id == az) {
			cout << endl << "N�v: " << aktualis->nev << endl;
			cout << "Neptun k�d: " << aktualis->neptunkod << endl;
			cout << "Els� zh eredm�nye: " << aktualis->ezh << endl;
			cout << "M�sodik zh eredm�nye: " << aktualis->mzh << endl;
			cout << "Vizsga eredm�nye: " << aktualis->vizsga << endl;
			cout << "Jegy: " << aktualis->jegy << endl;
			break;
		}
		else{
		elozo = aktualis;
		aktualis = aktualis->kovetkezo;
		}
	}
	if(!aktualis) {
	cout << endl << "Nincs ilyen azonos�t�" << endl << endl; 
	system("pause");
	return elso;
	}
	
	while (valasz != "0"){
		cout << endl << "Biztosan t�rli az adatokat? igen / nem" << endl;
		cin >> valasz;
	
		if ( valasz=="nem" ) {
			system("pause");
			return elso;
		}
		else if (valasz == "igen"){
			if(elozo) elozo->kovetkezo = aktualis->kovetkezo;
			else elso = aktualis->kovetkezo;
			free(aktualis);
			cout  << endl << "Az adatok t�rl�se megt�rt�nt." << endl << endl;
			system("pause"); 
			return elso;
		}
		else cout << endl << "Nem egy�rtelm� v�lasz" << endl;
	}
}


void adat::lista(adat* elso){
	system ("cls");
	
	adat* aktualis = elso;
	
	printf("%10s|%25s|%11s|%15s|%15s|%17s|%6s|\n", "Azonos�t�", "N�v", "Neptun k�d", "1.zh eredm�nye", "2.zh eredm�nye", "Vizsga eredm�nye", "Jegy");
	
	while(aktualis){
		printf("%10d|%25s|%11s|%15d|%15d|%17d|%6d|\n", aktualis->id, aktualis->nev, aktualis->neptunkod, aktualis->ezh, aktualis->mzh, aktualis->vizsga, aktualis->jegy);
		aktualis = aktualis->kovetkezo;
	}
	system("pause");
}










