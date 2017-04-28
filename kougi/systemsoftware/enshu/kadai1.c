#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//struct　をSeisekiに
typedef struct 
{
	int eng;
	int lang;
	int math;
	int total;
} Seiseki;

//struct Command
//typedef struct
//{
//	char command[10];
//	char option[4][50];	
//}Command;

//record 
typedef struct
{
	int number;
	char name[20];
	Seiseki seiseki;
} Record

bool checknumber(char *cmd)
{
	if(strcmp(cmd, "0"))
	{
		return 1;
	}
	else if(atoi(cmd) == 0 || atoi(cmd) > 100)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
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
		strcpy(tmp_record.name, cmd);

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
			return 0;
		}	  
		else if(checknumber(&cmd[0]))
		{
			printf("100以下の整数を入力してください。\n");
			return 0;
		}
		else
		{
			switch(i)
			{
				case 0:
					tmp_record.eng = atoi(cmd);
					break;
				case 1:
					tmp_record.lang = atoi(cmd);
					break;
				case 2:	
					tmp_record.math = atoi(cmd);
					break;
			}
						
		} 
		}
	}
	strcpy(record.name , tmp_record.name);
	record->eng = tmp_record.eng;
	record->math = tmp_record.math;
	record->lang = tmp_record.lang;
	record->total = tmp_record.eng + tmp_record.math + tmp_record.lang;
	record->number++; 
	printf("%d人目の成績を登録しました。\n", record->number);
	return 1;
}


//file input

//input oneshot
bool input1shot(char cmd, Record* record)
{
	Record tmp_record;
	char str[20];
	str = strtok(cmd, " ");
	str = strtok(NULL, " ");
	strcpy(tmp_record.name, str);

	for (i=0 ; i<3; i++)
	{
		str = strtok(NULL, " ");
		
		if (cmd[0] == "\0")
		{
			printf("オプションが足りません。\n");
			return 0;
		}	  
		else if(checknumber(&str[0]))
		{
			printf("100以下の整数を入力してください。\n");
			return 0;
		}
		else
		{
		switch(i)
		{
			case 0:
				tmp_record.eng = atoi(str);
				break;
			case 1:
				tmp_record.lang = atoi(str);
				break;
			case 2:	
				tmp_record.math = atoi(str);
			break;
		}
					
	} 
	}
	strcpy(record.name , tmp_record.name);
	record->eng = tmp_record.eng;
	record->math = tmp_record.math;
	record->lang = tmp_record.lang;
	record->total = tmp_record.eng + tmp_record.math + tmp_record.lang;
	record->number++; 
	printf("%d人目の成績を登録しました。\n", record->number);
	return 1;
}

void i_command(char cmd[50], Record* record)
{
	char[] str;
	str = strtok(cmd, " ");
	str = strtok(NULL, " ");

	if (str = NULL)	
	{
		input1by1(record);
		break;	
	}  	

	else if (str[0] == "-" &&　str[1] == "f")
	{
		fileinput(cmd, record);
		break;
	}

	else
	{
		input1shot(cmd, record);
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
			return 1;
		}
		
		else if(str[1] == "u")
		{
			namelist();	
			return 1;
		}
		
		else if(str[1] == "n")
		{
			nameoutput();
			return 1;
		}
		
		else if(str[1] == "e")
		{
			englishoutput();
			return 1;
		}
		
		else if(str[1] == "l")
		{
			languageoutput();
			return 1;
		}
		
		else if(str[1] == "m")
		{
			mathoutput();
			return 1;
		}
		else
		 {
			printf("このオプションは無効です\n");
		}
		return 0;
	}

	else
	{
		printf("このオプションは無効です\n");
		return 0;	
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
//void clearcmd(Command* command)
//{
//	command->command[0] = '\0';
//	int i = 0;
//	for (; i < 4; i++)
//		command->option[i][0] = '\0';
//	printf("\n:");
//} 

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





