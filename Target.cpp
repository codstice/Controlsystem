#include<iostream>
#include<bitset>
using namespace std;

class Target_model{
protected:
	int GPIO_CDM; // 초기화는 파일입출력을 통해 받도록 한다. gpio_cdm의 구성요소는 아래 주석과 같다.
	/*	bool clock_gating(전원연결 상태) //전원 켜짐(1) 꺼짐(0)
		bool degital_enable; //중앙제어 프로그램에서 타겟에 대한 제어권한 있음(1) 없음(0)
		bool mode;	//타겟에 대한 자동제어(1) 수동제어(0)
	*/
		//int *Register[4] ={&GPIO_CDM, NULL, NULL, NULL}; //기기들의 내부 요소들의 주소를 나타낸다. ex) 프린터의 경우 {CDM, 잉크, 종이, 시간} 이다.
		int value; //기기들의 내부 요소에 들어갈 수치다.

	manCtl(int *rgst, int value){*rgst = this->value; }
	virtual void autoCtl() = 0;
	virtual void status() = 0;
};


class Printer : public Target_model{ // 초기화는 파일입출력을 통해 받도록 한다.
public:
	int ink; 
	int paper;
	int last;		

    int *Register[4] = {&GPIO_CDM, &ink, &paper, &last};
	virtual void status(){
		cout<<"clock, degital_enable, mode : "<<bitset<3>(GPIO_CDM)<<endl;
		cout<<"잉크 : "<<ink<<"%"<<endl;
		cout<<"종이 : "<<paper<<"%"<<endl;
		cout<<"마지막 변경시간 : "<<last<<endl<<endl;
	}
	virtual void autoCtl(){
		GPIO_CDM |=1; //GPIO_CDM 에서 M비트(자동화 모드)를 강제로 1로 만든다.
		cout<<"잉크(endl), 종이(0~100)"<<endl;
		cout<<"프린터 유지보수 담당자에게 요구할 잉크의 양을 입력하세요 : ";
		cin >>ink;
		cout<<"프린터 유지보수 담당자에게 요구할 종이의 양을 입력하세요 : ";
		cin >>paper;
	}
};

class Aircon : public Target_model{ // 초기화는 파일입출력을 통해 받도록 한다.
public:
	int temper;
	int operate;
	int last;

//	int *Register[4] = {&GPIO_CDM, &temper, &operate, &last};
	virtual void status(){
		cout<<"clock, degital_enable, mode : "<<bitset<3>(GPIO_CDM)<<endl;
		cout<<"온도 : "<<temper<<"%"<<endl;
		cout<<"운전방식(0:송풍 1:냉방 2:난방) : "<<operate<<"%"<<endl;
		cout<<"마지막 변경시간 : "<<last<<"%"<<endl<<endl;
	}
	virtual void autoCtl(){
		GPIO_CDM |=1; //GPIO_CDM 에서 M비트(자동화 모드)를 강제로 1로 만든다.
		cout<<"온도(18~40), 운전방식(0:송풍 1:냉방 2:난방)"<<endl;
		cout<<"온도를 입력하세요 : ";
		cin >>temper;
		cout<<"운전방식을 입력하세요 : ";
		cin >>operate;
	}
};

class Door : public Target_model{ // 초기화는 파일입출력을 통해 받도록 한다.
public:
	int is_open;
    int is_error;
	int last;

//	int *Register[4] = {&GPIO_CDM, &is_open, &is_error, &last};
	virtual void status(){
		GPIO_CDM |=1; //GPIO_CDM 에서 M비트(자동화 모드)를 강제로 1로 만든다.
		cout<<"clock, degital_enable, mode : "<<bitset<3>(GPIO_CDM)<<endl;
		cout<<"개폐여부(0:닫힘 1:열림) : "<<is_open<<"%"<<endl;
		cout<<"기능이상(0:이상무 1:이상) : "<<is_error<<"%"<<endl;
		cout<<"마지막 변경시간 : "<<last<<endl<<endl;
	}
	virtual void autoCtl(){
		cout<<"개폐방식(0:닫힘 1:열림)"<<endl;
		cout<<"개폐방식을 입력하세요 : ";
		cin >>is_open;
	}
};
