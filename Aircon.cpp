#include <iostream>
using namespace std;

class Aircon  {
	/*상속대상*/
	unsigned short *reg;
	int data;
	int room;
	/*********/
	int temper;
	int operate;
	int last; //마지막 작동시간(로그기록)
	int mode; //에어컨 작동모드
	int room; //방의개수

public:
	void status() {
		for (int i = 0; i < room; i++) {
			if (mode == 1)
				cout << i + 1 << "번방 에어컨 온도:" << temper << "도, " << "송풍" << endl;
			else if (mode == 2)
				cout << i + 1 << "번방 에어컨 온도:" << temper << "도, " << "난방" << endl;
			else if (mode == 3)
				cout << i + 1 << "번방 에어컨 온도:" << temper << "도, " << "냉방" << endl;
			else //처음 mode 설정안하면 초기값 0
				cout << i + 1 << "현재 에어컨이 꺼져있습니다." << endl;
		}
	}
	void autoCtl(unsigned short* R, int data) {
		cout << "에어컨이 자동작동됩니다" << endl;
	}
	void manCtl(unsigned short* R, int data) {
		cout << "에어컨이 수동작동됩니다" << endl;
	}
};
