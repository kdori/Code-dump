#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>


void showMenu();
int confirm(char[80]);

struct dbRow{
	int id;//azonosító, kötelezõen egész
	char charactername[30];//név, kötelezõen szöveg
	int teamID;//csapat, választott, egész
	dbRow* nextRow;//láncolt listához kellõ, követketõ elem pointere
};

class db {//adatbázis fõ adatai + adatbázishoz tartozó metódusok
	//...class változók...
	dbRow *newRow,*actualRow,*actualRowSearch,*first = NULL,*rowBefore;
	int A_I = -1;//automatikus azonosítókiosztás: nem kell azonosítót beírni, ezt a program adja meg
	public:
		int doChoice(int);
		void insertRow();
		void deleteRow();
		void listRows();
		int searchRow(bool hasToPrint);//int mivel más metódusban fogom majd késõbb használni
		void editRow();
		db(){
			if (confirm("Engedélyezni szeretné az automatikus\n\tazonosítókiosztást?")) {
				A_I = 0;
			}
		}
};


int main() {
	/*
		MAIN:
			-menüvezérlés, menü kirajzolás függvény meghívása
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
			if (confirm("Valóban ki szeretne lépni?")) {
				return 1;
			}
			break;
		default:
			printf("\tIlyen opció nincsen.\n\t");
			system("pause");
			break;
	}
	return 0;
}

int confirm(char* text){
	/*
		CONFIRM:
			-Mivel sok helyen van megerõsítés, így könnyebb, ha a kiíráshoz csak 1 függvényt kell meghívni.
	*/
	int really = 0;
	do {
		system("cls");
		printf("\t\t\Adatnyilvántartó\n\n");
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
			-Sok sor a design része, és a main átláthatóbb ha külön függvényben van.
	*/
	system("cls");
	printf("\t\t\tAdatnyilvántartó\n\n");
	printf("\tKérem válasszon az alábbi lehetõségek közül:\n\n");
	printf("\t[1] Új adat\n\n");
	printf("\t[2] Adat törlés\n\n");
	printf("\t[3] Keresés\n\n");
	printf("\t[4] Adatmódosítás\n\n");
	printf("\t[5] Adatok kilistázása\n\n");
	printf("\t[6] Kilépés\n\n\t");
};

void db::insertRow(){
	/*
		INSERTROW:
			-ID bekérése(Keresés függvénnyel).
				-Ha nem automatikus az azonosítókiosztás, akkor id-t kér be.
			-Ha nem létezik az id, akkor bekéri a nevet.
				-Ha túl hosszú akkor újra.
			-Csapat azonosító bekérése.
			-Láncolt listába rakás, id-re rendezve, mert így szebb, és könnyebb lesz a listázás.
			-Mûvelet megismétlése.
	*/
	system("cls");
	printf("\t\tAdatnyilvántartó - Új adat\n\n");
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
			printf("Memóriahiba.");
			system("pause");
		}
		char temp[30];
		int toolong=0;
		do {
			if (toolong) {
				printf("\n\tA megadott név túl hosszú!\n\t");
			}
			printf("\n\tKérek egy nevet!\n\t>");
			fflush(stdin);
			scanf("%[^\n]",temp);
			toolong = 1;
		} while(strlen(temp)>=30);
		strcpy(this->newRow->charactername,temp);
		this->newRow->id = id;
		printf("\n\tKérek egy csapat azonosítót!");
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
		printf("\n\t\tAz adat sikeresen rögzítve.\n");
		system("pause");
	} else if (id==0) {
		printf("\n\t\tÉrvénytelen azonosító.[id>0 és id<=10000000]\n");
		system("pause");
	} else {
		printf("\n\t\tIlyen azonosító már van az adatbázisban.\n");
		system("pause");
	}
	
	if (confirm("Szeretne új adatot hozzáadni?")) {
		this->insertRow();
	}
};
void db::deleteRow(){
	/*
		DELETEROW:
			-ID bekérése(Keresés függvénnyel).
				-Ha nem automatikus az azonosítókiosztás, akkor id-t kér be.
			-Megerõsítés
			-Mûvelet megismétlése.
	*/
	int id = this->searchRow(true);
	system("cls");
	printf("\t\t\tAdatnyilvántartó - Törlés\n\n");
	if (id<0) {
		if (confirm("Valóban törölni szeretné a kiválasztott sort?")) {
			if (this->actualRowSearch->id==this->first->id) {
				this->first = this->actualRowSearch->nextRow;
			} else {
				this->rowBefore->nextRow = this->actualRowSearch->nextRow;
			}
			free(this->actualRowSearch);
			printf("\n\t\tSikeres törlés.\n\n\t");
			system("pause");
		}
	}
	if (confirm("Szeretne egy másik sort törtölni?")) {
		this->deleteRow();
	}
};
void db::listRows(){
	/*
		LISTROWS:
			-ID-re rendezve kiírja az adatokat. (Az id-re rendezéssel itt már nem kell foglalkozni, mert a bevitelnél már így tárolja el.)
	*/
	system("cls");
	printf("\t\tAdatnyilvántartó - Adatok kilistázása\n\n");
	printf("\tID\t|\t\tNév\t\t|Csapat azonosító\n");
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
			-A függvényt 2 módon lehet használni.
				(1) Kiiratásos keresés.
					-Bekér egy azonosítót, és kiírja az ehhez tartozó adatokat.
					-Ha nincsen ilyen azonosító akkor hibaüzenetet ír.
				(2) Kiiratás nélküli keresés.
					-Bekér egy azonosítót, és visszaadja azt ha nem létezik az adatbázisban.
					-Ha létezik akkor az azonosító -1x-esével tért vissza.
			-Ha a megadott azonosító érvénytelen, tehát 1-nél kisebb akkor 0 értékkel tér vissza.
			-A metódust azért csináltam 2 módon használhatóra, mert több helyen tudtam így használni. (Ellenõrzés + Keresés funkció)
	*/
	if (hasToPrint) {
		system("cls");
		printf("\t\t\tAdatnyilvántartó - Keresés\n\n");
	}
	
	int idToSearch;
	
	printf("\n\tKérek egy azonosítót!");
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
					printf("\t\t\tAdatnyilvántartó - Keresés\n\n");
					printf("\tID\t|\t\tNév\t\t|Csapat azonosító\n");
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
			printf("\n\t\tNincsen adat rögzítve ilyen azonosítóval.\n\n\t");
			system("pause");
		}
		return idToSearch;
	} else {
		if (hasToPrint) {
			printf("\n\t\tÉrvénytelen azonosító\n");
			system("pause");
		}
		return 0;
	}
};
void db::editRow(){
	/*
		EDITROW:
			-ID bekérése(Keresés függvénnyel).
			-Ha van ilyen id, akkor bekéri az új adatokat, és átírja a listában.
			-Mûvelet megismétlése.
	*/
	int id = this->searchRow(true);
	system("cls");
	printf("\t\t\tAdatnyilvántartó - Adatmódosítás\n\n");
	if (id<0) {
		char temp[30];
		int toolong=0;
		do {
			if (toolong) {
				printf("\n\tA megadott név túl hosszú!\n\t");
			}
			printf("\n\tKérek egy nevet!\n\t>");
			fflush(stdin);
			scanf("%[^\n]",temp);
			toolong = 1;
		} while(strlen(temp)>=30);
		strcpy(this->actualRowSearch->charactername,temp);
		printf("\n\tKérek egy csapat azonosítót!");
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
	
	if (confirm("Szeretne újra módosítani egy adatot?")) {
		this->editRow();
	}
};
