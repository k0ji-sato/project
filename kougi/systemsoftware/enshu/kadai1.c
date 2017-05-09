#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;

//struct　をSeisekiに
typedef struct 
{
	char name[20];
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
	Seiseki seiseki[50];
} Record;

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
	Seiseki tmp_seiseki;
	
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
		strcpy(tmp_seiseki.name, cmd);
	　	int i;
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
					tmp_seiseki.eng = atoi(cmd);
					break;
				case 1:
					tmp_seiseki.lang = atoi(cmd);
					break;
				case 2:	
					tmp_seiseki.math = atoi(cmd);
					break;
			}
						
		} 
		}
	}
//	strcpy(record.name , tmp_seiseki.name);
//	record->eng = tmp_record.eng;
//	record->math = tmp_record.math;
//	record->lang = tmp_record.lang;
	tmp_seiseki.total = tmp_seiseki.eng + tmp_seiseki.lang + tmp_seiseki.math;
	record->seiseki[record->number] = tmp_seiseki; 
	record->number++; 
	printf("%d人目の成績を登録しました。\n", record->number);
	return 1;
}


//file input
bool loadfile(FILE* fp,char cmd[], Record* record, char sep)
{
	Seiseki tmp_seiseki;
	Record tmp_record;
	tmp_record.number = 0;
	int rows = 0;
	char* tp;
	char rowStr[sizeof(tmp_seiseki)];

	while(fgets(rowStr, sizeof(tmp_seiseki), fp) != NULL && rows++ < 50)
	{
		if (((tp = strchr(rowStr, '\n')) != NULL)&&(strlen(rowStr) > 1))
		*tp = '\0';

		tp = strtok(rowStr, sep);
		strcpy(tmp_seiseki.name,tp);

		int i = 0;
		while(tp != NULL)
		{
			tp = strtok(NULL, sep);
			if(tp != NULL)
			{
				
				switch(i)
				{
					case 0:
						tmp_seiseki.eng = atoi(cmd);
						break;
					case 1:
						tmp_seiseki.lang = atoi(cmd);
						break;
					case 2:	
						tmp_seiseki.math = atoi(cmd);
				}
			}
			if(i++ > 3)
				break;
		}  
		
		if(i != 4)
		{
			puts("データ形式が正しくありません。");
			return 0;
		}
	}	

	tmp_seiseki.total = tmp_seiseki.eng + tmp_seiseki.lang + tmp_seiseki.math;
	record->seiseki[record->number] = tmp_seiseki; 
	record->number++; 
	printf("%d人目の成績を登録しました。\n", record->number);
	return 1;
}

bool fileInput(char cmd[], Record* record)
{
	FILE* fp;
    	char* str;
	char* ext;
	char* sep = '\0';
	str = strtok(cmd, " ");
	str = strtok(NULL, " ");
	str = strtok(NULL, " ");
	ext = strtok(str, ".");
	
    	if (str != NULL)
    	{
        	if (strcmp(ext, ".tsv")==0)
            		sep = '\t';
        	else if (strcmp(ext, ".csv")==0)
            		sep = ',';
        	else
        	{
            	puts("無効なファイル拡張子です。\n");
            	return 0;
        	}

        	if ((fp = fopen(str, "r")) == NULL)
        	{
            		puts("ファイルを開くことができません。");
            		return 0;
       		 }	

       		 if (!loadFile(fp,cmd, &record, sep))
        	{
            		fclose(fp);
     		       	return 0;
        	}
    	}
    	else
    	{
       		 puts("無効なファイル名です。");
        		return 0;
    	}

    	fclose(fp);
    	return 1;
}


//input oneshot
bool input1shot(char cmd[], Record* record)
{
	Seiseki tmp_seiseki;
	char* str;
	str = strtok(cmd, " ");
	str = strtok(NULL, " ");
	
	strcpy(tmp_seiseki.name, str);

	int i;

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
				tmp_seiseki.eng = atoi(str);
				break;
			case 1:
				tmp_seiseki.lang = atoi(str);
				break;
			case 2:	
				tmp_seiseki.math = atoi(str);
			break;
		}
					
		} 
	}
//	strcpy(record.name , tmp_record.name);
//	record->eng = tmp_record.eng;
//	record->math = tmp_record.math;
//	record->lang = tmp_record.lang;
//	record->total = tmp_record.eng + tmp_record.math + tmp_record.lang;
	tmp_seiseki.total = tmp_seiseki.eng + tmp_seiseki.lang + tmp_seiseki.math;
	record->seiseki[record->number] = tmp_seiseki; 
	record->number++; 
	printf("%d人目の成績を登録しました。\n", record->number);
	return 1;
}

void i_command(char cmd[], Record* record)
{
	char* str;
	str = strtok(cmd, " ");
	str = strtok(NULL, " ");

	if (record->number == 50)
	{
		puts("50人以上登録できません。");
	}

	else if (str = NULL)	
	{
		input1by1(record);
	}  	

	else if (str[0] == "-" && str[1] == "f")
	{
		fileinput(cmd, record);
	}

	else
	{
		input1shot(cmd, record);
	}
}

//----------------------------------------------------------
//Command "o"
bool stdoutput(Record* record)
{
	int i,j,k;
	printf("⭐︎-------成績一覧-------⭐︎");
	printf("登録者数: %d人", record->number);
	
	if(record->number == 0)
	{
		return 0;
	}

	printf("\t\t英語\t国語\t数学\t合計\n");
	float ave[4],dev[4];			
	int max[4],min[4],total[4];
	
	for (i=0; i<4;i++)
	{
		ave[i]=0.f;
		dev[i]=0.f;
		max[i]=0;
		min[i]=100;
	}
	

	for(j=0; j<record->number; j++)
	{
		if(max[0] < record->seiseki[j].eng)
		max[0] = record->seiseki[j].eng;
		if(min[0] > record->seiseki[j].eng)
		min[0] = record->seiseki[j].eng;

		if(max[1] < record->seiseki[j].lang)
		max[1] = record->seiseki[j].lang;
		if(min[1] > record->seiseki[j].lang)
		min[1] = record->seiseki[j].lang;
				
		if(max[2] < record->seiseki[j].math)
		max[2] = record->seiseki[j].math;
		if(min[2] > record->seiseki[j].math)
		min[2] = record->seiseki[j].math;
		
		if(max[3] < record->seiseki[j].total)
		max[3] = record->seiseki[j].total;
		if(min[3] > record->seiseki[j].total)
		min[3] = record->seiseki[j].total;
	
		ave[0] = ave[0] + record->seiseki[j].eng;
		ave[1] = ave[1] + record->seiseki[j].lang;
		ave[2] = ave[2] + record->seiseki[j].math;
		
		dev[0] = dev[0] + pow(record->seiseki[j].eng, 2.0);
		dev[1] = dev[1] + pow(record->seiseki[j].lang, 2.0);
		dev[2] = dev[2] + pow(record->seiseki[j].math, 2.0);
		dev[3] = dev[3] + pow(record->seiseki[j].total, 2.0);
		
	}
	ave[0] = ave[0]/record->number;
	ave[1] = ave[1]/record->number;
	ave[2] = ave[2]/record->number;
	ave[3] = ave[0]+ave[1]+ave[2];	
	
	dev[0] = dev[0] - pow(ave[0],2.0);
	dev[0] = sqrt(dev[0]);	
	dev[1] = dev[1] - pow(ave[1],2.0);
	dev[1] = sqrt(dev[1]);	
	dev[2] = dev[2] - pow(ave[2],2.0);
	dev[2] = sqrt(dev[2]);	
	dev[3] = dev[3] - pow(ave[3],2.0);
	dev[3] = sqrt(dev[3]);	

	printf("平均:\t\t%.1f点\t%.1f点\t%.1f点\t%.1f点\n", ave[0], ave[1], ave[2], ave[3]);
	printf("最高点:\t\t%d点\t%d点\t%d点\t%d点\n", max[0], max[1], max[2], max[3]);
    	printf("最低点:\t\t%d点\t%d点\t%d点\t%d点\n", min[0], min[1], min[2], min[3]);
    	printf("標準偏差:\t%.2f点\t%.2f点\t%.2f点\t%.2f点\n", dev[0], dev[1], dev[2], dev[3]);
   	return 1;

}

bool fileoutput(char cmd[], Record* record)
{
	FILE* fp;
	char* ext;
	char* str;	
	char sep;

	str = strtok(cmd, " ");
	str = strtok(NULL, " ");
	str = strtok(NULL, " ");
	ext = strtok(str, ".");

	if(ext == NULL)
	{
		puts("無効なファイル名です。");
		return 0;
	}
	else 
	{
		if(strcmp(ext,".tsv")==0)
		{
			sep = '\t';
		}	

		else if(strcmp(ext,".csv")==0)
		{
			sep = ',';
		}

		else 
		{
			puts("無効なファイル拡張子です。\ncsvかtsvを指定してください。");
			return 0;
		}

		if((fp = fopen(str, "w")) == NULL)
		{
			puts("ファイルを開くことができません。");
			return 0;
		}
		
		int i;
		for (i = 0; i < record->number; i++)
		{
			fprintf(fp, "%s%c%d%c%d%c%d\n",
               		record->seiseki[i].name, sep,
                record->seiseki[i].eng, sep,
                record->seiseki[i].lang, sep,
                record->seiseki[i].math);
		}
		printf("%sに出力しました。\n", str);
	}
	
	fclose(fp);
	return 1;
}

bool namelist(Record* record)
{
	puts("登録生徒一覧");
    	if (record->number == 0)
    	{
        	puts("登録されていません");
        	return 0;
    	}	
    	int i;
    	for (i=0; i < record->number; i++)
        	printf("%s\n", record->seiseki[i].name);
    	return 1;
 }	

bool nameoutput(char cmd[], Record* record)
{
	char* str;
	str = strtok(cmd, " ");
	str = strtok(NULL, " ");
	str = strtok(NULL, " ");
	
	if(str == "\0")
	{
		puts("オプションが少なすぎます。");
		return 0;
	}
	

	int i;
	for(i=0; i < record->number; i++)
	{
		if(strcmp(str ,record->seiseki[i].name) == 0)
		{
			puts("名前\t英語\t国語\t数学\t合計");
			printf("%s\t%d点\t%d点\t%d点\t%d点\n", 	record->seiseki[i].name,
								record->seiseki[i].eng,
								record->seiseki[i].lang,
								record->seiseki[i].math,
								record->seiseki[i].total);		
		return 1;
		}
	}
	
	puts("該当する生徒は登録されていません。");
	return 0;	
}

//typedef struct
//{
//	char name[50][20];
//	int score[50];
//} SortRecord;


void quicksort(SortRecord* sortrecord, int left ,int right)
{
	
	if (left < right)
	{
		int i = left, j = right;	
		int tmp;
		int pivot = sortrecord->score[i];

		while(1)
		{
			while(sortrecord->score[i] < pivot) i++;
			while(pivot < sortrecord->score[j]) j--;
	
			if(i >= j) break;
			
			tmp = sortrecord->score[i];
			sortrecord->score[i] = sortrecord->score[j];
			sortrecord->score[j] = tmp;
			i++;
			j--;
		}
		quicksort(&sortrecord, left,i-1);
		quicksort(&sortrecord, j+1, right);	
	}
}

bool englishoutput(Record* record)
{
	SortRecord sortrecord;
	
	int i;
	for (i=0 ; i < record->number ;i++)
	{
		sortrecord.name[i] = record->seiseki[i].name;
		sortrecord.score[i] = record->seiseki[i].eng;
	}

	quicksort(&sortrecord, 0, record->number - 1);	

	puts("名前\t英語\n");
	
	int j;
	for (j=0 ;j < record->number ;j++)
	{ 
		printf("%s\t%d\n", sortrecord.name[j],sortrecord.score[j]);
	}
	return 1;
}

bool languageoutput(Record* record)
{
	SortRecord sortrecord;
	
	int i;
	for (i=0 ; i < record->number ;i++)
	{
		sortrecord.name[i] = record->seiseki[i].name;
		sortrecord.score[i] = record->seiseki[i].lang;
	}

	quicksort(&sortrecord, 0, record->number - 1);	

	puts("名前\t国語\n");
	
	int j;
	for (j=0 ;j < record->number ;j++)
	{ 
		printf("%s\t%d\n", sortrecord.name[j],sortrecord.score[j]);
	}
}


bool mathoutput(Record* record)
{
	SortRecord sortrecord;
	
	int i;
	for (i=0 ; i < record->number ;i++)
	{
		sortrecord.name[i] = *record->seiseki[i].name;
		sortrecord.score[i] = *record->seiseki[i].math;
	}

	quicksort(&sortrecord, 0, record->number - 1);	

	puts("名前\t数学\n");
	
	int j;
	for (j=0 ;j < record->number ;j++)
	{ 
		printf("%s\t%d\n", sortrecord.name[j],sortrecord.score[j]);
	}
	return 1;
}



void o_command(char cmd[], Record* record)
{
	char* str;
	str = strtok(cmd, " ");
	str = strtok(NULL, " ");

	if (str = NULL)	
	{
		stdoutput(&record);	
	}

	else if (str[0]== "-")
	{
		if(str[1] == "f")
		{
			fileoutput(cmd, &record);
		}
		
		else if(str[1] == "u")
		{
			namelist(&record);	
		}
		
		else if(str[1] == "n")
		{
			nameoutput(cmd, &record);
		}
		
		else if(str[1] == "e")
		{
			englishoutput(&record);
		}
		
		else if(str[1] == "l")
		{
			languageoutput(&record);
		}
		
		else if(str[1] == "m")
		{
			mathoutput(&record);
		}
		else
		 {
			printf("このオプションは無効です\n");
		}
	}

	else
	{
		printf("このオプションは無効です\n");
	}
}


//----------------------------------------------------------
//Command "h"
void h_command()
{
	printf("----------\n");
	printf("|  Help  |\n");
	printf("----------\n");
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
int main()
{
	Record record;  
//	Command command;
//	command.command[0] = '\0';
	
	char cmd[50];
	cmd[0] = '\0';

	initRecord(&record);	

	while(cmd[0] != 'q')
	{	
		puts("q: 終了\nh: ヘルプ\n");
		fgets(cmd, sizeof(cmd), stdin);
		
		//生徒情報の入力
		if (cmd[0] == "i")
		{
		i_command(cmd,&record);				
		break;
		}

		//集計結果の表示
		else if (cmd[0] == "o")
		{
		o_command(cmd, &record);
		break;
		}
		//ヘルプの表示
		else if (cmd[0] == "h")
		{
		h_command();
		break;
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
		}
	}
	return 0;
}





