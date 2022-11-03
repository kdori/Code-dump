#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define SIZE 50
using namespace std;
// Adatanyilv�ntart�: �nekesek dalai �s megjelen�si �v�k
// K�sz�tette: Schlepp Kriszti�n


class adat{
	int id;
	char enekes_neve[SIZE];
	char dal_cime[SIZE];
	int megjelenes_eve;
	adat *kovetkezo;
	public:
	static adat* adat_bevitel(adat*);
	static void adat_listazas(adat*);
	static void adat_kereses(adat*);
	static void adat_modositas(adat*);
	static adat* adat_torles(adat*);
};




int main(){
	setlocale(LC_ALL, "");
	int funkcio = 1;
	adat *elso = NULL;
	while(funkcio != 0){
		system("cls");
		cout << "\t\tAdatnyilv�ntart�" << endl;
		cout << "\t�nekesek dalai �s megjelen�si �v�k" << endl;
		cout << "------------------------------------------------------" << endl;
		cout << "\t\t1: �j adat bevitele" << endl;
		cout << "\t\t2: Keres�s" << endl;
		cout << "\t\t3: Adatm�dos�t�s" << endl;
		cout << "\t\t4: T�rl�s" << endl;
		cout << "\t\t5: List�z�s" << endl;
		cout << "\t\t0: Bez�r�s" << endl;
		cout << "------------------------------------------------------" << endl;
		cout << "V�lasszon funkci�t: ";
		cin >> funkcio;
		switch(funkcio){
			case 1:
				elso = adat::adat_bevitel(elso);
				break;
			case 2:
				adat::adat_kereses(elso);
				break;
			case 3:
				adat::adat_modositas(elso);
				break;
			case 4:
				elso = adat::adat_torles(elso);
				break;
			case 5:
				adat::adat_listazas(elso);
				break;
			default:
				break;
		}
	}
}

adat* adat::adat_bevitel(adat* elso){
	int id, megjelenes_eve;
	system("cls");
	adat* uj = new adat;
	if(uj == NULL){
		printf("Hib�s foglal�s");
		system("pause");
		return NULL;
	}
	int azonos = 1;
	while(azonos != 0){
		cout << "K�rem az adat azonos�t�j�t: ";
		cin >> uj->id;
		while(cin.fail()){
			system("cls");
			cout << "Hiba: az azonos�t�nak eg�sz sz�mnak kell lennie" << endl << endl;
			system("pause");
			system("cls");
			cin.clear();
			cin.ignore(256,'\n');
			cout << "K�rem az adat azonos�t�j�t: ";
			cin >> uj->id;
		}	
		azonos = 0;
		adat *aktualis = elso, *elozo = NULL;
		while(aktualis != NULL && aktualis->id <= uj->id){
			if(aktualis->id == uj->id){
				azonos = 1;
				cout << "Hiba: a megadott azonos�t� m�r szerepel a nyilv�ntart�sban" << endl << endl;
				system("pause");
				system("cls");
				break;
			}else{
				elozo = aktualis;
				aktualis = aktualis->kovetkezo;	
			}
		}
		if(azonos != 1){
			if(elozo == NULL){
			elso = uj;
			}else{
				elozo->kovetkezo = uj;
			}
			uj->kovetkezo = aktualis;
		}
	}
	
	cin.clear();
	cin.ignore(256,'\n');
	cout << "K�rem az �nekes nev�t: ";
	cin.getline(uj->enekes_neve, SIZE);
	cout << "K�rem a dal c�m�t: ";
	cin.getline(uj->dal_cime, SIZE);
	cout << "K�rem a megjelen�s �v�t: ";
	cin >> uj->megjelenes_eve;
	while(cin.fail() || uj->megjelenes_eve > 2020){
		system("cls");
		cout << "Hiba: a megjelen�s �v�nek eg�sz sz�mnak kell lennie, �s legfeljebb 2020 lehet" << endl << endl;
		system("pause");
		system("cls");
		cin.clear();
		cin.ignore(256,'\n');
		cout << "K�rem a megjelen�s �v�t: ";
		cin >> uj->megjelenes_eve;
	}	

	
	cout << endl << "Sikeres adatfelvitel" << endl << endl;
	cin.clear();
	cin.ignore(256,'\n');
	system("pause");
	return elso;
}

void adat::adat_listazas(adat* elso){
	system("cls");
	printf("|%10s|%30s|%30s|%15s|\n", "Azonos�t�", "�nekes neve", "Dal c�me", "Megjelen�s �ve");
	cout << "-----------------------------------------------------------------------------------------" << endl;
	adat* aktualis = elso;
	while(aktualis != NULL){
		printf("|%10d|%30s|%30s|%15d|\n", aktualis->id, aktualis->enekes_neve, aktualis->dal_cime, aktualis->megjelenes_eve);
		aktualis = aktualis->kovetkezo;
	}
	system("pause");
}

void adat::adat_kereses(adat* elso){
	int id;
	system("cls");
	cout << "K�rem a keresett adat azonos�t�j�t: ";
	cin >> id;
	adat *aktualis = elso;
	int megtalalt = 0;
	while(aktualis != NULL){
		if(aktualis->id == id){
			megtalalt = 1;
			break;
		}
		aktualis = aktualis->kovetkezo;
	}
	if(megtalalt){
		system("cls");
		printf("|%10s|%30s|%30s|%15s|\n", "Azonos�t�", "�nekes neve", "Dal c�me", "Megjelen�s �ve");
		cout << "-----------------------------------------------------------------------------------------" << endl;
		printf("|%10d|%30s|%30s|%15d|\n\n", aktualis->id, aktualis->enekes_neve, aktualis->dal_cime, aktualis->megjelenes_eve);
	}else{
		system("cls");
		cout << "Hiba: a keresett adat nem tal�lhat�" << endl << endl;
	}
	system("pause");
}

void adat::adat_modositas(adat* elso){
	int id;
	system("cls");
	cout << "K�rem a m�dos�tand� adat azonos�t�j�t: ";
	cin >> id;
	adat *aktualis = elso;
	int megtalalt = 0;
	while(aktualis != NULL){
		if(aktualis->id == id){
			megtalalt = 1;
			break;
		}
		aktualis = aktualis->kovetkezo;
	}
	if(megtalalt){
		system("cls");
		printf("|%10s|%30s|%30s|%15s|\n", "Azonos�t�", "�nekes neve", "Dal c�me", "Megjelen�s �ve");
		cout << "-----------------------------------------------------------------------------------------" << endl;
		printf("|%10d|%30s|%30s|%15d|\n\n", aktualis->id, aktualis->enekes_neve, aktualis->dal_cime, aktualis->megjelenes_eve);
		cin.clear();
		cin.ignore(256,'\n');
		cout << "K�rem az �nekes nev�t: ";
		cin.getline(aktualis->enekes_neve, SIZE);
		cout << "K�rem a dal c�m�t: ";
		cin.getline(aktualis->dal_cime, SIZE);
		cout << "K�rem a megjelen�s �v�t: ";
		cin >> aktualis->megjelenes_eve;
		while(cin.fail() || aktualis->megjelenes_eve > 2020){
			system("cls");
			cout << "Hiba: a megjelen�s �v�nek eg�sz sz�mnak kell lennie, �s legfeljebb 2020 lehet" << endl << endl;
			system("pause");
			system("cls");
			cin.clear();
			cin.ignore(256,'\n');
			cout << "K�rem a megjelen�s �v�t: ";
			cin >> aktualis->megjelenes_eve;
		}
		
		cout << endl << "Sikeres adatm�dos�t�s" << endl << endl;
		cin.clear();
		cin.ignore(256,'\n');
		system("pause");
	}else{
		system("cls");
		cout << "Hiba: a keresett adat nem tal�lhat�" << endl << endl;
		system("pause");
	}
	
	
	
}

adat* adat::adat_torles(adat* elso){
	int id;
	system("cls");
	cout << "K�rem a t�rlend� adat azonos�t�j�t: ";
	cin >> id;
	adat *aktualis = elso, *elozo = NULL;;
	while(aktualis != NULL){
		if(aktualis->id == id){
			string valasz = "";
			system("cls");
			printf("|%10s|%30s|%30s|%15s|\n", "Azonos�t�", "�nekes neve", "Dal c�me", "Megjelen�s �ve");
			cout << "-----------------------------------------------------------------------------------------" << endl;
			printf("|%10d|%30s|%30s|%15d|\n\n", aktualis->id, aktualis->enekes_neve, aktualis->dal_cime, aktualis->megjelenes_eve);
				while(!(valasz == "igen" || valasz == "nem")){
				cout << "Biztosan v�glegesen t�rli az adatot? (igen / nem): ";
				cin >> valasz;
				if(valasz == "igen"){
					if(elozo != NULL){
						elozo->kovetkezo = aktualis->kovetkezo;
					}else{
						elso = aktualis->kovetkezo;
					}
					free(aktualis);
					system("cls");
					cout << "Sikeres t�rl�s" << endl << endl;
					system("pause"); 
					return elso;
				}else if(valasz == "nem"){
					system("cls");
					cout << "Az adat nem lett kit�r�lve" << endl << endl;
					system("pause"); 
					return elso;
				}else{
					cout << endl << "Nem egy�rtelm� v�lasz" << endl;
				}
			}
		}
		elozo = aktualis;
		aktualis = aktualis->kovetkezo;
	}
	
	system("cls");
	cout << "Hiba: a keresett adat nem tal�lhat�" << endl << endl;
	system("pause");
	return elso;
}


















