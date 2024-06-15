#include"Sat.h"
int Varjl[MaxNumVar + 1];
int var, nc;
int Su[10][10];
int main() {
	int op = 1;

	while (op) {
		printf("\n\n\n");//≤Àµ•
        printf("\t\t\t      Main Menu \n");
        printf("\t\t************************************\n");
        printf("\t\t\t1.  Sudoku   2.  SAT\n");
        printf("\t\t\t0.  Exit\n");
        printf("\t\t************************************\n");
        printf("\t\t\tPlease choose your operation[0--2]:\n");
        scanf("%d", &op);
        system("cls");//«Â∆¡
        switch (op) {
           case 1:
            Sudoku();
            break;
        case 2:
            Sat();
            break;
        case 0:
            exit(0);
        default:
            printf("\t\t\tPlease choose your operation again[0--2]:\n");
            scanf("%d", &op);
        }
	}
    return 0;
}
