#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <omp.h>
#include <vector>
using namespace std;

struct HSL {
	int h;
	int s;
	int l;
};
HSL rgb_to_hsl(int r_, int g_, int b_) {
	float r = r_ / 255.0;
	float g = g_ / 255.0;
	float b = b_ / 255.0;
	float c_max, c_min, delta;
	float h, s, l;
	if (r >= g & r >= b) {
		c_max = r;
	}
	else if (g >= r & g >= b) {
		c_max = g;
	}
	else {
		c_max = b;
	}

	if (r <= g & r <= b) {
		c_min = r;
	}
	else if (g <= r & g <= b) {
		c_min = g;
	}
	else {
		c_min = b;
	}

	delta = c_max - c_min;

	if (delta == 0) {
		h = 0.0;
	}
	else if (c_max == r) {
		h = 60.0 * (((g - b) / delta) + (g < b ? 6 : 0));
	}
	else if (c_max == g) {
		h = 60.0 * (((b - r) / float(delta)) + 2);
	}
	else {
		h = 60.0 * (((r - g) / float(delta)) + 4);
	}

	l = (c_max + c_min) / 2.0;

	if (delta == 0) {
		s = 0.0;
	}
	else {
		s = float(delta) / (1 - abs(2 * l - 1));
	}

	HSL result = { h, s * 100, l * 100};
	return result;
}

int main(int argc, char **argv)
{
	int size = 0, pixels_adress = 0, width = 0, height = 0;
	short int bits_per_pixel = 0;


	ifstream file("test.bmp", ios::in | ios::binary);

	// Переходим на 2 байт
	file.seekg(2, ios::beg);

	// Считываем размер файла
	file.read((char*) &size, sizeof(int));
	cout << "Size: " << size << endl;

	// Переходим на 10 байт
	file.seekg(10, ios::beg);

	// Считываем адрес, где лежит информация о пикселях
	file.read((char*)&pixels_adress, sizeof(int));
	cout << "pixels_adress: " << pixels_adress << endl;

	// Переходим на 18 байт
	file.seekg(18, ios::beg);


	//Считываем ширину картинки
	file.read((char*)&width, sizeof(int));
	cout << "width: " << width << endl;

	// Переходим на 22 байт
	file.seekg(22, ios::beg);

	//Считываем высоту картинки
	file.read((char*)&height, sizeof(int));
	cout << "height: " << height << endl;

	// Переходим на 28 байт
	file.seekg(28, ios::beg);

	//Считываем количество бит на пиксель
	file.read((char*)&bits_per_pixel, sizeof(short int));
	cout << "bits_per_pixel: " << bits_per_pixel << endl;

	//двигаемся в зону цветов пикселей
	file.seekg(pixels_adress, ios::beg);

	unsigned int b = 0;
	unsigned int g = 0;
	unsigned int r = 0;

	for (int i = 0; i < width * height * 3; i += 3) {
		file.read((char*)&b, 1);
		file.read((char*)&g, 1);
		file.read((char*)&r, 1);
		HSL hsl = rgb_to_hsl(r, b, g);
		cout << r << ":" << g << ":" << b << " - ";
		cout << hsl.h << ":" << hsl.s << ":" << hsl.l << endl;
	}

	//rgb_to_hsl(125, 145, 214);


	/*HSL hsl = rgb_to_hsl(0, 0, 128);
	cout << hsl.h << ":" << hsl.s << ":" << hsl.l << endl;*/
	return 0;
}
