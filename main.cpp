#include <iostream>
#include <stdlib.h>
#include "Target.cpp"
//File IO
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

void read_csv_log(Printer *ptr0, Aircon *ptr1, Door *ptr2);
void upLinePrompt(int count);
void showConsole(Printer *printer1, Aircon *aircon1, Door *door1);
void menu(Printer *printer1, Aircon *aircon1, Door *door1);

int main() {
	Printer printer1;
	Aircon aircon1;
	Door door1;

	cout << "Start Central Control System Program..." << endl;
	_sleep(1000);
	read_csv_log(&printer1, &aircon1, &door1);
	printer1.GPIO_CDM = 3; //test용      
	aircon1.GPIO_CDM = 2; //test용  
	door1.GPIO_CDM = 7; //test용  


	while (true) {
		showConsole(&printer1, &aircon1, &door1);
		menu(&printer1, &aircon1, &door1);
		_sleep(4000);
		system("cls");
	}
	
}

// 콘솔 특정부분만 지워버림 (재출력할 필요가 없게됨) 사용하게 되면 필요함 https://blog.dork94.com/31
void upLinePrompt(int count)
{
	for (int i = 0; i < count; ++i) {
		//printf("%c[2K",27);
		cout << "\33[2K"; //line clear
		cout << "\x1b[A"; //up line (ESC [ A) must be support VT100 escape seq
	}
}

void showConsole(Printer *printer1, Aircon *aircon1, Door *door1) {
	//showconsole
	cout << "                               전원   권한  자동모드" << endl;
	cout << "┌───────────────────┐" << endl;
	cout << "│                   │" << endl;
	cout << "│    중 앙  제 어   │" << endl;
	cout << "│                   │" << endl;
	cout << "└───────────────────┘" << endl;
	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └─────────────────── 프린터    ";

	if ((*(printer1->Register[0]) & 1)) //자동모드 
	{
		if ((*(printer1->Register[0]) == 7)) { //전원O 권한 O (0b111)
			cout << "■     ■     ■" << endl;
		}
		else if ((*(printer1->Register[0]) == 5)) { //전원O 권한 x (0b101)
			cout << "■     □     ■" << endl;
		}
		else if ((*(printer1->Register[0]) == 3)) { //전원x 권한 O (0b011)
			cout << "□     ■     ■" << endl;
		}
		else if ((*(printer1->Register[0]) == 1)) { //전원x 권한 x (0b001)
			cout << "□     □     ■" << endl;
		}
	}
	else if (!(*(printer1->Register[0]) & 1)) //수동모드
	{
		if ((*(printer1->Register[0]) == 6)) { //전원O 권한 O (0b110)
			cout << "■     ■     □" << endl;
		}
		else if ((*(printer1->Register[0]) == 4)) { //전원O 권한 x (0b100)
			cout << "■     □     □" << endl;
		}
		else if ((*(printer1->Register[0]) == 2)) { //전원x 권한 O (0b010)
			cout << "□     ■     □" << endl;
		}
		else if ((*(printer1->Register[0]) == 0)) { //전원x 권한 x (0b000)
			cout << "□     □     □" << endl;
		}
	}
	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └─────────────────── 에어컨    ";

	if ((*(aircon1->Register[0]) & 1)) //자동모드 
	{
		if ((*(aircon1->Register[0]) == 7)) { //전원O 권한 O (0b111)
			cout << "■     ■     ■" << endl;
		}
		else if ((*(aircon1->Register[0]) == 5)) { //전원O 권한 x (0b101)
			cout << "■     □     ■" << endl;
		}
		else if ((*(aircon1->Register[0]) == 3)) { //전원x 권한 O (0b011)
			cout << "□     ■     ■" << endl;
		}
		else if ((*(aircon1->Register[0]) == 1)) { //전원x 권한 x (0b001)
			cout << "□     □     ■" << endl;
		}
	}
	else if (!(*(aircon1->Register[0]) & 1)) //수동모드
	{
		if ((*(aircon1->Register[0]) == 6)) { //전원O 권한 O (0b110)
			cout << "■     ■     □" << endl;
		}
		else if ((*(aircon1->Register[0]) == 4)) { //전원O 권한 x (0b100)
			cout << "■     □     □" << endl;
		}
		else if ((*(aircon1->Register[0]) == 2)) { //전원x 권한 O (0b010)
			cout << "□     ■     □" << endl;
		}
		else if ((*(aircon1->Register[0]) == 0)) { //전원x 권한 x (0b000)
			cout << "□     □     □" << endl;
		}
	}

	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └─────────────────── 문        ";

	if ((*(door1->Register[0]) & 1)) //자동모드 
	{
		if ((*(door1->Register[0]) == 7)) { //전원O 권한 O (0b111)
			cout << "■     ■     ■" << endl;
		}
		else if ((*(door1->Register[0]) == 5)) { //전원O 권한 x (0b101)
			cout << "■     □     ■" << endl;
		}
		else if ((*(door1->Register[0]) == 3)) { //전원x 권한 O (0b011)
			cout << "□     ■     ■" << endl;
		}
		else if ((*(door1->Register[0]) == 1)) { //전원x 권한 x (0b001)
			cout << "□     □     ■" << endl;
		}
	}
	else if (!(*(door1->Register[0]) & 1)) //수동모드
	{
		if ((*(door1->Register[0]) == 6)) { //전원O 권한 O (0b110)
			cout << "■     ■     □" << endl;
		}
		else if ((*(door1->Register[0]) == 4)) { //전원O 권한 x (0b100)
			cout << "■     □     □" << endl;
		}
		else if ((*(door1->Register[0]) == 2)) { //전원x 권한 O (0b010)
			cout << "□     ■     □" << endl;
		}
		else if ((*(door1->Register[0]) == 0)) { //전원x 권한 x (0b000)
			cout << "□     □     □" << endl;
		}
	}

	cout << "===================================================" << endl;
	cout << "[*] CLI" << endl;
	cout << "[>] ";
}

void menu(Printer *printer1, Aircon *aircon1, Door *door1) {
	int num = 7;
	string Selectmenu;
	int Selectnum;
	cin >> Selectmenu;
	cout << " " << endl;
	if (!Selectmenu.compare("프린터")) {
		cout << "1.전원 켜기/끄기\t\t2.잉크/종이 넣기 요청\t\t3.잉크 종이 잔량 확인" << endl;
		cout << "[>] ";
		cin.ignore(); //cin의 버퍼를 비움
		cin >> Selectnum;
		cout << " " << endl;
		if (Selectnum == 1) {
			if (*(printer1->Register[0]) == 1)
			{
				cout << "프린터를 끄는중.";
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 5; j++) {
						cout << ".";
						_sleep(1000);
					}
					cout << "\b\b\b\b\b";
					cout << "     ";
					cout << "\b\b\b\b\b";
				}
				cout << endl;
				*(printer1->Register[0]) ^= 0x1 << 2; //3번째 비트(전원비트)만 반전
				cout << "프린터가 꺼졌습니다." << endl;

			}
			else {
				cout << "프린터를 키는중";
				for (int i = 0; i < 2; i++) {
					//cout << "\b\b\b\b\b";
					for (int j = 0; j < 5; j++) {
						cout << ".";
						_sleep(1000);
					}
					cout << "\b\b\b\b\b";
					cout << "     ";
					cout << "\b\b\b\b\b";
				}
				cout << endl;
				*(printer1->Register[0]) ^= 0x1 << 2; //3번째 비트(전원비트)만 반전
				cout << "프린터가 켜졌습니다." << endl;
			}
		}
		else if (Selectnum == 2) {
			printer1->autoCtl();
		}
		else if (Selectnum == 3) {
			printer1->status();
		}
		//void upLinePrompt(int count)
	}
	else if (!Selectmenu.compare("에어컨")) {
		cout << "1.전원 켜기/끄기\t\t2.희망온도 설정\t\t3.현재 가동상태 확인" << endl;
		cout << "[>] ";
		cin.ignore(); //cin의 버퍼를 비움
		cin >> Selectnum;
		cout << " " << endl;
		if (Selectnum == 1) {
			if (*(aircon1->Register[0]) == 1)
			{
				cout << "에어컨을 끄는중.";
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 5; j++) {
						cout << ".";
						_sleep(1000);
					}
					cout << "\b\b\b\b\b";
					cout << "     ";
					cout << "\b\b\b\b\b";
				}
				cout << endl;
				*(aircon1->Register[0]) ^= 0x1 << 2; //3번째 비트(전원비트)만 반전
				cout << "에어컨이 꺼졌습니다." << endl;

			}
			else {
				cout << "에어컨을 키는중";
				for (int i = 0; i < 2; i++) {
					//cout << "\b\b\b\b\b";
					for (int j = 0; j < 5; j++) {
						cout << ".";
						_sleep(1000);
					}
					cout << "\b\b\b\b\b";
					cout << "     ";
					cout << "\b\b\b\b\b";
				}
				cout << endl;
				*(aircon1->Register[0]) ^= 0x1 << 2; //3번째 비트(전원비트)만 반전
				cout << "에어컨이 켜졌습니다." << endl;
			}
		}
		else if (Selectnum == 2) {
			aircon1->autoCtl();
		}
		else if (Selectnum == 3) {
			aircon1->status();
		}
		//void upLinePrompt(int count)
	}
	else if (!Selectmenu.compare("문")) {
		cout << "1.개문/폐문 설정하기\t\t2.현재 개폐여부 확인" << endl;
		cout << "[>] ";
		cin.ignore(); //cin의 버퍼를 비움
		cin >> Selectnum;
		cout << " " << endl;
		if (Selectnum == 1) {
			printer1->autoCtl();
		}
		else if (Selectnum == 2) {
			printer1->status();
		}
		//void upLinePrompt(int count)
	}
	else {
		cout << " " << endl;
		cout << "finding .." << endl;
		_sleep(2000);
		cout << "ERROR:연결된 장치가 없습니다" << endl;
	}
}


// readlog file 


int row = 3; //배열의 인덱스를 세기위한 변수
int col = 5; //배열의 인덱스를 세기위한 변수
string log_GPIO_CDM[3]; 
vector <vector < unsigned int > > log_CDM_reg;
string log_CDM_time[3][2];

void read_csv_log(Printer *ptr0, Aircon *ptr1, Door *ptr2) { // 실행과 동시에 과거에 저장된 로그로부터 데이터를 수집하도록 한다.

	std::ifstream csv("./log.csv");
	csv.ignore(500, '\n'); //첫 줄(세로 index)을 무시한다.
	std::string line;


	if (csv.is_open()) {
		
		log_CDM_reg.assign(row, vector<unsigned int>(col, 1));

		int i = 0; //i는 각종 장치들. 0번:printer 1번:aircon 2번:door. 
		for (std::string row_line; std::getline(csv, row_line);) {
			//첫 열(가로 index)을 무시한다.
			const auto pos = row_line.find(',');
			if (pos != string::npos)
				row_line.erase(0, pos + 1);

			std::istringstream row_stream(row_line);
			int j = 0; //j는 각종 장치들의 레지스터들.
			for (std::string column; std::getline(row_stream, column, ',');) {
				if (j == 0) //hex
				{
					log_GPIO_CDM[i] = column;
					//cout << log_GPIO_CDM[i] << endl; //확인용
				}
				else if (j == 3)
				{
					log_CDM_time[i][j - 3] = column; //시간은 string data에 저장
				}
				else if (j == 4)
				{
					log_CDM_time[i][j - 3] = column;
					//cout << "레지스터" << i << "의 최근 수정 시간 : " << log_CDM_time[i][j - 4] + " " + log_CDM_time[i][j-3] << endl; //확인용
				}
				else {
					log_CDM_reg[i][j] = stoi(column.c_str());
					//cout << stof(column.c_str()) << endl; //확인용
				}
				j++;
			}
			i++;
		}
		cout << "loading log success\n" << endl;

	}
	else {
		cout << "Unable to open file";
	}


	//nogada
	//csv파일로 부터 읽은 정보를 클래스이 레지스터에 저장하는 코드
	*(ptr0->Register[0]) = stoi(log_GPIO_CDM[0]);
	*(ptr0->Register[1]) = log_CDM_reg[0][0];
	*(ptr0->Register[2]) = log_CDM_reg[0][1];
	*(ptr0->Register[3]) = stoi(log_CDM_time[0][0]);

	*(ptr1->Register[0]) = stoi(log_GPIO_CDM[1]);
	*(ptr1->Register[1]) = log_CDM_reg[1][0];
	*(ptr1->Register[2]) = log_CDM_reg[1][1];
	*(ptr1->Register[3]) = stoi(log_CDM_time[1][0]);

	*(ptr2->Register[0]) = stoi(log_GPIO_CDM[2]);
	*(ptr2->Register[1]) = log_CDM_reg[2][0];
	*(ptr2->Register[2]) = log_CDM_reg[2][1];
	*(ptr2->Register[3]) = stoi(log_CDM_time[2][0]);

}
void showdata() {
	/***showing. if i=0 : printer , i=1 : aircon , i=2 : door***/
	char target_name[3][10] = { "printer","aircon","door" };
	cout << "\treg0\treg1 \treg2 \tlast" << endl;

	for (int i = 0; i < row; i++) {
		cout << target_name[i] << "\t";
		for (int j = 0; j < col; j++) {
			if (j >= 3)
			{
				cout << log_CDM_time[i][j - 3] << "\t";
			}

			else if (j == 0) {
				cout << "0b" << bitset<3>(stoi(log_GPIO_CDM[i])) << "\t";
			}
			else
				cout << log_CDM_reg[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
