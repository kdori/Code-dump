#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#define MAX 50
#define MAX2 100

void bubblesort();
void enter();

int valaszt, azon, m, i, j, torol, x;
int k=0, z=0;
int az[MAX], ar[MAX];
char nev[MAX][MAX2], csere[MAX2];

int main(){
	setlocale (LC_ALL,"");

	while(valaszt!=6){
		printf("--------Adatnyilvántartó program--------\n");
		printf("[1.] Újadat bevitel\n");
		printf("[2.] Keresés\n");
		printf("[3.] Adatmódosítás\n");
		printf("[4.] Törlés\n");
		printf("[5.] Listázás\n");
		printf("[6.] Kilépés\n");

		printf("Válassz egy menüpontot! Ezt választottad: "); scanf("%d",&valaszt);
	
		if(valaszt == 1){
			system("CLS");	
			printf("--------Adatnyilvántartó program--------\n");
			printf("[1.] Újadat bevitel\n");
			printf("[2.] Keresés\n");
			printf("[3.] Adatmódosítás\n");
			printf("[4.] Törlés\n");
			printf("[5.] Listázás\n");
			printf("[6.] Kilépés\n");	
			printf("Kérem az új azonosítót: "); scanf("%d",&azon);
			i=0;
			while (i<k){
				if (azon == az[i]){
					printf("Már létezik ez az azonosító.");
					break;
				}
				i++;
			}
			if (i == k){
				az[k]=azon;
				printf("Kérem az azonosítóhoz tartozó terméknevet: ");
				i=0;
				nev[k][i]=getchar();
					while ((nev[k][i]=getchar())!='\n'){
						i++;
					}
					nev[k][i]='\0';
				printf("Kérem a termék árát: "); scanf("%d", &ar[k]);
				k++;
			}
			enter();
			system("CLS");	
		}
		else if(valaszt == 2){
			system("CLS");
			printf("--------Adatnyilvántartó program--------\n");
			printf("[1.] Újadat bevitel\n");
			printf("[2.] Keresés\n");
			printf("[3.] Adatmódosítás\n");
			printf("[4.] Törlés\n");
			printf("[5.] Listázás\n");
			printf("[6.] Kilépés\n");
			printf("Kérem a keresett termék azonosítóját: "); scanf("%d", &azon);
			i=0;
			z=0;
			while(i<k){
				if (azon == az[i]){
					printf("Termék neve: %s \n", nev[i]);
					printf("Termék ára: %d \n", ar[i]);
					z++;
					break;
					}
				i++;
				}
				if (z == 0){
				printf("Nincs ilyen azonosító. \n");
				}
			enter();
			system("CLS");		
		}
		else if(valaszt == 3){
			system("CLS");
			printf("--------Adatnyilvántartó program--------\n");
			printf("[1.] Újadat bevitel\n");
			printf("[2.] Keresés\n");
			printf("[3.] Adatmódosítás\n");
			printf("[4.] Törlés\n");
			printf("[5.] Listázás\n");
			printf("[6.] Kilépés\n");
			printf("Kérem a keresett termék azonosítóját: "); scanf("%d", &azon);
			i=0;
			while (i<k){
				if (azon == az[i]){
					printf("Termék neve: %s \n", nev[i]);
					printf("Termék ára: %d \n", ar[i]);
					printf("Termék új neve: ");
					m=0;
					nev[i][m]=getchar();
						while ((nev[i][m]=getchar())!='\n'){
						m++;
						}
					nev[i][m]='\0';
					printf("Termék új ára: "); scanf("%d", &ar[i]);
					z++;
					break;
					
					}
				i++;
				}
				if (z == 0){
					printf("Nem tartozik adat a keresett azonosítóhoz. \n");
				}
			enter();
			system("CLS");		
		}
		else if(valaszt == 4){	
			system("CLS");	
			printf("--------Adatnyilvántartó program--------\n");
			printf("[1.] Újadat bevitel\n");
			printf("[2.] Keresés\n");
			printf("[3.] Adatmódosítás\n");
			printf("[4.] Törlés\n");
			printf("[5.] Listázás\n");
			printf("[6.] Kilépés\n");
			printf("Kérem a keresett termék azonosítóját: "); scanf("%d", &azon);
			for (i=0;i<k;i++){
				if (azon == az[i]){
					printf("Termék neve: %s \n", nev[i]);
					printf("Termék ára: %d \n", ar[i]);
					printf("Biztosan törlöd? Ha igen, nyomj 1-et: "); scanf("%d", &torol);
					if (torol == 1){
						while (i<k){
							az[i]=az[i+1];
							ar[i]=ar[i+1];
							strcpy(nev[i],nev[i+1]);
							i++;
						}
						k--;
						printf("A törlés sikeres volt. \n");
					}
					else printf("Nem történt törlés. \n");
					break;
				}
			}
			if (i == k){
				printf("Nem tartozik adat a keresett azonosítóhoz. \n");
				}
			enter();		
			system("CLS");		
		}
		else if(valaszt == 5){
			system("CLS");
			printf("--------Adatnyilvántartó program--------\n");
			printf("[1.] Újadat bevitel\n");
			printf("[2.] Keresés\n");
			printf("[3.] Adatmódosítás\n");
			printf("[4.] Törlés\n");
			printf("[5.] Listázás\n");
			printf("[6.] Kilépés\n");
			printf("Azonosító \t Termék neve \t Termék ára \n");
			bubblesort();
			i=0;
			while (i<k){
				printf("%d \t\t %s \t\t %d \n", az[i], nev[i], ar[i]);
				i++;
			}
			enter();
			system("CLS");	
		}
		else if(valaszt == 6){
			int gomb;
			printf("Szeretne kilpéni? Ha igen, nyomj 1-et: ");
			scanf("%d",&gomb);
			if (gomb!=1){
				valaszt=0;
				system("CLS");
			} 
			else {
				enter();
			}
		}
		else{
			printf("Nincs ilyen menüpont.");
		}
	}
}

void bubblesort(){
	for(i=0; i<k; i++){
		for(j=0; j<k-1; j++){
			if(az[j]>az[j+1]){
				x = az[j];
				az[j] = az[j+1];
				az[j+1] = x;
			
				x = ar[j];
				ar[j] = ar[j+1];
				ar[j+1] = x;
			
				strcpy(csere,nev[j]);
				strcpy(nev[j],nev[j+1]);
				strcpy(nev[j+1],csere);
			}
		}
	}

}
void enter(){ 
	char c;
	fflush(stdin);
	printf("Nyomj egy entert a folytatáshoz!");
	scanf("%c",&c);
}

