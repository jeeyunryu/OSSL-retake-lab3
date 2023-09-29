typedef struct{
    char name[20];
    int kor, eng, math;
} Score;

int addScore(Score *s);
void readScore(Score s[], int no);
void listScore(Score* s[], int cnt);
int updateScore(Score *s);
int selectMenu();
int deleteScore(Score* s[], int cnt);
