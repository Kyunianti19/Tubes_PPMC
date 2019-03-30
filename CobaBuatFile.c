#include <stdio.h>
#include <string.h>

int main () {
	// tipe data bentukan untuk variabel layout dan routing
	typedef struct {
		// simbol akan berisi simbol komponen (R1, R2, Te, dll)
		// dan juga digunakan untuk simbol jalur routing (!, @, #, dll) --> meskipun cuma 1 char
		char simbol[40][40][5];
		int rowNeff; // Nilai efektif jumlah baris yang dipilih user
		int colNeff; // Nilai efektif jumlah kolom yang dipilih user
	} arrayPCB;
	
	arrayPCB varLayout, varRouting;
	FILE *file1;
	FILE *file2;
	int A,B;
	int i,j;
	
//	for (i=0; i<3; i++) {
//		for (j=0; j<2-1; j++) {
//			printf ("Baris ke-%d : ", i+1);
//			scanf ("%s ", varLayout.simbol[i][j]);
//		}
//		scanf ("%s\n", varLayout.simbol[i][j]);
//	}
//	varLayout.simbol[0][1][0] = ' ';
//	varLayout.simbol[2][0][0] = ' ';
//	
//	file1 = fopen ("emitter_layout.csv", "w");
//	fprintf (file1, "%d, %d\n", 2, 3);
//	for (i=0; i<3; i++) {
//		for (j=0; j<2-1; j++) {
//			fprintf (file1, "%s,", varLayout.simbol[i][j]);
//		}
//		fprintf (file1, "%s\n", varLayout.simbol[i][j]);
//	}
//	fclose (file1);
//	file2 = fopen ("emitter_routing.csv", "w");
//	fprintf (file2, "%d, %d\n", 9, 1);
//	fclose (file2);
	char buff[41][200];
	char *token;
	file1 = fopen ("uji_coba2_layout.csv", "r");
//	fscanf (file1, "%d,%d", &A, &B);
//	printf("%d %d\n", A, B);
	//fgets (buff[0], 200, file1);
	for (i=0; i<41; i++) {
		//fscanf (file1, "%s\n", buff[i]);
		fgets (buff[i], 200, file1);
	}
	token = strtok(buff[0], ","); A = atoi(token);
	token = strtok(NULL, "\n"); B = atoi(token);
	
	for (i=1; i<B+1; i++) {
		printf ("%s\n", buff[i]);
//		for (j=0; j<2; j++) {
//			printf ("Ini (%d,%d) : %s\n", i, j, varLayout.simbol[i][j]);
//		}
		//printf ("%s\n", varLayout.simbol[i][j]);
	}
	for (i=1; i<B+1; i++) {
		j = 0;
		token = strtok(buff[i], ",\n"); printf ("token :%scek\n", token);
		strcpy (varLayout.simbol[i][j], token); printf ("var %d: %s\n", j+1, varLayout.simbol[i][j]);
		for (j=1; j<A-1; j++) {
			token = strtok(NULL, ",\n"); printf ("token :%scek\n", token);
			strcpy (varLayout.simbol[i][j], token); printf ("var %d: %s\n", j+1, varLayout.simbol[i][j]);
		}
		token = strtok(NULL, "\n"); printf ("token :%scek\n", token);
		strcpy (varLayout.simbol[i][j], token); printf ("var %d: %s\n", j+1, varLayout.simbol[i][j]);
	}
	fclose (file1);
	//printf ("Ini kosong : %s\n", varLayout.simbol[i][j]);
}
