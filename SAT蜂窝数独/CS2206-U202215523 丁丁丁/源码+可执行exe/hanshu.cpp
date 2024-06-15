#include"Sat.h"


int Sat() {
	int op = 1,ddd, savejudge;
	clock_t start, end;
	double time;
	char filename[300];
	Node ccs;
	ClauseList* S = NULL;
	ClauseList* cs;
	while (op) {
		system("cls");
		printf("\n\n\n");//菜单
		printf("\t\t\t      SAT问题 \n");
		printf("\t\t************************************\n");
		printf("\t\t1. 从cnf中读取  2.DPLL求解  3.遍历\n");
		printf("\t\t0.  Exit\n");
		printf("\t\t************************************\n");
		printf("\t\tPlease choose your operation[0--3]:\n");
		scanf("%d", &op);
		//清屏
		switch (op) {
		case 2:
			for (int i = 1; i <= MaxNumVar; i++) {
				Varjl[i] = Unknow;
			}
			start = clock();

			ddd = DPLL2(&S);   

			end = clock();
			time = (double)(end - start)*1000 / CLOCKS_PER_SEC;
			if (ddd == 0) {
				savejudge=Save(0,filename,time);
				printf("无解！\n");
			}
			else {
				printf("成功！\n");
				savejudge=Save(1,filename,time);
				for (int i = 1; i <= var; i++) {
					if (Varjl[i] == True) {
						printf("%d %d   ", i,Varjl[i]);
					}
					else {
						printf("-%d %d   ", i,Varjl[i]);
					}
				}
			}
			printf("\n本次用时 %.6f  ms\n", time);
			if (savejudge == 1) {
				printf("已保存到同名文件中");
			}
			if (savejudge == 0) {
				printf("保存失败！");
			}
			getchar(); getchar();
			break;

		case 1:
			printf("请输入cnf文件名：\n");
			scanf("%s", filename);
			ddd = Readcnf(filename, &S,&var,&nc);
			if (ddd == 1) printf("读取成功！");
			else {
				printf("读取失败！");
				S = NULL;
			}

			getchar(); getchar();
			break;

		case 3:
			if (S == NULL) {
				printf("请先输入cnf文件\n");
			}
			else {
				PrintfCnf(S);
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
}

int DPLL(ClauseList** S) {
	ClauseList* qian;
	Node x;
	qian = IsSingleClause(*S);
	while (qian!=NULL) {
		x.data = qian->p->data;
		x.negated = qian->p->negated;
		x.next = NULL;
		qian->w = -1;
		if (x.negated == 1) {
			Varjl[x.data] = True;
		}
		if (x.negated == 0) {
			Varjl[x.data] = False;
		}
		Propagation(S, x);
		if (IsOK(*S)) return 1;
		else if (IsEmpty(*S)) return 0;
		qian= IsSingleClause(*S);
	}
	qian = *S;
	while (qian != NULL) {
		if (qian->w != -1) {
			x.data = qian->p->data;
			x.negated = qian->p->negated;
			x.next = NULL;
		}
		qian = qian->next;
	}
	

	ClauseList* Sc = Copy(*S);

	//printf("选取了%d %d\n", x.data, x.negated);
	Add(&Sc, x);
	if (DPLL(&Sc)) {
		ClearList(&Sc);
		return 1;
	}
	else {
		ClearList(&Sc);
		ClauseList* Sc2 = Copy(*S);
		if (x.negated == 1) x.negated = 0;
		else x.negated = 1;
		Add(&Sc2, x);
		return DPLL(&Sc2);
	}

}

int check() {
	for (int i = 1; i <= var; i++) {
		if (Varjl[i] != True && Varjl[i] != False) return 0;
	}
	return 1;
}

ClauseList* IsSingleClause(ClauseList* S) { //找单子句
	ClauseList* l = S;
	while (l != NULL) {
		if (l->w == 1) return l;
		l = l->next;
	}
	return NULL;
}

ClauseList* Copy(ClauseList* S) {
	ClauseList* q = NULL, * c = NULL;
	ClauseList* h = NULL;
	Node* n = NULL, * cc = NULL;
	q = S;
	h = (ClauseList*)malloc(sizeof(ClauseList));

	h->next = NULL;
	h->w = q->w;

	if (q->p == NULL) {
		h->p = NULL;
	}
	else {
		h->p = (Node*)malloc(sizeof(Node));
		h->p->data = q->p->data;
		h->p->negated = q->p->negated;
		h->p->next = NULL;
		n = q->p->next;
		cc = h->p;
		while (n != NULL) {
			cc->next = (Node*)malloc(sizeof(Node));
			cc = cc->next;
			cc->data = n->data;
			cc->negated = n->negated;
			cc->next = NULL;
			n = n->next;
		}
	}

	c = h;
	q = q->next;
	while (q != NULL) {
		c->next=(ClauseList*)malloc(sizeof(ClauseList));
		c = c->next;

		c->w = q->w;

		if (q->p == NULL) {
			c->p = NULL;
		}
		else {
			c->p = (Node*)malloc(sizeof(Node));
			c->p->data = q->p->data;
			c->p->negated = q->p->negated;
			c->p->next = NULL;
			n = q->p->next;
			cc = c->p;
			while (n != NULL) {
				cc->next = (Node*)malloc(sizeof(Node));
				cc = cc->next;
				cc->data = n->data;
				cc->negated = n->negated;
				cc->next = NULL;
				n = n->next;
			}
		}
		q = q->next;
		
	}
	c->next= NULL;
	return h;
}

int IsOK(ClauseList* S) {
	ClauseList* l = S;
	while (l != NULL) {
		if (l->w != -1) return 0;
		l = l->next;
	}
	return 1;
}

int IsEmpty(ClauseList* S) { //有没有空子句
	ClauseList* l = S;
	while (l != NULL) {
		if (l->w == 0) return 1;
		l = l->next;
	}
	return 0;
}

void Propagation(ClauseList** S, Node x) {//单子句传播
	ClauseList* current = *S;
	ClauseList* pre = NULL;
	while (current != NULL) {
		Node* prev = NULL;
		Node* current_p = current->p;
		if (current->w > 0) {
			while (current_p != NULL) {
				if (current_p->data == x.data) {
					if (current_p->negated == x.negated) {
						current->w = -1;
						break;
					}
					else {
						if (prev == NULL) {
							
							current->p = current_p->next;
							free(current_p);
							current_p = current->p;
						}
						else {
							prev->next = current_p->next;
							free(current_p);
							current_p = prev->next;
						}
						(current->w)--;
					}
				}
				else {
					prev = current_p;
					current_p = current_p->next;
				}
			}
		}
		pre = current;
		current = current->next;
	}
}

int Readcnf(char* filename, ClauseList** s,int* var,int* nc) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("ERROR!\n");
		return 0;
	}
	int aa, bb;

	int num=1,m;
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
	*var = aa;
	*nc = bb;

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

void PrintfCnf(ClauseList* S) {
	ClauseList* l;
	Node* q;
	l = S;
	while (l != NULL) {
		//printf("%d   ", l->w);
		q = l->p;
		while (q != NULL) {
			if (q->negated == 1) printf("%d ", q->data);
			else printf("-%d ", q->data);
			q = q->next;
		}
		printf("    ");
		l = l->next;
	}
}

//释放函数*2
void ClearNodeList(Node* node) {
	if (node == NULL) {
		return;
	}

	Node* current = node;
	while (current != NULL) {
		Node* temp = current;
		current = current->next;
		free(temp);
	}
}

void ClearList(ClauseList** S) {
	if (S == NULL || *S == NULL) {
		return;
	}

	ClauseList* current = *S;
	while (current != NULL) {
		ClauseList* temp = current;
		current = current->next;
		ClearNodeList(temp->p);  // 释放 Node 链表内存
		free(temp);
	}

	*S = NULL;  // 设置 S 为 NULL，确保外部指针不再引用已释放的内存
}

//加单子句函数
void Add(ClauseList** S, Node x) {
	ClauseList* l;
	l = *S;
	while (l->next != NULL) {
		l = l->next;
	}
	
	l->next= (ClauseList*)malloc(sizeof(ClauseList));
	l = l->next;
	l->p= (Node*)malloc(sizeof(Node));
	l->p->data = x.data;
	l->p->negated = x.negated;
	l->p->next = NULL;
	l->next = NULL;
	l->w = 1;
	return ;
}

//保存函数
int Save(int a, char* filename,double time) {
	int l = strlen(filename);
	int i = 0;
	char nf[300];
	strcpy(nf, filename);
	strcat(nf, ".res");
	FILE* fp;
	fp = fopen(nf, "w");
	if (fp == NULL) {
		return 0;
	}
	if (a == 0) {
		fprintf(fp, "s  0\n");
		fprintf(fp, "v  none\n");
		fprintf(fp, "t  %.6f  ms\n",time);
	}
	if (a == 1) {
		fprintf(fp, "s  1\n");
		fprintf(fp, "v  ");
		for (int i = 1; i <= var; i++) {
			if (Varjl[i] == True) {
				fprintf(fp,"%d  ", i);
			}
			else {
				fprintf(fp,"-%d  ", i);
			}
		}
		fprintf(fp, "\n");
		fprintf(fp, "t  %.6f  ms\n", time);
	}
	fclose(fp);
	printf("%s\n", nf);
	return 1;
}

int DPLL2(ClauseList** S) {
	ClauseList* qian;
	Node x;
	qian = IsSingleClause(*S);
	while (qian != NULL) {
		x.data = qian->p->data;
		x.negated = qian->p->negated;
		x.next = NULL;
		qian->w = -1;
		if (x.negated == 1) {
			Varjl[x.data] = True;
		}
		if (x.negated == 0) {
			Varjl[x.data] = False;
		}
		Propagation(S, x);
		if (IsOK(*S)) return 1;
		else if (IsEmpty(*S)) return 0;
		qian = IsSingleClause(*S);
	}
	qian = *S;
	int num = 1000;
	while (qian != NULL) {
		if (qian->w < num) {
			num = qian->w;
		}
		qian = qian->next;
	}
	qian = *S;
	while (qian != NULL) {
		if (qian->w == num) {
			x.data = qian->p->data;
			x.negated = qian->p->negated;
			break;
		}
		qian = qian->next;
	}

	ClauseList* Sc = Copy(*S);

	//printf("选取了%d %d\n", x.data, x.negated);
	Add(&Sc, x);
	if (DPLL(&Sc)) {
		ClearList(&Sc);
		return 1;
	}
	else {
		ClearList(&Sc);
		ClauseList* Sc2 = Copy(*S);
		if (x.negated == 1) x.negated = 0;
		else x.negated = 1;
		Add(&Sc2, x);
		return DPLL(&Sc2);
	}

}