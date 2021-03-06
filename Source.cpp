#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
using namespace std;

#include <stdio.h>
#include <Windows.h>

int nScreenWidth = 100;			// Console Screen Size X (columns)
int nScreenHeight = 30;		// Console Screen Size Y (rows)
int countt = 0;
class Sort;
void print(Sort* sort, wchar_t* screen, HANDLE& hConsole, DWORD& dwBytesWritten);
class Sort
{
private:

	int temp;
	int count;
	int no;

public:
	int x[100];
	Sort(int n) :no(n)
	{
		for (int i = no - 1; i >= 0; i--)
		{
			x[i] = no-1-i;


		}
		this->random();
		

	}
	void init()
	{
		for (int i = no - 1; i >= 0; i--)
		{
			x[i] = no - 1 - i;


		}
	}
	void random()
	{
		for (int i = 0; i < no; i++)
		{

			int j = rand() % no;
			temp = x[i];
			x[i] = x[j];
			x[j] = temp;

		}
	}
	void BubbleSort(wchar_t* screen, HANDLE& hConsole, DWORD& dwBytesWritten)
	{
		count = 0;
		bool sorted = false;
		int last = no - 1;
		while (!sorted)
		{

			sorted = true;
			for (int j = 0; j < last; j++)
			{

				if (x[j + 1] < x[j])
				{
					temp = x[j];
					x[j] = x[j + 1];
					x[j + 1] = temp;
					sorted = false;
				}
				::print(this, screen, hConsole, dwBytesWritten);
				count++;
			}
			last--;
			
			

		}
		
	}
	void insertionSort(wchar_t* screen, HANDLE& hConsole, DWORD& dwBytesWritten)
	{
		count = 0;
		for (int i = 1; i < no; i++)
		{
			int k = i;
			for (int j = i - 1; j > -1; j--)
			{
				count++;
				

				if (x[j] > x[j + 1])
				{
					temp = x[j];
					x[j] = x[j + 1];
					x[j + 1] = temp;
					k = j;
					::print(this, screen, hConsole, dwBytesWritten);
				}
				else
					break;

			}


		}

	}
	void MergeSort()
	{

	}
	void Merge()
	{
	}
	void swap(int a, int b)
	{
		int temp;
		temp = a;
		a = b;
		b = temp;
	}
	
};


int main()
{
	
	// Create Screen Buffer
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	_CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(hConsole, &info);

	if (info.dwSize.X < nScreenWidth)
	{
		nScreenWidth = info.dwSize.X;
	}
	if (info.dwSize.Y < nScreenHeight)
	{
		nScreenHeight = info.dwSize.Y;
	}

	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];

	COORD coord = { nScreenWidth ,nScreenHeight };
	SetConsoleScreenBufferSize(hConsole, coord);

	// setting color 
	WORD chattr = FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE;

	SetConsoleTextAttribute(hConsole, chattr);
	
	//Window Size
	SMALL_RECT windowSize = { 0, 0, nScreenWidth - 1, nScreenHeight - 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
	
	if (!SetConsoleScreenBufferSize(hConsole, coord))
	{
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
		return -1;
	}
	SetConsoleActiveScreenBuffer(hConsole);

	DWORD dwBytesWritten = 0;

	Sort sort(nScreenHeight);
	

		::print(&sort, screen,hConsole,dwBytesWritten); //prints in screen by swapping buffers

		sort.BubbleSort(screen,hConsole,dwBytesWritten); // Bubble sorting algo

		sort.random(); // Randomizing the integers

		::print(&sort, screen, hConsole, dwBytesWritten); 

		sort.insertionSort(screen, hConsole, dwBytesWritten);
		Sleep(1000);


	return 0;
}

void print(Sort* sort, wchar_t *screen,HANDLE& hConsole,DWORD& dwBytesWritten)
{
	for (int x = 0; x < nScreenWidth; x++)
	{

		for (int y = 0; y < nScreenHeight; y++)
		{
			// Each Row
			if (x < sort->x[y])
			{
				/* jUST to show a better movement in sorting*/
				if(sort->x[y]%5==0)
				screen[y*nScreenWidth + x] = '-';
				else if (sort->x[y]%5 == 1)
				screen[y*nScreenWidth + x] = ';';
				else if (sort->x[y] % 5 == 2)
					screen[y*nScreenWidth + x] = '{';
				else if (sort->x[y] % 5 == 3)
					screen[y*nScreenWidth + x] = '|';
				else if (sort->x[y] % 5 == 4)
					screen[y*nScreenWidth + x] = ':';
				else
				{
				screen[y*nScreenWidth + x] = '@';
				}
			}
			else
				screen[y*nScreenWidth + x] = ' ';
	
		}
	}
	Sleep(100);
	screen[nScreenWidth * nScreenHeight - 1] = '\0';

	WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);	// Display Frame

	
	
}
