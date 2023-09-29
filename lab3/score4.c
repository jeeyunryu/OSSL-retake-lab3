#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[20];
    int kor, eng, math;
} Score;

int selectMenu();
int addScore(Score *s);
void readScore(Score s[], int no);
int updateScore(Score *s);
void listScore(Score* s[], int cnt);
int selectNum(Score* s[], int cnt);
int saveToFile(Score* s[], int cnt);
int searchName(Score* s[], int cnt);
int loadData(Score* s[]);
int deleteScore(Score* s[], int cnt);

int main(void){
    Score* s[20];
    int count = 0, menu;
    int idx;
    int cnt;

    cnt = loadData(s);
    idx = cnt;

    while (1){
        menu = selectMenu();
        if (menu == 0) break;
        
        else if (menu == 2){
            s[idx] = (Score *)malloc(sizeof(Score));
            if(addScore(s[idx++])) {
                printf("=> �߰���!\n"); 
                cnt++;
            }

        }

        if(menu == 1 || menu == 3 || menu == 4 || menu == 5) {
            if(idx == 0) continue;
            else if (menu == 1) listScore(s, cnt);

            else if (menu == 3){
                int n;
                n = selectNum(s, cnt);
                if(n == 0) continue;

                if(updateScore(s[n-1]) == 1) printf("=> ��������!\n");
            }
            else if (menu == 4){
                if(deleteScore(s, cnt) == 1) {
                     printf("=> ������!\n");
                     idx--;
                }
                else {
                    printf("=> ��ҵ�!\n");
                }
                
                
            }

            else if (menu == 5) {
                if(saveToFile(s, cnt)) printf("=> �����!\n");
            }

            
        }
        
        else if(menu ==6) {
                
                if(searchName(s, cnt) == 0) printf("=> �˻��� ������ ����!!\n");
            }

        
    }
    printf("\n�����!\n");
    return 0;
}

int deleteScore(Score* s[], int cnt) {
    int cancel;
    int n;

    n = selectNum(s, cnt);
    if(n == 0) return -1;
    printf("���� �����Ͻðڽ��ϱ�?(���� :1)");
    scanf("%d", &cancel);
    if(cancel) {
        
        int no = 0;
        for(int i = 0; i < cnt; i++) {
            if(s[i] == NULL) {
                continue;
            }
            no++;
            if(no == n) {
                free(s[i]);
                s[i] = NULL;
            }
        }
        return 1;
        
    } else return -1;
}

int loadData(Score* s[]){
    int j = 0;
    FILE *fp;
    fp = fopen("score.txt", "rt");

    if(fp == NULL) {
        printf("=> ���� ����\n");
        return 0;
    }
    
    else {
         for(; j < 20; j++) {
            s[j] = (Score *)malloc(sizeof(Score));
        
            if(fscanf(fp, "%s", s[j]->name)== EOF) break; 
            
            fscanf(fp, "%d", &s[j]->kor);
            fscanf(fp, "%d", &s[j]->eng);
            fscanf(fp, "%d", &s[j]->math);
        }
        printf("=> �ε� ����!\n");
    
    }
   fclose(fp);
   return j;
}

int searchName(Score* s[], int cnt) {
    char sname[20];
    int no = 0;
    
    printf("���ϴ� �̸���? ");
    scanf("%s", sname);
    printf("\nNo Name Kor Eng Math Sum Avg\n");
    printf("================================\n");
    for(int i = 0; i < cnt; i++) {
        if(s[i] == NULL) continue;
        no++;
        
        if(strstr(s[i]->name, sname)) {
            readScore(s[i], no);
        }
    }

    return no;
}

int selectMenu(){
    int menu;
    printf("\n*** �������� ***\n");
    printf("1. ��ȸ\n2. �߰�\n3. ����\n4. ����\n5. ��������\n6. �̸��˻�\n0. ����\n\n>> ���ϴ� �޴���? ");
    scanf("%d", &menu);
    return menu;
}

int saveToFile(Score* s[], int cnt) {
    FILE *fp;
    fp = fopen("score.txt", "wt");
    for(int i = 0; i < cnt; i++) {
        if(s[i] == NULL) continue;
        fprintf(fp, "%s %d %d %d\n", s[i]->name, s[i]->kor, s[i]->eng, s[i]->math);
    }
    fclose(fp);
    return 1;
}

int selectNum(Score* s[], int cnt) {
    int n;
    listScore(s, cnt);
    printf("\n��ȣ�� (��� :0)? ");
    scanf("%d", &n);
    return n;
}

int addScore(Score* s) {
    printf("�̸���? ");
    scanf("%s", s->name);
    printf("�����? ");
    scanf("%d", &s->kor);
    printf("�����? ");
    scanf("%d", &s->eng);
    printf("������? ");
    scanf("%d", &s->math);
    return 1;

}

void listScore(Score* s[], int cnt) {
    
    int no = 0;

    printf("\nNo Name Kor Eng Math Sum Avg\n");
    printf("================================\n");

    for(int i = 0; i < cnt; i++) {
        
        if(s[i] == NULL) continue;
        no++;
        readScore(s[i], no);
    }
}

void readScore(Score* s, int no) {
    int sum = 0;
    double avg;

    sum = s->kor + s->eng + s->math;
    avg = sum / 3.0;
    printf("%d %s %d %d %d %d %.1f\n", no , s->name, s->kor, s->eng, s->math, sum, avg); 
}


int updateScore(Score* s) {
    printf("�̸���? ");
    scanf("%s", s->name);
    printf("�����? ");
    scanf("%d", &s->kor);
    printf("�����? ");
    scanf("%d", &s->eng);
    printf("������? ");
    scanf("%d", &s->math);
    return 1;

}
