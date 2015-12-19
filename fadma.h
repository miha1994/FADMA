#pragma once
#define VERSION		1.041
#include <windows.h>
#include <locale>
#include <stdio.h>
#include <iostream>
using namespace std;
#define butdwn(vk_button)		(GetAsyncKeyState(vk_button) & 1<<15)			// ���� ������� vk_button ������, ������������ �������, � ��������� ������ - ����
#define butup(vk_button)		(!butdwn(vk_button))							// ���� ������� vk_button ������, ������������ ����, � ��������� ������ - �������
#define waitbutdwn(vk_button)	while(butup(vk_button))							// �������� ������� ������� vk_button
#define waitbutup(vk_button)	while(butdwn(vk_button))						// ���� �������� ������, ������ �� ������
#define waitbutdwn_(vk_button)	while(butup(vk_button))Sleep(10)							// �������� ������� ������� vk_button
#define waitbutup_(vk_button)	while(butdwn(vk_button))Sleep(10)						// ���� �������� ������, ������ �� ������

#define setpressbut(vk_button)	{keybd_event(vk_button, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0 );keybd_event(vk_button, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0 );}
#define setpressbut_plus(vk_button,middle) {keybd_event(vk_button, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0 );middle; keybd_event(vk_button, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0 );}
#define wpressbut(vk_button,erase)	{waitbutup(vk_button); waitbutdwn(vk_button); waitbutup(vk_button); if(erase)setpressbut (VK_BACK);}

#define pause_					{waitbutup(VK_RETURN); waitbutdwn(VK_RETURN); waitbutup(VK_RETURN);}	
																				// ��� �������� �� ��������� ���� ���������� ������� ������� ������� Enter
#define exit_					{waitbutup('0');waitbutup('1');waitbutup(0x0D);ws_("\nExit?");while(butup('0') && butup('1') && butup(0x0D)); if(butdwn('1') || butdwn(0x0D)) exit(0); wc_(10);}
																				// ���� �� ������ �� ���� �� ������� 0, 1, Enter, ������ �� ������, ����� ����,
																				// � ������ ������� 1 ��� Enter, �������������� ����� �� ���������

#define wi_(integer)			fprintf(stderr,"%lld ",(__int64)(integer))		// ����� ������ �����
#define wip_(integer)			{wi_(integer); pause_;}							// ����� ������ ����� � ��������� ������� Enter ����� �����
#define wiel_(integer)			{wi_(integer); wc_(10);}						// ����� ������ ����� � ������� ����� ������ ����� ����
#define wielp_(integer)			{wiel_(integer); pause_}						// ����� ������ �����, ������� ����� ������ � ��������� ������� Enter ����� �����
#define wie_(integer)			{wi_(integer); exit_}							// ����� ������ ����� �, ���� ������������ ������� �����, ���������� ������ ���������

#define wd_(double_)			fprintf(stderr,"%Lg ",(long double)(double_))	// ����� ����� ������������� ����
#define wdp_(double_)			{wd_(double_); pause_}							// ���������� � wi_
#define wdel_(double_)			{wd_(double_); wc_(10);}
#define wdelp_(double_)			{wdel_(double_); pause_;}
#define wde_(double_)			{wd_(double_); exit_}

#define ws_(string_)			fprintf(stderr,"%s",string_)					// ����� ������
#define wsp_(string_)			{ws_(string_); pause_ }							// ���������� � wi_
#define wsel_(string_)			{ws_(string_); wc_(10);}
#define wselp_(string_)			{wsel_(string_); pause_}
#define wse_(string_)			{ws_(string_); exit_}

#define wc_(char_)				putc(char_,stderr)								// ����� �������
#define wcp_(char_)				{wc_(char_); pause_}							// ���������� � wi_
#define wcel_(char_)			{wc_(char_); wc_(10);}
#define wcelp_(char_)			{wcel_(char_); pause_}
#define wce_(char_)				{wc_(char_); exit_}

#define Pi						3.1415926535									// ���������
#define e_						2.7182818284
#define log_(Base, LogValue)	(log (double (LogValue)) / log (double (Base))) // ���������
#define lb_(LogValue)			log_ (2, LogValue)						// ��������
#define lg_(LogValue)			log_ (10, LogValue)						// ����������
#define ln_(LogValue)			log_ (e_, LogValue)						// �����������
inline double rad_ (double degree);			// ������� ���� �� �������� � �������
inline double deg_ (double radian);		// ������� ���� �� ������ � �������

#define _FOR_(I,INITVALUE,N_)	for (I = (INITVALUE); I < (N_); ++I)		// ����� ������������ �����������
#define _FOR(I,N_)				_FOR_ (I, 0, N_)							// � �������������� ����� for

#define FOR_(I,INITVALUE,N_)	for (int I = (INITVALUE), variable_N = (N_); I < variable_N; ++I)
#define FOR(I,N_)				FOR_ (I, 0, N_)
#define For(N_)					FOR (count_variable_for_loop_, N_)
#define _n_						<< ' ' <<

// �������� ������
#define clrscr					{system("cls"); gotoxy(0,0);}

char *Str (char *Str_, char *fmt, ...);

extern HANDLE hCons;

// ����� �����
class Point:public POINT {
public:
	Point (int X = 0, int Y = 0) {x = X; y = Y;}
	Point (COORD c) {x = c.X, y = c.Y;}
};
extern Point scrn;

namespace Where {
	int x();	// ������� ���������� x ������� � �������
	int y();	// ������� ���������� y ������� � �������
	Point p();	// ���������� ����� � ������������, ������������ � ������������ ������� � �������
}
void gotoxy(int x_pos, int y_pos);	// ������� ������� � ������� � ����� � ������������ x, y
Point operator + (const Point &p0, const Point &p1);
Point operator - (const Point &p0, const Point &p1);
Point operator * (const Point &p, const int i);
Point operator * (const int i,const Point &p);
bool operator == (const Point p0, const Point p1);
bool operator != (const Point p0, const Point p1);
#define coord_(coordinate, max_coord_value)		((coordinate) * (~(~long(0) << 16)) / (max_coord_value))

void getscreensize (Point &rdp); // ������� � scrn ���������� ������
void click (Point P, bool LEFT = 1);	// ���������� ������ ���� (����� ������ ����, ���� LEFT == true)
inline void click (int x, int y, bool LEFT = 1);
void line (Point A, Point B, bool LEFT = 1);	// �������� ������ ���� � ����� A, ����� ���������� ������ � ���� B � ��������� ������ ���� (����� ������ ����, ���� LEFT == true)
void line (int x1, int y1, int x2, int y2, bool LEFT = 1);
// ����� ������ ��� "�������" ����
void print_l(const char *text, int indent = 0, int width = 79);
template <class T>
class er_check{
public:
	T data;
	bool error_;
	er_check () : error_ (0) {}
};
void error(char *text);
#define error_(text) {error__(text); retval.error = 1; return retval;}
void error__(char *text);

inline bool isruss(int Char); // ���������, �������� �� ������ ������ �������� ��������

 // ������ ��� ������� �� ����� File � ������� �� � ������ string_ (���� string_ != NULL), �� ��� ���, ���� ������� f �� ������ !while_f (�� ���� �� �������� ����������� �������)
bool readallc (int (*f) (int), bool while_f, FILE *File = stdin, char *string_ = NULL);
string tolower (string s); // �� ���� �������� ������ ����������� ������� tolower

string toupper (string s); // �� ���� �������� ������ ����������� ������� toupper

void printintstr(int *StringOfInt, FILE *File = stdout, bool torus = 0);	// ����� ������, �������������� ��� ������ �� ���������� ���� int

// ����� ������� �� ������ n
class mod {
	UINT val;
	UINT n;
public:
	mod (UINT N, int value = 0): n(N), val (value % N) {if (val < 0) val += n;}
	void set_N (UINT N) {n = N; val %= N;}
	mod& operator = (int i) {return *this = mod (n,i);}
	mod& operator ++ () {val = (val+1)%n; return *this;}
	mod operator ++ (int) {mod D(*this); val = (val+1)%n; return D;}
	mod& operator -- () {val = (val+n-1) % n; return *this;}
	mod operator -- (int) {mod D(*this); val = (val+n-1) % n; return D;}
	mod operator + (int a) {return mod (n, val+a);}
	mod operator - (int a) {return mod (n, val-a);}
	mod & operator += (int a) { return *this = *this + a; }
	mod & operator -= (int a) { return *this = *this - a; }
	operator int () { return val; }
};

#define MAX_NUMBER_OF_DIGITS -1
// ����� ��������� ������������� ������� number � �������� ����� ������ �� �����, ���� endline == true
template <class T>
void binout (T number, bool endline = true,int Number_of_digits = MAX_NUMBER_OF_DIGITS);
inline int setcolor (int color);	// ������ ���� ��������� � ������� �������� � ������� �����
int setcolor (const char *color);	// ������ ���� ��������� � ������� �������� � ������� ������
int to_color (const char *color);	
#pragma comment(lib, "winmm.lib")
#include <MMSystem.h>

// ������
class timer {
	ULONG time, ptime;
	bool stopped;
public:
	timer () {reset ();}
	void reset () {	stopped = 0; time = timeGetTime (); }	// �������� �����
	void stop () { ptime = timeGetTime (); stopped = 1;}	// ������������� ������
	void restart () { if(stopped) {stopped = 0; time += timeGetTime() - ptime;}	// ����������� ������
		else error("������ �� ��� ���������� ����� ������� restart");
	}
	ULONG get_time () {return stopped ? ptime - time : timeGetTime () - time;} // �������� �����
	void show_time () { wiel_ (get_time ());}		// ����� ������� � stderr
};

extern int MENU_Color;
// ��������� ������ � ������������� ����� �������, � ������� ��������� ������ title � num_of_options ��������� ������
// (������, ���������� �������� ������ ���������� � �������, ������� � 3-�� ���������). ������������ ��������� �������� ����� ���������� ������ ����
int menu (string title, int num_of_options, ...);	

//template <class T>
int getval (int *var,char * text, bool clearScreen); // ������ �����, ���� clearScreen == true, ������� text � ��������� � *var ��������. ���������� *var.