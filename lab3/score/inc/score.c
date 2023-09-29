#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

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

void readScore(Score* s, int no) {
    int sum = 0;
    double avg;

    sum = s->kor + s->eng + s->math;
    avg = sum / 3.0;
    printf("%d %s %d %d %d %d %.1f\n", no , s->name, s->kor, s->eng, s->math, sum, avg); 
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
int selectNum(Score* s[], int cnt) {
    int n;
    listScore(s, cnt);
    printf("\n��ȣ�� (��� :0)? ");
    scanf("%d", &n);
    return n;
}
int deleteScore(Score* s[], int cnt) {
    int cancel;
    int n;

    n = selectNum(s, cnt);
    if(n == 0) return -1;
    printf("������ �����Ͻðڽ��ϱ�?(���� :1)");
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
