#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

int selectNum(Score* s[], int cnt);
int saveToFile(Score* s[], int cnt);
int searchName(Score* s[], int cnt);
int loadData(Score* s[]);


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

        if(menu == 1 || menu == 3 || menu == 4 || menu == 5 || menu == 6) {
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

            else if(menu ==6) {
                
                if(searchName(s, cnt) == 0) printf("=> 검색된 데이터 없음!!\n");
            }
        }

        
    }
    printf("\n종료됨!\n");
    return 0;
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
    int sum = 0;
    double avg;

    
    printf("검색할 메뉴는? ");
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


