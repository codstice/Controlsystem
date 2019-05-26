#include<iostream>
using namespace std;

class door : public Target_model{ // 초기화는 파일입출력을 통해 받도록 한다.
public:	

	int is_open;
    int is_error;
	int last;

	int *Register[4] = {&GPIO_CDM, &is_open, &is_error, &last};
	virtual void status(){
		cout<<"개폐여부(0:닫힘 1:열림) : "<<is_open<<"%\n"<<"기능이상(0:이상무 1:이상) : "<<is_error<<"%\n"<<"마지막 변경시간 : "<<last<<"%\n\n";
	}
	virtual void autoCtl(int *rgst, int value){
		cout<<"개폐여부(0:닫힘 1:열림) 기능이상(0:이상무 1:이상)\n조작할 양을 입력하세요 : ";
		cin >>is_open>>is_error;
	}
};
