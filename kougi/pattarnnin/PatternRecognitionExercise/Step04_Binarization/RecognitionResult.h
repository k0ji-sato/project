/*! @file		RecognitionResult.h
    @brief		�F�����ʂ�ۑ�����\���̂��`�����t�@�C��
	@author		Ken'ichi Morooka
	@date		2012.05.14
	@version	2.0.0
*/

#ifndef __RECOGNITIONRESULT__
#define __RECOGNITIONRESULT__

/*!
	@brief	�F�����ʂ�ۑ�����t�@�C�����e���v���[�g
	@n		%05d-%05d�̑O�����w�K�T���v�����C�㔼���e�X�g�T���v�����ɑΉ�����
	@n		��F�w�K�T���v����100�C�e�X�g�T���v����1000�̏ꍇ��"result-training_00100-test_01000.txt"�ƂȂ�  
*/
const char RecognitionResultFile[] = "result-training_%05d-test_%05d.txt";

/*!
  @struct		RecognitionResult
  @brief		�F�����ʂ�ۑ����邽�߂̍\����
*/
typedef struct RecognitionResult {
	int class_num;			/*!< �N���X�� */

	/*!
	@brief	�����Ώƕ\�iConfusion Matrix�j
	@n		res[�F�����Ăق����N���X���x��][�F���������ʂ̃N���X���x��]
	@n		��Fres[4][9]=10�̏ꍇ�C�N���X4�ƔF�����ׂ��T���v�����N���X9�Ƃ��ĔF���������̂�10�������Ƃ�������  
	@n		��Fres[4][4]=10�̏ꍇ�C�N���X4�ƔF�����ׂ��T���v�����N���X4�Ƃ��ĔF���������̂�10�������Ƃ������ƂȂ̂ł��̏ꍇ�������F�����ꂽ�T���v����10�������Ƃ������ƂɂȂ�
	*/
	int **res;				/*!< �����Ώƕ\�iConfusion Matrix�j */
	double *ratio;			/*!< �e�N���X�̔F���� */
	double average_ratio;	/*!< ���ϔF���� */

	/*!
	  @fn		RecognitionResult(int _class_num)
	  @brief	�R���X�g���N�^
	  @param	[in] _class_num	�N���X��
	*/
	RecognitionResult(int _class_num)
	{
		int i, j;
		class_num = _class_num;
		res = new int*[class_num];
		for (i=0; i<class_num; i++){
			res[i] = new int [class_num];
		}
		for (i=0; i<class_num; i++){
			for (j=0; j<class_num; j++){
				res[i][j] = 0;
			}
		}

		ratio = new double [class_num];
		for (i=0; i<class_num; i++){
			ratio[i] = 0.0;
		}

		average_ratio = 0.0;
	
	}

	/*!
	  @fn		~RecognitionResult()
	  @brief	�f�X�g���N�^
	*/
	~RecognitionResult()
	{
		int i;
		for (i=0; i<class_num; i++){
			delete [] res[i];
		}		
		delete [] res;
	}

	/*!
	  @fn		void CalcRatio()
	  @brief	�F�������v�Z����
	*/
	void CalcRatio()
	{
		int i, j;
		int correct, total;

		for (i=0; i<class_num; i++){
			total = 0;
			for (j=0; j<class_num; j++){
				total += res[i][j];
				if (i==j){
					correct = res[i][j];
				}
			}
			ratio[i] = (double)correct/total;
			average_ratio += ratio[i];
		}

		average_ratio /= class_num;
	}

	/*!
	  @fn		void PrintRecognitionResult()
	  @brief	�F������W���o�͂ɕ\������
	*/
	void PrintRecognitionResult()
	{
		int i, j;

		printf("\n\n");
		for (i=0; i<class_num; i++){
			printf("\tC%d", i);	
		}
		printf("\n");
		for (i=0; i<class_num; i++){
			printf("C%d", i);	
			for (j=0; j<class_num; j++){
				printf("\t%4d", res[i][j]);	
			}
			printf("\n");
		}		
		printf("\nRecognition Ratio\n");
		for (i=0; i<class_num; i++){
			printf("Class %d\t%3.2lf\n", i, ratio[i]*100);	
		}
		printf("Average\t%2.2lf\n",average_ratio*100);	
		
	}

	/*!
	  @fn		void SaveRecognitionResult(char *filename)
	  @brief	�F�������t�@�C���ɏo�͂���
	  @param	[in] *filename	�t�@�C�����ւ̃|�C���^
	*/
	void SaveRecognitionResult(char *filename)
	{
		int i, j;
		FILE *fp;

		if((fp = fopen( filename, "w" )) == NULL){
			printf("The file \"%s\" was not opened.", filename);
			return;
		}

		for (i=0; i<class_num; i++){
			fprintf(fp, "\tC%d", i);	
		}
		fprintf(fp, "\n");

		for (i=0; i<class_num; i++){
			fprintf(fp, "C%d", i);	
			for (j=0; j<class_num; j++){
				fprintf(fp, "\t%4d", res[i][j]);	
			}
			fprintf(fp, "\n");
		}		
		fprintf(fp, "\nRecognition Ratio\n");
		for (i=0; i<class_num; i++){
			fprintf(fp, "Class %d\t%3.2lf\n", i, ratio[i]*100);	
		}
		fprintf(fp, "Average\t%2.2lf\n",average_ratio*100);	

		fclose(fp);		
	}

} RecognitionResult;

#endif//__RECOGNITIONRESULT__