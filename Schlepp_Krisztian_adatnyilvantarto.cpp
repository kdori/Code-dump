#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define SIZE 50
using namespace std;
// Adatanyilvántartó: Énekesek dalai és megjelenési évük
// Készítette: Schlepp Krisztián


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
		cout << "\t\tAdatnyilvántartó" << endl;
		cout << "\tÉnekesek dalai és megjelenési évük" << endl;
		cout << "------------------------------------------------------" << endl;
		cout << "\t\t1: Új adat bevitele" << endl;
		cout << "\t\t2: Keresés" << endl;
		cout << "\t\t3: Adatmódosítás" << endl;
		cout << "\t\t4: Törlés" << endl;
		cout << "\t\t5: Listázás" << endl;
		cout << "\t\t0: Bezárás" << endl;
		cout << "------------------------------------------------------" << endl;
		cout << "Válasszon funkciót: ";
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
		printf("Hibás foglalás");
		system("pause");
		return NULL;
	}
	int azonos = 1;
	while(azonos != 0){
		cout << "Kérem az adat azonosítóját: ";
		cin >> uj->id;
		while(cin.fail()){
			system("cls");
			cout << "Hiba: az azonosítónak egész számnak kell lennie" << endl << endl;
			system("pause");
			system("cls");
			cin.clear();
			cin.ignore(256,'\n');
			cout << "Kérem az adat azonosítóját: ";
			cin >> uj->id;
		}	
		azonos = 0;
		adat *aktualis = elso, *elozo = NULL;
		while(aktualis != NULL && aktualis->id <= uj->id){
			if(aktualis->id == uj->id){
				azonos = 1;
				cout << "Hiba: a megadott azonosító már szerepel a nyilvántartásban" << endl << endl;
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
	cout << "Kérem az énekes nevét: ";
	cin.getline(uj->enekes_neve, SIZE);
	cout << "Kérem a dal címét: ";
	cin.getline(uj->dal_cime, SIZE);
	cout << "Kérem a megjelenés évét: ";
	cin >> uj->megjelenes_eve;
	while(cin.fail() || uj->megjelenes_eve > 2020){
		system("cls");
		cout << "Hiba: a megjelenés évének egész számnak kell lennie, és legfeljebb 2020 lehet" << endl << endl;
		system("pause");
		system("cls");
		cin.clear();
		cin.ignore(256,'\n');
		cout << "Kérem a megjelenés évét: ";
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
	printf("|%10s|%30s|%30s|%15s|\n", "Azonosító", "Énekes neve", "Dal címe", "Megjelenés éve");
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
	cout << "Kérem a keresett adat azonosítóját: ";
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
		printf("|%10s|%30s|%30s|%15s|\n", "Azonosító", "Énekes neve", "Dal címe", "Megjelenés éve");
		cout << "-----------------------------------------------------------------------------------------" << endl;
		printf("|%10d|%30s|%30s|%15d|\n\n", aktualis->id, aktualis->enekes_neve, aktualis->dal_cime, aktualis->megjelenes_eve);
	}else{
		system("cls");
		cout << "Hiba: a keresett adat nem található" << endl << endl;
	}
	system("pause");
}

void adat::adat_modositas(adat* elso){
	int id;
	system("cls");
	cout << "Kérem a módosítandó adat azonosítóját: ";
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
		printf("|%10s|%30s|%30s|%15s|\n", "Azonosító", "Énekes neve", "Dal címe", "Megjelenés éve");
		cout << "-----------------------------------------------------------------------------------------" << endl;
		printf("|%10d|%30s|%30s|%15d|\n\n", aktualis->id, aktualis->enekes_neve, aktualis->dal_cime, aktualis->megjelenes_eve);
		cin.clear();
		cin.ignore(256,'\n');
		cout << "Kérem az énekes nevét: ";
		cin.getline(aktualis->enekes_neve, SIZE);
		cout << "Kérem a dal címét: ";
		cin.getline(aktualis->dal_cime, SIZE);
		cout << "Kérem a megjelenés évét: ";
		cin >> aktualis->megjelenes_eve;
		while(cin.fail() || aktualis->megjelenes_eve > 2020){
			system("cls");
			cout << "Hiba: a megjelenés évének egész számnak kell lennie, és legfeljebb 2020 lehet" << endl << endl;
			system("pause");
			system("cls");
			cin.clear();
			cin.ignore(256,'\n');
			cout << "Kérem a megjelenés évét: ";
			cin >> aktualis->megjelenes_eve;
		}
		
		cout << endl << "Sikeres adatmódosítás" << endl << endl;
		cin.clear();
		cin.ignore(256,'\n');
		system("pause");
	}else{
		system("cls");
		cout << "Hiba: a keresett adat nem található" << endl << endl;
		system("pause");
	}
	
	
	
}

adat* adat::adat_torles(adat* elso){
	int id;
	system("cls");
	cout << "Kérem a törlendõ adat azonosítóját: ";
	cin >> id;
	adat *aktualis = elso, *elozo = NULL;;
	while(aktualis != NULL){
		if(aktualis->id == id){
			string valasz = "";
			system("cls");
			printf("|%10s|%30s|%30s|%15s|\n", "Azonosító", "Énekes neve", "Dal címe", "Megjelenés éve");
			cout << "-----------------------------------------------------------------------------------------" << endl;
			printf("|%10d|%30s|%30s|%15d|\n\n", aktualis->id, aktualis->enekes_neve, aktualis->dal_cime, aktualis->megjelenes_eve);
				while(!(valasz == "igen" || valasz == "nem")){
				cout << "Biztosan véglegesen törli az adatot? (igen / nem): ";
				cin >> valasz;
				if(valasz == "igen"){
					if(elozo != NULL){
						elozo->kovetkezo = aktualis->kovetkezo;
					}else{
						elso = aktualis->kovetkezo;
					}
					free(aktualis);
					system("cls");
					cout << "Sikeres törlés" << endl << endl;
					system("pause"); 
					return elso;
				}else if(valasz == "nem"){
					system("cls");
					cout << "Az adat nem lett kitörölve" << endl << endl;
					system("pause"); 
					return elso;
				}else{
					cout << endl << "Nem egyértelmû válasz" << endl;
				}
			}
		}
		elozo = aktualis;
		aktualis = aktualis->kovetkezo;
	}
	
	system("cls");
	cout << "Hiba: a keresett adat nem található" << endl << endl;
	system("pause");
	return elso;
}


















