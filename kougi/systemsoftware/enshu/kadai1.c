#include <stdio.h>
#include <math.h>
#include <string.h>

//struct　をSeisekiに
typedef struct 
{
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

//record 
typedef struct
{
	int number;
	char name[20];
	Seiseki seiseki;
} Record

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

//----------------------------------------------------------
//Command "i"

//input one by one
bool input1by1(Record* record)
{
	char cmd[50];	
	Record tmp_record;
	
	printf("%d人目の成績を入力してください。\n", record->number +1);
	printf("名前:　");
	fgets(cmd,sizeof(cmd),stdin);

	if (cmd[0] == "\0")
	{
		printf("何も入力されていません。\n");
		return 0;
	}	  
	else 
	{
		strcpy(tmprecord.name, cmd);

		for (i=0 ; i<3; i++)
		{
			switch(i)
			{
				case 0:
					printf("英語: ");
					break;
				case 1:
					printf("国語: ");
					break;
				case 2:	
					printf("数学: ");
					break;
			}
		fgets(cmd, sizeof(cmd),stdin);
		if (cmd[0] == "\0")
		{
			printf("何も入力されていません。\n");
		}	  
		

		}
	}

}


//file input

//input oneshot


void i_command(char cmd[50], Record* record)
{
	char[] str;
	str = strtok(cmd, " ");
	str = strtok(NULL, " ");

	if (str = NULL)	
	{
		input1by1();
		break;	
	}  	

	else if (str[0] == "-" &&　str[1] == "f")
	{
		fileinput();
		break;
	}

	else
	{
		input1shot();
		break;	
	}
}

//----------------------------------------------------------
//Command "o"

void o_command(char cmd[50], Record* record)
{
	char[] str;
	str = strtok(cmd, " ");
	str = strtok(NULL, " ");

	if (str = NULL)	
	{
		stdoutput();
		break;	
	}  	

	else if (str[0]== "-")
	{
		if(str[1] == "f")
		{
			fileoutput();
			break;
		}
		
		else if(str[1] == "u")
		{
			namelist();	
			break;
		}
		
		else if(str[1] == "n")
		{
			nameoutput();
			break;
		}
		
		else if(str[1] == "e")
		{
			englishoutput();
			break;
		}
		
		else if(str[1] == "l")
		{
			languageoutput();
			break;
		}
		
		else if(str[1] == "m")
		{
			mathoutput();
			break;
		}
		else
		 {
			printf("このオプションは無効です\n");
		}
		break;
	}

	else
	{
		printf("このオプションは無効です\n");
		break;	
	}
}


//----------------------------------------------------------
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

//----------------------------------------------------------
//clear command
void clearcmd(Command* command)
{
	command->command[0] = '\0';
	int i = 0;
	for (; i < 4; i++)
		command->option[i][0] = '\0';
	printf("\n:");
} 

//----------------------------------------------------------
//initialize the record
void initRecord(Record* record)
{
	record->number = 0; 
}

//----------------------------------------------------------
int main(){
	Record record;  
	puts("q: 終了\nh: ヘルプ\n");
//	Command command;
//	command.command[0] = '\0';

	Record record;

	char cmd[50];
	cmd[0] = '\0';

	while(cmd[0] != 'q')
	{
		clearcmd(&command);
		
		gets(cmd);
		fgets(cmd, sizeof(cmd), stdin);
		
		//生徒情報の入力
		if (cmd[0] == "i")
		{
		i_command();				
		break;
		}

		//集計結果の表示
		else if (cmd[0] == "o")
		{
		o_command();
		break;
		}
		//ヘルプの表示
		else if (cmd[0] == "h")
		{
		h_command();
		break
		}
		//プログラムの終了
		else if (cmd[0] == "q")
		{
			printf("プログラムを終了します\n");
		break;
		}
		//エラー
		else
		{
		printf("このコマンドは無効です\n");	
		break;
		}
	}
	return 0;
}





