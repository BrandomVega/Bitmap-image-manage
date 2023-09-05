/*
    BRANDOM EDUARDO VEGA ENCISO
    IIA
    1BM1
    17/12/2021
*/

#include "Program.h"


int ImageInfo(Image* image, char* path){
    
	FILE *fileImage = NULL;
	if (strlen(path) == 0)	//no tiene extension			
		return 3;
	else if (strchr(path, '.') == NULL)		//no tiene formato  
		return 4;
	
	fileImage = fopen(path, "rb");  
	if (!fileImage)	
		return 1;

	fread(&image->signatureFile, sizeof(uint16_t), 1, fileImage);
	if (!isBMP(image->signatureFile))			//no tiene formato bmp
		return 5;

	fread(&image->header, sizeof(IHDR), 1, fileImage);
	fread(&image->data,   sizeof(IDAT), 1, fileImage);

	if (image->data.height != VALIDSIZE || image->data.width!= VALIDSIZE)
		return 2;


    
	image->matriz = (unsigned char*)malloc(image->data.imgSize);    

	if(image->matriz==NULL){
		puts("No se pudo reservar memoria para los datos");
		fclose(fileImage);
		exit(1);
	}
	fread(image->matriz, image->data.imgSize, 1, fileImage);
	fclose(fileImage);

	return 0;
}
void initImage(Image* resultado, Image* original){
    resultado->signatureFile = BMP;
    resultado->header.AdicionalCarecteristics = original->header.AdicionalCarecteristics;
    resultado->header.copyReserved = original->header.copyReserved;
    resultado->header.offset = original->header.offset;
    resultado->header.size	= original->header.size;
    resultado->data.bpp = original->data.bpp;
    resultado->data.channels = original->data.channels;
    resultado->data.colorsRange = original->data.colorsRange;
    resultado->data.compression = original->data.compression;
    resultado->data.height = original->data.height;
    resultado->data.ihdrSize = original->data.ihdrSize;
    resultado->data.imgSize = original->data.imgSize;
    resultado->data.imxtcolors = original->data.imxtcolors;
    resultado->data.resX = original->data.resX;
    resultado->data.resY = original->data.resY;
    resultado->data.width = original->data.width;

}


int writeResult(Image* image){
	FILE *fileImage = NULL;
	
	strcat(image->name, ".bmp");
	fileImage = fopen(image->name, "wb+");
	if (!fileImage)
		return 1;

	fwrite(&image->signatureFile, sizeof(uint16_t), 1, fileImage);
	fwrite(&image->header, 1, sizeof(IHDR), fileImage);
	fwrite(&image->data,   1, sizeof(IDAT), fileImage);
	fwrite(&image->rgbquad,   1, sizeof(image->rgbquad), fileImage);
	fwrite(image->matriz, image->data.imgSize, 1, fileImage);

	fclose(fileImage);
	printf("%s created \n", image->name);
	return 0;
}


void addImages(Image* imageResult,Image* img1,Image* img2,Image* img3){
	initImage(imageResult, img1);
	imageResult->matriz = malloc(img1->data.imgSize*sizeof(char));
	imageResult->rgbquad=img1->rgbquad;
	int i;
	for (i = 0; i < img1->data.imgSize; i++){
        //imageResult->matriz[i] = img1->matriz[i]+img2->matriz[i]+img3->matriz[i]; 
        imageResult->matriz[i] = (img1->matriz[i]+img2->matriz[i]+img3->matriz[i])/3; 
		//printf("%d ",imageResult->matriz[i]);
	}
}
void liberarMemoria(Image* img1,Image* img2,Image* img3,Image* imageResult){
    free(img1);
    free(img2);
    free(img3);
    free(imageResult);
}

