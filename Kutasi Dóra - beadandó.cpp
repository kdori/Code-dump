#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

class adat{
	int azon;
	char hol[80];
	int ar;
	char mire[80];
	adat *kovetkezo=NULL;
	public:
	static adat* ujadat(adat*);
	static void keres(adat*);
	static void modos(adat*);
	static adat* torol(adat*);
	static void kiir(adat*);
	
};

void menu();

int main(){
	setlocale(LC_ALL,"hun");
	menu();
}

void menu(){
	adat *elso = NULL;
	printf("\tK�ltekez�sek\n\n\t1. �j adat\n\t2. Keres�s\n\t3. Modos�t�s\n\t4. T�rl�s\n\t5. Lista\n\t6. Kil�p�s\n");
    int v;
    scanf("%d",&v);
    switch(v)
    {
        case 1:
        	elso=adat :: ujadat(elso);
        	system("cls");
            menu();
            break;
        case 2: 
		    adat :: keres(elso);
		    system("cls");
			menu();
            break;
        case 3:
        	adat :: modos(elso);
        	system("cls");
        	menu();
            break;
        case 4:
        	elso=adat :: torol(elso);
        	system("cls");
            menu();
            break;
        case 5:
        	adat :: kiir(elso);
        	system("cls");
            menu();
            break;   
		case 6:
			break;
		default: 
			printf("Ilyen opci� nincs!\n");
			break;
		}
}

adat* adat :: ujadat(adat *elso){
	system("cls");
	printf("\t�j adat\n\n");
	adat *uj = new adat;
	if(!uj){
		printf("Hib�s foglal�s");
		system("pause");
		return NULL;
	}
	printf("Azanos�t�:");
	scanf("%d",&uj->azon);
	adat *aktual = elso;
	adat *elozo = NULL;
	while(aktual && aktual->azon <= uj->azon){
		if(aktual->azon == uj->azon){
		printf("Azonos�t� �tk�z�s!\n");
		fflush(stdin);
		printf("K�rem be az �j azonos�t�t:");
		scanf("%d",&uj->azon);
		continue;
		}
		else{
		elozo = aktual;
		aktual = aktual->kovetkezo;	
		}
	}

		if(!elozo) elso = uj; 
		else elozo->kovetkezo = uj; 
		uj->kovetkezo = aktual;
		
	
	
	
	
	/*
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
			
			while(aktual->azon <= uj->azon)
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
	*/
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
	
	return elso;
}

void adat :: keres(adat *elso){
	int az;
	system("cls");
	printf("\tKeres�s\n\n");
	printf("Azonos�t�:");
	scanf("%d",&az);
	
	adat *aktual = elso;
	
	while(aktual){
		if(aktual->azon == az){
			printf("V�s�rl�s heyle:%s\n",aktual->hol);
			printf("V�s�rl�s �sszege:%d\n",aktual->ar);
			printf("Term�k neve:%s\n",aktual->mire);
			break;
		}
		
		aktual = aktual->kovetkezo;
		
	}
	
	if(!aktual){
		printf("Nincs ilyen azonos�t�!");
	}
	
	system("pause");
	
}

void adat :: modos(adat *elso){
	int az;
	system("cls");
	printf("\tModos�t�s\n\n");
	printf("Azonos�t�:");
	scanf("%d",&az);
	fflush(stdin);
	adat *aktual = elso;
	
	while(aktual){
		if(aktual->azon == az){
			
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
		printf("Nincs ilyen azonos�t�!");
	}
	
	system("pause");
	
}

adat* adat :: torol(adat *elso){
	system("cls");
	printf("\tT�rl�s\n\n");
	if(elso==NULL)
	{
		printf("Nincs adat!");
		}
	else{
		
		printf("Azonos�t�:");
		int az;
		scanf("%d",&az);
		
		adat *aktual = elso;
		
		adat *elozo = NULL;
		
		
		while(aktual){
			
			if(az == aktual->azon){
				printf("Biztos t�r�lni akarod-e?(igen/nem)");
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
			printf("Nincs ilyen azonos�t�!");
		}
	}
	
return elso;	
	
}

void adat :: kiir(adat *elso){
	system("cls");
	printf("\tLista\n\n");
	printf("Azon\t�ruh�z\t\t�r\tTerm�k neve");
	if(!elso){
		printf("Nincsenek elemek!");
		return;
	}
	adat *aktual=elso;
	while(aktual){
		
		printf("\n%4d%10s%10d%10s",aktual->azon,aktual->hol,aktual->ar,aktual->mire);
		aktual=aktual->kovetkezo;
	}
	printf("\n");
	system("pause");	
}


