/*
    BRANDOM EDUARDO VEGA ENCISO
    IIA
    1BM1
    17/12/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define VALIDSIZE 512

#define BMP 0x4D42
#define isBMP(type) (type == BMP ? 1 : 0)

typedef struct 
{
	uint32_t size;						// Tamaño del archivo 
	uint16_t AdicionalCarecteristics;	// Informacion reservada de la imagen
	uint16_t copyReserved;				// idk
	uint32_t offset;					// Valor donde empieza el pixel 0
} IHDR;

typedef struct 
{
	uint32_t ihdrSize;		// Tamaño de la cabecera 
	uint32_t width;			// Ancho de la imagen
	uint32_t height;		// Alto de la imagen
	uint16_t channels;		// Planos de color 
	uint16_t bpp;			// bits por pixel	// if 32, r 1 byte, g 1 byte, b 1 byte, a 1 byte
	uint32_t compression;	// Informacion sobre la compresion utilizada
	uint32_t imgSize;		// Tamaño de los datos de imagen 
	uint32_t resX;			// Resolucion X
	uint32_t resY;			// Resolucion Y 
	uint32_t colorsRange;	// Rango de colores
	uint32_t imxtcolors;	// idk
} IDAT;

typedef struct
{
	uint16_t signatureFile;	// type file
	IHDR header;			// header
	IDAT data;				// data
	unsigned char* rgbquad; 
	unsigned char* matriz;
	char *name;				// image's name
} Image;

int ImageInfo(Image* image, char* path);
int saveResult(Image* image);
int writeResult(Image* image);
void addImages(Image* , Image*, Image*, Image* );
void liberarMemoria(Image* img1,Image* img2,Image* img3,Image* imageResult);