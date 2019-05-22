#include <iostream>
using namespace std;

class Door {
	/*상속대상*/
	unsigned short *reg;
	int data;
	/*********/
	int is_open; //개폐여부
	int is_error; //에러발생여부
	int last; //마지막 작동시간(로그)
	int room;
public:
	void status() {
		cout << "개폐여부 : " << is_open << endl;
		cout << "에러발생여부 : " << is_error << endl;
		cout << "최근 작동 시간 : " << last << endl;
	}
	void autoCtl(unsigned short* R, int data) {
		cout << "문이 자동으로 작동됩니다" << endl;
	}
	void manCtl(unsigned short* R, int data) {
		cout << "문이 수동으로 작동됩니다" << endl;
	}
};
