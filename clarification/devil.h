#include <iostream>
using namespace std;
#pragma once

#include <windows.h>
#include <il\il.h>//|
// ���������� DevIL
#pragma comment(lib, "DevIL.lib") //|


enum Pixelformat
{
	AG_BGR,  //������ �������� B|G|R
	AG_BGRA, //������ �������� B|G|R|A
	AG_RGB,  //������ �������� R|G|B
	AG_RGBA  //������ �������� R|G|B|A
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
	int Depth;   //������� �����������(����� ������ ��� 3D �������), �� ��������� = 1
	int Format;  //������ ��������
	int Type;    //��� ������ � ������, � �������� = IL_UNSIGNED_BYTE
};

typedef struct ImageData
{
	unsigned char * Data; //��������� �� ������ ����������

	int Width;            //������ �����������
	int Height;           //������ �����������
	int Bpp;              //���������� ���� �� �������
	int Stride;           //���������� ���� � ����� ������ ��������

	Pixelformat PixFormat;//������ ��������
	BaseIMGInfo BaseInfo; //�������� ��������� �����������, ������ ��� ���������� ����������� � DevIL

	int R_idx;            //������� �������� � �������
	int G_idx;            //������� ������� � �������
	int B_idx;            //������� ������ � �������
	int A_idx;            //������� �����-������ � �������, ������ ��� AG_RGBA ��� AG_BGRA
};

ImageData * agLoadImage(char * FileName); //������� ��� �������� �����������
bool agSaveImage(ImageData * IMG, char * FileName, ImageType IType); //������� ��� ���������� �����������
ImageData * agNewImage(int Width, int Height, Pixelformat PFormat); //������� ��� �������� ������,�������, �����������
ImageData * agCloneImage(ImageData * Src); //������� ��� �������� ����� �����������
