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

}

// Prosedur untuk memuat proyek lama (sudah ada filenya)
// Meminta nama file, jika tidak ada file tersebut beri suatu pesan
// File ada maka return 1, jika tidak ada maka return 0
int LoadProject() {

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
void LayoutingManual();
// Prosedur menampilkan routing rangkaian PCB Dot Matriks
void TampilkanRouting();
// Prosedur melakukan routing manual : meminta input sambungan simpul/node dari user (memilih simbol juga)
void RoutingManual();