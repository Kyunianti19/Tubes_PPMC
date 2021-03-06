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
			NewProject();
			MenuUtama();
		} else if (inputMenu == 2) {
			if (LoadProject()==1) {
				MenuUtama();
			} else {
				printf ("Proyek tidak ditemukan\n");
			}
		}
		printf ("\n");
	} while (inputMenu!=3);
}
