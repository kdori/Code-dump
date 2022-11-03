
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

struct adat{
	int azon;
	char hol[80];
	int ar;
	char mire[80];
	adat *kovetkezo=NULL;
};

adat *elso = NULL;

void menu();
void ujadat();
void keres();
void modos();
void torol();
void kiir();

int main(){
	setlocale(LC_ALL,"hun");
	menu();
}

void menu(){
	printf("\tKöltekezések\n\n\t1. Új adat\n\t2. Keresés\n\t3. Modosítás\n\t4. Törlés\n\t5. Lista\n\t6. Kilépés\n");
    int v;
    scanf("%d",&v);

    switch(v)
    {
        case 1:
        	ujadat();
        	system("cls");
            menu();
            break;
        case 2: 
		    keres();
		    system("cls");
			menu();
            break;
        case 3:
        	modos();
        	system("cls");
        	menu();
            break;
        case 4:
        	torol();
        	system("cls");
            menu();
            break;
        case 5:
        	kiir();
        	system("cls");
            menu();
            break;   
		case 6:
			break;
		default: 
			printf("Ilyen opció nincs!\n");
			break;
		}
}

void ujadat(){
	system("cls");
	printf("\tÚj adat\n\n");
	printf("Azonosító:");
	fflush(stdin);
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

void keres(){
	int az;
	system("cls");
	printf("\tKeresés\n\n");
	printf("Azonosító:");
	scanf("%d",&az);
	
	adat *aktual = elso;
	
	while(aktual){
		if(aktual->azon == az){
			printf("Vásárlás heyle:%s\n",aktual->hol);
			printf("Vásárlás összege:%d\n",aktual->ar);
			printf("Termék neve:%s\n",aktual->mire);
			break;
		}
		
		aktual = aktual->kovetkezo;
		
	}
	
	if(!aktual){
		printf("Nincs ilyen azonosító!");
	}
	
	system("pause");
	
}

void modos(){
	int az;
	system("cls");
	printf("\tModosítás\n\n");
	printf("Azonosító:");
	scanf("%d",&az);
	fflush(stdin);
	adat *aktual = elso;
	
	while(aktual){
		if(aktual->azon == az){
			
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
		printf("Nincs ilyen azonosító!");
	}
	
	system("pause");
	
}

void torol(){
	system("cls");
	printf("\tTörlés\n\n");
	if(elso==NULL)
	{
		printf("Nincs adat!");
		}
	else{
		
		printf("Azonosító:");
		int az;
		scanf("%d",&az);
		
		adat *aktual = elso;
		
		adat *elozo = NULL;
		
		
		while(aktual){
			
			if(az == aktual->azon){
				printf("Biztos törölni akarod-e?(igen/nem)");
				char val[4];
				scanf("%s",val);
				if(strcmp(val,"nem")==1){
					break;
				}
				if(!elozo){
					elso=aktual->kovetkezo;
					free(aktual);
				}
				else{
				elozo->kovetkezo=aktual->kovetkezo;
				free(aktual);
				}
				
				break;
			}	
			
			elozo = aktual;
			aktual = aktual->kovetkezo;
			
		}
		if(!aktual){
			printf("Nincs ilyen azonosító!");
		}
	}
	
	
	
}

void kiir(){
	system("cls");
	printf("\tLista\n\n");
	printf("Azon\tÁruház\t\tÁr\tTermék neve");
	if(!elso){
		printf("Nincsenek elemek!");
		return;
	}
	adat *aktual=elso;
	while(aktual){
		
		printf("\n%4d\t%10s\t%5d%15s",aktual->azon,aktual->hol,aktual->ar,aktual->mire);
		aktual=aktual->kovetkezo;
	}
	printf("\n");
	system("pause");	
}


