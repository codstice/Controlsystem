#include<iostream>
using namespace std;
class Target_model{
public:
	int GPIO_CDM; // 초기화는 파일입출력을 통해 받도록 한다. gpio_cdm의 구성요소는 아래 주석과 같다.
	/*	bool clock_gating(전원연결 상태) //전원 켜짐(1) 꺼짐(0)
		bool degital_enable; //중앙제어 프로그램에서 타겟에 대한 제어권한 있음(1) 없음(0)
		bool mode;	//타겟에 대한 자동제어(1) 수동제어(0)
	*/
		//int *Register[4] ={&GPIO_CDM, NULL, NULL, NULL}; //기기들의 내부 요소들의 주소를 나타낸다. ex) 프린터의 경우 {CDM, 잉크, 종이, 시간} 이다.
		int data; //기기들의 내부 요소에 들어갈 수치다.

	manCtl(int *rgst, int value){*rgst = value; }
	virtual void autoCtl();
	virtual void status();
};
