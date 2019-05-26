#include <iostream>
using namespace std;

class printer : public Target_model{ // 초기화는 파일입출력을 통해 받도록 한다.
public:
	/* 상속대상 */
	int ink; 
	int paper;
	int last;		

    int *Register[4] = {&GPIO_CDM, &ink, &paper, &last};
	virtual void status(){
		cout<<"잉크 잔여량 : "<<ink<<"%\n"<<"종이 잔여량 : "<<paper<<"%\n"<<"마지막 변경시간 : "<<last<<"%\n"<<endl;
	}
	virtual void autoCtl(int *rgst, int value){
		cout<<"잉크(0~100) 종이(0~100)\n조작할 양을 입력하세요 : ";
		cin >>ink>>paper;
	}
};
