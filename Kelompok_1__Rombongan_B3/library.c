//***********************************************************// 
// [ Source Code ] // 
// Institution : Institut Teknologi Bandung 
// Name : <Nama Praktikan> 
// File Name : ProgramUtama.c 
// Dependency : stdio.h, math.h, library.c, stdlib.h, math.h, string.h // 
// Description: 
// Please only write 64 characters maximum. If you write 
// more than 64, please write it on the next line. Thanks! // 
// Status: 
// 1. Yunianti Khotimah - 18317014 : NewProject, LoadProject, Gabungin semua, fixing tampilkan layout bugs
// 2. Aminul Solihin - 18317026: Create function Designrulechecker and tampilkan routing, fix bugs in DRC but there is still bug
// 3. Fadhil Musthafa - 18317020 : SaveProject, RoutingManual
// 4. Joshua Adi - 18317032 : TampilkanLayout, LayoutingManual

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
		//printf("Ambil selesai\n"); //Debug
		token = strtok(fileLine[0], ","); varLayout.colNeff = atoi(token);
		token = strtok(NULL, "\n"); varLayout.rowNeff = atoi(token);
		for (i=1; i<varLayout.rowNeff+1; i++) {
			j = 0;
			token = strtok(fileLine[i], ",");
			strcpy (varLayout.simbol[i-1][j], token);// printf ("Ini %d:%s\n", j, varLayout.simbol[i-1][j]); //Debug
			for (j=1; j<varLayout.colNeff-1; j++) {
				token = strtok(NULL, ",");
				strcpy (varLayout.simbol[i-1][j], token);// printf ("Ini %d:%s\n", j, varLayout.simbol[i-1][j]); //Debug
			}
			token = strtok(NULL, "\n");
			strcpy (varLayout.simbol[i-1][j], token);// printf ("Ini %d:%s\n", j, varLayout.simbol[i-1][j]); //Debug
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
			TampilkanLayout();
		} else if (inputMode == 2) {
			//Melakukan layouting manual
			LayoutingManual();
		} else if (inputMode == 3) {
			//Menampilkan routing
			TampilkanRouting();
		} else if (inputMode == 4) {
			//Melakukan routing manual
			RoutingManual();
		} else if (inputMode == 5) {
			//Melakukan layouting otomatis
		} else if (inputMode == 6) {
			//Melakukan routing otomatis
		} else if (inputMode == 7) {
			//Melakukan design rule checker
			designRuleChecker(part);
		} else if (inputMode == 8) {
			//Simpan proyek
			SaveProject();
		}
		printf ("\n");
	} while (inputMode!=8);
}

// Prosedur menampilkan layout rangkaian PCB Dot Matriks
void TampilkanLayout() {
    int i,j,k;
    // printf("%d\n", varLayout.colNeff );// debug
    // printf("%d\n", varLayout.rowNeff );// debug

    for (i=0;i<varLayout.rowNeff;i++){
        for (j=0; j<varLayout.colNeff; j++) {
        	if (varLayout.simbol[i][j][0]!=' ') {
        		strcpy(kompfix2[i+1][j+1].namkomp,varLayout.simbol[i][j]);
        	}
    	}
    }
    printf(" ");
    for (i=1;i<=varLayout.colNeff;i++){
        printf("%d\t",i);}
        for (j=1;j<=varLayout.rowNeff;j++){
            printf("\n%d ",j);
            for (k=1;k<=varLayout.colNeff;k++){
                printf("%s\t",kompfix2[j][k].namkomp);
            }

    }
    // printf("ini col : %d\n", varLayout.colNeff );// debug
    // printf("Ini row : %d\n", varLayout.rowNeff );// debug
};

// Prosedur melakukan layout manual : meminta input komponen dari user
void LayoutingManual(){
	int i, j;
	int validasiOut = 1; 
    int valid =1;
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
                if ((tempkom2.koor1.x<=varLayout.colNeff)&&(tempkom2.koor1.y<=varLayout.rowNeff)){
                    printf("Koordinat Kaki 2 : ");
                    scanf("%d,%d",(&tempkom2.koor2.x),(&tempkom2.koor2.y));
                    if ((tempkom2.koor2.x<=varLayout.colNeff)&&(tempkom2.koor2.y<=varLayout.rowNeff)) {
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
                }
            }

        //bila input kapasitor
        if (tempkom2.komp[0]=='C'){
                printf("Koordinat Kaki 1 : ");
                scanf("%d,%d",(&tempkom2.koor1.x),(&tempkom2.koor1.y));
                if ((tempkom2.koor1.x<=varLayout.colNeff)&&(tempkom2.koor1.y<=varLayout.rowNeff)){
                    printf("Koordinat Kaki 2 : ");
                    scanf("%d,%d",(&tempkom2.koor2.x),(&tempkom2.koor2.y));
                if ((tempkom2.koor2.x<=varLayout.colNeff)&&(tempkom2.koor2.y<=varLayout.rowNeff)){
                    if (((kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp[0] == '\0')&& //validasi posisi kosong
                         (kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp[0] == '\0'))&&
                        ((abs(tempkom2.koor1.x - tempkom2.koor2.x) >= 1 )|| //validasi jarak antar komponen benar
                         (abs(tempkom2.koor1.y - tempkom2.koor2.y) >= 1 )))
                    {
                        strcpy (kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp,tempkom2.komp);
                        strcpy (kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp,tempkom2.komp);
                    } else {
                        printf("peletakan komponen salah, jarak minimum antar kaki kapasitor yaitu 1 lubang\n");
                    }
                }
            }
        }

        //bila input jumper
        if (tempkom2.komp[0]=='J'){
                printf("Koordinat Kaki 1 : ");
                scanf("%d,%d",(&tempkom2.koor1.x),(&tempkom2.koor1.y));
                if ((tempkom2.koor1.x<=varLayout.colNeff)&&(tempkom2.koor1.y<=varLayout.rowNeff)){
                    printf("Koordinat Kaki 2 : ");
                    scanf("%d,%d",(&tempkom2.koor2.x),(&tempkom2.koor2.y));
                    if ((kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp[0] == '\0')&& //validasi posisi kosong
                        (kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp[0] == '\0'))
                        //lupa validasi letak komponen sebelumnya yg udh dimasukin
                    {
                        strcpy(kompfix2[tempkom2.koor1.x][tempkom2.koor1.y].namkomp,tempkom2.komp);
                        strcpy(kompfix2[tempkom2.koor2.x][tempkom2.koor2.y].namkomp,tempkom2.komp);
                    } else {
                        printf("peletakan komponen salah, koordinat sudah terisi\n");
                    }
                }
        }

        //bila input transistor
                if (tempkom2.komp[0]=='T'){
                printf("Koordinat Kaki 1 : ");
                scanf("%d,%d",(&tempkom3.koor1.x),(&tempkom3.koor1.y));
                if ((tempkom3.koor1.x<=varLayout.colNeff)&&(tempkom3.koor1.y<=varLayout.rowNeff)){
                    printf("Koordinat Kaki 2 : ");
                    scanf("%d,%d",(&tempkom3.koor2.x),(&tempkom3.koor2.y));
                    if ((tempkom3.koor2.x<=varLayout.colNeff)&&(tempkom3.koor2.y<=varLayout.rowNeff)){
                        printf("Koordinat Kaki 3 : ");
                        scanf("%d,%d",(&tempkom3.koor3.x),(&tempkom3.koor3.y));
                        if ((tempkom3.koor3.x<=varLayout.colNeff)&&(tempkom3.koor3.y<=varLayout.rowNeff)){
                            if (((kompfix2[tempkom3.koor1.x][tempkom3.koor1.y].namkomp[0] == '\0')&& //validasi posisi kosong
                                 (kompfix2[tempkom3.koor2.x][tempkom3.koor2.y].namkomp[0] == '\0')&&
                                 (kompfix2[tempkom3.koor3.x][tempkom3.koor3.y].namkomp[0] == '\0'))&&
                                ((abs(tempkom3.koor1.x - tempkom3.koor2.x) >= 1 )|| //validasi jarak antar kaki
                                 (abs(tempkom3.koor2.x - tempkom3.koor3.x) >= 1 )||
                                 (abs(tempkom3.koor3.x - tempkom3.koor1.x) >= 1 )||
                                 (abs(tempkom3.koor1.y - tempkom3.koor2.y) >= 1 )||
                                 (abs(tempkom3.koor2.y - tempkom3.koor3.y) >= 1 )||
                                 (abs(tempkom3.koor3.y - tempkom3.koor1.y) >= 1 )))
                            {
                                strcpy(kompfix2[tempkom3.koor1.x][tempkom3.koor1.y].namkomp,tempkom2.komp);
                                strcpy(kompfix2[tempkom3.koor2.x][tempkom3.koor2.y].namkomp,tempkom2.komp);
                                strcpy(kompfix2[tempkom3.koor3.x][tempkom3.koor3.y].namkomp,tempkom2.komp);
                            } else {
                                printf("peletakan komponen salah, jarak minimum antar kaki transistor 1 lubang\n");
                            }
                        }
                    }
                }
        }
        // printf("%d\n", varLayout.colNeff ); //Debug
        // printf("%d\n", varLayout.rowNeff ); //Debug

    //bila input q/Q (Quit)
    if ((tempkom2.komp[0]=='Q')||(tempkom2.komp[0]=='q')){
        validasiOut = 0;
    }

 } while (validasiOut);

    for (i=0;i<varLayout.rowNeff;i++){
        for (j=0; j<varLayout.colNeff; j++) {
        	if (kompfix2[i+1][j+1].namkomp[0]!='\0') {
        		strcpy(varLayout.simbol[i][j],kompfix2[i+1][j+1].namkomp);
        	}
    	}
    }

    //printf("byeeee ! \n"); //NANDAIN MASUK SINI AJA.. HAPUS YAK NANTI
 //MenuUtama();
};

// Prosedur menampilkan routing rangkaian PCB Dot Matriks
void TampilkanRouting() {
	int i, j, k;

	printf("[Layout Rangkaian pada PCB Dot Matriks]\n");
	for (i = 0; i <=varRouting.rowNeff; i++) {
		for (j = 0; j <= varRouting.colNeff; j++) {
			if (i==0 && j==0) {
				printf("   ");
				for (k = 1;k<=varRouting.colNeff;k++){
					if(k==varRouting.colNeff) {
						printf("%3d\n",k); 
					}
					else {
						printf("%3d",k);
					}
				}
				//printf("Sesuatu"); //Debug
			}							
			else {
				//printf("%d", j); //Debug
				if ( j==0) {
					printf("%3d",i);
				}
				else if (i>0) {
					// if (varRouting.simbol[i-1][j-1] = NULL) {
					// 	printf(" ");
					// }
					// else {
					printf("%3c",varRouting.simbol[i-1][j-1][0]); 
					// }
				}
			}
		}
		printf("\n");
	}
}
	

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
		k=1; s=1;
		do {
			printf("\nPilih Simbol (!,@,#,$,%,^,&,*,(,)): ");
			scanf(" %c",&simb);
			if (simb!='!'&&simb!='@'&&simb!='#'&&simb!='$'&&simb!='%'&&simb!='^'&&simb!='&'&&simb!='*'&&simb!=','){
				printf("Ulangi input simbol, simbol salah\n");
			}
		} while (simb!='!'&&simb!='@'&&simb!='#'&&simb!='$'&&simb!='%'&&simb!='^'&&simb!='&'&&simb!='*'&&simb!=',');
			

		printf("Kordinat %d: ",k);
		scanf("%s",&koord);
		while ((strcmp(koord,"q")!=0)&&(strcmp(koord,"Q")!=0)&&(strcmp(koord,"n")!=0)&&(strcmp(koord,"N")!=0)){
			token = strtok(koord,","); x=atoi(token); 
			token = strtok(NULL,""); y=atoi(token);
			route[s][k][0] = simb;
			route[s][k][1] = tempx; route[s][k][3] = x;
			route[s][k][2] = tempy; route[s][k][4] = y;

			if(tempx==0 && tempy==0) {
				varRouting.simbol[x-1][y-1][0] = simb;
			}
			
			if (Hitungjarak(x-tempx,y-tempy)<=1) {
				varRouting.simbol[x-1][y-1][0] = simb;	
			}else{
				if (x==tempx){
					if (tempy<=y) {
						for (j=tempy;j<=y; j++){
							varRouting.simbol[x-1][j-1][0] = simb;		
							//printf ("%s\n", varRouting.simbol[x][j]); //Debug				
						}
					} else if (y<tempy){
						for (j=y;j<=tempy;j++){
							varRouting.simbol[x-1][j-1][0] = simb;
							//printf ("%s\n", varRouting.simbol[x][j]); //Debug	
						}
					}
				} else if (y==tempy){
					if (tempx<=x) {
						for (i=tempx;i<=x; i++){
							varRouting.simbol[i-1][y-1][0] = simb;
							//printf ("%s\n", varRouting.simbol[x][j]); //Debug	
						}
					} else if (x<tempx){
						for (i=x;i<=tempx;i++){
							varRouting.simbol[i-1][y-1][0] = simb;
							//printf ("%s\n", varRouting.simbol[x][j]);	//Debug	
						}
					}
				}
			}

			tempy=y;
			tempx=x;
			k++;
			printf("Kordinat %d: ",k);
			scanf("%s",&koord);

		}
		s++;
	
	} while (strcmp(koord,"n")==0||strcmp(koord,"N")==0);
	
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
	int i, j;

	fileLayout = fopen(filenameLayout, "w");
	fileRouting = fopen(filenameRouting, "w");

	// Inisiasi file Layout dan Routing, agar formatnya benar
	fprintf (fileLayout, "%d,%d\n", varLayout.colNeff, varLayout.rowNeff);
	fprintf (fileRouting, "%d,%d\n", varRouting.colNeff, varRouting.rowNeff);
	// printf("%d\n", varLayout.colNeff ); //Debug
 //    printf("%d\n", varLayout.rowNeff ); //Debug
	
	for (i=0; i<varLayout.rowNeff; i++) {
		for (j=0; j<varLayout.colNeff-1; j++) {
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
