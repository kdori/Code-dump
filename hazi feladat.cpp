#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

class adat{ public:
	int azon;
	char hol[80];
	int ar;
	char mire[80];
	adat *kovetkezo=NULL;
};

adat *elso = NULL;

class adatb: public adat { public:
void ujadat();
void keres();
void modos();
void torol();
void kiir();
};

int main(){
	setlocale(LC_ALL,"hun");
	adatb a;
	int v = 1;
	while(v != 6){
	printf("\tKöltekezések\n\n\t1. Új adat\n\t2. Keresés\n\t3. Modosítás\n\t4. Törlés\n\t5. Lista\n\t6. Kilépés\n");
    scanf("%d",&v);
    switch(v)
    {
        case 1:
        	a.ujadat();
        	system("cls");
            break;
        case 2: 
		    a.keres();
		    system("cls");
            break;
        case 3:
        	a.modos();
        	system("cls");
            break;
        case 4:
        	a.torol();
        	system("cls");
            break;
        case 5:
        	a.kiir();
        	system("cls");
            break;   
		case 6:
			system("cls");
			break;
		default: 
			printf("Ilyen opció nincs!\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void adatb::ujadat(){
	system("cls");
	printf("\tÚj adat\n\n");
	printf("Azonosító:");
	adat *uj = (adat*) malloc(sizeof(adat));
	scanf("%d",&uj->azon);
	
	if(!elso)
	{
		uj->kovetkezo = elso;
		elso = uj;
	}
	else{
		adat *aktual = elso;
		
		adat *elozo = NULL;
		
		while(aktual){
			if(aktual->azon == uj->azon)
			{
				printf("Azonosító ütközés!\n");
				fflush(stdin);
				printf("Kérem be az új azonosítót:");
				scanf("%d",&uj->azon);
				continue;
			}
			
			if(aktual->azon > uj->azon)
			{
				uj->kovetkezo = aktual;
				if(elozo)
					elozo->kovetkezo = uj;
                else
                    elso = uj;
				break;
			}
			
			elozo = aktual;
			aktual = aktual->kovetkezo;
			
		}
		if(!aktual){
			elozo->kovetkezo = uj;
			uj->kovetkezo = NULL;
		}
	}
	
	printf("Vásárlás helye:");
	scanf("%s",uj->hol);
	fflush(stdin);
	printf("Vásárlás összege:");
	scanf("%d",&uj->ar);
	fflush(stdin);
	printf("Termék neve:");
	fflush(stdin);
	scanf("%s",uj->mire);
	fflush(stdin);
}

void adatb::keres(){
	int az;
	system("cls");
	printf("\tKeresés\n\n");
	printf("Azonosító:");
	scanf("%d",&az);
	
	adat *aktual = elso;
	
	while(aktual){
		if(aktual->azon == az){
			printf("Vásárlás helye:%s\n",aktual->hol);
			printf("Vásárlás összege:%d\n",aktual->ar);
			printf("Termék neve:%s\n",aktual->mire);
			break;
		}
		
		aktual = aktual->kovetkezo;
		
	}
	
	if(!aktual){
		printf("Nincs ilyen azonosító!\n");
	}
	
	system("pause");
	
}

void adatb::modos(){
	int az;
	system("cls");
	printf("\tMódosítás\n\n");
	printf("Azonosító:");
	scanf("%d",&az);
	fflush(stdin);
	adat *aktual = elso;
	
	while(aktual){
		if(aktual->azon == az){
			printf("Vásárlás helye:%s\n",aktual->hol);
			printf("Vásárlás összege:%d\n",aktual->ar);
			printf("Termék neve:%s\n",aktual->mire);
			printf("\nÚj adatok:\n");
			
			printf("Vásárlás helye:");
			scanf("%s",aktual->hol);
			fflush(stdin);
			printf("Vásárlás összege:");
			scanf("%d",&aktual->ar);
			fflush(stdin);
			printf("Termék neve:");
			scanf("%s",aktual->mire);
			fflush(stdin);
			break;
		}
		
		aktual = aktual->kovetkezo;
		
	}
	
	if(!aktual){
		printf("Nincs ilyen azonosító!\n");
	}
	
	system("pause");
	
}

void adatb::torol(){
	system("cls");
	printf("\tTörlés\n\n");
	if(elso==NULL)
	{
		printf("Nincs adat!\n");
		system("pause");
		}
	else{
		printf("Azonosító:");
		int az;
		scanf("%d",&az);
		
		adat *aktual = elso;
		
		adat *elozo = NULL;
		
		
		while(aktual){
			if(aktual->azon == az){
				printf("Vásárlás helye:%s\n",aktual->hol);
				printf("Vásárlás összege:%d\n",aktual->ar);
				printf("Termék neve:%s\n\n",aktual->mire);
				printf("Biztos törölni akarod-e?(igen/nem)");
				string val;
				cin >> val;
				if(val =="nem"){
					system("pause");
					break;
				}
				else if(val == "igen"){
				if(!elozo){
					elso=aktual->kovetkezo;
					free(aktual);
				}
				else{
				elozo->kovetkezo=aktual->kovetkezo;
				free(aktual);
				}
				printf("Az adatok törölve.\n");
				system("pause");
				break;
				}
				else {
					printf("Nem egyértelmû válasz. Az adatok nem lettek törölve.\n");
					system("pause");
					break;
				}
			}	
			
			elozo = aktual;
			aktual = aktual->kovetkezo;
			
		}
		if(!aktual){
			printf("Nincs ilyen azonosító!");
			system("pause");
		}
	}
	
}

void adatb::kiir(){
	system("cls");
	printf("\tLista\n\n");
	if(!elso){
		printf("Nincsenek elemek!\n");
		system("pause");
		return;
	}
	printf("Azon\tÁruház\t\tÁr\tTermék neve");
	adat *aktual=elso;
	while(aktual){
		
		printf("\n%4d%10s%10d%10s",aktual->azon,aktual->hol,aktual->ar,aktual->mire);
		aktual=aktual->kovetkezo;
	}
	printf("\n");
	system("pause");	
}



