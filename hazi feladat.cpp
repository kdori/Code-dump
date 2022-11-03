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
	printf("\tK�ltekez�sek\n\n\t1. �j adat\n\t2. Keres�s\n\t3. Modos�t�s\n\t4. T�rl�s\n\t5. Lista\n\t6. Kil�p�s\n");
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
			printf("Ilyen opci� nincs!\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void adatb::ujadat(){
	system("cls");
	printf("\t�j adat\n\n");
	printf("Azonos�t�:");
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
				printf("Azonos�t� �tk�z�s!\n");
				fflush(stdin);
				printf("K�rem be az �j azonos�t�t:");
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
	
	printf("V�s�rl�s helye:");
	scanf("%s",uj->hol);
	fflush(stdin);
	printf("V�s�rl�s �sszege:");
	scanf("%d",&uj->ar);
	fflush(stdin);
	printf("Term�k neve:");
	fflush(stdin);
	scanf("%s",uj->mire);
	fflush(stdin);
}

void adatb::keres(){
	int az;
	system("cls");
	printf("\tKeres�s\n\n");
	printf("Azonos�t�:");
	scanf("%d",&az);
	
	adat *aktual = elso;
	
	while(aktual){
		if(aktual->azon == az){
			printf("V�s�rl�s helye:%s\n",aktual->hol);
			printf("V�s�rl�s �sszege:%d\n",aktual->ar);
			printf("Term�k neve:%s\n",aktual->mire);
			break;
		}
		
		aktual = aktual->kovetkezo;
		
	}
	
	if(!aktual){
		printf("Nincs ilyen azonos�t�!\n");
	}
	
	system("pause");
	
}

void adatb::modos(){
	int az;
	system("cls");
	printf("\tM�dos�t�s\n\n");
	printf("Azonos�t�:");
	scanf("%d",&az);
	fflush(stdin);
	adat *aktual = elso;
	
	while(aktual){
		if(aktual->azon == az){
			printf("V�s�rl�s helye:%s\n",aktual->hol);
			printf("V�s�rl�s �sszege:%d\n",aktual->ar);
			printf("Term�k neve:%s\n",aktual->mire);
			printf("\n�j adatok:\n");
			
			printf("V�s�rl�s helye:");
			scanf("%s",aktual->hol);
			fflush(stdin);
			printf("V�s�rl�s �sszege:");
			scanf("%d",&aktual->ar);
			fflush(stdin);
			printf("Term�k neve:");
			scanf("%s",aktual->mire);
			fflush(stdin);
			break;
		}
		
		aktual = aktual->kovetkezo;
		
	}
	
	if(!aktual){
		printf("Nincs ilyen azonos�t�!\n");
	}
	
	system("pause");
	
}

void adatb::torol(){
	system("cls");
	printf("\tT�rl�s\n\n");
	if(elso==NULL)
	{
		printf("Nincs adat!\n");
		system("pause");
		}
	else{
		printf("Azonos�t�:");
		int az;
		scanf("%d",&az);
		
		adat *aktual = elso;
		
		adat *elozo = NULL;
		
		
		while(aktual){
			if(aktual->azon == az){
				printf("V�s�rl�s helye:%s\n",aktual->hol);
				printf("V�s�rl�s �sszege:%d\n",aktual->ar);
				printf("Term�k neve:%s\n\n",aktual->mire);
				printf("Biztos t�r�lni akarod-e?(igen/nem)");
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
				printf("Az adatok t�r�lve.\n");
				system("pause");
				break;
				}
				else {
					printf("Nem egy�rtelm� v�lasz. Az adatok nem lettek t�r�lve.\n");
					system("pause");
					break;
				}
			}	
			
			elozo = aktual;
			aktual = aktual->kovetkezo;
			
		}
		if(!aktual){
			printf("Nincs ilyen azonos�t�!");
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
	printf("Azon\t�ruh�z\t\t�r\tTerm�k neve");
	adat *aktual=elso;
	while(aktual){
		
		printf("\n%4d%10s%10d%10s",aktual->azon,aktual->hol,aktual->ar,aktual->mire);
		aktual=aktual->kovetkezo;
	}
	printf("\n");
	system("pause");	
}



