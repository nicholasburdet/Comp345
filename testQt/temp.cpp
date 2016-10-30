#include <iostream>
#include <string>
#include <conio.h>
#include "MapScreen.h"
using namespace std;

int width = 11;
int height = 12;
int currentPosition[2] = { 0,0 };

void startUp()
{

}

void output(MapScreen ms)
{
	system("cls");
	for (int yAxis = 0; yAxis < height + 2; yAxis++)
	{
		for (int xAxis = 0; xAxis < width + 2; xAxis++)
		{
			if (xAxis == 0 || yAxis == 0 || xAxis == width + 1 || yAxis == height + 1)
			{
				//Drawing the edges
				cout << " # ";
			}
			else
			{
				if (ms.isPassable(xAxis - 1, yAxis - 1))
				{
					cout << "   ";
				}
				else
				{
					cout << " # ";
				}
			}
		}
		cout << "\n\n";
	}
}

void input()
{
	if (_kbhit())
	{
		if (_getch() == '\033')
		{
			_getch();
			switch (_getch())
			{
			case 'A':
				//UP
				if (currentPosition[1] != 0)
				{
					currentPosition[1]--;
				}
				break;
			case 'B':
				//DOWN
				if (currentPosition[1] != height - 1)
				{
					currentPosition[1]++;
				}
				break;
			case 'C':
				//RIGHT
				if (currentPosition[0] != 0)
				{
					currentPosition[0]--;
				}
				break;
			case 'D':
				//LEFT
				if (currentPosition[0] != width - 1)
				{
					currentPosition[0]++;
				}
				break;

			}
		}
	}
}

int amain()
{
	int i;

	string a = "hello";
	string b = "hello";
	bool end = false;

	MapScreen ms;
	ms.initMap(width, height);
	cout << "Checking..";

	/*
	if (a.compare(b) == 0)
	{
	if (ms.checkExit() == true)
	cout << "exit found";
	else
	cout << "exit no found";
	}
	*/
	output(ms);
	while (end == false)
	{
		output(ms);
		input();
	}

	//cout << "Please enter an integer";
	cin >> i;
	return 0;

}