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
		printf("--------Adatnyilv�ntart� program--------\n");
		printf("[1.] �jadat bevitel\n");
		printf("[2.] Keres�s\n");
		printf("[3.] Adatm�dos�t�s\n");
		printf("[4.] T�rl�s\n");
		printf("[5.] List�z�s\n");
		printf("[6.] Kil�p�s\n");

		printf("V�lassz egy men�pontot! Ezt v�lasztottad: "); scanf("%d",&valaszt);
	
		if(valaszt == 1){
			system("CLS");	
			printf("--------Adatnyilv�ntart� program--------\n");
			printf("[1.] �jadat bevitel\n");
			printf("[2.] Keres�s\n");
			printf("[3.] Adatm�dos�t�s\n");
			printf("[4.] T�rl�s\n");
			printf("[5.] List�z�s\n");
			printf("[6.] Kil�p�s\n");	
			printf("K�rem az �j azonos�t�t: "); scanf("%d",&azon);
			i=0;
			while (i<k){
				if (azon == az[i]){
					printf("M�r l�tezik ez az azonos�t�.");
					break;
				}
				i++;
			}
			if (i == k){
				az[k]=azon;
				printf("K�rem az azonos�t�hoz tartoz� term�knevet: ");
				i=0;
				nev[k][i]=getchar();
					while ((nev[k][i]=getchar())!='\n'){
						i++;
					}
					nev[k][i]='\0';
				printf("K�rem a term�k �r�t: "); scanf("%d", &ar[k]);
				k++;
			}
			enter();
			system("CLS");	
		}
		else if(valaszt == 2){
			system("CLS");
			printf("--------Adatnyilv�ntart� program--------\n");
			printf("[1.] �jadat bevitel\n");
			printf("[2.] Keres�s\n");
			printf("[3.] Adatm�dos�t�s\n");
			printf("[4.] T�rl�s\n");
			printf("[5.] List�z�s\n");
			printf("[6.] Kil�p�s\n");
			printf("K�rem a keresett term�k azonos�t�j�t: "); scanf("%d", &azon);
			i=0;
			z=0;
			while(i<k){
				if (azon == az[i]){
					printf("Term�k neve: %s \n", nev[i]);
					printf("Term�k �ra: %d \n", ar[i]);
					z++;
					break;
					}
				i++;
				}
				if (z == 0){
				printf("Nincs ilyen azonos�t�. \n");
				}
			enter();
			system("CLS");		
		}
		else if(valaszt == 3){
			system("CLS");
			printf("--------Adatnyilv�ntart� program--------\n");
			printf("[1.] �jadat bevitel\n");
			printf("[2.] Keres�s\n");
			printf("[3.] Adatm�dos�t�s\n");
			printf("[4.] T�rl�s\n");
			printf("[5.] List�z�s\n");
			printf("[6.] Kil�p�s\n");
			printf("K�rem a keresett term�k azonos�t�j�t: "); scanf("%d", &azon);
			i=0;
			while (i<k){
				if (azon == az[i]){
					printf("Term�k neve: %s \n", nev[i]);
					printf("Term�k �ra: %d \n", ar[i]);
					printf("Term�k �j neve: ");
					m=0;
					nev[i][m]=getchar();
						while ((nev[i][m]=getchar())!='\n'){
						m++;
						}
					nev[i][m]='\0';
					printf("Term�k �j �ra: "); scanf("%d", &ar[i]);
					z++;
					break;
					
					}
				i++;
				}
				if (z == 0){
					printf("Nem tartozik adat a keresett azonos�t�hoz. \n");
				}
			enter();
			system("CLS");		
		}
		else if(valaszt == 4){	
			system("CLS");	
			printf("--------Adatnyilv�ntart� program--------\n");
			printf("[1.] �jadat bevitel\n");
			printf("[2.] Keres�s\n");
			printf("[3.] Adatm�dos�t�s\n");
			printf("[4.] T�rl�s\n");
			printf("[5.] List�z�s\n");
			printf("[6.] Kil�p�s\n");
			printf("K�rem a keresett term�k azonos�t�j�t: "); scanf("%d", &azon);
			for (i=0;i<k;i++){
				if (azon == az[i]){
					printf("Term�k neve: %s \n", nev[i]);
					printf("Term�k �ra: %d \n", ar[i]);
					printf("Biztosan t�rl�d? Ha igen, nyomj 1-et: "); scanf("%d", &torol);
					if (torol == 1){
						while (i<k){
							az[i]=az[i+1];
							ar[i]=ar[i+1];
							strcpy(nev[i],nev[i+1]);
							i++;
						}
						k--;
						printf("A t�rl�s sikeres volt. \n");
					}
					else printf("Nem t�rt�nt t�rl�s. \n");
					break;
				}
			}
			if (i == k){
				printf("Nem tartozik adat a keresett azonos�t�hoz. \n");
				}
			enter();		
			system("CLS");		
		}
		else if(valaszt == 5){
			system("CLS");
			printf("--------Adatnyilv�ntart� program--------\n");
			printf("[1.] �jadat bevitel\n");
			printf("[2.] Keres�s\n");
			printf("[3.] Adatm�dos�t�s\n");
			printf("[4.] T�rl�s\n");
			printf("[5.] List�z�s\n");
			printf("[6.] Kil�p�s\n");
			printf("Azonos�t� \t Term�k neve \t Term�k �ra \n");
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
			printf("Szeretne kilp�ni? Ha igen, nyomj 1-et: ");
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
			printf("Nincs ilyen men�pont.");
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
	printf("Nyomj egy entert a folytat�shoz!");
	scanf("%c",&c);
}

