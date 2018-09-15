#include <iostream>
using namespace std;
#pragma once

#include <windows.h>
#include <il\il.h>//|
// Подключаем DevIL
#pragma comment(lib, "DevIL.lib") //|


enum Pixelformat
{
	AG_BGR,  //Формат пикселей B|G|R
	AG_BGRA, //Формат пикселей B|G|R|A
	AG_RGB,  //Формат пикселей R|G|B
	AG_RGBA  //Формат пикселей R|G|B|A
};

enum ImageType
{
	AG_BMP = 0x0420,  //!< Microsoft Windows Bitmap - .bmp extension
	AG_JPG = 0x0425,  //!< JPEG - .jpg, .jpe and .jpeg extensions
	AG_PNG = 0x042A,  //!< Portable Network Graphics - .png extension
	AG_TGA = 0x042D,  //!< TrueVision Targa File - .tga, .vda, .icb and .vst extensions
	AG_TIF = 0x042E,  //!< Tagged Image File Format - .tif and .tiff extensions
	AG_JP2 = 0x0441   //!< Jpeg 2000 - .jp2 extension
};

typedef struct BaseIMGInfo
{
	int Depth;   //Глубина изобаржения(нужно только для 3D текстур), по умолчанию = 1
	int Format;  //Формат пикселей
	int Type;    //Тип данных в памяти, в основном = IL_UNSIGNED_BYTE
};

typedef struct ImageData
{
	unsigned char * Data; //Указатель на данные изобржения

	int Width;            //Ширина изображения
	int Height;           //Высота изображения
	int Bpp;              //Количество байт на пиксель
	int Stride;           //Количество байт в одной строке пикселей

	Pixelformat PixFormat;//Формат пикселей
	BaseIMGInfo BaseInfo; //Основные параметры изображения, нужные для сохранения изображений в DevIL

	int R_idx;            //Позиция красного в пикселе
	int G_idx;            //Позиция зелёного в пикселе
	int B_idx;            //Позиция синего в пикселе
	int A_idx;            //Позиция альфа-канала в пикселе, только для AG_RGBA или AG_BGRA
};

ImageData * agLoadImage(char * FileName); //Функция для загрузки изображения
bool agSaveImage(ImageData * IMG, char * FileName, ImageType IType); //Функция для сохранения изображения
ImageData * agNewImage(int Width, int Height, Pixelformat PFormat); //Функция для создания нового,пустого, изображения
ImageData * agCloneImage(ImageData * Src); //Функция для создания копии изображения
