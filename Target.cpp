#include<iostream>
#include<bitset>
#include <ctime>
//#include "time.cpp"
//#include "timestamp.h"
using namespace std;

class Target_model{
public:
	int GPIO_CDM; // 초기화는 파일입출력을 통해 받도록 한다.`			 gpio_cdm의 구성요소는 아래 주석과 같다.
	/*	bool clock_gating(전원연결 상태) //전원 켜짐(1) 꺼짐(0)
		bool degital_enable; //중앙제어 프로그램에서 타겟에 대한 제어권한 있음(1) 없음(0)
		bool mode;	//타겟에 대한 자동제어(1) 수동제어(0)
	*/
		//int *Register[4] ={&GPIO_CDM, NULL, NULL, NULL}; //기기들의 내부 요소들의 주소를 나타낸다. ex) 프린터의 경우 {CDM, 잉크, 종이, 시간} 이다.
		int value; //기기들의 내부 요소에 들어갈 수치다.
	//manCtl에 &멤버변수를 줄 땐 Register[1]과 같이 호출해서 쓰도록 한다. "보고서엔 주석으로 포인터 배열의 내용에는 실제 임베디드 장치의 레지스터를 작성하면 된다"고 작성
	int manCtl(int *rgst, int v){*rgst = v; GPIO_CDM |=1;} /* 모드변경 함수 따로 만들까?*/
	virtual int autoCtl() = 0;
	virtual int status() = 0;
}; 


class Printer : public Target_model{ // 초기화는 파일입출력을 통해 받도록 한다.
public:
	// ink, paper, last와 같은 요소들은 실제 임베디드 장치의 요소들이다. 보고서엔 "Register 배열이 있으므로 상용프로그램에서는 아래 변수는 필요없다"고 작성
	int ink; 
	int paper;
	int last;

	//manCtl에 &멤버변수를 줄 땐 Register[1]과 같이 호출해서 쓰도록 한다. 보고서엔 "포인터 배열의 내용에는 실제 임베디드 장치의 레지스터를 작성하면 된다"고 작성
    int *Register[4] = {&GPIO_CDM, &ink, &paper, &last}; 
	virtual int status(){
		cout<<"clock, degital_enable, mode : 0b"<<bitset<3>(*Register[0])<<endl;
		cout<<"잉크 : "<<*Register[1]<<"%"<<endl;
		cout<<"종이 : "<<*Register[2]<<"%"<<endl;
	    time_t last_to_time = *Register[3];   
		cout<<"마지막 변경시간 : "<<ctime(&last_to_time)<<endl<<endl;
	}
	virtual int autoCtl(){
		if (!(*Register[0] & 4))
			{cout<<"전원이 안들어와 있습니다.";return 0;}
		if (!(*Register[0] & 2))
			{cout<<"타겟 제어장치에서 타겟 회로로의 비트 입력권한이 없습니다.";return 0;}
		GPIO_CDM |=1; //GPIO_CDM 에서 M비트(자동화 모드)를 강제로 1로 만든다.
		cout<<"잉크(endl), 종이(0~100)"<<endl;
		cout<<"프린터 유지보수 담당자에게 요구할 잉크의 양을 입력하세요 : ";
		cin >>*Register[1];
		cout<<"프린터 유지보수 담당자에게 요구할 종이의 양을 입력하세요 : ";
		cin >>*Register[2];
		//cout 현재시각 표시, *Register[3]에 현재시각 저장 \n
	}
};

class Aircon : public Target_model{ // 초기화는 파일입출력을 통해 받도록 한다.
public:
	int temper;
	int operate;
	int last;

	int *Register[4] = {&GPIO_CDM, &temper, &operate, &last};
	virtual int status(){
		cout<<"clock, degital_enable, mode : 0b"<<bitset<3>(*Register[0])<<endl;
		cout<<"온도 : "<<*Register[1]<<"%"<<endl;
		cout<<"운전방식(0:송풍 1:냉방 2:난방) : "<<*Register[2]<<"%"<<endl;
	    time_t last_to_time = *Register[3];   
		cout<<"마지막 변경시간 : "<<ctime(&last_to_time)<<endl<<endl;
	}
	virtual int autoCtl(){
		if (!(*Register[0] & 4))
			{cout<<"전원이 안들어와 있습니다.";return 0;}
		if (!(*Register[0] & 2))
			{cout<<"타겟 제어장치에서 타겟 회로로의 비트 입력권한이 없습니다.";return 0;}
		GPIO_CDM |=1; //GPIO_CDM 에서 M비트(자동화 모드)를 강제로 1로 만든다.
		cout<<"온도(18~40), 운전방식(0:송풍 1:냉방 2:난방)"<<endl;
		cout<<"온도를 입력하세요 : ";
		cin >>*Register[1];
		cout<<"운전방식을 입력하세요 : ";
		cin >>*Register[2];
		//cout 현재시각 표시, *Register[3]에 현재시각 저장 \n
	}
};

class Door : public Target_model{ // 초기화는 파일입출력을 통해 받도록 한다.
public:
	int is_open;
    int is_error;
	int last;

	int *Register[4] = {&GPIO_CDM, &is_open, &is_error, &last};
	virtual int status(){
		GPIO_CDM |=1; //GPIO_CDM 에서 M비트(자동화 모드)를 강제로 1로 만든다.
		cout<<"clock, degital_enable, mode : 0b"<<bitset<3>(*Register[0])<<endl;
		cout<<"개폐여부(0:닫힘 1:열림) : "<<*Register[1]<<"%"<<endl;
		cout<<"기능이상(0:이상무 1:이상) : "<<*Register[2]<<"%"<<endl;
	    time_t last_to_time = *Register[3];   
		cout<<"마지막 변경시간 : "<<ctime(&last_to_time)<<endl<<endl;
	}
	virtual int autoCtl(){
		if (!(*Register[0] & 4))
			{cout<<"전원이 안들어와 있습니다.";return 0;}
		if (!(*Register[0] & 2))
			{cout<<"타겟 제어장치에서 타겟 회로로의 비트 입력권한이 없습니다.";return 0;}
		cout<<"개폐방식(0:닫힘 1:열림)"<<endl;
		cout<<"개폐방식을 입력하세요 : ";
		cin >>*Register[1];
		//cout 현재시각 표시, *Register[3]에 현재시각 저장 \n
	}
}; 
