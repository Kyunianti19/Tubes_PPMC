/* ----------------------- PROGRAM UTAMA ----------------------- */
/* Program Utama, yang akan di compile dan dijalankan            */
/* Ketentuan penulisan variabel :                                */
/* 1. Nama jelas dan bermakna (jangan cuma A, B, C)              */
/* 2. Dimulai lowercase, jika beda kata gunakan uppercase        */
/*    pada huruf pertama kata selanjutnya untuk memisahkan       */
/* contoh variabel benar : resistorAwal, teganganInput           */
/* Penulisan konstanta pakai #define aja yaaa					 */

#include "library.c"

void main () {
	do {
		printf ("Menu:\n");
		printf ("	1. Buat Proyek Baru\n");
		printf ("	2. Muat Proyek dari Berkas\n");
		printf ("	3. Keluar\n");
		printf ("Masukan: "); scanf("%d", &inputMenu);
		if (inputMenu > 3 || inputMenu < 1) {
			printf ("Pilihan menu tidak ada. Masukan ulang!\n");
		} else if (inputMenu == 1) {
			//NewProject();
			//MenuUtama();
		} else if (inputMenu == 2) {
			//LoadProject();
			//Jika file ada, maka muat MenuUtama();
		}
		printf ("\n");
	} while (inputMenu!=3);
}