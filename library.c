/* --------------- IMPLEMENTASI FUNGSI DI LIBRARY.H --------------- */
/* Tempat mengimplementasikan fungsi-fungsi					        */
/* Ketentuan penulisan variabel :                                   */
/* 1. Nama jelas dan bermakna (jangan cuma A, B, C)                 */
/* 2. Dimulai lowercase, jika beda kata gunakan uppercase           */
/*    pada huruf pertama kata selanjutnya untuk memisahkan          */
/* contoh variabel benar : resistorAwal, teganganInput              */
/* Penulisan konstanta pakai #define aja yaaa					    */
//==================================================================//

#include "library.h"

/* -----IMPLEMENTASI FUNGSI----- */
// Prosedur untuk membuat proyek baru, meminta input nama proyek dan ukuran PCB
void NewProject() {
	int i, j;

	printf ("\n====== Membuat Proyek Baru ======\n");
	do {
		// Input nama proyek yang diinginkan user
		printf ("Masukkan nama proyek: ");
		scanf ("%s", namaProyek);
		// Mengecek file eksternal baru untuk Layout dan Routing, serta membuka file tersebut untuk dilakukan pembacaan ada tidaknya file
		strcpy(filenameLayout, namaProyek);
		strcpy(filenameRouting, namaProyek);
		strcat(filenameLayout, "_layout.csv");
		strcat(filenameRouting, "_routing.csv");
		fileLayout = fopen(filenameLayout, "r");
		fileRouting = fopen(filenameRouting, "r");
		if ((fileLayout!=NULL)&&(fileRouting!=NULL)) {
			printf ("Nama proyek sudah ada. Silahkan tulis nama lain!\n");
		}
	} while ((fileLayout!=NULL)&&(fileRouting!=NULL));
	// Menutup pembacaan file, lalu membuka kembali untuk dituliskan file baru
	fclose(fileLayout);
	fclose(fileRouting);
	fileLayout = fopen(filenameLayout, "w");
	fileRouting = fopen(filenameRouting, "w");
	// Input ukuran PCB hingga memenuhi syarat
	printf ("Masukkan ukuran PCB NxM (0<N,M<=40):\n");
	do {
		printf ("Masukkan N (jumlah kolom): "); scanf ("%d", &varLayout.colNeff);
	} while (varLayout.colNeff<1 || varLayout.colNeff>40);
	do {
		printf ("Masukkan M (jumlah baris): "); scanf ("%d", &varLayout.rowNeff);
	} while (varLayout.rowNeff<1 || varLayout.rowNeff>40);
	varRouting.colNeff = varLayout.colNeff;
	varRouting.rowNeff = varLayout.rowNeff;
	// Menginisiasi semua nilai simbol dalam variabel Layout dan Routing menjadi kosong (' '), JANGAN berikan nilai NULL
	for (i=0; i<varLayout.rowNeff; i++) {
		for (j=0; j<varLayout.colNeff; j++) {
			varLayout.simbol[i][j][0]= ' ';
			varRouting.simbol[i][j][0] = ' ';
		}
	}
	// Inisiasi file Layout dan Routing, agar formatnya benar
	fprintf (fileLayout, "%d,%d\n", varLayout.colNeff, varLayout.rowNeff);
	fprintf (fileRouting, "%d,%d\n", varRouting.colNeff, varRouting.rowNeff);
	for (i=0; i<varLayout.rowNeff; i++) {
		for (j=0; j<varLayout.colNeff-1; j++) {
			fprintf (fileLayout, "%s,", varLayout.simbol[i][j]);
			fprintf (fileRouting, "%s,", varRouting.simbol[i][j]);
		}
		fprintf (fileLayout, "%s\n", varLayout.simbol[i][j]);
		fprintf (fileRouting, "%s\n", varRouting.simbol[i][j]);
	}
	// Menutup file
	fclose(fileLayout);
	fclose(fileRouting);
	printf("\n");
}

// Prosedur untuk memuat proyek lama (sudah ada filenya)
// Meminta nama file, jika tidak ada file tersebut beri suatu pesan
// File ada maka return 1, jika tidak ada maka return 0
int LoadProject() {
	int i, j;
	char *token;
	char fileLine[41][200];

	// Meminta input nama proyek yang ingin dibuka
	// Mmebuka file proyek untuk Layout dan Routing dengan nama tersebut
	printf ("\n====== Memuat Proyek Lama ======\n");
	printf ("Masukkan nama proyek: ");
	scanf ("%s", namaProyek);
	strcpy(filenameLayout, namaProyek);
	strcpy(filenameRouting, namaProyek);
	strcat(filenameLayout, "_layout.csv");
	strcat(filenameRouting, "_routing.csv");
	fileLayout = fopen(filenameLayout, "r");
	fileRouting = fopen(filenameRouting, "r");
	// Jika tidak ditemukan file-nya, maka beri pesan kesalahan pada menu utama
	if ((fileLayout==NULL)&&(fileRouting==NULL)) {
		// Menutup file
		fclose(fileLayout);
		fclose(fileRouting);
		return 0;
	} 
	// Jika file ditemukan, maka masukkan data dari file ke dalam variabel di program ini
	else {
		// Memasukkan data fileLayout ke dalam variabel varLayout
		for (i=0; i<41; i++) {
			fgets(fileLine[i], 200, fileLayout);
		}
		token = strtok(fileLine[0], ","); varLayout.colNeff = atoi(token);
		token = strtok(NULL, "\n"); varLayout.rowNeff = atoi(token);
		for (i=1; i<varLayout.rowNeff+1; i++) {
			j = 0;
			token = strtok(fileLine[i], ",");
			strcpy (varLayout.simbol[i-1][j], token); //printf ("Ini :%sspasi\n", varLayout.simbol[i-1][j]); //Debug
			for (j=1; j<varLayout.colNeff-1; j++) {
				token = strtok(NULL, ",");
				strcpy (varLayout.simbol[i-1][j], token); //printf ("Ini :%sspasi\n", varLayout.simbol[i-1][j]); //Debug
			}
			token = strtok(NULL, "\n");
			strcpy (varLayout.simbol[i-1][j], token); //printf ("Ini :%sspasi\n", varLayout.simbol[i-1][j]); //Debug
		}
		// Memasukkan data fileRouting ke dalam variabel varRouting
		for (i=0; i<41; i++) {
			fgets(fileLine[i], 200, fileRouting);
		}
		token = strtok(fileLine[0], ","); varRouting.colNeff = atoi(token);
		token = strtok(NULL, "\n"); varRouting.rowNeff = atoi(token);
		for (i=1; i<varRouting.rowNeff+1; i++) {
			j = 0;
			token = strtok(fileLine[i], ",");
			strcpy (varRouting.simbol[i-1][j], token); //printf ("Ini :%sspasi\n", varRouting.simbol[i-1][j]); //Debug
			for (j=1; j<varRouting.colNeff-1; j++) {
				token = strtok(NULL, ",");
				strcpy (varRouting.simbol[i-1][j], token); //printf ("Ini :%sspasi\n", varRouting.simbol[i-1][j]); //Debug
			}
			token = strtok(NULL, "\n");
			strcpy (varRouting.simbol[i-1][j], token); //printf ("Ini :%sspasi\n", varRouting.simbol[i-1][j]); //Debug
		}
		printf("\n");
		// Menutup file
		fclose(fileLayout);
		fclose(fileRouting);
		return 1;
	}
}

// Prosedur untuk menampilkan menu utama dan pilihan modenya
void MenuUtama() {
	do {
		printf ("[Menu Utama]\n");
		printf ("Pilih Mode:\n");
		printf ("	1. Tampilkan Layout\n");
		printf ("	2. Layouting Manual\n");
		printf ("	3. Tampilkan Routing\n");
		printf ("	4. Routing Manual\n");
		printf ("	5. Layout Otomatis\n");
		printf ("	6. Routing Otomatis\n");
		printf ("	7. Design Rule Checker\n");
		printf ("	8. Simpan Proyek dan Keluar\n");
		printf ("Pilih Mode: "); scanf("%d", &inputMode);
		if (inputMode > 8 || inputMode < 1) {
			printf ("Pilihan mode tidak ada. Masukan ulang!\n");
		} else if (inputMode == 1) {
			//Menampilkan layout
		} else if (inputMode == 2) {
			//Melakukan layouting manual
		} else if (inputMode == 3) {
			//Menampilkan routing
		} else if (inputMode == 4) {
			//Melakukan routing manual
			RoutingManual();
		} else if (inputMode == 5) {
			//Melakukan layouting otomatis
		} else if (inputMode == 6) {
			//Melakukan routing otomatis
		} else if (inputMode == 7) {
			//Melakukan design rule checker
		} else if (inputMode == 8) {
			//Simpan proyek
		}
		printf ("\n");
	} while (inputMode!=8);
}

// Prosedur menampilkan layout rangkaian PCB Dot Matriks
void TampilkanLayout();

// Prosedur melakukan layout manual : meminta input komponen dari user
void LayoutingManual(){
	int i,j,k;

/* Dari Josh dikirim lewat line
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct koor {
    int x;
    int y;
}koor;

typedef struct komponen2kaki {
    char komp[10];//nama komponen
    koor koor1;
    koor koor2;
}komponen2kaki;

typedef struct komponen3kaki {
    char komp[10];
    koor koor1;
    koor koor2;
    koor koor3;
}komponen3kaki;

typedef struct kompfix {
    char namkomp[10];
}kompfix;

int i, j, k;
komponen2kaki tempkom2;
komponen3kaki tempkom3;
char tempc;
kompfix kompfix2 [100][100];
int max1=1,max2=1;
int valid=1, validasiOut=1, panjangKataBlkg,count;

kompfix LayoutingManual(){
// int i,j,k;
 printf("[Mode Layout]\nIsi q atau Q untuk kembali ke menu\n");
 do {
        printf("Pilih Komponen (R,C,T,J): ");
        scanf("%s", (tempkom2.komp));
        //validasi apabila input salah
        if ((tempkom2.komp[0] == 'R')||(tempkom2.komp[0]=='T')||(tempkom2.komp[0]=='C')||
            (tempkom2.komp[0]=='J')||(tempkom2.komp[0]=='Q')||(tempkom2.komp[0]=='q')){
        valid = 0;}

        while (valid==1){
   printf("Ulangi input komponen, komponen tidak tersedia\n");
            printf("Pilih Komponen (R,C,T,J): ");
            scanf("%s", (tempkom2.komp));
            if ((tempkom2.komp[0] == 'R')||(tempkom2.komp[0]=='T')||(tempkom2.komp[0]=='C')||
            (tempkom2.komp[0]=='J')||(tempkom2.komp[0]=='Q')||(tempkom2.komp[0]=='q')){
                valid = 0;
            }
        }

        //bila input resistor
        if (tempkom2.komp[0]=='R'){
                printf("Koordinat Kaki 1 : ");
                scanf("%d,%d",(&tempkom2.koor1.x),(&tempkom2.koor1.y));
                if (max1<=tempkom2.koor1.x){
                    max1=tempkom2.koor1.x;
                }
                if (max2<=tempkom2.koor1.y){
                    max2 = tempkom2.koor1.y;
                }
                printf("Koordinat Kaki 2 : ");
                scanf("%d,%d",(&tempkom2.koor2.x),(&tempkom2.koor2.y));
                if (max1<=tempkom2.koor2.x){
                    max1=tempkom2.koor2.x;
                }
                if (max2<=tempkom2.koor2.y){
                    max2 = tempkom2.koor2.y;
                }
                if (((kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp[0] == '\0')&& //validasi posisi kosong
                     (kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp[0] == '\0'))&&
                    ((abs(tempkom2.koor1.x - tempkom2.koor2.x) >= 3 )|| //validasi jarak antar komponen benar
                     (abs(tempkom2.koor1.y - tempkom2.koor2.y) >= 3 )))
                {
                    strcpy((kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp),(tempkom2.komp)) ;
                    strcpy((kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp),(tempkom2.komp)) ;
                } else {
                    printf("peletakan komponen salah, jarak minimum antar kaki resistor yaitu 3 lubang/ sudah terdapat komponen\n");
                }
        }

        //bila input kapasitor
        if (tempkom2.komp[0]=='C'){
                printf("Koordinat Kaki 1 : ");
                scanf("%d,%d",(&tempkom2.koor1.x),(&tempkom2.koor1.y));
                if (max1<=tempkom2.koor1.x){
                    max1=tempkom2.koor1.x;
                }
                if (max2<=tempkom2.koor1.y){
                    max2 = tempkom2.koor1.y;
                }
                printf("Koordinat Kaki 2 : ");
                scanf("%d,%d",(&tempkom2.koor2.x),(&tempkom2.koor2.y));
                if (max1<=tempkom2.koor2.x){
                    max1=tempkom2.koor2.x;
                }
                if (max2<=tempkom2.koor2.y){
                    max2 = tempkom2.koor2.y;
                }
                if (((kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp[0] == '\0')&& //validasi posisi kosong
                     (kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp[0] == '\0'))&&
                    ((abs(tempkom2.koor1.x - tempkom2.koor2.x) >= 1 )|| //validasi jarak antar komponen benar
                     (abs(tempkom2.koor1.y - tempkom2.koor2.y) >= 1 )))
                {
                    strcpy (kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp,tempkom2.komp);
                    strcpy (kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp,tempkom2.komp);
                } else {
                    printf("peletakan komponen salah, jarak minimum antar kaki kapasitor yaitu 1 lubang");
                }
        }

        //bila input jumper
        if (tempkom2.komp[0]=='J'){
                printf("Koordinat Kaki 1 : ");
                scanf("%d,%d",(&tempkom2.koor1.x),(&tempkom2.koor1.y));
                if (max1<=tempkom2.koor1.x){
                    max1=tempkom2.koor1.x;
                }
                if (max2<=tempkom2.koor1.y){
                    max2 = tempkom2.koor1.y;
                }
                printf("Koordinat Kaki 2 : ");
                scanf("%d,%d",(&tempkom2.koor2.x),(&tempkom2.koor2.y));
                if (max1<=tempkom2.koor2.x){
                    max1=tempkom2.koor2.x;
                }
                if (max2<=tempkom2.koor2.y){
                    max2 = tempkom2.koor2.y;
                }
                if ((kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp[0] == '\0')&& //validasi posisi kosong
                    (kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp[0] == '\0'))
                    //lupa validasi letak komponen sebelumnya yg udh dimasukin
                {
                    strcpy(kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp,tempkom2.komp);
                    strcpy(kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp,tempkom2.komp);
                } else {
                    printf("peletakan komponen salah, koordinat sudah terisi");
                }
        }

        //bila input transistor
                if (tempkom2.komp[0]=='T'){
                printf("Koordinat Kaki 1 : ");
                scanf("%d,%d",(&tempkom3.koor1.x),(&tempkom3.koor3.y));
                if (max1<=tempkom3.koor1.x){
                    max1=tempkom3.koor1.x;
                }
                if (max2<=tempkom3.koor1.y){
                    max2 = tempkom3.koor1.y;
                }
                printf("Koordinat Kaki 2 : ");
                scanf("%d,%d",(&tempkom3.koor2.x),(&tempkom3.koor2.y));
                if (max1<=tempkom3.koor2.x){
                    max1=tempkom3.koor2.x;
                }
                if (max2<=tempkom3.koor2.y){
                    max2 = tempkom3.koor2.y;
                }
                printf("Koordinat Kaki 3 : ");
                scanf("%d,%d",(&tempkom3.koor3.x),(&tempkom3.koor3.y));
                if (max1<=tempkom3.koor3.x){
                    max1=tempkom3.koor3.x;
                }
                if (max2<=tempkom3.koor3.y){
                    max2 = tempkom3.koor3.y;
                }
                if (((kompfix2[tempkom3.koor1.x][tempkom3.koor1.y].namkomp[0] == '\0')&& //validasi posisi kosong
                     (kompfix2[tempkom3.koor2.x][tempkom3.koor2.y].namkomp[0] == '\0')&&
                     (kompfix2[tempkom3.koor3.x][tempkom3.koor3.y].namkomp[0] == '\0'))&&
                    ((abs(tempkom3.koor1.x - tempkom3.koor2.x) >= 1 )|| //validasi jarak antar kaki
                     (abs(tempkom3.koor2.x - tempkom3.koor3.x) >= 1 )||
                     (abs(tempkom3.koor1.y - tempkom3.koor2.y) >= 1 )||
                     (abs(tempkom3.koor2.y - tempkom3.koor3.y) >=1 )))
                {
                    strcpy(kompfix2[tempkom3.koor1.x][tempkom3.koor1.y].namkomp,tempkom2.komp);
                    strcpy(kompfix2[tempkom3.koor2.x][tempkom3.koor2.y].namkomp,tempkom2.komp);
                    strcpy(kompfix2[tempkom3.koor3.x][tempkom3.koor3.y].namkomp,tempkom2.komp);
                } else {
                    printf("peletakan komponen salah, jarak minimum antar kaki transistor 1 lubang");
                }
        }
    //bila input q/Q (Quit)
    if ((tempkom2.komp[0]=='Q')||(tempkom2.komp[0]=='q')){
        validasiOut = 0;
    }

 } while (validasiOut);

    printf("loop hehe\n"); //NANDAIN MASUK SINI AJA.. HAPUS YAK NANTI
 //MenuUtama();
};



void TampilkanLayout() {
    int i,j,k;
    printf(" ");
    for (i=1;i<=max2;i++){
        printf("%d\t",i);}
        for (j=1;j<=max1;j++){
            printf("\n%d ",j);
            for (k=1;k<=max2;k++){
                printf("%s\t",kompfix2[j][k].namkomp);
            }

    }

};

int main (){
LayoutingManual();
max1 = max1 +5;
max2 = max2 +5;
TampilkanLayout();
}

               /* panjangKataBlkg = strlen(kompfix2[j][k].namkomp)-1;
                if (panjangKataBlkg != 0){
                    count++;
                } else {
                printf(" ");}*/
*/
	
};

// Prosedur menampilkan routing rangkaian PCB Dot Matriks
void tampilkanRouting(char route[Rmax][Cmax]){
		for (int i = 0; i <=Rmax; i++) {
			for (int j = 0; j<=Cmax; j++){
				if ( i==0){
					for (int k = 1;k<=Cmax;k++){
						if(k==Cmax){
							printf("\n",k);}
						else {
							printf(" %d",k);}}							
				else {
					if ( j=0){
						prinf("%d",i);}
					else {
						if (route[i-1][j-1] = NULL){
							printf(" ");}
						else {
							printf("%c",route[i-1][j-1]); }}}}}}}


	
// Prosedur melakukan routing manual : meminta input sambungan simpul/node dari user (memilih simbol juga)
void RoutingManual(){
	int i,j,k,s, tempx,tempy;
	char simb,jwb;		//input simbol dan jawaban
	char koord[4];	//input koordinat
	int x,y; 		//kordinat
	char *token;

	tempx=0;
	tempy=0;
	

	printf("Isi `q` atau `Q` untuk kembali ke menu\n");
	printf("Isi `n` atau `N` untuk memulai pada simpul (node) baru\n");
	do {
		printf("Pilih Simbol (!,@,#,$,%,^,&,*,(,)): ");
		scanf("%c",&simb);
		k=1; s=1;
		while (simb !='!'||simb !='@'||simb !='#'||simb !='$'||simb !='%'||simb !='^'||simb !='&'||simb !='*'||simb !=','){
			printf("Ulangi input simbol, simbol salah\n");
			printf("Pilih Simbol (!,@,#,$,%,^,&,*,(,)): ");
			scanf("%c",&simb);
		}

		printf("Kordinat %d: ",k);
		scanf("%s",&koord);
		while ((koord!='q'||koord!='Q')&&(koord!='n'||koord!='N')){
			token = strtok(koord,","); x=atoi(token); 
			token = strtok(NULL,"\n"); y=atoi(token);
			route[s][k][0] = simb;
			route[s][k][1] = tempx; route[s][k][3] = x;
			route[s][k][2] = tempy; route[s][k][4] = y;
			
			if (Hitungjarak(x-tempx,y-tempy)<=2) {
				strcpy(varRouting.simbol[x][y], simb);
			}else{
				if (x==tempx){
					if (tempy<=y) {
						for (j=tempy+1;j<=y; j++){
							strcpy(varRouting.simbol[x][j], simb);							
						}
					} else if (y<tempy){
						for (j=y+1;j<=tempy;j++){
							strcpy(varRouting.simbol[x][j], simb);
						}
					}
				} else if (y==tempy){
					if (tempx<=x) {
						for (i=tempx+1;i<=x; i++){
							strcpy(varRouting.simbol[i][y], simb);
						}
					} else if (x<tempx){
						for (i=x+1;i<=tempx;i++){
							strcpy(varRouting.simbol[i][y], simb);	
						}
					}
				}
			}

			tempy=y;
			tempx=x;
			printf("Kordinat %d: ",k++);
			scanf("%s",&koord);

		}
		s++;

	} while (koord=='n'||koord=='N');

	MenuUtama();	
}

// Prosedur melakukan layout otomatis
void LayoutOtomatis();

// Prosedur melakukan routing otomatis
void RoutingOtomatis();

// Prosedur ....
typedef struct koordinat {
	int kaki[2];
	
} coordinate;

typedef struct transistor {
	coordinate B;
	coordinate E;
	coordinate C;
}BJT;
BJT T;

typedef struct routing {
	coordinate lokasi[2];
}routingCoordinate;


typedef struct komponen {
    routingCoordinate point[40];
} component;

component part[3][5];

void designRuleChecker(component part[3][5]){
		
		int r = 1, c = 1; 
		char **arr = malloc(sizeof(char*)*r); 
		char baca[150];	  
		FILE *drc;
		drc = fopen("DRC.txt","r");
		fgets(baca,150,drc);
		int q =1;
		
		while(!feof(drc)) {
			
			puts(baca);
			for (int i=0;i<strlen(baca);i++){
				 if(baca[i] !=' '){
					 arr[c-1] = malloc(sizeof(char)*q);
					 arr[c-1][i] = baca[i];					
				 }
				 printf("%c\n",arr[c-1][i]);
				 q++;
				 arr[c-1] = realloc(arr[c-1],sizeof(char*)*q);
			 }
			 
			 r++;
			 c++;
			 arr = realloc(arr, sizeof(char*)*r);
			 fgets(baca,150,drc);
			
		}
		fclose(drc);
							 
		
	
		char cekT ={' '};
		int max = 7;		
		int designcek = 0;
		int cekkoordinat = 0;
		for (int i = 1; i<=3;i++){
			for (int j =1;j<=5;j++){
				for (int k = 1;k<=max;k++){
					for (int l = 1;l<=2;l++){
						for (int m = 1;m<=2;m++){
							if (part[i-1][j].point[k-1].lokasi[l-1].kaki[m] == part[i][j].point[k].lokasi[l].kaki[m]){
								cekkoordinat++;
								if(part[i][j].point[k].lokasi[l].kaki[m] == T.B.kaki[m] ){
									cekT = 'B';
								}
								else if (part[i][j].point[k].lokasi[l].kaki[m] == T.E.kaki[m] ){
									cekT = 'E';
								}
								else if (part[i][j].point[k].lokasi[l].kaki[m] == T.C.kaki[m] ){
									cekT = 'C';						
								}
							}
							if (cekkoordinat ==2){							  
								for (int n = 1;n<=max;n++){
									if (arr[n][4] == arr[n-1][4] || arr[n][3] == arr[n-1][3]) {
										if (arr[n][0] == 'C' && arr[n][1] == 'b' && i ==1 && j==1 && cekT =='B'){
											designcek++;
										}
										else if (arr[n][0] == 'C' && arr[n][1] == 'c' && i ==1 && j==2 && cekT =='C'){
											designcek++;
										}
										else if (arr[n][0] == 'C' && arr[n][1] == 'e' && i ==1 && j==3 && cekT =='E'){
											designcek++;
										}
										else if (arr[n][0] == 'R' && arr[n][1] == '1' && i ==2 && j==1 && cekT =='B'){
											designcek++;
										}
										else if (arr[n][0] == 'R' && arr[n][1] == '2' && i ==2 && j==2 && cekT =='B'){
											designcek++;
										}
										else if (arr[n][0] == 'R' && arr[n][1] == 'c' &&i ==2 && j==3 && cekT =='C'){
											designcek++;
										}
										else if (arr[n][0] == 'R' && arr[n][1] == 'e' &&i ==2 && j==4 && cekT =='E'){
											designcek++;
										}
										else if (arr[n][0] == 'J' && arr[n][1] == '1' && i ==3 && j==1){
											designcek++;
										}
										else if (arr[n][0] == 'J' && arr[n][1] == '2' && i ==3 && j==2 && cekT =='C'){
											designcek++;
										}
										else {
											if( i ==1){
												if (j==1){
													printf("ERROR! Kaki %c terhubung dengan Kaki %s \n",arr[n][0],"Cb");
												}
												else if (j==2){
													printf("ERROR! Kaki %c terhubung dengan Kaki %s \n",arr[n][0],"Cc");
												}
												else if (j==3){
													printf("ERROR! Kaki %c terhubung dengan Kaki %s \n",arr[n][0],"Ce");
												}
											else if(i==2){
												if (j==1){
													printf("ERROR! Kaki %c terhubung dengan Kaki %s \n",arr[n][0],"R1");
												}
												else if (j==2){
													printf("ERROR! Kaki %c terhubung dengan Kaki %s \n",arr[n][0],"R2");
												}
												else if (j==3){
													printf("ERROR! Kaki %c terhubung dengan Kaki %s \n",arr[n][0],"Rc");
												}
												else if (j==4){
													printf("ERROR! Kaki %c terhubung dengan Kaki %s \n",arr[n][0],"Re");
												}
											else if(i==3){
												if (j==1){
													printf("ERROR! Kaki %c terhubung dengan Kaki %s \n",arr[n][0],"Ji");
												}
												else if (j==2){
													printf("ERROR! Kaki %c terhubung dengan Kaki %s \n",arr[n][0],"Jo");
												}
												
											}
										}
									}
								}
							}
						
					
				
			else {
				if( i ==1){
					if (j==1){
						printf("ERROR! Kaki %c tidak terhubung dengan Kaki %s \n",arr[j][0],"Cb");
						}
					else if (j==2){
						printf("ERROR! Kaki %c tidak terhubung dengan Kaki %s \n",arr[j][0],"Cc");
						}
					else if (j==3){
						printf("ERROR! Kaki %c tidak terhubung dengan Kaki %s \n",arr[j][0],"Ce");
						}
					}
				else if(i==2){
					if (j==1){
						printf("ERROR! Kaki %c tidak terhubung dengan Kaki %s \n",arr[j][0],"R1");
						}
					else if (j==2){
						printf("ERROR! Kaki %c tidak terhubung dengan Kaki %s \n",arr[j][0],"R2");
						}
					else if (j==3){
						printf("ERROR! Kaki %c tidak terhubung dengan Kaki %s \n",arr[j][0],"Rc");
						}
					else if (j==4){
						printf("ERROR! Kaki %c tidak terhubung dengan Kaki %s \n",arr[j][0],"Re");
					}
					}
				else if(i==3){
					if (j==1){
						printf("ERROR! Kaki %c tidak terhubung dengan Kaki %s \n",arr[j][0],"Ji");
						}
					else if (j==2){
						printf("ERROR! Kaki %c tidak terhubung dengan Kaki %s \n",arr[j][0],"Jo");
					}
					}
					}
				}
			}
			}
		}
	}
}
}
}
		
								


// Prosedur menyimpan kembali variabel ke dalam file eksternalnya
// Jangan lupa buka file untuk di-write lalu tutup file-nya
void SaveProject(){
	fileLayout = fopen(filenameLayout, "w");
	fileRouting = fopen(filenameRouting, "w");

	// Inisiasi file Layout dan Routing, agar formatnya benar
	fprintf (fileLayout, "%d,%d\n", varLayout.colNeff, varLayout.rowNeff);
	fprintf (fileRouting, "%d,%d\n", varRouting.colNeff, varRouting.rowNeff);
	
	for (int i=0; i<varLayout.rowNeff; i++) {
		for (int j=0; j<varLayout.colNeff-1; j++) {
			fprintf (fileLayout, "%s,", varLayout.simbol[i][j]);
			fprintf (fileRouting, "%s,", varRouting.simbol[i][j]);
		}
		fprintf (fileLayout, "%s\n", varLayout.simbol[i][j]);
		fprintf (fileRouting, "%s\n", varRouting.simbol[i][j]);
	}
	
	fclose(fileLayout);
	fclose(fileRouting);
	printf("\n");
}

//Fungsi Menghitung jumlah kuadrat jarak dari koordinat 
int Hitungjarak(int x, int y){
		float r;
		r=x*x+y*y;
		return (r);  
	}
