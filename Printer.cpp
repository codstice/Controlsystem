#include <iostream>
using namespace std;

class Printer {
	/*상속대상*/
	unsigned short *reg;
	int data;
	/*********/
	int ink;
	int paper;
	int last;

public:
	void status() { 
		cout << "잉크 잔여량 : " << ink << endl;
		cout << "종이 잔여량 : " << paper << endl;
		cout << "최근 작동 시간 : " << last << endl;
	}
	void autoCtl(unsigned short* R, int data) {
		cout << "프린터가 자동작동됩니다" << endl;
	}
	void manCtl(unsigned short* R, int data) {
		cout << "프린터가 수동작동됩니다" << endl;
	}
};
