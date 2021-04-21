//"map-input-480-480.dat"
# define _CRT_SECURE_NO_WARNINGS
//"map-input-480-480.dat"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
#pragma pack(push, 1)

void ROWCOLUMN();
void findMaxMin();
void loadGreyscale();
void outputImage();

int ROW, COLUMN;
int MIN, MAX;
char FILENAME[100];
char PPM[10] = ".ppm";
int ARR[10000][10000];

struct RGB {
	int R;
	int G;
	int B;
};
struct RGB M[10000][10000];

int main(void) {

	ROWCOLUMN();
	findMaxMin();
	loadGreyscale();
	outputImage();

	return 0;
}

void ROWCOLUMN() {
	printf("파일 이름을 입력하시오 : ");
	gets_s(FILENAME, sizeof(FILENAME));

	int row[10];
	int column[10];
	int j = 0, k = 0, count = 0;

	for (int i = 1; i <= 100; i++) {
		if (FILENAME[i] == '-' || FILENAME[i] == '.') {
			count++;
		}
	}

	count = 0;
	for (int i = 1; i <= 100; i++) {
		if (FILENAME[i] == '-' || FILENAME[i] == '.') {
			count++;
		}
		if (count == 2) {
			row[j] = FILENAME[i] - '0';
			j++;
		}
		if (count == 3) {
			column[k] = FILENAME[i] - '0';
			k++;
		}
		if (count >= 5) {
			printf("Error : Problem reading in rows and colums");
			exit(1);
		}
	}

	for (int x = 1; x < j; x++) {
		ROW += row[x] * pow(10, (j - x - 1));
	}

	for (int x = 1; x < k; x++) {
		COLUMN += column[x] * pow(10, (k - x - 1));
	}

}

void findMaxMin() {

	FILE* fp = fopen(FILENAME, "r");
	if (fp == NULL) {
		printf("Error : Unable to open file <%s>", FILENAME);
		exit(1);
	}
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {/////////////////////////////////////////////////////////////////////////////////////////////
			fscanf(fp, "%d", &ARR[i][j]);
		}
	}

	FILE* ffp = fopen(FILENAME, "r");
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			double b;
			double result;
			fscanf(ffp, "%lf", &b);
			int a = (int)b;
			result = b - (double)a;
			if (result == 0.0) {

			}
			else {
				printf("Error : Read a non-integer value");
				exit(1);
			}
		}
	}
	fclose(ffp);

	int count = 0;
	FILE* fpp = fopen(FILENAME, "r");
	if (fpp == NULL) {
		printf("Error : Unable to open file <%s>", FILENAME);
		exit(1);
	}
	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < 10000; j++) {/////////////////////////////////////////////////////////////////////////////////////////////
			int a;
			fscanf(fpp, "%d", &a);
			if (feof(fpp))break;
			count++;
		}
	}
	if (count < (ROW * COLUMN)) {
		printf("Error : End of file reached prior to getting all the required data");
		exit(1);
	}
	else if (count > (ROW * COLUMN)) {
		printf("Error : Too many data points");
		exit(1);
	}
	fclose(fpp);




	int max = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (ARR[i][j] > max) {
				max = ARR[i][j];
			}
		}
	}
	MAX = max;

	int min = 100000;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (ARR[i][j] < min) {
				min = ARR[i][j];
			}
		}
	}
	MIN = min;



}


void loadGreyscale() {

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {

			double W = (double)(ARR[i][j] - MIN);
			double WW = (double)(MAX - MIN);
			int result = (int)(((W / WW)) * 255.0);
			double resultt = (W / WW) * 255.0;
			double resulttt = resultt - (double)result;

			if (resulttt >= 0.5) {
				result += 1;
			}

			M[i][j].R = result;
			M[i][j].G = result;
			M[i][j].B = result;
		}
	}
	printf("계산이 완료되었습니다. 파일을 생성할 동안 기다려주십시요 \n");
}

void outputImage() {

	strcat(FILENAME, PPM);
	FILE* f = fopen(FILENAME, "wb");

	if (f == NULL) {
		printf("Error : Unable to open file <%s>", FILENAME);
		exit(1);
	}

	fprintf(f, "%c%d\n%d %d\n%d\n", 'P', 3, ROW, COLUMN, 255);
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			fprintf(f, "%d %d %d ", M[i][j].R, M[i][j].G, M[i][j].B);
		}
		fprintf(f, "\n");
	}

	fclose(f);

	printf("완료되었습니다. 파일을 열어주세요");
}