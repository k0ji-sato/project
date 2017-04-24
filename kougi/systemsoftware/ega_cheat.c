//Stack を作る理由はデータ入力の途中で入力が途切れた場合のため
//完全に入力が確定してから登録する



#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

typedef int bool;
#define TRUE  1
#define FALSE 0

#define MAX_STUDENTS 50
#define NUM_SUBJECTS 3

//------------------------------------------------------------------------------
//Record structure
typedef struct
{
    char name[50];
    int score[NUM_SUBJECTS + 1];
} Record;

//Stack for the Record
typedef struct
{
    int numRecord;
    Record record[MAX_STUDENTS];
    char subjectName[NUM_SUBJECTS][10];
} RecordStack;

//Command structure
typedef struct
{
    char command[10];
    char option[4][50];
} Command;

//------------------------------------------------------------------------------
//check if the arg is empty
bool isEmptyStr(char* str)
{
    char* tp;
    if ((tp  = strchr(str, '\n')) != NULL)
        *tp = '\0';

    if (str[0] == '\0')
        return TRUE;
    else
        return FALSE;
}

//------------------------------------------------------------------------------
//analyze the command
void analyzeCommand(char* cmd, Command* command)
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
            puts("オプションが多すぎます．");
            return;
        }
    }
}

//"i" command
//------------------------------------------------------------------------------
//push the record to the record_stack
bool pushRecord(RecordStack* record_stack, Record* record)
{
    if (record_stack->numRecord < MAX_STUDENTS)
    {
        record->score[3] = record->score[0] + record->score[1] + record->score[2];
        record_stack->record[record_stack->numRecord] = *record;
        record_stack->numRecord++;
        return TRUE;
    }
    else
    {
        puts("full");
        return FALSE;
    }
}

//fill in items one by one
//RecordStackはポインタで宣言されているのに　printf内では普通の変数で使われているのはなぜ？
bool defaultInput(RecordStack* record_stack)
{
    char cmd[50];
    Record tmp_record;

    printf("%d人目の成績を入力してください．\n", record_stack->numRecord + 1);
    
    printf("名前: ");
    fgets(cmd, sizeof(cmd), stdin);

    if (isEmptyStr(cmd))
    {
        puts("何も入力されていません．");
        return FALSE;
    }
    strcpy(tmp_record.name, cmd);

    int i = 0;
    for (; i < NUM_SUBJECTS; i++)
    {
        printf("%s: ", record_stack->subjectName[i]);
        fgets(cmd, sizeof(cmd), stdin);
        if (isEmptyStr(cmd))
        {
            puts("何も入力されていません．");
            return FALSE;
        }
        tmp_record.score[i] = atoi(cmd);
    }

    if(pushRecord(record_stack, &tmp_record))
    {
        printf("%d人目の成績を登録しました．\n", record_stack->numRecord);
        return TRUE;
    }
    else
        return FALSE;
}

//fill in items by one shot
bool easyInput(Command* command, RecordStack* record_stack)
{
    Record tmp_record;
    strcpy(tmp_record.name, command->option[0]);

    int i = 1;
    for (; i <= NUM_SUBJECTS; i++)
    {
        if (isEmptyStr(command->option[i]))
        {
            puts("オプションが少なすぎます．\nUsage: i [NAME] [SCORE1] [SCORE2] [SCORE3]");
            return FALSE;
        }
        tmp_record.score[i - 1] = atoi(command->option[i]);
    }

    if(pushRecord(record_stack, &tmp_record))
    {
        printf("%d人目の成績を登録しました．\n", record_stack->numRecord);
        return TRUE;
    }
    else
        return FALSE;
}

bool loadFile(FILE* fp, RecordStack* record_stack, char arg_sep)
{
    Record tmp_record;
    RecordStack tmp_stack;
    tmp_stack.numRecord = 0;
    int rows = 0;
    char* tp;
    char sep[1] = {arg_sep};
    char rowStr[sizeof(tmp_record)];

    while(fgets(rowStr, sizeof(tmp_record), fp) != NULL && rows++ < MAX_STUDENTS)
    {
        if (((tp  = strchr(rowStr, '\n')) != NULL)&&(strlen(rowStr) > 1))
            *tp = '\0';

        tp = strtok( rowStr, sep );
        strcpy(tmp_record.name, tp);

        int i = 0;
        while (tp != NULL)
        {
            tp = strtok(NULL, sep);
            if (tp != NULL)
            {
                tmp_record.score[i] = atoi(tp);
            }
            if (i++ > 3)
                break;
        }

        if (i != 4)
        {
            puts("データ形式が正しくありません．");
            return FALSE;
        }

        if(!pushRecord(&tmp_stack, &tmp_record))
            return FALSE;
    }

    int j;
    for (j = 0; j < tmp_stack.numRecord; j++)
    {
        if(!pushRecord(record_stack, &(tmp_stack.record[j])))
        {
            printf("%d人目の成績を登録しました．\n", record_stack->numRecord);
            return TRUE;
        }
    }

    if (rows == 0)
    {
        puts("ファイルが空です．");
        return FALSE;
    }
    return TRUE;
}

//load a external file
bool fileInput(Command* command, RecordStack* record_stack)
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
            puts("無効なファイル拡張子です．\ncsvかtsvを指定して下さい．");
            return FALSE;
        }

        if ((fp = fopen(command->option[1], "r")) == NULL)
        {
            puts("ファイルを開くことができません．");
            return FALSE;
        }

        if (!loadFile(fp, record_stack, sep))
        {
            fclose(fp);
            return FALSE;
        }
    }
    else
    {
        puts("無効なファイル名です．");
        return FALSE;
    }

    fclose(fp);
    return TRUE;
}

void i_command(Command* command, RecordStack* record_stack)
{
    if (isEmptyStr(command->option[0]))
        defaultInput(record_stack);
    else
    {
        switch (command->option[0][0])
        {
            case '-':
                switch (strcmp(command->option[0], "-f"))
                {
                    case 0:
                        fileInput(command, record_stack);
                        break;
                    default:
                        puts("無効なオプションです");
                        break;
                }
                break;
            default:
                easyInput(command, record_stack);
                break;
        }
    }
}

//"o" command
//------------------------------------------------------------------------------
bool defaultOutput(RecordStack* record_stack)
{
    puts("-------成績一覧--------");
    printf("登録者数: %d人\n", record_stack->numRecord);
    
    if (record_stack->numRecord == 0)
    {
        puts("no record");
        return FALSE;
    }

    puts("\t\t英語\t国語\t数学\t合計");
    float ave[NUM_SUBJECTS + 1], dev[NUM_SUBJECTS + 1];
    int max[NUM_SUBJECTS + 1], min[NUM_SUBJECTS + 1];

    int i = 0, j = 0;
    for (; i < NUM_SUBJECTS + 1; i++)
    {
        ave[i] = 0.f;
        dev[i] = 0.f;
        max[i] = INT_MIN;
        min[i] = INT_MAX;
    }

    i = 0;
    for (; i < NUM_SUBJECTS + 1; i++)
    {
        for (j = 0; j < record_stack->numRecord; j++)
        {
            if (max[i] < record_stack->record[j].score[i])
                max[i] = record_stack->record[j].score[i];
            if (min[i] > record_stack->record[j].score[i])
                min[i] = record_stack->record[j].score[i];
            ave[i] += record_stack->record[j].score[i];
            dev[i] += pow(record_stack->record[j].score[i],2.0)/record_stack->numRecord;
        }
        ave[i] /= record_stack->numRecord;
        dev[i] -= pow(ave[i], 2.0);
        dev[i] = sqrt(dev[i]);
    }

    printf("　　平均:\t%.1f点\t%.1f点\t%.1f点\t%.1f点\n", ave[0], ave[1], ave[2], ave[3]);
    printf("　最高点:\t%d点\t%d点\t%d点\t%d点\n", max[0], max[1], max[2], max[3]);
    printf("　最低点:\t%d点\t%d点\t%d点\t%d点\n", min[0], min[1], min[2], min[3]);
    printf("標準偏差:\t%.2f点\t%.2f点\t%.2f点\t%.2f点\n", dev[0], dev[1], dev[2], dev[3]);
    return TRUE;
}

//o -f [file_address]\t%.1f点
bool fileOutput(Command* command, RecordStack* record_stack)
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
            puts("無効なファイル拡張子です．\ncsvかtsvを指定して下さい．");
            return FALSE;
        }

        if ((fp = fopen(command->option[1], "w")) == NULL)
        {
            puts("ファイルを開くことができません．");
            return FALSE;
        }

        int i;
        for (i = 0; i < record_stack->numRecord; i++)
        {
            fprintf(fp, "%s%c%d%c%d%c%d\n",
                record_stack->record[i].name, sep,
                record_stack->record[i].score[0], sep,
                record_stack->record[i].score[1], sep,
                record_stack->record[i].score[2]);
        }

        printf("%sに出力しました．\n", command->option[1]);
    }
    else
    {
        puts("無効なファイル名です．");
        return FALSE;
    }

    fclose(fp);
    return TRUE;
}

//o -u
bool listName(RecordStack* record_stack)
{
    puts("登録生徒一覧");
    if (record_stack->numRecord == 0)
    {
        puts("登録されていません");
        return FALSE;
    }
    int i = 0;
    for (; i < record_stack->numRecord; i++)
        printf("%s\n", record_stack->record[i].name);
    return TRUE;
}

//o -n [name]
bool personalScore(Command* command, RecordStack* record_stack)
{
    char* tmp = command->option[1];
    if (isEmptyStr(tmp))
    {
        puts("オプションが少なすぎます．");
        return FALSE;
    }

    puts("名前\t英語\t国語\t数学\t合計");

    int i = 0;
    for (; i < record_stack->numRecord; i++)
    {
        if (!strcmp(command->option[1], record_stack->record[i].name))
        {
            printf("%s\t%d点\t%d点\t%d点\t%d点\n",
                record_stack->record[i].name,
                record_stack->record[i].score[0],
                record_stack->record[i].score[1],
                record_stack->record[i].score[2],
                record_stack->record[i].score[0]
                + record_stack->record[i].score[1]
                + record_stack->record[i].score[2]
            );
        }
    }
    return TRUE;
}

void quickSort(RecordStack* record_stack, int code, int left, int right)
{
    int i = left;
    int j = right;
    int pivot = record_stack->record[(i + j) / 2].score[code];

    while (TRUE)
    {
        while (record_stack->record[i].score[code] > pivot)
            i++;
        while (pivot > record_stack->record[j].score[code])
            j--;
        if (i >= j)
            break;

        //swap the records
        Record tmp;
        tmp = record_stack->record[i];
        record_stack->record[i++] = record_stack->record[j];
        record_stack->record[j--] = tmp;
    }

    if (left < i - 1)
        quickSort(record_stack, code, left, i - 1);
    if (j + 1 <  right)
        quickSort(record_stack, code, j + 1, right);
}

//o [-e | -l | -m]
bool subjectScore(RecordStack* record_stack, int code)
{
    int i;
    printf("-------%sの成績--------\n", record_stack->subjectName[code]);
    printf("登録者数: %d人\n", record_stack->numRecord);
    printf("%sの成績\n学生名\t点数\n", record_stack->subjectName[code]);

    RecordStack sorted_stack = *record_stack;
    quickSort(&sorted_stack, code, 0, sorted_stack.numRecord - 1);

    for (i = 0; i < sorted_stack.numRecord; i++)
        printf("%s\t%d点\n", sorted_stack.record[i].name, sorted_stack.record[i].score[code]);

    return TRUE;
}

void o_command(Command* command, RecordStack* record_stack)
{
    char* tmp = command->option[0];
    if (isEmptyStr(tmp))
        defaultOutput(record_stack);
    else if (!strcmp(tmp, "-f"))
        fileOutput(command, record_stack);
    else if (!strcmp(tmp, "-u"))
        listName(record_stack);
    else if (!strcmp(tmp, "-n"))
        personalScore(command, record_stack);
    else if (!strcmp(tmp, "-e"))
        subjectScore(record_stack, 0);
    else if (!strcmp(tmp, "-l"))
        subjectScore(record_stack, 1);
    else if (!strcmp(tmp, "-m"))
        subjectScore(record_stack, 2);
    else
        puts("無効なオプションです．");
}

//"h" command
//------------------------------------------------------------------------------
void h_command()
{
    puts("-----------------------------------------------------");
    puts("  課題01-01，課題01-02，課題01-03全て実装しました．");
    puts("-----------------------------------------------------");
    printf("  i\t\t成績情報を入力\n");
    printf("  i [-f FILE]\t成績情報をFILEから入力\n");
    printf("  i [NAME] [ENGLISH_SCORE] [JAPANESE_SCORE] [MATH_SCORE]\n\t\t成績情報の簡易入力\n\n");
    
    printf("  o\t\t集計結果を表示（各科目と合計の平均点・最高点・最低点・標準偏差）\n");
    printf("  o [-f FILE]\t成績情報をFILEに出力\n");
    printf("  o [-u]\t登録生徒名一覧を表示\n");
    printf("  o [-n NAME]\tNAMEで指定した生徒の成績を表示\n");
    printf("  o [-e]\t英語の成績を点数が高い順に表示\n");
    printf("  o [-l]\t国語の成績を点数が高い順に表示\n");
    printf("  o [-m]\t算数の成績を点数が高い順に表示\n\n");

    printf("  q\t\t終了\n");
    printf("  h\t\tヘルプ表示\n\n");
}

//clear commands
//------------------------------------------------------------------------------
void clearCommand(Command* command)
{
    command->command[0] = '\0';
    int i = 0;
    for (; i < 4; i++)
        command->option[i][0] = '\0';
    printf("\n:");
}

//initialize the stack
//------------------------------------------------------------------------------
void initRecordStack(RecordStack* record_stack)
{
    strcpy(record_stack->subjectName[0],"英語");
    strcpy(record_stack->subjectName[1],"国語");
    strcpy(record_stack->subjectName[2],"数学");
    record_stack->numRecord = 0;
}

//------------------------------------------------------------------------------
int main()
{
    puts("q: 終了\nh: ヘルプ");

    Command command;
    command.command[0] = '\0';

    RecordStack record_stack;
    initRecordStack(&record_stack);

    while(command.command[0] != 'q')
    {
        clearCommand(&command);

        char cmd[100], temp;
        fgets(cmd, sizeof(cmd), stdin);

        analyzeCommand(cmd, &command);

        if ((int)strlen(command.command) > 1)
        {
            puts("コマンドが見つかりません．");
            command.command[0] = '\0'; //for 'q' command
            continue;
        }

        switch(command.command[0])
        {
            case 'i':
                i_command(&command, &record_stack);
                break;
            case 'o':
                o_command(&command, &record_stack);
                break;
            case 'h':
                h_command();
                break;
            case 'q':
                puts("プログラム終了");
                break;
            default:
                puts("コマンドが見つかりません．");
                break;
        }
    }

    return 0;
}
