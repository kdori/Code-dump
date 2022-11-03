#include <iostream>
#include <stdlib.h>
using namespace std;
struct strukt{
	char szoveg[80];
	int hossz;
	int kisbetu;
};
class osztaly{
	struct valami{
		
	};
	public : osztaly(){
		adatok=0;
	}
	int adatok;
	strukt tomb[100];
	void beolvas();
	private : int hoszmeghat(char szoveg[80]);
	private : int kisbetuk(char szoveg[80]);
	public  : void leghosszabb();
			  void legrovidebb();
			  float atlag();
			  char* arany();
};

int main(){
	setlocale(LC_ALL,"");
	osztaly a;
	a.beolvas();
	a.leghosszabb();
	a.legrovidebb();
	cout << "A szavak hosszának átlaga: " << a.atlag();
	cout<< "\nA legkisebb arányú szó: "<<a.arany();
}


void osztaly::beolvas(){
	bool eleg=true;
	while(eleg){
		system("cls");
		cout<<"Kérem adjon meg egy szöveget:";
		cin>>tomb[adatok].szoveg;
		tomb[adatok].hossz=hoszmeghat(tomb[adatok].szoveg);
		tomb[adatok].kisbetu=kisbetuk(tomb[adatok].szoveg);
		adatok++;
		cout<<"Szeretne még adatot felvenni?\n1.igen\n2.nem\n";
		int i;
		cin >> i;
		switch(i){
			case 1:
				eleg=true;
				break;
			default:
				eleg=false;
				system("cls");
				break;
		}
	}
	
}
int osztaly::hoszmeghat(char szoveg[80]){
	int hossz;
	for (int i=0;i<80 && szoveg[i]!='\0';++i){
	hossz=i;
	}
	return hossz+1;
}
int osztaly::kisbetuk(char szoveg[80]){
	int kisbetu=0;
	for (int i=0;i<80 && szoveg[i]!='\0';++i){
		if(szoveg[i]>='a' && szoveg[i]<='z'){
			kisbetu++;
		}
	}
	return kisbetu;
}
void osztaly::leghosszabb(){
	int max=0,index;
	for (int i=0;i<adatok;++i){
		if(tomb[i].hossz>max){
			max=tomb[i].hossz;
			index=i;
		}
	}
	cout << "A leghosszabb szöveg: "<<tomb[index].szoveg<<endl;
}
void osztaly :: legrovidebb(){
	int min=tomb[0].hossz,index=0;
	for (int i=1;i<adatok;++i){
		if(tomb[i].hossz<min){
			min=tomb[i].hossz;
			index=i;
		}
}
cout << "A legrovidebb szöveg: "<<tomb[index].szoveg<<endl;}

float osztaly :: atlag(){
	float atlag=0.0;
	for (int i=0;i<adatok;++i){
		atlag+=tomb[i].hossz;
	}
	atlag/=adatok;
	return atlag;
}
char* osztaly::arany(){
	int index=0;
	float minarany=tomb[0].hossz/tomb[0].kisbetu;;
for (int i =1;i<adatok;++i){
	float mintaarany=tomb[i].hossz/tomb[i].kisbetu;
	if(minarany<mintaarany){
		minarany=mintaarany;
		index=i;
	}
}
return tomb[index].szoveg;
}
