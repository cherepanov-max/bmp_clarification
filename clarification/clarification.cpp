#define _CRT_SECURE_NO_WARNINGS
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
#include <math.h>
#include <cmath>

using namespace std;

struct HSL {
	float h;
	float s;
	float l;
};
struct RGB {
	int r;
	int g;
	int b;
};
struct RGBf {
	float r;
	float g;
	float b;
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

	HSL result = {h, s * 100, l * 100};
	return result;
}
RGB hsl_to_rgb(float h, float s_, float l_) {
	float c, x, m, r, g, b;
	float s = s_ / 100.0;
	float l = l_ / 100.0;
	//float h = h_ / 360.0;
	//float q, p, tr, tg, tb;
	RGB rgb;
	RGBf rgbf;

	/*if (l < 0.5) {
		q = l * (1.0 + s);
	}
	else {
		q = l + s - (l * s);
	}

	p = 2.0 * l - q;
	tr = h + (1 / 3.0);
	tg = h;
	tb = h - (1 / 3.0);

	for ()

	if (tr < 0) {
		tr = tr + 1;
	}
	if (tr > 1) {
		tr = tr - 1;
	}

	if (tg < 0) {
		tg = tg + 1;
	}
	if (tg > 1) {
		tg = tg - 1;
	}
	if (tb < 0) {
		tb = tb + 1;
	}
	if (tb > 1) {
		tb = tb - 1;
	}

	if (tr < (1 / 6.0))
	{ rgbf.r = p + ((q - p) * 6.0 * tr); }
	else if (tr >= 1 / 6.0 and tr < 0.5)
	{ rgbf.r = q; }
	else if (tr >= 0.5 and tr < 2 / 3.0)
	{ rgbf.r = p + ((q - p) * (2 / 3.0 - tr) * 6.0); }
	else 
	{ rgbf.r = p; }

	if (tg < (1 / 6.0))
	{		rgbf.g = p + ((q - p) * 6.0 * tg);
	}
	else if (tg >= 1 / 6.0 and tg < 0.5)
	{
		rgbf.g = q;
	}
	else if (tg >= 0.5 and tg < 2 / 3.0)
	{
		rgbf.g = p + ((q - p) * (2 / 3.0 - tg) * 6.0);
	}
	else
	{
		rgbf.g = p;
	}

	if (tb < (1 / 6.0))
	{ rgbf.b = p + ((q - p) * 6.0 * tb); }
	else if (tb >= 1 / 6.0 and tb < 0.5) 
	{ rgbf.b = q; }
	else if (tb >= 0.5 and tb < 2 / 3.0)
	{ rgbf.b = p + ((q - p) * (2 / 3.0 - tb) * 6.0); }
	else 
	{ rgbf.b = p; }



	rgb = { (int)round(rgbf.r * 255),(int)round(rgbf.g * 255),(int)round(rgbf.b * 255) };*/

	
	c = (1 - abs(2.0 * l - 1)) * s;
	x = c * (1 - fabs(fmod(((float)(h) / 60), 2) - 1));
	m = l - c / 2.0;

	if (h >= 0 and h < 60) {
		rgbf.r = c;
		rgbf.g = x;
		rgbf.b = 0;
	}
	else if (h >= 60 and h < 120) {
		rgbf.r = x;
		rgbf.g = c;
		rgbf.b = 0;
	}
	else if (h >= 120 and h < 180) {
		rgbf.r = 0;
		rgbf.g = c;
		rgbf.b = x;
	}
	else if (h >= 180 and h < 240) {
		rgbf.r = 0;
		rgbf.g = x;
		rgbf.b = c;
	}
	else if (h >= 240 and h < 300) {
		rgbf.r = x;
		rgbf.g = 0;
		rgbf.b = c;
	}
	else if (h >= 300 and h < 360) {
		rgbf.r = c;
		rgbf.g = 0;
		rgbf.b = x;
	}
	else {
		cout << "H > 359!";
	}

	rgb.r = round((rgbf.r + m) * 255.0);
	rgb.g = round((rgbf.g + m) * 255.0);
	rgb.b = round((rgbf.b + m) * 255.0);

	return rgb;

}

int main(int argc, char **argv)
{
	setlocale(LC_CTYPE, "rus");
	int size = 0, pixels_adress = 0, width = 0, height = 0;
	short int bits_per_pixel = 0;


	ifstream file("my.bmp", ios::in | ios::binary);

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

	/*unsigned int b = 0;
	unsigned int g = 0;
	unsigned int r = 0;
	float k;

	cout << "на скаолько процентов увеличить светлоту? (дробью)" << endl;
	cin >> k;
	cout << endl;*/
	int dop = 4 - width % 4;

	cout << endl << dop << endl;

	std::ofstream os("temp0.bmp", std::ios::binary);

	unsigned char signature[2] = { 'B', 'M' };
	unsigned int fileSize = 14 + 40 + width * height * 3;
	unsigned int reserved = 0;
	unsigned int offset = 14 + 40;

	unsigned int headerSize = 40;
	unsigned int dimensions1 = width;
	unsigned int dimensions2 = height;
	unsigned short colorPlanes = 1;
	unsigned short bpp = 24;
	unsigned int compression = 0;
	unsigned int imgSize = width * height * 3;
	unsigned int resolution[2] = { 2795, 2795 };
	unsigned int pltColors = 0;
	unsigned int impColors = 0;

	os.write(reinterpret_cast<char*>(signature), sizeof(signature));
	os.write(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
	os.write(reinterpret_cast<char*>(&reserved), sizeof(reserved));
	os.write(reinterpret_cast<char*>(&offset), sizeof(offset));

	os.write(reinterpret_cast<char*>(&headerSize), sizeof(headerSize));
	os.write(reinterpret_cast<char*>(&dimensions1), sizeof(dimensions1));
	os.write(reinterpret_cast<char*>(&dimensions2), sizeof(dimensions2));
	os.write(reinterpret_cast<char*>(&colorPlanes), sizeof(colorPlanes));
	os.write(reinterpret_cast<char*>(&bpp), sizeof(bpp));
	os.write(reinterpret_cast<char*>(&compression), sizeof(compression));
	os.write(reinterpret_cast<char*>(&imgSize), sizeof(imgSize));
	os.write(reinterpret_cast<char*>(resolution), sizeof(resolution));
	os.write(reinterpret_cast<char*>(&pltColors), sizeof(pltColors));
	os.write(reinterpret_cast<char*>(&impColors), sizeof(impColors));

	unsigned char x, r, g, b, null;

	null = 0;

	for (int i = 0; i < dimensions2; ++i)
	{
		int u = 0;
		for (int j = 0; j < dimensions1 + dop; ++j)
		{
			//x = 0;
			/*r = rand() % 256;
			g = rand() % 256;
			b = rand() % 256;*/
			file.read((char*)&b, 1);
			file.read((char*)&g, 1);
			file.read((char*)&r, 1);
			os.write(reinterpret_cast<char*>(&b), sizeof(b));
			os.write(reinterpret_cast<char*>(&g), sizeof(g));
			os.write(reinterpret_cast<char*>(&r), sizeof(r));
			if (i >= dimensions1) {
				os.write(reinterpret_cast<char*>(&null), sizeof(null));
				os.write(reinterpret_cast<char*>(&null), sizeof(null));
				os.write(reinterpret_cast<char*>(&null), sizeof(null));
			}
			//os.write(reinterpret_cast<char*>(&x), sizeof(x));
			u++;
		}
	}

	os.close();


	/*char jj, hh;
	int gg = 0;
	for (int i = 0; i < size; i++) {
		file.read((char*)&jj, 1);
		//test.write((char*)&jj, 1);
		test.read((char*)&hh, 1);
		if (jj != hh) {
			cout << gg << endl;
		}
		gg++;
	}
	test.close();
	/*file.read((char*)&jj, 1);
	cout << jj << endl;*/


	/*for (int i = 0; i < width * height * 3; i += 3) {
		file.read((char*)&b, 1);
		file.read((char*)&g, 1);
		file.read((char*)&r, 1);
		HSL hsl = rgb_to_hsl(r, b, g);
		
		cout << r << ":" << g << ":" << b << " - ";
		cout << hsl.h << ":" << hsl.s << ":" << hsl.l << " - ";
		hsl.l = hsl.l + hsl.l * k;
		if (hsl.l > 100) {
			hsl.l = 100;
		}
		RGB rgb = hsl_to_rgb(hsl.h, hsl.s, hsl.l);
		cout << hsl.h << ":" << hsl.s << ":" << hsl.l << " - ";
		cout << rgb.r << ":" << rgb.g << ":" << rgb.b << endl;
		new_file.write((char*)&rgb.b, 1);
		new_file.write((char*)&rgb.g, 1);
		new_file.write((char*)&rgb.r, 1);
	}

	//new_file.close();*/

	
	/*HSL hsl = rgb_to_hsl(225, 255, 14);
	cout << hsl.h << ":" << hsl.s << ":" << hsl.l << endl;
	RGB rgb = hsl_to_rgb(hsl.h, hsl.s, hsl.l);
	cout << rgb.r << ":" << rgb.g << ":" << rgb.b << endl;*/

	

	/*int a;

	FILE *f1, *f2;

	f1 = fopen("my.bmp", "rb"); // поток_1 для чтения файла_1
	f2 = fopen("my20.bmp", "wb"); // поток_2 для записи в файл_2

	fseek(f1, 0, SEEK_END);
	long fSize = ftell(f1); // определяем размер файла_1 в байтах
	fseek(f1, 0, SEEK_SET); // возвращаем указатель в начало

	for (int i = 0; i < fSize / 4; i++) // цикл перезаписи
	{
		fread(&a, sizeof(int), 1, f1); // читаем из файла_1
		fwrite(&a, sizeof(int), 1, f2); // записываем в файл_2
	}

	fclose(f1);
	fclose(f2);*/


	return 0;
}
