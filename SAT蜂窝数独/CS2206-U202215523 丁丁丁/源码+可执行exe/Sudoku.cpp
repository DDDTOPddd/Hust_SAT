#include"Sat.h"

int ToCnf(int a[][10]) {
	int b[10][10];
	FILE* fp;
	fp = fopen("Sudoku.cnf", "w");
	if (fp == NULL) {
		printf("fail!\n");
		return 0;
	}
	fprintf(fp, "p cnf 1000 7407\n");//行数

	b[1][1] = 51; b[1][2] = 41; b[1][3] = 31; b[1][4] = 21; b[1][5] = 11;
	b[2][1] = 61; b[2][2] = 52; b[2][3] = 42; b[2][4] = 32; b[2][5] = 22; b[2][6] = 12;
	b[3][1] = 71; b[3][2] = 62; b[3][3] = 53; b[3][4] = 43; b[3][5] = 33; b[3][6] = 23; b[3][7] = 13;
	b[4][1] = 81; b[4][2] = 72; b[4][3] = 63; b[4][4] = 54; b[4][5] = 44; b[4][6] = 34; b[4][7] = 24; b[4][8] = 14;
	b[5][1] = 91; b[5][2] = 82; b[5][3] = 73; b[5][4] = 64; b[5][5] = 55; b[5][6] = 45; b[5][7] = 35; b[5][8] = 25; b[5][9] = 15;
	b[6][1] = 92; b[6][2] = 83; b[6][3] = 74; b[6][4] = 65; b[6][5] = 56; b[6][6] = 46; b[6][7] = 36; b[6][8] = 26;
	b[7][1] = 93; b[7][2] = 84; b[7][3] = 75; b[7][4] = 66; b[7][5] = 57; b[7][6] = 47; b[7][7] = 37;
	b[8][1] = 94; b[8][2] = 85; b[8][3] = 76; b[8][4] = 67; b[8][5] = 58; b[8][6] = 48;
	b[9][1] = 95; b[9][2] = 86; b[9][3] = 77; b[9][4] = 68; b[9][5] = 59;


	//每一个格子不能填同样的数字  2196
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= a[i][0]; j++) {
			for (int p = 1; p <= 9; p++) {
				for (int q = 1; q < p; q++) {
					fprintf(fp, "-%d%d%d -%d%d%d 0\n", i, j, p, i, j, q);
				}
			}
		}
	}
	

	//1-9行,每一行上的任意两格不能为同样的。  1656
	for (int i = 1; i <= 9; i++) {
		int j = a[i][0];
		for (int k = 1; k <= 9; k++) {
			for (int p = 1; p <= j; p++) {
				for (int q = 1; q < p; q++) {
					fprintf(fp, "-%d%d%d -%d%d%d 0\n", i, p, k, i, q, k);
				}
			}
		}
	}

	//第5行  一定有123456789          9
	for (int k = 1; k <= 9; k++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(fp, "5%d%d ", j, k);
		}
		fprintf(fp, "0\n");
	}

	
	//第4行 12345678  23456789
	//一定有 2345678                  7
	for (int k = 2; k <= 8; k++) {
		for (int j = 1; j <= 8; j++) {
			fprintf(fp, "4%d%d ", j, k);
		}
		fprintf(fp, "0\n");
	}
	//选填（1）（9）                  2
	for (int j = 1; j <= 8; j++) {
		fprintf(fp, "4%d1 4%d9 ", j,j);
	}
	fprintf(fp, "0\n");
	



	//第6行同4     一定有 2345678                  7
	for (int k = 2; k <= 8; k++) {
		for (int j = 1; j <= 8; j++) {
			fprintf(fp, "6%d%d ", j, k);
		}
		fprintf(fp, "0\n");
	}
	//选填（1）（9）                  2
	for (int j = 1; j <= 8; j++) {
		fprintf(fp, "6%d1 6%d9 ", j,j);
	}
	fprintf(fp, "0\n");
	



	//第3行 一定有34567                5
	for (int k = 3; k <= 7; k++) {
		for (int j = 1; j <= 7; j++) {
			fprintf(fp, "3%d%d ", j, k);
		}
		fprintf(fp, "0\n");
	}
	//选填（18） （28） （29）         3
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "3%d1 3%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "3%d2 3%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "3%d2 3%d9 ", j, j);
	}
	fprintf(fp, "0\n");



	//第7行   一定有34567                5
	for (int k = 3; k <= 7; k++) {
		for (int j = 1; j <= 7; j++) {
			fprintf(fp, "7%d%d ", j, k);
		}
		fprintf(fp, "0\n");
	}
	//选填（18） （28） （29）         3
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "7%d1 7%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "7%d2 7%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "7%d2 7%d9 ", j, j);
	}
	fprintf(fp, "0\n");




	//第2行   123456 234567 345678 456789
	//一定有456                         3
	for (int k = 4; k <= 6; k++) {
		for (int j = 1; j <= 6; j++) {
			fprintf(fp, "2%d%d ", j, k);
		}
		fprintf(fp, "0\n");
	}
	//选填 17  27  28  37  38  39       6
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "2%d1 2%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "2%d2 2%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "2%d2 2%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "2%d3 2%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "2%d3 2%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "2%d3 2%d9 ", j, j);
	}
	fprintf(fp, "0\n");
	



	//第8行
	//一定有456                         3
	for (int k = 4; k <= 6; k++) {
		for (int j = 1; j <= 6; j++) {
			fprintf(fp, "8%d%d ", j, k);
		}
		fprintf(fp, "0\n");
	}
	//选填 17  27  28  37  38  39       6
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "8%d1 8%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "8%d2 8%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "8%d2 8%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "8%d3 8%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "8%d3 8%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "8%d3 8%d9 ", j, j);
	}
	fprintf(fp, "0\n");




	//第1行 12345 23456 34567 45678 56789
	//一定有5                             1
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d5 ", j);
	}
	fprintf(fp, "0\n");
	//选填 16  26  27  36  37  38  46  47  48  49           10
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d1 1%d6 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d2 1%d6 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d2 1%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d3 1%d6 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d3 1%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d3 1%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d4 1%d6 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d4 1%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d4 1%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "1%d4 1%d9 ", j, j);
	}
	fprintf(fp, "0\n");





	//第9行 12345 23456 34567 45678 56789
	//一定有5                             1
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d5 ", j);
	}
	fprintf(fp, "0\n");
	//选填 16  26  27  36  37  38  46  47  48  49           10
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d1 9%d6 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d2 9%d6 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d2 9%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d3 9%d6 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d3 9%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d3 9%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d4 9%d6 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d4 9%d7 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d4 9%d8 ", j, j);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "9%d4 9%d9 ", j, j);
	}
	fprintf(fp, "0\n");



	//斜1
	for (int i = 1; i <= 9; i++) {
		int j = a[i][0];
		for (int k = 1; k <= 9; k++) {
			for (int p = 1; p <= j; p++) {
				for (int q = 1; q < p; q++) {
					fprintf(fp, "-%d%d -%d%d 0\n", b[i][p], k, b[i][q], k);
				}
			}
		}
	}

	for (int k = 1; k <= 9; k++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(fp, "%d%d ", b[5][j], k);
		}
		fprintf(fp, "0\n");
	}
	//第4行 12345678  23456789
	//一定有 2345678                  7
	for (int k = 2; k <= 8; k++) {
		for (int j = 1; j <= 8; j++) {
			fprintf(fp, "%d%d ", b[4][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填（1）（9）                  2
	for (int j = 1; j <= 8; j++) {
		fprintf(fp, "%d1 %d9 ", b[4][j], b[4][j]);
	}
	fprintf(fp, "0\n");
	
	//第6行
	for (int k = 2; k <= 8; k++) {
		for (int j = 1; j <= 8; j++) {
			fprintf(fp, "%d%d ", b[6][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填（1）（9）                  2
	for (int j = 1; j <= 8; j++) {
		fprintf(fp, "%d1 %d9 ", b[6][j], b[6][j]);
	}
	fprintf(fp, "0\n");
	



	//第3行 一定有34567                5
	for (int k = 3; k <= 7; k++) {
		for (int j = 1; j <= 7; j++) {
			fprintf(fp, "%d%d ", b[3][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填（18） （28） （29）         3
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d1 %d8 ", b[3][j], b[3][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d2 %d8 ", b[3][j], b[3][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d2 %d9 ", b[3][j], b[3][j]);
	}
	fprintf(fp, "0\n");

	//第7行 一定有34567                5
	for (int k = 3; k <= 7; k++) {
		for (int j = 1; j <= 7; j++) {
			fprintf(fp, "%d%d ", b[7][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填（18） （28） （29）         3
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d1 %d8 ", b[7][j], b[7][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d2 %d8 ", b[7][j], b[7][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d2 %d9 ", b[7][j], b[7][j]);
	}
	fprintf(fp, "0\n");



	//第2行   123456 234567 345678 456789
	//一定有456                         3
	for (int k = 4; k <= 6; k++) {
		for (int j = 1; j <= 6; j++) {
			fprintf(fp, "%d%d ", b[2][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填 17  27  28  37  38  39       6
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d1 %d7 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d2 %d7 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d2 %d8 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d7 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d8 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d9 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");

	//第8行   123456 234567 345678 456789
	//一定有456                         3
	for (int k = 4; k <= 6; k++) {
		for (int j = 1; j <= 6; j++) {
			fprintf(fp, "%d%d ", b[8][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填 17  27  28  37  38  39       6
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d1 %d7 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d2 %d7 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d2 %d8 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d7 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d8 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d9 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");


	//第1行 12345 23456 34567 45678 56789
	//一定有5                             1
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d5 ", b[1][j]);
	}
	fprintf(fp, "0\n");
	//选填 16  26  27  36  37  38  46  47  48  49           10
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d1 %d6 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d2 %d6 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d2 %d7 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d6 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d7 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d8 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d6 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d7 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d8 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d9 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");

	//第9行 12345 23456 34567 45678 56789
	//一定有5                             1
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d5 ", b[9][j]);
	}
	fprintf(fp, "0\n");
	//选填 16  26  27  36  37  38  46  47  48  49           10
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d1 %d6 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d2 %d6 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d2 %d7 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d6 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d7 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d8 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d6 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d7 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d8 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d9 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");

	//斜2
	int x = 15;
	for (int j = 1; j <= 5; j++) {
		b[1][j] = x;
		x += 11;
	}
	x = 14;
	for (int j = 1; j <= 5; j++) {
		b[2][j] = x;
		x += 11;
	}
	b[2][6] = 68;
	x = 13;
	for (int j = 1; j <= 5; j++) {
		b[3][j] = x;
		x += 11;
	}
	b[3][6] = 67; b[3][7] = 77;
	x = 12;
	for (int j = 1; j <= 5; j++) {
		b[4][j] = x;
		x += 11;
	}
	b[4][6] = 66; b[4][7] = 76; b[4][8] = 86;
	x = 11;
	for (int j = 1; j <= 5; j++) {
		b[5][j] = x;
		x += 11;
	}
	x = 65;
	for (int j = 6; j <= 9; j++) {
		b[5][j] = x;
		x += 10;
	}
	x = 21;
	for (int j = 1; j <= 4; j++) {
		b[6][j] = x;
		x += 11;
	}
	x = 64;
	for (int j = 5; j <= 8; j++) {
		b[6][j] = x;
		x += 10;
	}
	x = 31;
	for (int j = 1; j <= 3; j++) {
		b[7][j] = x;
		x += 11;
	}
	x = 63;
	for (int j = 4; j <= 7; j++) {
		b[7][j] = x;
		x += 10;
	}
	x = 41;
	for (int j = 1; j <= 2; j++) {
		b[8][j] = x;
		x += 11;
	}
	x = 62;
	for (int j = 3; j <= 6; j++) {
		b[8][j] = x;
		x += 10;
	}
	x = 51;
	for (int j = 1; j <= 5; j++) {
		b[9][j] = x;
		x += 10;
	}


	for (int i = 1; i <= 9; i++) {
		int j = a[i][0];
		for (int k = 1; k <= 9; k++) {
			for (int p = 1; p <= j; p++) {
				for (int q = 1; q < p; q++) {
					fprintf(fp, "-%d%d -%d%d 0\n", b[i][p], k, b[i][q], k);
				}
			}
		}
	}

	for (int k = 1; k <= 9; k++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(fp, "%d%d ", b[5][j], k);
		}
		fprintf(fp, "0\n");
	}
	//第4行 12345678  23456789
	//一定有 2345678                  7
	for (int k = 2; k <= 8; k++) {
		for (int j = 1; j <= 8; j++) {
			fprintf(fp, "%d%d ", b[4][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填（1）（9）                  2
	for (int j = 1; j <= 8; j++) {
		fprintf(fp, "%d1 %d9 ", b[4][j], b[4][j]);
	}
	fprintf(fp, "0\n");

	//第6行
	for (int k = 2; k <= 8; k++) {
		for (int j = 1; j <= 8; j++) {
			fprintf(fp, "%d%d ", b[6][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填（1）（9）                  2
	for (int j = 1; j <= 8; j++) {
		fprintf(fp, "%d1 %d9 ", b[6][j], b[6][j]);
	}
	fprintf(fp, "0\n");



	//第3行 一定有34567                5
	for (int k = 3; k <= 7; k++) {
		for (int j = 1; j <= 7; j++) {
			fprintf(fp, "%d%d ", b[3][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填（18） （28） （29）         3
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d1 %d8 ", b[3][j], b[3][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d2 %d8 ", b[3][j], b[3][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d2 %d9 ", b[3][j], b[3][j]);
	}
	fprintf(fp, "0\n");

	//第7行 一定有34567                5
	for (int k = 3; k <= 7; k++) {
		for (int j = 1; j <= 7; j++) {
			fprintf(fp, "%d%d ", b[7][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填（18） （28） （29）         3
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d1 %d8 ", b[7][j], b[7][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d2 %d8 ", b[7][j], b[7][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 7; j++) {
		fprintf(fp, "%d2 %d9 ", b[7][j], b[7][j]);
	}
	fprintf(fp, "0\n");



	//第2行   123456 234567 345678 456789
	//一定有456                         3
	for (int k = 4; k <= 6; k++) {
		for (int j = 1; j <= 6; j++) {
			fprintf(fp, "%d%d ", b[2][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填 17  27  28  37  38  39       6
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d1 %d7 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d2 %d7 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d2 %d8 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d7 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d8 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d9 ", b[2][j], b[2][j]);
	}
	fprintf(fp, "0\n");

	//第8行   123456 234567 345678 456789
	//一定有456                         3
	for (int k = 4; k <= 6; k++) {
		for (int j = 1; j <= 6; j++) {
			fprintf(fp, "%d%d ", b[8][j], k);
		}
		fprintf(fp, "0\n");
	}
	//选填 17  27  28  37  38  39       6
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d1 %d7 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d2 %d7 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d2 %d8 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d7 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d8 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 6; j++) {
		fprintf(fp, "%d3 %d9 ", b[8][j], b[8][j]);
	}
	fprintf(fp, "0\n");


	//第1行 12345 23456 34567 45678 56789
	//一定有5                             1
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d5 ", b[1][j]);
	}
	fprintf(fp, "0\n");
	//选填 16  26  27  36  37  38  46  47  48  49           10
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d1 %d6 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d2 %d6 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d2 %d7 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d6 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d7 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d8 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d6 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d7 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d8 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d9 ", b[1][j], b[1][j]);
	}
	fprintf(fp, "0\n");

	//第9行 12345 23456 34567 45678 56789
	//一定有5                             1
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d5 ", b[9][j]);
	}
	fprintf(fp, "0\n");
	//选填 16  26  27  36  37  38  46  47  48  49           10
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d1 %d6 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d2 %d6 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d2 %d7 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d6 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d7 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d3 %d8 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d6 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d7 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d8 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	for (int j = 1; j <= 5; j++) {
		fprintf(fp, "%d4 %d9 ", b[9][j], b[9][j]);
	}
	fprintf(fp, "0\n");
	
	fclose(fp);
	return 1;

}



void Sudoku() {
	ClauseList* S = NULL;
	Node x;
	x.next = NULL;

	int op=1,ddd=0;
	char filename[300];
	Su[1][0] = 5;
	Su[2][0] = 6;
	Su[3][0] = 7;
	Su[4][0] = 8;
	Su[5][0] = 9;
	Su[6][0] = 8;
	Su[7][0] = 7;
	Su[8][0] = 6;
	Su[9][0] = 5;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= Su[i][0]; j++) {
			Su[i][j] = 0;
		}
	}
	while (op) {
		system("cls");
		printf("\n\n\n");//菜单
		printf("\t\t\t      Sudoku问题 \n");
		printf("\t\t************************************\n");
		printf("\t\t1. 初始化  2.求解  3.写Sudokucnf\n");
		printf("\t\t0.  Exit\n");
		printf("\t\t************************************\n");
		printf("\t\tPlease choose your operation[0--3]:\n");
		scanf("%d", &op);
		
		switch (op) {
		case 1:
			printf("请输入文件名：\n");
			scanf("%s", filename);
			if (ddd = First(filename)) {
				printf("OK!\n");
				Tu();

			}
			else {
				for (int i = 1; i <= 9; i++) {
					for (int j = 1; j <= Su[i][0]; j++) {
						Su[i][j] = 0;
					}
				}
				printf("Fail!");
			}
			getchar(); getchar();
			break;
		case 2:
			ddd = ReadSudoku(&S);
			for (int i = 1; i <= MaxNumVar; i++) {
				Varjl[i] = Unknow;
			}
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= Su[i][0]; j++) {
					if (Su[i][j] != 0) {
						x.data = Su[i][j] + 10 * j + 100 * i;
						x.negated = 1;
						//printf("%d已经添加\n", x.data);
						Add(&S, x);
					}
				}
			}

			ddd = DPLL(&S);
			if (ddd == 0) {
				printf("无解！\n");
			}
			else {
				printf("success!\n");
				for (int k = 111; k <= 1000; k++) {
					if (Varjl[k] == True) {
						int p, q, r;
						r = k % 10;
						q = (k / 10) % 10;
						p = k / 100;
						Su[p][q] = r;
					}
				}
				Tu();
			}
			getchar(); getchar();
			break;
		case 3:
			ddd = ToCnf(Su);
			if (ddd == 1) {
				printf("OK!");
			}
			getchar(); getchar();
			break;
		case 0:
			exit(0);
		default:
			printf("\t\t\tPlease choose your operation again[0--1]:\n");
			scanf("%d", &op);
		}
	}
	return ;
}


int First(char* filename) {
	
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("ERROR!\n");
		return 0;
	}
	int a, b, c;
	fscanf(fp, "%d %d %d", &a,&b,&c);
	while (a != 0) {
		Su[a][b] = c;
		fscanf(fp, "%d %d %d", &a, &b, &c);
	}
	fclose(fp);
	return 1;
}

void Tu() {
	int x;
	for (int i = 1; i <= 9; i++) {
		x = 9 - Su[i][0];
		if (i <= 5) {
			for (int k = 0; k < x; k++) printf("  ");
		}
		else {
			for (int k = 1; k < x; k++) printf("  ");
		}
		
		if (i <= 5) {
			for (int k = 0; k < Su[i][0]; k++) {
				printf(" / \\");
			}
			printf("\n");
		}
		else {
			for (int k = 0; k <= Su[i][0]; k++) {
				printf(" \\ /");
			}
			printf("\n");
		}
		for (int k = 0; k < x; k++) printf("  ");
		for (int j = 1; j <= Su[i][0]; j++) {
			if (Su[i][j] == 0) {
				printf("| . ");
			}
			else {
				printf("| %d ",Su[i][j]);
			}
		}
		printf("|\n");

	}
	printf("         \\ / \\ / \\ / \\ / \\ /\n");
}

int ReadSudoku(ClauseList** s) {
	FILE* fp = fopen("Sudoku.cnf", "r");
	if (fp == NULL) {
		printf("ERROR!\n");
		return 0;
	}
	int aa, bb;

	int num = 1, m;
	char c;
	//CnfSign k;
	ClauseList* h = NULL;
	ClauseList* lp = NULL;
	Node* hh = NULL;
	Node* pp = NULL;


	fscanf(fp, "%c", &c);
	while (c == 'c') {//注释行
		while (c != '\n' && c != '\r') {
			fscanf(fp, "%c", &c);
		}
		if (c == '\n') fscanf(fp, "%c", &c);
	}

	if (c == 'p') {//读p行
		fscanf(fp, " cnf %d %d", &aa, &bb);
	}

	//二维尾插法读入nc行数据
	h = (ClauseList*)malloc(sizeof(ClauseList));
	fscanf(fp, "%d", &m);
	if (m == 0) {
		free(h);
		return 0;
	}
	hh = (Node*)malloc(sizeof(Node));
	if (m > 0) {
		hh->data = abs(m);
		hh->negated = 1;
	}
	if (m < 0) {
		hh->data = abs(m);
		hh->negated = 0;
	}
	hh->next = NULL;

	pp = hh;

	while (1) {
		fscanf(fp, "%d", &m);
		if (m == 0) break;

		pp->next = (Node*)malloc(sizeof(Node));
		pp = pp->next;
		if (m > 0) {
			pp->data = abs(m);
			pp->negated = 1;
		}
		if (m < 0) {
			pp->data = abs(m);
			pp->negated = 0;
		}
		pp->next = NULL;
		num++;
	}

	h->w = num;
	h->p = hh;
	h->next = NULL;
	lp = h;

	for (int i = 1; i < bb; i++) {
		num = 1;
		lp->next = (ClauseList*)malloc(sizeof(ClauseList));
		lp = lp->next;
		fscanf(fp, "%d", &m);

		hh = (Node*)malloc(sizeof(Node));
		if (m > 0) {
			hh->data = abs(m);
			hh->negated = 1;
		}
		if (m < 0) {
			hh->data = abs(m);
			hh->negated = 0;
		}
		hh->next = NULL;
		pp = hh;

		while (1) {
			fscanf(fp, "%d", &m);
			if (m == 0) break;

			pp->next = (Node*)malloc(sizeof(Node));
			pp = pp->next;
			if (m > 0) {
				pp->data = abs(m);
				pp->negated = 1;
			}
			if (m < 0) {
				pp->data = abs(m);
				pp->negated = 0;
			}
			pp->next = NULL;
			num++;
		}

		lp->w = num;
		lp->p = hh;
		lp->next = NULL;
	}

	*s = h;
	fclose(fp);
	return 1;
}