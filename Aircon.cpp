#include <iostream>
using namespace std;

class Aircon{ // 초기화는 파일입출력을 통해 받도록 한다.
	int temper;
	int operate;
	int last;

//	int *Register[4] = {&GPIO_CDM, &temper, &operate, &last};
	virtual void status(){cout<<"온도 : "<<temper<<"%\n"<<"운전방식(0:송풍 1:냉방 2:난방) : "<<operate<<"%\n"<<"마지막 변경시간 : "<<last<<"%\n\n";}
	virtual void autoCtl(int *rgst, int value){
		cout<<"온도(18~40) 운전방식(0:송풍 1:냉방 2:난방)\n조작할 양을 입력하세요 : ";
		cin >>temper>>operate;
	}
};


