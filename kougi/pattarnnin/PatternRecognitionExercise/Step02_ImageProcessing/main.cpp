/*! @file		main.cpp
    @brief		Step02_ImageProcessing�v���W�F�N�g�̃��C���t�@�C��
	@n			�摜��ǂݍ���ŋP�x�l��ύX���ĕۑ�����
	@n			��f�ւ̃A�N�Z�X���@���K������
	@author		Ken'ichi Morooka
	@date		2012.05.14
	@version	2.0.0
*/

#include "Config.h"
#include "PgmIO.h"

void ImageProcessing(PgmImage *src, PgmImage *dst);

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

				ImageProcessing(img, res);//�摜�����ŋP�x�l�𔼕��ɂ���

				sprintf(filename, "gray_%d-%04d.pgm", label, sample);
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
  @fn		void ImageProcessing(PgmImage *src, PgmImage *dst)
  @brief	�P�x�l�𔼕��ɂ���
  @param	[in]	*src	�ϊ����̉摜���i�[���郁�����ւ̃|�C���^
  @param	[out]	*dst	�ϊ���̉摜���i�[���郁�����ւ̃|�C���^
*/
void ImageProcessing(PgmImage *src, PgmImage *dst)
{
	for (int y=0; y<src->height; y++){
		for (int x=0; x<src->width; x++){
			//�ϊ����摜�̉�f�ɃA�N�Z�X���Ēl�𔼕��ɂ���
			//�ϊ���摜�̓����ʒu�̉�f�ɉ�f�l���i�[����
			dst->pixel[y][x] = src->pixel[y][x]/2;
		}
	}
}