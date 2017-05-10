/*! @file		main.cpp
    @brief		Step01_ImageIOプロジェクトのメインファイル
	@n			Donfig.h内で指定しているPGM画像を読み込んで，カレントフォルダに保存する
	@n			画像の読み込み方法と保存方法を習得する
	@author		Ken'ichi Morooka
	@date		2012.05.14
	@version	2.0.0
*/

#include "Config.h"
#include "PgmIO.h"

int main()
{
	char filename[128];
	
	//PGM画像を格納するメモリの確保
	PgmImage *img = new PgmImage(ImageSize, ImageSize);

	//各クラスの画像枚数を計算する
	int each_class_num = TrainingSampleNum/ClassNum;
	for (int label=0; label<ClassNum; label++){
		for (int sample=0; sample<each_class_num; sample++){
			sprintf(filename, TrainingDataFile, label, sample);
			printf("Loading the file %s\n", filename);
			if (!LoadPgmImage(filename, img, label)){ //画像の読み込み
				return 0;
			} else {
				sprintf(filename, "save_test_%d-%04d.pgm", label, sample);
				if (!SavePgmImage(filename, img)){ //画像の保存
					return 0;
				}
			}
		}
	}

	delete img;
}

