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


class printer : public Target_model{ // 초기화는 파일입출력을 통해 받도록 한다.
	int ink; 
	int paper;
	int last;		

    int *Register[4] = {&GPIO_CDM, &ink, &paper, &last};
	virtual void status(){cout<<"잉크 : "<<ink<<"%\n"<<"종이 : "<<paper<<"%\n"<<"마지막 변경시간 : "<<last<<"%\n\n";}
	virtual void autoCtl(int *rgst, int value){
		cout<<"잉크(0~100) 종이(0~100)\n조작할 양을 입력하세요 : ";
		cin >>ink>>paper;
	}
};

class air_con{ // 초기화는 파일입출력을 통해 받도록 한다.
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

class door{ // 초기화는 파일입출력을 통해 받도록 한다.
	int is_open;
    int is_error;
	int last;

//	int *Register[4] = {&GPIO_CDM, &is_open, &is_error, &last};
	virtual void status(){cout<<"개폐여부(0:닫힘 1:열림) : "<<is_open<<"%\n"<<"기능이상(0:이상무 1:이상) : "<<is_error<<"%\n"<<"마지막 변경시간 : "<<last<<"%\n\n";}
	virtual void autoCtl(int *rgst, int value){
		cout<<"개폐여부(0:닫힘 1:열림) 기능이상(0:이상무 1:이상)\n조작할 양을 입력하세요 : ";
		cin >>is_open>>is_error;
	}
};
