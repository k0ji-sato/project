/*! @file		main.cpp
    @brief		Step04_Binarization�v���W�F�N�g�̃��C���t�@�C��
	@n			�摜��ǂݍ����2�l�����ۑ�����
	@n			��f�ւ̃A�N�Z�X���@���K������
	@author		Ken'ichi Morooka
	@date		2012.05.29
	@version	2.0.0
*/

#include "Config.h"
#include "PgmIO.h"

void Binarization(PgmImage *src, PgmImage *dst);

int main()
{
	char filename[128];
	
	//PGM�摜���i�[���郁�����̊m��
	PgmImage *img = new PgmImage(ImageSize, ImageSize); //���͉摜
	PgmImage *res = new PgmImage(ImageSize, ImageSize); //���ʉ摜

	//�e�N���X�̉摜�������v�Z����
	int each_class_num = TrainingSampleNum/ClassNum;
	for (int label=0; label<ClassNum; label++){
		for (int sample=0; sample<each_class_num; sample++){
			sprintf(filename, TrainingDataFile, label, sample);
			printf("Loading the file %s\n", filename);
			if (!LoadPgmImage(filename, img, label)){ //�摜�̓ǂݍ���
				return 0;
			} else {

				Binarization(img, res);//�Q�l���������s��

				sprintf(filename, "binary_%d-%04d.pgm", label, sample);
				if (!SavePgmImage(filename, res)){ //���ʉ摜�̕ۑ�
					return 0;
				}
			}
		}
	}

	delete img;
	delete res;
}

/*!
  @fn		void Binarization(PgmImage *src, PgmImage *dst)
  @brief	�P�x�l�𔼕��ɂ���
  @param	[in]	*src	�ϊ����̉摜���i�[���郁�����ւ̃|�C���^
  @param	[out]	*dst	�ϊ���̉摜���i�[���郁�����ւ̃|�C���^
*/
void Binarization(PgmImage *src, PgmImage *dst)
{
	int th_val = 200;

	for (int y=0; y<src->height; y++){
		for (int x=0; x<src->width; x++){

			if (src->pixel[y][x] < th_val)
				dst->pixel[y][x] = 255;
			else
				dst->pixel[y][x] = 0;				
		}
	}
}