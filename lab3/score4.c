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
                printf("=> 추가됨!\n"); 
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

                if(updateScore(s[n-1]) == 1) printf("=> 수정성공!\n");
            }
            else if (menu == 4){
                if(deleteScore(s, cnt) == 1) {
                     printf("=> 삭제됨!\n");
                     idx--;
                }
                else {
                    printf("=> 취소됨!\n");
                }
                
                
            }

            else if (menu == 5) {
                if(saveToFile(s, cnt)) printf("=> 저장됨!\n");
            }

            
        }
        
        else if(menu ==6) {
                
                if(searchName(s, cnt) == 0) printf("=> 검색된 데이터 없음!!\n");
            }

        
    }
    printf("\n종료됨!\n");
    return 0;
}

int deleteScore(Score* s[], int cnt) {
    int cancel;
    int n;

    n = selectNum(s, cnt);
    if(n == 0) return -1;
    printf("정말 삭제하시겠습니까?(삭제 :1)");
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
        printf("=> 파일 없음\n");
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
        printf("=> 로딩 성공!\n");
    
    }
   fclose(fp);
   return j;
}

int searchName(Score* s[], int cnt) {
    char sname[20];
    int no = 0;
    
    printf("원하는 이름은? ");
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
    printf("\n*** 점수계산기 ***\n");
    printf("1. 조회\n2. 추가\n3. 수정\n4. 삭제\n5. 파일저장\n6. 이름검색\n0. 종료\n\n>> 원하는 메뉴는? ");
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
    printf("\n번호는 (취소 :0)? ");
    scanf("%d", &n);
    return n;
}

int addScore(Score* s) {
    printf("이름은? ");
    scanf("%s", s->name);
    printf("국어는? ");
    scanf("%d", &s->kor);
    printf("영어는? ");
    scanf("%d", &s->eng);
    printf("수학은? ");
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
    printf("이름은? ");
    scanf("%s", s->name);
    printf("국어는? ");
    scanf("%d", &s->kor);
    printf("영어는? ");
    scanf("%d", &s->eng);
    printf("수학은? ");
    scanf("%d", &s->math);
    return 1;

}
