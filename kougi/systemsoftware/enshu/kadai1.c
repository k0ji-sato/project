#include <stdio.h>
#include <math.h>
#include <string.h>

//struct　をSeisekiに
typedef struct {
	char name[10];
	int eng;
	int lang;
	int math;
} Seiseki;

//struct Command
typedef struct
 {
	char command[10];
	char option[4][50];	
}Command;
 
//名前を入力
char Getchar()
{
char name[20];
gets(name);
return name;
}

//点数を入力
int Getpoint()
{
int point;
gets(point);

return point;
}

//Command "h"
void h_command()
{
	puts("----------");
	puts("|  Help  |");
	puts("----------");
	printf( " i\t試験結果の入力\n");
	printf( " i -f [FILE]\t試験結果をFILEから入力 \n");
	printf( " i [名前][英語の点数][国語の点数][数学の点数]\t成績情報の簡易入力 \n\n");
	printf( " o\t集計結果の表示\n");
	printf( " o -f [FILE]\t集計結果をFILEに表示\n");
	printf( " o -u\t登録生徒名一覧の表示\n");
	printf( " o -n [生徒名]\t指定した生徒の成績を表示\n");
	printf( " o -e\t英語の成績を点数の高い順に表示\n");
	printf( " o -l\t国語の成績を点数の高い順に表示\n");
	printf( " o -m\t数学の成績を点数の高い順に表示\n\n");
	printf( " q\t終了\n\n");
	printf( " h\tヘルプ表示\n\n");
}

int main(){
Seiseki student[50];
  
puts("q: 終了\nh: ヘルプ\n");

while(1){
char cmd[20];
	gets(cmd);
	//生徒情報の入力
	if (cmd[0] == "i")
		{
				
		}
	//集計結果の表示
	else if (cmd[0] == "o")
		{
		char* opt = strtok(cmd, " -");
		
		
		}
	//ヘルプの表示
	else if (cmd[0] == "h")
		{
		printf("");
		}
	//プログラムの終了
	else if (cmd[0] == "q")
		{
		break;
		}
	//エラー
	else
		{
		printf("ERROR:That command is not found");	
		}
}
return 0;
}





