#pragma once
#include <iostream>
#include <bitset>
#include <ctime>
#include <windows.h>
#define font_blue() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define font_red() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY)
#define font_white() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define font_green() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define font_yellow() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)

using namespace std;


class Target_model {
public:
	int GPIO_CDM; // 초기화는 파일입출력을 통해 받도록 한다. gpio_cdm의 구성요소는 아래 주석과 같다.
	//bool clock_gating(전원연결 상태) //전원 켜짐(1) 꺼짐(0)
	//bool digital_enable; //중앙제어 프로그램에서 타겟에 대한 제어권한 있음(1) 없음(0)
	//bool mode;   //타겟에 대한 자동제어(1) 수동제어(0)

	int value; //기기들의 내부 요소에 들어갈 수치다.
	int manCtl(int *rgst, int v) { *rgst = v; GPIO_CDM |= 1; }
	virtual void autoCtl() = 0;
	virtual int status() = 0;
	int get_Month()
	{
		time_t now;
		struct tm *current_tm;

		now = time(NULL);
		current_tm = localtime(&now);

		return current_tm->tm_mon + 1;
	}

	int get_Hour()
	{
		time_t now;
		struct tm *current_tm;

		now = time(NULL);
		current_tm = localtime(&now);

		return current_tm->tm_hour;
	}

	int get_Minute()
	{
		time_t now;
		struct tm *current_tm;

		now = time(NULL);
		current_tm = localtime(&now);

		return current_tm->tm_min;
	}
};


class Printer : public Target_model { // initialized by File I/O 
public:
	// Printer's variables. In real, These variables is not needed because Commercial Software use register instead of.
	int ink;
	int paper;
	int last;

	//This variables is real
	int *Register[4] = { &GPIO_CDM, &ink, &paper, &last };

	virtual int status() {
		if (!(*Register[0] & 4)) {
			cout << "프린터의 전원이 꺼져있어 상태를 출력할 수 없습니다.\n\n";
			return 0;
		}
		cout << "clock, digital_enable, mode : ";font_yellow();cout << "0b" << bitset<3>(*Register[0]) << endl;font_white();
		cout << "잉크 : " << *Register[1] << "%" << endl;
		cout << "종이 : " << *Register[2] << "%" << endl;
		time_t last_to_time = *Register[3];
		cout << "마지막 변경시간 : " << ctime(&last_to_time) << endl << endl;
	}

	virtual void autoCtl() {
		if (!(*Register[0] & 4))
		{
			cout << "전원이 들어와있지 있습니다."; return;
		}
		if (!(*Register[0] & 2))
		{
			cout << "타겟 제어장치에서 타겟 회로로의 비트 입력권한이 없습니다."; return;
		}
		GPIO_CDM |= 1; // convert M bit(Auto mode) to 1 in GPIO_CDM 
		cout << "잉크(0~100%), 종이(0~100%)" << endl;
		cout << "프린터 유지보수 담당자에게 요구할 잉크의 양을 입력하세요 : ";
		cin >> *Register[1];
		cout << "프린터 유지보수 담당자에게 요구할 종이의 양을 입력하세요 : ";
		cin >> *Register[2];
		last = time(NULL); // store last modification time 
	}
};

class Aircon : public Target_model { // initialized by File I/O 
public:
	int temper;
	int operate;
	int last;

	int *Register[4] = { &GPIO_CDM, &temper, &operate, &last };
	virtual int status() {
		if (!(*Register[0] & 4)) {
			cout << "에어컨의 전원이 꺼져있어 상태를 출력할 수 없습니다.\n\n";
			return 0;
		}
		cout << "clock, digital_enable, mode : ";font_yellow();cout << "0b" << bitset<3>(*Register[0]) << endl;font_white();
		cout << "온도 : " << *Register[1] << "＇" << endl;
		cout << "운전방식(0:송풍 1:냉방 2:난방) : " << *Register[2] << endl;
		time_t last_to_time = *Register[3];
		cout << "마지막 변경시간 : " << ctime(&last_to_time) << endl << endl;
	}
	virtual void autoCtl() {
		if (!(*Register[0] & 4))
		{
			cout << "전원이 들어와있지 있습니다."; return;
		}
		if (!(*Register[0] & 2))
		{
			cout << "타겟 제어장치에서 타겟 회로로의 비트 입력권한이 없습니다."; return;
		}
		GPIO_CDM |= 1; // convert M bit(Auto mode) to 1 in GPIO_CDM 
		cout << "온도(18~40), 운전방식(0:송풍 1:냉방 2:난방)" << endl;
		do {
			cout << "온도를 입력하세요 : ";
			cin >> *Register[1];
		} while (*Register[1] < 18 || *Register[1] > 40);
		cout << "운전방식을 입력하세요 : ";
		cin >> *Register[2];

		// This area is exception handling by Month
		if (*Register[2] == 1 && (get_Month() == 11 || get_Month() == 12 || get_Month() == 1 || get_Month() == 2 || get_Month() == 3)) {
			cout << "겨울에는 냉방기능을 사용할 수 없습니다." << endl;
			*Register[2] = 2;
			cout << "난방기능을 사용하도록 설정했습니다." << endl;
		}
		if (*Register[2] == 2 && (get_Month() == 11 || get_Month() == 6 || get_Month() == 7 || get_Month() == 8 || get_Month() == 9 || get_Month() == 10)) {
			cout << "여름에는 난방기능을 사용할 수 없습니다." << endl;
			*Register[2] = 1;
			cout << "냉방기능을 사용하도록 설정했습니다." << endl;
		}
		last = time(NULL); // store last modification time 
	}
};

class Door : public Target_model { // initialized by File I/O 
public:
	int is_open;
	int is_error;
	int last;

	int *Register[4] = { &GPIO_CDM, &is_open, &is_error, &last };
	virtual int status() {
		if (!(*Register[0] & 4)) {
			cout << "출입문의 전원이 꺼져있어 상태를 출력할 수 없습니다.\n\n";
			return 0;
		}
		*Register[2] = 0;

		// This area is exception handling by Hour
		// The domitary closed time is 00:00 AM ~ 05:00 AM
		if (5 > get_Hour() && *Register[1] == 1) {
			*Register[2] = 1;
		}
		else if (5 < get_Hour() && *Register[1] == 0) {
			*Register[2] = 1;
		}

		GPIO_CDM |= 1; // convert M bit(Auto mode) to 1 in GPIO_CDM 
		cout << "clock, digital_enable, mode : ";font_yellow();cout << "0b" << bitset<3>(*Register[0]) << endl;font_white();
		cout << "개폐여부(0:닫힘 1:열림) : " << *Register[1] << endl;
		cout << "기능이상(0:이상무 1:이상) : ";
		if (*Register[2]) font_red();
		cout << *Register[2] << endl;
		font_white();
		time_t last_to_time = *Register[3];
		cout << "마지막 변경시간 : " << ctime(&last_to_time) << endl << endl;
	}
	virtual void autoCtl() {
		if (!(*Register[0] & 4))
		{
			cout << "전원이 들어와있지 있습니다."; return;
		}
		if (!(*Register[0] & 2))
		{
			cout << "타겟 제어장치에서 타겟 회로로의 비트 입력권한이 없습니다."; return;
		}
		cout << "개폐방식(0:닫힘 1:열림)" << endl;
		cout << "개폐방식을 입력하세요 : ";
		cin >> *Register[1];
		last = time(NULL); // store last modification time 
	}
};

