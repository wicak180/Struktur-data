/* Nama kelompok
================================
1. Arif wicaksono 		14116033
2. Nayaka pitra radity 		14116030
3. Isnan nughraga Marcheriz 	14116018
================================
*/

//Nama Program : Brain Challenge
//Keterangan   : Program mengingat jumlah bintang tiap scene					

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define boolean unsigned char
#define true 1
#define false 0

#define Nil NULL
typedef int infotype;
typedef struct tElmtList *address;
typedef struct tElmtList { 
	  infotype Sum;   //menampung data
	  infotype data;  //menampung jumlah scene
	  address next;
} ElmtList;

typedef struct { 
	  address First;
} List;

#define data(P) (P)->data
#define Next(P) (P)->next
#define Sum(P)  (P)->Sum
#define First(L) ((L).First)

//digunakan mengalokasikan memori 
address Alokasi (infotype X, infotype Y){ 
	address P = (address) malloc (sizeof (ElmtList));
	if (P!=Nil){
		data(P) = X;
		Sum(P) 	= Y;
		Next(P) = Nil;
		return P;
	} else {
		return Nil;
	}
}

void Dealokasi (address P){
	free(P);
}

boolean IsEmpty(List L){ 
	return (First(L)==Nil );
}

void CreateEmpty(List *L){ 
	First(*L) = Nil;
}

void InsertLast(List * L, address P){ 
	address Last;

    if(IsEmpty(*L)){
		Next(P)		= First(*L);
		First(*L)	= P;
	}	
	else {
		Last = First(*L);
		while(Next (Last)!=Nil){
			Last = Next(Last);
			}
		Next(Last) = P;	
	}
}

void DelFirst (List *L, address *P){
	if(First(*L)!= Nil){
		*P 			= First(*L);
		First(*L)	= Next(First(*L));
		Next(*P)	= Nil;	
	}
}

//--------------Fungsi Timer---------------//
void Timer(double seconds){
    clock_t end;
    end = clock() + seconds * CLOCKS_PER_SEC;
    while( clock() < end ) {
        clock();
    }
}
//--------------------------------------------//

char random(){
    int n;

    n = rand() % 6;
    if(n == 1){
    	return '/';
    } else if(n == 2){
    	return '%';
	} else if(n == 3){
    	return '$';
	} else if(n == 4){
    	return '+';
	} else if(n == 5){
    	return '*';
	} else if(n == 0){
    	return '#';
	}
}

boolean CekBintang(char huruf[], int i){
	return ( huruf[i] == '*');
}

void TampilScene(int *skor, int *scene){
	char huruf[16];
	int i, y=0, s=0;

	s = *scene; 
	s++;
	*scene = s;	 
	
	system("cls"); //delete screen
	printf("Scene -%d\n\n",*scene);
	srand(time(NULL));
    for(i=0;i<15;i++) {
        huruf[i] = random();
        if(CekBintang(huruf, i)){
       		y++;  //menghitung jumlah bintang yang benar
		}
    }
    //Y memberi jumlah jawaban benar pada *sum
	*skor = y; 
    printf("%s\n\n", huruf); 
    printf("Note : Ingatlah Jumlah * yang keluar pada scene ini\n");
}

void TanyaBintang(List *L, boolean *start){
	int jawaban;
	
	address P = First(*L);
	printf("Berapa jumlah * yang muncul pada Scene %d?\n\n",data(P));	
	printf("Jawaban : ");
	scanf("%d", &jawaban);
	if(jawaban == Sum(P)){
		DelFirst(&(*L), &P);
	} else{
		printf("\n----Permainan Berakhir----\n");
		printf("Maaf jawaban terakhir anda salah\n\n");
		printf("jumlah scene yang berhasil di jawab dengan benar : %d", data(P)-1);
		*start = false;
	}
}

void Play(List *L, int *sum, int *scene, boolean *start){	
	int i=1;
	*start = true;
	
	while(*start){
		TampilScene(&(*sum), &(*scene));
		InsertLast(&(*L), Alokasi(*scene,*sum));
		Timer(5);
		system("cls"); //delete screen
		if(i > 2){
			TanyaBintang(&(*L), &(*start));
		}
		i++;
	}
}

int main(){
	List L;
	int pilih;
	int sum  = 0;
	int scene = 0;
	boolean start;
\
	CreateEmpty(&L);
	do{
		printf("--------Brain Challenge-------\n");
		printf("[1] Main\n");
		printf("[0] Keluar\n\n");
		printf("Pilihan : ");
		scanf("%d", &pilih);
	
		if(pilih == 1){
			Play(&L, &sum, &scene, &start); 
			return 0;
		}else if (pilih == 0) {
			printf("\n---Terima kasih---");
			return 0;
		}	
	} while(pilih != 0);	
}


