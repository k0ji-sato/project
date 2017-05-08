#include <stdio.h>
#include <string.h>
#include <math.h>

typedef int bool;
#define TRUE  1
#define FALSE 0

typedef struct
{
    	char name[50];
    	int score[4];
} Seiseki;

typedef struct
{
    	int number;
    	Seiseki seiseki[50];
    	char subjectName[3][10];
} Record;

typedef struct
{
    	char command[10];
    	char option[4][50];
} Command;

bool isemptystr(char* str)
{
    	char* tp;

    	if ((tp  = strchr(str, '\n')) != NULL)
        	*tp = '\0';

    	if (str[0] == '\0')
    		return TRUE;
    	else
        	return FALSE;
}

void analyzecommand(char* cmd, Command* command)
{
    	char* tp;
    
	if (((tp  = strchr(cmd, '\n')) != NULL)&&(strlen(cmd) > 1))
        	*tp = '\0';

    	tp = strtok( cmd, " " );

    	strcpy(command->command, tp);

    	int i = 0;

    	while (tp != NULL)
    	{
        	tp = strtok( NULL, " " );
        	if (tp != NULL)
        	{
         	   	strcpy(command->option[i], tp);
        	}
        	if (i++ > 4)
        	{
        	    	puts("無効なコマンドです。");
            	return;
        	}
    	}
}

//"i" command
bool pushRecord(Record* record, Seiseki* seiseki)
{
       	seiseki->score[3] = seiseki->score[0] + seiseki->score[1] + seiseki->score[2];
       	record->seiseki[record->number] = *seiseki;
       	record->number++;
       	return TRUE;
}

bool stdinput(Record* record)
{
    	char cmd[50];
    	Seiseki tmp_seiseki;

    	printf("%d人目の成績を入力してください。\n", record->number + 1);
       	printf("名前: ");
   
 	fgets(cmd, sizeof(cmd), stdin);
	
    	if (isemptystr(cmd))
    	{
        	puts("入力がありません。");
        	return FALSE;
   	}	

    	strcpy(tmp_seiseki.name, cmd);

    	int i = 0;
    	for (; i < 3; i++)
    	{
        	printf("%s: ", record->subjectName[i]);

        	fgets(cmd, sizeof(cmd), stdin);

        	if (isemptystr(cmd))
        	{
	            	puts("入力がありません。");
        	    	return FALSE;
        	}	
        	tmp_seiseki.score[i] = atoi(cmd);
    	}	

    	if(pushRecord(record, &tmp_seiseki))
    	{
        	printf("%d人目の成績を登録しました。\n", record->number);
        	return TRUE;
    	}	
    	else
        	return FALSE;
}

bool input1shot(Command* command, Record* record)
{
    	Seiseki tmp_seiseki;
    	strcpy(tmp_seiseki.name, command->option[0]);

    	int i = 1;
    	for (; i <= 3; i++)
    	{
        	if (isemptystr(command->option[i]))
        	{
            	puts("オプションが少なすぎます。\n");
            	return FALSE;
        	}
        	tmp_seiseki.score[i - 1] = atoi(command->option[i]);
    	}

    	if(pushRecord(record, &tmp_seiseki))
    	{
        	printf("%d人目の成績を登録しました。\n", record->number);
        	return TRUE;
    	}
    	else
        	return FALSE;
}

bool loadFile(FILE* fp, Record* record, char arg_sep)
{
    	Seiseki tmp_seiseki;
    	Record tmp_record;
    	tmp_record.number = 0;
    	int rows = 0;
    	char* tp;
    	char sep[1] = {arg_sep};
    	char rowStr[sizeof(tmp_seiseki)];
	
    	while(fgets(rowStr, sizeof(tmp_seiseki), fp) != NULL && rows < 50)
    	{
        	rows++;
		if (((tp  = strchr(rowStr, '\n')) != NULL)&&(strlen(rowStr) > 1))
            	*tp = '\0';

        	tp = strtok(rowStr, sep);
        	strcpy(tmp_seiseki.name, tp);

        	int i = 0;
        	while (tp != NULL)
        	{
        	    	tp = strtok(NULL, sep);
            		if (tp != NULL)
            		{
                		tmp_seiseki.score[i] = atoi(tp);
            		}
			i++;
            		if (i > 2)	
			{
				break;
        		}
		}

        	if (i != 3)
        	{
            		puts("データ形式が正しくありません。");
            		return FALSE;
        	}
		
        	if(!pushRecord(&tmp_record, &tmp_seiseki))
            	return FALSE;
    	}

	tmp_record.number = rows;

    	int j;
    	for (j = 0; j < tmp_record.number; j++)
    	{
        	if(pushRecord(record, &(tmp_record.seiseki[j])))
        	{
            		printf("%d人目の成績を登録しました。\n", record->number);
            		return TRUE;
        	}
    	}

    	if (rows == 0)
    	{
     	   	puts("ファイルが空です。");
        	return FALSE;
    	}
    	return TRUE;
}

bool fileInput(Command* command, Record* record)
{
    	FILE* fp;
    	char* ext = strchr(command->option[1], '.');
    	char sep = '\0';

    	if (ext != NULL)
    	{
        	if (!strcmp(ext, ".tsv"))
           	sep = '\t';
        	else if (!strcmp(ext, ".csv"))
            	sep = ',';
        	else
        	{
        	    	puts("無効なファイル拡張子です。\ncsvかtsvを指定して下さい。");
            		return FALSE;
        	}

        	if ((fp = fopen(command->option[1], "r")) == NULL)
        	{
            		puts("ファイルを開くことができません。");
            		return FALSE;
        	}

        	if (!loadFile(fp, record, sep))
        	{
            		fclose(fp);
            		return FALSE;
        	}
    	}
    		else
    		{
        	puts("無効なファイル名です。");
        	return FALSE;
    		}

   	fclose(fp);
    	return TRUE;
}

void i_command(Command* command, Record* record)
{
	if(record->number > 49)
		puts("これ以上登録できません。");
    	else if (isemptystr(command->option[0]))
        	stdinput(record);
    	else
    	{
        	switch (command->option[0][0])
        	{
            	case '-':
               		switch (strcmp(command->option[0], "-f"))
                	{
                    	case 0:
                        	fileInput(command, record);
                        	break;
                    	default:
                        	puts("無効なコマンドです");
                        	break;
                	}
                	break;
            	default:
                	input1shot(command, record);
                	break;
        	}
    	}
}

//"o" command
bool stdoutput(Record* record)
{
    	puts("⭐︎-------成績一覧--------⭐︎");
    	printf("登録者数: %d人\n", record->number);
    
    	if (record->number == 0)
    	{
        	puts("成績が登録されていません。");
        	return FALSE;
    	}

    	puts("\t\t英語\t国語\t数学\t合計");
    	float ave[4], dev[4];
    	int max[4], min[4];

   	int i = 0, j = 0;
    	for (; i < 4; i++)
    	{
        	ave[i] = 0.f;
        	dev[i] = 0.f;
        	max[i] = 0;
        	min[i] = 100;
    	}

    	i = 0;
    	for (; i < 4; i++)
    	{
        	for (j = 0; j < record->number; j++)
        	{
            		if (max[i] < record->seiseki[j].score[i])
                	max[i] = record->seiseki[j].score[i];
            		if (min[i] > record->seiseki[j].score[i])
                	min[i] = record->seiseki[j].score[i];
            		ave[i] += record->seiseki[j].score[i];
            		dev[i] += pow(record->seiseki[j].score[i],2.0)/record->number;
       		}	
        	ave[i] /= record->number;
        	dev[i] -= pow(ave[i], 2.0);
        	dev[i] = sqrt(dev[i]);
    	}	

    	printf("　　平均:\t%.1f点\t%.1f点\t%.1f点\t%.1f点\n", ave[0], ave[1], ave[2], ave[3]);
    	printf("　最高点:\t%d点\t%d点\t%d点\t%d点\n", max[0], max[1], max[2], max[3]);
    	printf("　最低点:\t%d点\t%d点\t%d点\t%d点\n", min[0], min[1], min[2], min[3]);
    	printf("標準偏差:\t%.2f点\t%.2f点\t%.2f点\t%.2f点\n", dev[0], dev[1], dev[2], dev[3]);
    	return TRUE;
}

bool fileoutput(Command* command, Record* record)
{
    	FILE* fp;
    	char* ext = strchr(command->option[1], '.');
    	char sep;

    	if (ext != NULL)
    	{
        	if (!strcmp(ext, ".tsv"))
            	sep = '\t';
        	else if (!strcmp(ext, ".csv"))
        	sep = ',';
        	else
        	{
            		puts("無効なファイル拡張子です。\ncsvかtsvを指定して下さい。");
            		return FALSE;
        	}
	
        	if ((fp = fopen(command->option[1], "w")) == NULL)
        	{
            		puts("ファイルを開くことができません。");
            		return FALSE;
        	}

        	int i;
        	for (i = 0; i < record->number; i++)
        	{
            		fprintf(fp, "%s%c%d%c%d%c%d\n",
                	record->seiseki[i].name, sep,
                	record->seiseki[i].score[0], sep,
                	record->seiseki[i].score[1], sep,
                	record->seiseki[i].score[2]);
       	 	}	

        	printf("%sに出力しました。\n", command->option[1]);
    	}
    	else
    	{
        	puts("無効なファイル名です。");
        	return FALSE;
    	}

    	fclose(fp);
    	return TRUE;
}

bool namelist(Record* record)
{
    	puts("登録生徒一覧");
    	if (record->number == 0)
    	{
    		puts("生徒が登録されていません");
        	return FALSE;
    	}
    	int i = 0;
    	for (; i < record->number; i++)
        	printf("%s\n", record->seiseki[i].name);
    	return TRUE;
}

bool personalscore(Command* command, Record* record)
{
    	char* tmp = command->option[1];
    	if (isemptystr(tmp))
    	{
        	puts("オプションが少なすぎます。");
        	return FALSE;
    	}	

    	puts("名前\t英語\t国語\t数学\t合計");

    	int i = 0;
    	for (; i < record->number; i++)
    	{
        	if (!strcmp(command->option[1], record->seiseki[i].name))
        	{
        	    	printf("%s\t%d点\t%d点\t%d点\t%d点\n",
                	record->seiseki[i].name,
                	record->seiseki[i].score[0],
                	record->seiseki[i].score[1],
                	record->seiseki[i].score[2],
                	record->seiseki[i].score[0]
                	+ record->seiseki[i].score[1]
                	+ record->seiseki[i].score[2]);	
        	}
    	}
    	return TRUE;
}

void quickSort(Record* record, int sub, int left, int right)
{
    	int i = left;
    	int j = right;
    	int pivot = record->seiseki[left].score[sub];
    	

	while (TRUE)
    	{
        	while (record->seiseki[i].score[sub] > pivot)
            	i++;
        	while (pivot > record->seiseki[j].score[sub])
            	j--;
        	if (i >= j)
            	break;

        	Seiseki tmp;
        	tmp = record->seiseki[i];
        	record->seiseki[i++] = record->seiseki[j];
        	record->seiseki[j--] = tmp;
    	}
    	if (left < i - 1)
        	quickSort(record, sub, left, i - 1);
    	if (j + 1 <  right)
        	quickSort(record, sub, j + 1, right);
}

bool subjectscore(Record* record, int sub)
{
    	int i;
 
   	printf("⭐︎-------%sの成績--------⭐︎\n", record->subjectName[sub]);
    	printf("登録者数: %d人\n", record->number);
    	printf("%sの成績\n名前\t点数\n", record->subjectName[sub]);

    	Record sorted_stack = *record;
    	quickSort(&sorted_stack, sub, 0, sorted_stack.number - 1);

    	for (i = 0; i < sorted_stack.number; i++)
        	printf("%s\t%d点\n", sorted_stack.seiseki[i].name, sorted_stack.seiseki[i].score[sub]);

    	return TRUE;
}

void o_command(Command* command, Record* record)
{
    	char* tmp = command->option[0];
    	if (isemptystr(tmp))
        	stdoutput(record);
    	else if (!strcmp(tmp, "-f"))
        	fileoutput(command, record);
    	else if (!strcmp(tmp, "-u"))
        	namelist(record);
    	else if (!strcmp(tmp, "-n"))
        	personalscore(command, record);
    	else if (!strcmp(tmp, "-e"))
        	subjectscore(record, 0);
    	else if (!strcmp(tmp, "-l"))
        	subjectscore(record, 1);
    	else if (!strcmp(tmp, "-m"))
        	subjectscore(record, 2);
    	else
        	puts("無効なコマンドです。");
}

//"h" command
void h_command()
{
    	puts("\t\t---------");
    	puts("\t\t| ヘルプ |");
    	puts("\t\t---------");
    	printf("  i\t\t試験結果の入力\n");
    	printf("  i [-f] [FILE]\t試験結果のファイル入力\n");
    	printf("  i [名前] [英語の点数] [国語の点数] [数学の点数]\n\t\t試験結果の一括入力\n\n");
    	printf("  o\t\t集計結果の表示\n");
    	printf("  o [-f] [FILE]\t集計結果をFILEに出力\n");
    	printf("  o [-u]\t登録生徒名一覧を表示\n");
    	printf("  o [-n] [NAME]\t指定した生徒の成績を表示\n");
    	printf("  o [-e]\t英語の成績を表示（点数の高い順）\n");
    	printf("  o [-l]\t国語の成績を表示（点数の高い順）\n");
    	printf("  o [-m]\t算数の成績を表示（点数の高い順）\n\n");

    	printf("  q\t\t終了\n");
    	printf("  h\t\tヘルプ表示\n\n");
}

void clearCommand(Command* command)
{
	command->command[0] = '\0';
    	int i = 0;
    	for (; i < 4; i++)
        	command->option[i][0] = '\0';
    	printf("\n:");
}

void InitRecord(Record* record)
{
    	strcpy(record->subjectName[0],"英語");
    	strcpy(record->subjectName[1],"国語");
    	strcpy(record->subjectName[2],"数学");
   	record->number = 0;
}

//main
int main()
{
	Command command;
	command.command[0] = '\0';
   	Record record;
    	InitRecord(&record);

   	puts("q: 終了\nh: ヘルプ");
    	while(command.command[0] != 'q')
    	{
        	clearCommand(&command);
        	char inp[100], tmp;
        	fgets(inp, sizeof(inp), stdin);
        	analyzecommand(inp, &command);
       		if ((int)strlen(command.command) > 1)
        	{
            		puts("無効なコマンドです。");
            		command.command[0] = '\0'; 
           		 continue;
        	}

        	switch(command.command[0])
        	{
            	case 'i':
                	i_command(&command, &record);
                	break;
            	case 'o':
                	o_command(&command, &record);
                	break;
            	case 'h':
                	h_command();
                	break;
            	case 'q':
                	puts("プログラム終了");
                	break;
            	default:
                	puts("無効なコマンドです。");
                	break;
        	}
   	 }

    	return 0;
}
