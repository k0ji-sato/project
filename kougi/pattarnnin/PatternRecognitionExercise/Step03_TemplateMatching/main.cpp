/*! @file		main.cpp
    @brief		Step03_TemplateMatching�v���W�F�N�g�̃��C���t�@�C��
	@n			�w�K�T���v���摜�ƃe�X�g�T���v���摜�Ԃ�L1�������v�Z���ĕ����F��������
	@n			��{�I�ȃp�^�[���F�����@���K������
	@author		Ken'ichi Morooka
	@date		2012.05.14
	@version	2.0.0
*/

#include <stdlib.h>
#include "Config.h"
#include "PgmIO.h"
#include "RecognitionResult.h"

int LoadTemplateImages(PgmImage **tmp);
int TemplateMatching(PgmImage **tmp);

int main()
{
	PgmImage **tmp = new PgmImage*[TrainingSampleNum];
	for (int i=0; i<TrainingSampleNum; i++){
		tmp[i] = new PgmImage(ImageSize, ImageSize);
	}

	LoadTemplateImages(tmp);

	TemplateMatching(tmp);

	for (int i=0; i<TrainingSampleNum; i++){
		delete  tmp[i];
	}
	delete tmp;
	return 0;
}


/*!
  @fn		int CalcL1Distance(PgmImage *img1, PgmImage *img2)
  @brief	2���̉摜�Ԃ�L1�������v�Z����
  @param	[in]	*img1	1���ڂ̉摜
  @param	[in]	*img2	2���ڂ̉摜
  @return	L1�����l
*/
int CalcL1Distance(PgmImage *img1, PgmImage *img2)
{
	int dis = 0;
	int x, y;

	for  (y=0; y<img1->height; y++){
		for (x=0; x<img1->width; x++){
			dis += abs(img1->pixel[y][x] - img2->pixel[y][x]);
		}
	}

	return dis;
}

/*!
  @fn		int LoadTemplateImages(PgmImage **tmp)
  @brief	�w�K�p�摜��ǂݍ���
  @param	[out]	**tmp	�e���v���[�g�摜���w�K�T���v������ǂݏo���Ċi�[���郁�����ւ̃|�C���^
  @n		�ǂݏo���摜��1���Ƃ͌���Ȃ��̂�2�����|�C���^�ɂ��Ă���
  @return	1:���ׂẴe���v���[�g�̓ǂݏo���ɐ���
  @n		0:�e���v���[�g�̓ǂݏo���Ɏ��s
*/
int LoadTemplateImages(PgmImage **tmp)
{
	char filename[256];

	int img_no = 0;
	int each_class_num = TrainingSampleNum/ClassNum;
	for (int label=0; label<ClassNum; label++){
		for (int sample=0; sample<each_class_num; sample++){
			sprintf(filename, TrainingDataFile, label, sample);
			printf("\rLoading the file %s\n", filename);
			if (!LoadPgmImage(filename, tmp[img_no++], label)){
				return 0;
			}
		}
	}

	return 1;
}

/*!
  @fn		int ReturnMatchLabel(PgmImage *img, PgmImage **tmp)
  @brief	���͉摜�ɑ΂��čł�L1�������������w�K�T���v���̃N���X���x���𒲂ׂ�
  @param	[in]	*img	���͉摜
  @param	[in]	**tmp	�w�K�T���v����ǂݍ��񂾃e���v���[�g�摜�Q
  @return	L1�������ł������������N���X���x��
  @n		-1:���s
*/
int ReturnMatchLabel(PgmImage *img, PgmImage **tmp)
{
	int match_label = -1;
	int min_dis = 32767;
	for (int i=0; i<TrainingSampleNum; i++){
		int dis = CalcL1Distance(img, tmp[i]);
		if (dis < min_dis){
			min_dis = dis;
			match_label = tmp[i]->label;
		}
	}

	return match_label;
}

/*!
  @fn		int TemplateMatching(PgmImage **tmp)
  @brief	���C���֐�����Ăяo���e���v���[�g�}�b�`���O�p�֐�
  @n		�e�X�g�T���v����1�����ǂݏo���ă}�b�`���O���ʂ𓾂�
  @n		�}�b�`���O���ʂ͌��ʊi�[�p�̍\���̂ɋL�^
  @param	[in]	**tmp	�w�K�T���v����ǂݍ��񂾃e���v���[�g�摜�Q
  @return	1:���ׂẴe�X�g�T���v���̃e���v���[�g�}�b�`���O�ɐ����i�F����100%�Ƃ����Ӗ��ł͂Ȃ��I�j
  @n		0:�e�X�g�T���v���̓ǂݍ��݂Ɏ��s
*/
int TemplateMatching(PgmImage **tmp)
{
	char filename[256];
	PgmImage *img = new PgmImage(ImageSize, ImageSize);
	RecognitionResult *result = new RecognitionResult(ClassNum);

	int each_class_num = TestSampleNum/ClassNum;	//�e�N���X�̃T���v�������Z�o
	int match_label = -1;

	for (int label=0; label<ClassNum; label++){
		for (int sample=0; sample<each_class_num; sample++){
			sprintf(filename, TestDataFile, label, sample);
			printf("\rLoading the file %s\n", filename);
			if (!LoadPgmImage(filename, img, label)){	//�e�X�g�T���v���̓ǂݍ���
				return 0;
			}
			match_label = ReturnMatchLabel(img, tmp);	//�e�X�g�T���v���Ƀ}�b�`�����N���X���x���𓾂�
			result->res[img->label][match_label] ++;	//�����Ώƕ\�̊Y���������C���N�������g����
		}
	}

	result->CalcRatio();								//�F�������v�Z
	result->PrintRecognitionResult();					//�F������\��
	sprintf(filename, RecognitionResultFile, TrainingSampleNum, TestSampleNum);
	result->SaveRecognitionResult(filename);			//�F������ۑ�

	delete result;
	delete img;

	return 1;
}

