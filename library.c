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
	int i,j,k, tempx,tempy;
	char simb;		//input simbol
	char koord[4];	//input koordinat
	int x,y; 		//kordinat
	char *token;

	tempx=0;
	tempy=0;
	k=1;
 /*
	int Hitungjarak(int x, int y){
		float r;
		r=x*x+y*y;
		if (r==2) {return 1}
		else {return 0}  ;
	} 
*/

	printf("Isi `q` atau `Q` untuk kembali ke menu\n");
	printf("Isi `n` atau `N` untuk memulai pada simpul (node) baru\n");
	do {
		printf("Pilih Simbol (!,@,#,$,%,^,&,*,(,)): ");
		scanf("%c",&simb);
		while (simb != ('!'||'@'||'#'||'$'||'%'||'^'||'&'||'*'||',')){
			printf("Ulangi input simbol, simbol salah\n");
			printf("Pilih Simbol (!,@,#,$,%,^,&,*,(,)): ");
			scanf("%c",&simb);
		}

		printf("Kordinat %d: ",k);
		scanf("%s",&koord);
		while (koord!=('q'||'Q')&&koord!=('n'||'N')){
			token = strtok(koord,","); x=atoi(token); tempx=x;
			token = strtok(NULL,"\n"); y=atoi(token); tempy=y;
			if (Hitungjarak(x-tempx,y-tempy)=1) {
				strcpy(varRouting.simbol[x][y], simb);
			}else{
				if (x=tempx){
					if (tempy<y) {
						for (j=tempy+1;j<=y; j++){
							strcpy(varRouting.simbol[x][j], simb);
						}
					} else if (y<tempy){
						for (j=y+1;j<=tempy;j++){
							strcpy(varRouting.simbol[x][j], simb);
						}
					}
				} else if (y=tempy){
					if (tempx<x) {
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

			printf("Kordinat %d: ",k++);
			scanf("%s",&koord);

		};
		

	} while (koord==('n'||'N')&&koord!=('q'||'Q')); //quit dan new hal yang berbeda belom di fixed in
	
};

// Prosedur melakukan layout otomatis
void LayoutOtomatis();

// Prosedur melakukan routing otomatis
void RoutingOtomatis();

// Prosedur ....
void designRuleChecker(char mat[Nmax][Nmax]) {
		for (int i = 1; i <=Nmax; i++)
			{
				for (int j = 1; j <=Nmax; j++)
					{
						if (mat[i][j] == mat[i+1][j+1])
							{
							
						}
								


// Prosedur menyimpan kembali variabel ke dalam file eksternalnya
// Jangan lupa buka file untuk di-write lalu tutup file-nya
void SaveProject();
