#pragma once
#include "Target.cpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void read_csv_log(Printer *ptr0, Aircon *ptr1, Door *ptr2); 
void showConsole(Printer *printer1, Aircon *aircon1, Door *door1);
void menu(Printer *printer1, Aircon *aircon1, Door *door1);
bool fexists(const std::string& filename);

int main() {

	system("mode con cols=80 lines=55");
	font_white();
	Printer printer1;
	Aircon aircon1;
	Door door1;

	//exception handling non-csv file
	if (!fexists("log.csv")) {
		cout << "csv 파일을 찾을 수 없습니다. csv 파일을 생성합니다." << endl;
		ofstream outFile("log.csv");
		outFile << ",reg1,reg2,reg3,last,\nprinter,7,90,100,1559323990 ,\naircon,6,23,2,1559323990 ,\ndoor,7,1,0,1559323990 ," << endl;
		outFile.close();
		cout << "csv 파일을 정상적으로 생성하였습니다." << endl;
	}

	cout << "Start Central Control System Program..." << endl;
	_sleep(1000);
	read_csv_log(&printer1, &aircon1, &door1);

	while (true) {
		showConsole(&printer1, &aircon1, &door1);
		cout << endl;
		cout << "========================================================" << endl << endl;
		cout << "printer status\n";
		printer1.status();
		cout << "aircon status\n";
		aircon1.status();
		cout << "door status\n";
		door1.status();
		cout << "========================================================" << endl << endl;
		cout << "[*] CLI" << endl;
		cout << "[>] ";

		menu(&printer1, &aircon1, &door1);
		_sleep(4000);
		system("cls");
	}

}

void showConsole(Printer *_printer1_, Aircon *_aircon1_, Door *_door1_) { 

	cout << "                                ";font_red();cout << "전원";font_blue();cout << "   권한";font_green();cout << "   자동모드  " << endl;font_red();
	cout << "┌───────────────────┐" << endl;
	cout << "│                   │" << endl;
	cout << "│    중 앙  제 어   │" << endl;
	cout << "│                   │" << endl;
	cout << "└───────────────────┘" << endl;
	if (*((*_printer1_).Register[0]) & 4) font_red();else font_white();
	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └──────────";
	if (*((*_printer1_).Register[0]) & 2) font_blue();else font_white();
	cout << "───────── ";
	font_white();
	cout << "프린터    ";
	font_red();
	((*((*_printer1_).Register[0]) & 4)) ? cout << "■     " : cout << "□     ";font_blue();
	((*((*_printer1_).Register[0]) & 2)) ? cout << "■     " : cout << "□     ";font_green();
	((*((*_printer1_).Register[0]) & 1)) ? cout << "■" << endl : cout << "□" << endl;
	if (*((*_aircon1_).Register[0]) & 4) font_red();else font_white();
	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └──────────";
	if (*((*_aircon1_).Register[0]) & 2) font_blue();else font_white();
	cout << "───────── ";
	font_white();
	cout << "에어컨    ";font_red();
	((*((*_aircon1_).Register[0]) & 4)) ? cout << "■     " : cout << "□     ";font_blue();
	((*((*_aircon1_).Register[0]) & 2)) ? cout << "■     " : cout << "□     ";font_green();
	((*((*_aircon1_).Register[0]) & 1)) ? cout << "■" << endl : cout << "□" << endl;

	if (*((*_door1_).Register[0]) & 4) font_red();else font_white();
	cout << " │" << endl;
	cout << " │" << endl;
	cout << " └──────────";
	if (*((*_door1_).Register[0]) & 2) font_blue();else font_white();
	cout << "───────── ";
	font_white();
	cout << "출입문    ";
	font_red();

	((*((*_door1_).Register[0]) & 4)) ? cout << "■     " : cout << "□     ";font_blue();
	((*((*_door1_).Register[0]) & 2)) ? cout << "■     " : cout << "□     ";font_green();
	((*((*_door1_).Register[0]) & 1)) ? cout << "■" << endl : cout << "□" << endl;
	font_white();

}

void menu(Printer *printer1, Aircon *aircon1, Door *door1) { //this is CLI
	int num = 7;
	string Selectmenu;
	int Selectnum;
	cin >> Selectmenu;
	cout << " " << endl;
	if (!Selectmenu.compare("프린터")) {
		cout << "1.전원 켜기/끄기\t\t2.잉크/종이 넣기 요청\t\t" << endl;
		cout << "[>] ";
		cin.ignore(); //clear cin buffer
		cin >> Selectnum;
		cout << " " << endl;
		if (Selectnum == 1) {
			if (*(printer1->Register[0]) & 4)
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
				*(printer1->Register[0]) ^= 0x1 << 2; //Only third bit(Onoff bit) reverse
				cout << "프린터가 꺼졌습니다." << endl;

			}
			else {
				cout << "프린터를 키는중";
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
				*(printer1->Register[0]) ^= 0x1 << 2; //Only third bit(Onoff bit) reverse
				cout << "프린터가 켜졌습니다." << endl;
			}
		}
		else if (Selectnum == 2) {
			printer1->autoCtl();
		}

	}
	else if (!Selectmenu.compare("에어컨")) {
		cout << "1.전원 켜기/끄기\t\t2.희망온도 설정\t\t" << endl;
		cout << "[>] ";
		cin.ignore(); //clear cin buffer
		cin >> Selectnum;
		cout << " " << endl;
		if (Selectnum == 1) {
			if (*(aircon1->Register[0]) & 4)
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
				*(aircon1->Register[0]) ^= 0x1 << 2; //Only third bit(Onoff bit) reverse
				cout << "에어컨이 꺼졌습니다." << endl;

			}
			else {
				cout << "에어컨을 키는중";
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
				*(aircon1->Register[0]) ^= 0x1 << 2; //Only third bit(Onoff bit) reverse
				cout << "에어컨이 켜졌습니다." << endl;
			}
		}
		else if (Selectnum == 2) {
			aircon1->autoCtl();
		}
	}
	else if (!Selectmenu.compare("출입문")) {
		cout << "1.출입문 관리장치 전원 켜기/끄기\t\t2.개문/폐문 설정하기\t\t" << endl;
		cout << "[>] ";
		cin.ignore(); //clear cin buffer
		cin >> Selectnum;
		cout << " " << endl;

		if (Selectnum == 1) {
			if (*(door1->Register[0]) & 4)
			{
				cout << "출입문을 잠그는중.";
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 5; j++) {
						cout << ".";
						_sleep(500);
					}
					cout << "\b\b\b\b\b";
					cout << "     ";
					cout << "\b\b\b\b\b";
				}
				cout << endl;
				*(door1->Register[0]) ^= 0x1 << 2; //Only third bit(Onoff bit) reverse
				cout << "출입문이 잠겼습니다." << endl;

			}
			else {
				cout << "출입문을 여는중";
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 5; j++) {
						cout << ".";
						_sleep(500);
					}
					cout << "\b\b\b\b\b";
					cout << "     ";
					cout << "\b\b\b\b\b";
				}
				cout << endl;
				*(door1->Register[0]) ^= 0x1 << 2; //Only third bit(Onoff bit) reverse
				cout << "출입문이 열렸습니다." << endl;
			}
		}
		else if (Selectnum == 2) {
			door1->autoCtl();
		}
	}
	else {
		cout << " " << endl;
		cout << "finding .." << endl;
		_sleep(2000);
		cout << "ERROR:연결된 장치가 없습니다" << endl;
	}
}


// read file segment
int row = 3; //row index of csv table (for Counting)
int col = 5; //col index of csv table (for Counting)

// read file values  
string log_GPIO_CDM[3]; 
vector <vector < unsigned int > > log_CDM_reg;
string log_CDM_time[3];

void read_csv_log(Printer *ptr0, Aircon *ptr1, Door *ptr2) { // Collect log data from csv 

	std::ifstream csv("./log.csv");
	csv.ignore(500, '\n'); //ignore first column. start reading second column.
	std::string line;


	if (csv.is_open()) {

		log_CDM_reg.assign(row, vector<unsigned int>(col, 1));

		int i = 0; //i means each embedded devices. 0:printer 1:aircon 2:door. 
		for (std::string row_line; std::getline(csv, row_line);) {
			
			//ignore first row. start reading second row.
			const auto pos = row_line.find(',');
			if (pos != string::npos)
				row_line.erase(0, pos + 1);


			std::istringstream row_stream(row_line);
			int j = 0; //j means each registers.

			//This loop sort by each registers and by each embedded devices
			for (std::string column; std::getline(row_stream, column, ',');) {
				if (j == 0) // first register : GPIO_CDM
				{
					log_GPIO_CDM[i] = column;
				}
				else if (j == 3) // last register : time stamp register
				{
					log_CDM_time[i]= column; //시간은 string data에 저장
				}
				else {
					log_CDM_reg[i][j] = stoi(column.c_str());
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

	//Manufacturing log datas to class's register datas 

	*(ptr0->Register[0]) = stoi(log_GPIO_CDM[0]);
	*(ptr0->Register[1]) = log_CDM_reg[0][1];
	*(ptr0->Register[2]) = log_CDM_reg[0][2];
	*(ptr0->Register[3]) = stoi(log_CDM_time[0]);

	*(ptr1->Register[0]) = stoi(log_GPIO_CDM[1]);
	*(ptr1->Register[1]) = log_CDM_reg[1][1];
	*(ptr1->Register[2]) = log_CDM_reg[1][2];
	*(ptr1->Register[3]) = stoi(log_CDM_time[1]);

	*(ptr2->Register[0]) = stoi(log_GPIO_CDM[2]);
	*(ptr2->Register[1]) = log_CDM_reg[2][1];
	*(ptr2->Register[2]) = log_CDM_reg[2][2];
	*(ptr2->Register[3]) = stoi(log_CDM_time[2]);
}

bool fexists(const std::string& filename) {
	ifstream ifile(filename.c_str());
	return (bool)ifile;
}

// not used code //

//* If you check log data from csv file, you can use this code*//
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

//* This is console clear specific area you chooseed.  https://blog.dork94.com/31
void upLinePrompt(int count)
{
	for (int i = 0; i < count; ++i) {
		//printf("%c[2K",27);
		cout << "\33[2K"; //line clear
		cout << "\x1b[A"; //up line (ESC [ A) must be support VT100 escape seq
	}
}
