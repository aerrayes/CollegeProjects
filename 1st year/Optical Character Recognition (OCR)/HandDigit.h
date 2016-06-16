#ifndef _HAND_DIGIT_H
#define _HAND_DIGIT_H

#include <cstdlib>
#include <fstream>

using namespace std;

#define IMG_SIZE (28*28)

void getDigit(int *img)
{
	system("HandDigitEntry.exe");
	ifstream in("tmp_digit");

	for(int i = 0; i < IMG_SIZE; i++)
	{
		in >> img[i];
	}

	in.close();
}

#endif