#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>


void showMenu();
int confirm(char[80]);

struct dbRow{
	int id;//azonos�t�, k�telez�en eg�sz
	char charactername[30];//n�v, k�telez�en sz�veg
	int teamID;//csapat, v�lasztott, eg�sz
	dbRow* nextRow;//l�ncolt list�hoz kell�, k�vetket� elem pointere
};

class db {//adatb�zis f� adatai + adatb�zishoz tartoz� met�dusok
	//...class v�ltoz�k...
	dbRow *newRow,*actualRow,*actualRowSearch,*first = NULL,*rowBefore;
	int A_I = -1;//automatikus azonos�t�kioszt�s: nem kell azonos�t�t be�rni, ezt a program adja meg
	public:
		int doChoice(int);
		void insertRow();
		void deleteRow();
		void listRows();
		int searchRow(bool hasToPrint);//int mivel m�s met�dusban fogom majd k�s�bb haszn�lni
		void editRow();
		db(){
			if (confirm("Enged�lyezni szeretn� az automatikus\n\tazonos�t�kioszt�st?")) {
				A_I = 0;
			}
		}
};


int main() {
	/*
		MAIN:
			-men�vez�rl�s, men� kirajzol�s f�ggv�ny megh�v�sa
	*/
	setlocale(LC_ALL,"");
	db database;
	int choice;
	int acceptedQuit = 0;
	int really;
	
	do {
		showMenu(); 
		if (!acceptedQuit) {
			scanf("%d",&choice);
		}
		acceptedQuit = database.doChoice(choice);
		
	} while (acceptedQuit==0);
	
}

int db::doChoice(int choice){
	switch (choice) {
		case 1:
			this->insertRow();
			break;
		case 2:
			this->deleteRow();
			break;
		case 3:
			this->searchRow(true);
			break;
		case 4:
			this->editRow();
			break;
		case 5:
			this->listRows();
			break;
		case 6:
			showMenu();				
			if (confirm("Val�ban ki szeretne l�pni?")) {
				return 1;
			}
			break;
		default:
			printf("\tIlyen opci� nincsen.\n\t");
			system("pause");
			break;
	}
	return 0;
}

int confirm(char* text){
	/*
		CONFIRM:
			-Mivel sok helyen van meger�s�t�s, �gy k�nnyebb, ha a ki�r�shoz csak 1 f�ggv�nyt kell megh�vni.
	*/
	int really = 0;
	do {
		system("cls");
		printf("\t\t\Adatnyilv�ntart�\n\n");
		printf("\t%s [0=Nem | 1=Igen]",text);
		int error=0;
		do {
			if (error) {
				printf("\t>");
			} else {
				printf("\n\t>");
			}
			error = 1;
			fflush(stdin);
		} while (!scanf("%d",&really));
		
	} while(really!=0 && really!=1);
	return really;
}

void showMenu(){
	/*
		SHOWMENU:
			-Sok sor a design r�sze, �s a main �tl�that�bb ha k�l�n f�ggv�nyben van.
	*/
	system("cls");
	printf("\t\t\tAdatnyilv�ntart�\n\n");
	printf("\tK�rem v�lasszon az al�bbi lehet�s�gek k�z�l:\n\n");
	printf("\t[1] �j adat\n\n");
	printf("\t[2] Adat t�rl�s\n\n");
	printf("\t[3] Keres�s\n\n");
	printf("\t[4] Adatm�dos�t�s\n\n");
	printf("\t[5] Adatok kilist�z�sa\n\n");
	printf("\t[6] Kil�p�s\n\n\t");
};

void db::insertRow(){
	/*
		INSERTROW:
			-ID bek�r�se(Keres�s f�ggv�nnyel).
				-Ha nem automatikus az azonos�t�kioszt�s, akkor id-t k�r be.
			-Ha nem l�tezik az id, akkor bek�ri a nevet.
				-Ha t�l hossz� akkor �jra.
			-Csapat azonos�t� bek�r�se.
			-L�ncolt list�ba rak�s, id-re rendezve, mert �gy szebb, �s k�nnyebb lesz a list�z�s.
			-M�velet megism�tl�se.
	*/
	system("cls");
	printf("\t\tAdatnyilv�ntart� - �j adat\n\n");
	int id;
	if (this->A_I>=0) {
		A_I++;
		id = A_I;
	} else {
		id = this->searchRow(false);
	}
	if (id>0) {
		newRow = (dbRow*)malloc(sizeof(dbRow));
		if (!newRow) {
			printf("Mem�riahiba.");
			system("pause");
		}
		char temp[30];
		int toolong=0;
		do {
			if (toolong) {
				printf("\n\tA megadott n�v t�l hossz�!\n\t");
			}
			printf("\n\tK�rek egy nevet!\n\t>");
			fflush(stdin);
			scanf("%[^\n]",temp);
			toolong = 1;
		} while(strlen(temp)>=30);
		strcpy(this->newRow->charactername,temp);
		this->newRow->id = id;
		printf("\n\tK�rek egy csapat azonos�t�t!");
		int error=0;
		do {
			if (error) {
				printf("\t>");
			} else {
				printf("\n\t>");
			}
			error = 1;
			fflush(stdin);
		} while (!scanf("%d",&this->newRow->teamID));
		
		this->newRow->nextRow = NULL;
		this->rowBefore = NULL;
		this->actualRow = this->first;
		while (this->actualRow&&id>this->actualRow->id){
			this->rowBefore=this->actualRow;
			this->actualRow = this->actualRow->nextRow;
		}
		
		if (!this->rowBefore) {
			this->first = this->newRow;
		} else {
			this->rowBefore->nextRow = this->newRow;
		}
		this->newRow->nextRow = this->actualRow;
		printf("\n\t\tAz adat sikeresen r�gz�tve.\n");
		system("pause");
	} else if (id==0) {
		printf("\n\t\t�rv�nytelen azonos�t�.[id>0 �s id<=10000000]\n");
		system("pause");
	} else {
		printf("\n\t\tIlyen azonos�t� m�r van az adatb�zisban.\n");
		system("pause");
	}
	
	if (confirm("Szeretne �j adatot hozz�adni?")) {
		this->insertRow();
	}
};
void db::deleteRow(){
	/*
		DELETEROW:
			-ID bek�r�se(Keres�s f�ggv�nnyel).
				-Ha nem automatikus az azonos�t�kioszt�s, akkor id-t k�r be.
			-Meger�s�t�s
			-M�velet megism�tl�se.
	*/
	int id = this->searchRow(true);
	system("cls");
	printf("\t\t\tAdatnyilv�ntart� - T�rl�s\n\n");
	if (id<0) {
		if (confirm("Val�ban t�r�lni szeretn� a kiv�lasztott sort?")) {
			if (this->actualRowSearch->id==this->first->id) {
				this->first = this->actualRowSearch->nextRow;
			} else {
				this->rowBefore->nextRow = this->actualRowSearch->nextRow;
			}
			free(this->actualRowSearch);
			printf("\n\t\tSikeres t�rl�s.\n\n\t");
			system("pause");
		}
	}
	if (confirm("Szeretne egy m�sik sort t�rt�lni?")) {
		this->deleteRow();
	}
};
void db::listRows(){
	/*
		LISTROWS:
			-ID-re rendezve ki�rja az adatokat. (Az id-re rendez�ssel itt m�r nem kell foglalkozni, mert a beviteln�l m�r �gy t�rolja el.)
	*/
	system("cls");
	printf("\t\tAdatnyilv�ntart� - Adatok kilist�z�sa\n\n");
	printf("\tID\t|\t\tN�v\t\t|Csapat azonos�t�\n");
	printf("\t---------------------------------------------------------\n");
	this->actualRowSearch = this->first;
	while (this->actualRowSearch) {
		printf("\t%d\t|%30s\t|%d\n",this->actualRowSearch->id,this->actualRowSearch->charactername,this->actualRowSearch->teamID);
		printf("\t---------------------------------------------------------\n");
		this->actualRowSearch = this->actualRowSearch->nextRow;
	}
	printf("\n\n\t");
	system("pause");
};
int db::searchRow(bool hasToPrint){
	/*
		SEARCHROW:
			-A f�ggv�nyt 2 m�don lehet haszn�lni.
				(1) Kiirat�sos keres�s.
					-Bek�r egy azonos�t�t, �s ki�rja az ehhez tartoz� adatokat.
					-Ha nincsen ilyen azonos�t� akkor hiba�zenetet �r.
				(2) Kiirat�s n�lk�li keres�s.
					-Bek�r egy azonos�t�t, �s visszaadja azt ha nem l�tezik az adatb�zisban.
					-Ha l�tezik akkor az azonos�t� -1x-es�vel t�rt vissza.
			-Ha a megadott azonos�t� �rv�nytelen, teh�t 1-n�l kisebb akkor 0 �rt�kkel t�r vissza.
			-A met�dust az�rt csin�ltam 2 m�don haszn�lhat�ra, mert t�bb helyen tudtam �gy haszn�lni. (Ellen�rz�s + Keres�s funkci�)
	*/
	if (hasToPrint) {
		system("cls");
		printf("\t\t\tAdatnyilv�ntart� - Keres�s\n\n");
	}
	
	int idToSearch;
	
	printf("\n\tK�rek egy azonos�t�t!");
	int error=0;
	do {
		if (error) {
			printf("\t>");
		} else {
			printf("\n\t>");
		}
		error = 1;
		fflush(stdin);
	} while (!scanf("%d",&idToSearch));
	if (idToSearch>0 && idToSearch<=9999999) {
		this->actualRowSearch = this->first;
		while (this->actualRowSearch) {
			if ((this->actualRowSearch->id)==idToSearch) {
				if (hasToPrint) {
					system("cls");
					printf("\t\t\tAdatnyilv�ntart� - Keres�s\n\n");
					printf("\tID\t|\t\tN�v\t\t|Csapat azonos�t�\n");
					printf("\t---------------------------------------------------------\n");
					printf("\t%d\t|%30s\t|%d\n",this->actualRowSearch->id,this->actualRowSearch->charactername,this->actualRowSearch->teamID);
					printf("\t---------------------------------------------------------\n");
					system("pause");
				}
				return (-1*idToSearch);
			}
			this->rowBefore = this->actualRowSearch;
			this->actualRowSearch = this->actualRowSearch->nextRow;
		}
		if (hasToPrint) {
			printf("\n\t\tNincsen adat r�gz�tve ilyen azonos�t�val.\n\n\t");
			system("pause");
		}
		return idToSearch;
	} else {
		if (hasToPrint) {
			printf("\n\t\t�rv�nytelen azonos�t�\n");
			system("pause");
		}
		return 0;
	}
};
void db::editRow(){
	/*
		EDITROW:
			-ID bek�r�se(Keres�s f�ggv�nnyel).
			-Ha van ilyen id, akkor bek�ri az �j adatokat, �s �t�rja a list�ban.
			-M�velet megism�tl�se.
	*/
	int id = this->searchRow(true);
	system("cls");
	printf("\t\t\tAdatnyilv�ntart� - Adatm�dos�t�s\n\n");
	if (id<0) {
		char temp[30];
		int toolong=0;
		do {
			if (toolong) {
				printf("\n\tA megadott n�v t�l hossz�!\n\t");
			}
			printf("\n\tK�rek egy nevet!\n\t>");
			fflush(stdin);
			scanf("%[^\n]",temp);
			toolong = 1;
		} while(strlen(temp)>=30);
		strcpy(this->actualRowSearch->charactername,temp);
		printf("\n\tK�rek egy csapat azonos�t�t!");
		int error=0;
		do {
			if (error) {
				printf("\t>");
			} else {
				printf("\n\t>");
			}
			error = 1;
			fflush(stdin);
		} while (!scanf("%d",&this->actualRowSearch->teamID));
	}
	
	if (confirm("Szeretne �jra m�dos�tani egy adatot?")) {
		this->editRow();
	}
};
