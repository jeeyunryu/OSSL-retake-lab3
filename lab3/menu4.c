#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    char type[20];
    int price;
} Menu;

int selectMenu();
int addMenu(Menu* m);
void readMenu(Menu m[], int cnt);
int updateMenu(Menu* m);
void  listMenu(Menu* m[], int cnt);
int selectNum(Menu* m[], int cnt);
int saveToFile(Menu* m[], int cnt);
int searchName(Menu* m[], int cnt);
int loadData(Menu* m[]);
int deleteMenu(Menu* m[], int cnt);


int main() {
    int menu;
    Menu* m[20];

    int cnt;
    int idx;
    
    int n;
    int cancel;

    cnt = loadData(m);
    idx = cnt;


    while(1) {
        menu = selectMenu();
        if(menu == 0) break;
        if(menu == 1 || menu == 3 || menu == 4 || menu == 5 || menu == 6) {
            if(idx == 0) continue;

            else if(menu == 1) {
                listMenu(m, cnt);
            }

            else if(menu == 3) {
                n = selectNum(m, cnt);
                if(updateMenu(m[n-1])) printf("=> ��������!\n");
            }

            else if(menu == 4) {
                if(deleteMenu(m, cnt) == 1)  {
                    printf("=> ������!\n");
                    idx--;
                }
                else printf("��ҵ�!\n");
                
            }

            else if(menu == 5) {
               if(saveToFile(m, cnt)) printf("=> �����!\n");
            }

            else if (menu == 6) {
                if(searchName(m, cnt) == 0) printf("=> �˻��� ������ ����!\n");
            }
        }
        
        if(menu == 2) {
            m[cnt] = (Menu *)malloc(sizeof(Menu));
            if(addMenu(m[cnt++])) printf("=>�߰���!\n");
            idx++;
        }
        
    }

    printf("\n�����!\n");
    return 0;
}

int deleteMenu(Menu* m[], int cnt) {
    int cancel;
    int n;

    n = selectNum(m, cnt);
    if(n == 0) return -1;
    printf("������ �����Ͻðڽ��ϱ�?(���� :1)");
    scanf("%d", &cancel);
    if(cancel) {
        int no = 0;
        for(int i = 0; i < cnt; i++) {
            if(m[i] == NULL) {
                continue;
            }
            no++;
            if(no == n) {
                free(m[i]);
                m[i] = NULL;
            }
        }
        return 1;
        
    } else return -1;
}

int loadData(Menu* m[]) {
    int j;
    FILE *fp;
    fp = fopen("menu.txt", "rt");
    
    if(fp == NULL) {
        printf("=> ���� ����\n");
        return 0;
    }


    for(j = 0; j < 20; j++) {
        m[j] = (Menu *)malloc(sizeof(Menu));
        if(fscanf(fp, " %s", m[j]->name) == EOF) break;
        fscanf(fp, "%s", m[j]->type);
        fscanf(fp, "%d", &m[j]->price);
    }
    
    fclose(fp);
    printf("�ε� ����!\n");
    return j;
}

int searchName(Menu* m[], int cnt) {
    int no = 0;
    char sname[20];
    printf("�˻��� �̸���? ");
    scanf("%s", sname);
    printf("\n*****************\n");
    for(int i = 0; i < cnt; i++) {
        if (m[i] == NULL) continue;
        no++;
        if(strstr(m[i]->name, sname)) {
            readMenu(m[i], no);
        }
    }
    return no;
}

int saveToFile(Menu* m[], int cnt) {
    FILE* fp;
    fp = fopen("menu.txt", "wt");
    for(int i = 0; i < cnt; i++) {
        if(m[i] == NULL) continue;
        fprintf(fp, "%s %s %d\n", m[i]->name, m[i]->type, m[i]->price);
    }
    fclose(fp);
    return 1;
}

int selectNum(Menu* m[], int cnt) {
    
    int n;
    listMenu(m, cnt);
    printf("\n��ȣ�� (��� :0)? ");
    scanf("%d", &n);
    
    return n;
}

int selectMenu() {
    int menu;
    printf("\n*** PizzaYaho ***\n");
    printf("1. ��ȸ\n2. �߰�\n3. ����\n4. ����\n5. ��������\n6. �̸��˻�\n0. ����\n\n>> ���ϴ� �޴���? ");
    scanf("%d", &menu);
    
    return menu;
}

void listMenu(Menu* m[], int cnt) {
    printf("\n*****************\n");
    int no = 0;
    for(int i = 0; i < cnt; i++){
        if(m[i] == NULL) continue;
        no++;
        readMenu(m[i], no);
    }
    return;
    
}

int addMenu(Menu* m) {
    
    printf("\n�޴�����? ");
    scanf(" %[^\n]s", m->name); 
    printf("�޴�����(P/S/R)? ");
    scanf("%s", m->type);
    printf("������? ");
    scanf("%d", &m->price);
    return 1;
}

void readMenu(Menu m[], int no) {
   printf("%-10d %d %s %s\n", no, m->price, m->type, m->name);
}

int updateMenu(Menu* m) {
    printf("\n�� �޴�����? ");
    scanf(" %[^\n]s", m->name); 
    printf("�� �޴�����(P/S/R)? ");
    scanf("%s", m->type);
    printf("�� ������? ");
    scanf("%d", &m->price);
    return 1;
}



