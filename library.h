/* ------------------------ HEADER FILE ------------------------ */
/* List semua variabel global dan deklarasi fungsi di sini !!!   */

/* Ketentuan penulisan variabel :                                */
/* 1. Nama jelas dan bermakna (jangan cuma A, B, C)              */
/* 2. Dimulai lowercase, jika beda kata gunakan uppercase        */
/*    pada huruf pertama kata selanjutnya untuk memisahkan       */
/* contoh variabel benar : resistorAwal, teganganInput           */
/* 3. Gunakan variabel i, j, atau k untuk proses iterasi		 */
/* Penulisan konstanta pakai #define aja yaaa					 */

/* Ketentuan penulisan fungsi :                                  */
/* 1. Nama jelas dan bermakna (jangan cuma A, B, C)              */
/* 2. Dimulai uppercase, jika beda kata gunakan uppercase        */
/*    pada huruf pertama kata selanjutnya untuk memisahkan       */
/* contoh variabel benar : NewProject, LoadProject               */

/* -----LIST LIBRARY----- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* -----LIST KONSTANTA----- */
// Ukuran PCB dot matriks maksimum
#define dimensiMaks 40 

/* -----LIST STRUKTUR DATA----- */
// tipe data bentukan untuk variabel layout dan routing
typedef struct {
	// simbol akan berisi simbol komponen (R1, R2, Te, dll)
	// dan juga digunakan untuk simbol jalur routing (!, @, #, dll) --> meskipun cuma 1 char
	char simbol[dimensiMaks][dimensiMaks][5];
	int rowNeff; // Nilai efektif jumlah baris yang dipilih user
	int colNeff; // Nilai efektif jumlah kolom yang dipilih user
} arrayPCB;

/* -----LIST VARIABEL GLOBAL----- */
// variabel inputMenu dan inputMode menyimpan nilai pilihan menu masukkan dari user
int inputMenu, inputMode; 
// variabel untuk menyimpan nama proyek serta deklarasi pointer FILE
char namaProyek[30];
char namaDRC[30];
char filenameLayout[50];
char filenameRouting[50];
FILE *fileLayout;
FILE *fileRouting;
FILE *fileDRC;
// variabel yang menyimpan data Layout dan Routing
arrayPCB varLayout, varRouting;

//Variabel untuk menyimpan tracing routing manual
int route[160][5];

/* -----LIST FUNGSI----- */
// Prosedur untuk membuat proyek baru, meminta input nama proyek dan ukuran PCB
void NewProject();

// Prosedur untuk memuat proyek lama (sudah ada filenya)
// Meminta nama file, jika tidak ada file tersebut beri suatu pesan
// File ada maka return 1, jika tidak ada maka return 0
int LoadProject();

// Prosedur untuk menampilkan menu utama dan pilihan modenya
void MenuUtama();

// Prosedur menampilkan layout rangkaian PCB Dot Matriks
void TampilkanLayout();

// Prosedur melakukan layout manual : meminta input komponen dari user
void LayoutingManual();

// Prosedur menampilkan routing rangkaian PCB Dot Matriks
void TampilkanRouting();

// Prosedur melakukan routing manual : meminta input sambungan simpul/node dari user (memilih simbol juga)
void RoutingManual();

// Prosedur melakukan layout otomatis
void LayoutOtomatis();

// Prosedur melakukan routing otomatis
void RoutingOtomatis();

// Prosedur ....
void DesignRuleChecker();

// Prosedur menyimpan kembali variabel ke dalam file eksternalnya
// Jangan lupa buka file untuk di-write lalu tutup file-nya
void SaveProject();

//Fungsi menghitung jarak, mengembalikan jarak dalam kordinat polar
int Hitungjarak(int x, int y);