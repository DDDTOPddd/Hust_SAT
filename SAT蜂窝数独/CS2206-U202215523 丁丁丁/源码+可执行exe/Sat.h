#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define Unknow -1
#define False 0
#define True 1
#define None 2

#define MaxNumVar 1000

extern int Varjl[MaxNumVar + 1];
extern int var, nc;

extern int Su[10][10];//��������

typedef struct Node {
	int data;
	int negated;//1��  0��+
	struct Node* next;
}Node;

typedef struct clauselist {
	int w;//�Ӿ��Ԫ������-1����ɾ����
	Node* p;
	clauselist* next;
}ClauseList;

int Readcnf(char* filename, ClauseList** s, int* var, int* nc);
int Sat();
int DPLL(ClauseList** S);
int DPLL2(ClauseList** S);
void Propagation(ClauseList** S, Node x);//���Ӿ䴫��
ClauseList* Copy(ClauseList* S);
void ClearNodeList(Node* node);
void ClearList(ClauseList** S);
void PrintfCnf(ClauseList* S);
void Add(ClauseList** S, Node x);
int Save(int a, char* filename, double time);
int check();
int IsEmpty(ClauseList* S);//��û�п��Ӿ�
int IsOK(ClauseList* S);
ClauseList* IsSingleClause(ClauseList* S);


void Sudoku();
int ToCnf(int a[][10]);
int First(char* filename);
void Tu();
int ReadSudoku(ClauseList** s);
