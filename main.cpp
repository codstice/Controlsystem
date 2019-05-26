#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
//#include "timestamp.h"
using namespace std;

int main()
{
	std::ifstream csv("D:/연습작품/visual studio data/cplus/test4.csv");
	csv.ignore(500, '\n'); //첫 줄(세로 index)을 무시한다.
	std::string line;

	string log_GPIO_CDM[3];
	vector <vector < float > > log_CDM_reg;
	string log_CDM_time[3][2];

	if (csv.is_open()) {
		int row = 3; //배열의 인덱스를 세기위한 변수
		int col = 5;
		log_CDM_reg.assign(row, vector<float>(col, 1));

		int i = 0; //i는 각종 장치들. 0번:printer 1번:aircon 2번:door. 
		for (std::string row_line; std::getline(csv, row_line);)
		{
			//첫 열(가로 index)을 무시한다.
			const auto pos = row_line.find(',');
			if (pos != string::npos)
				row_line.erase(0, pos + 1);

			std::istringstream row_stream(row_line);
			int j = 0; //j는 각종 장치들의 레지스터들.
			for (std::string column; std::getline(row_stream, column, ',');)
			{
				if (j == 0) //hex
				{
					log_GPIO_CDM[i] = column;
					cout << log_GPIO_CDM[i] << endl; //확인용
				}
				else if (j == 3)
				{
					log_CDM_time[i][j-3] = column; //시간은 string data에 저장
				}
				else if (j == 4)
				{
					log_CDM_time[i][j-3] = column;
					cout << "레지스터" << i << "의 최근 수정 시간 : " << log_CDM_time[i][j - 4] + " " + log_CDM_time[i][j-3] << endl; //확인용
				}
				else {
					log_CDM_reg[i][j] = stof(column.c_str());
					cout << stof(column.c_str()) << endl; //확인용
				}
				j++;
			}
			i++;
		}

		/***showing. if i=0 : printer , i=1 : aircon , i=2 : door***/
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (j >= 3)
				{
					cout << log_CDM_time[i][j-3] << "\t";
				}

				else if (j == 0) {
					cout << log_GPIO_CDM[i] << "\t";
				}
				else 
					cout << log_CDM_reg[i][j] << "\t";
			}
			cout << endl;
		}
	}
	else {
		cout << "Unable to open file";
	}
}


/*타임스탬프 구하는법
https://kimgagakk.tistory.com/493 +
int index = column.find_first_of("-");
					string sub_str = column.substr(0, index);
					int year = atoi(sub_str.c_str());
					column = column.substr(index + 1);

					index = column.find_first_of("-");
					sub_str = column.substr(0, index);
					int month = atoi(sub_str.c_str());

					index = column.find_first_of(" ");
					sub_str = column.substr(0, index);
					int day = atoi(column.c_str());

					index = column.find_first_of(":");
					sub_str = column.substr(0, index);
					int hour = atoi(column.c_str());

					index = column.find_first_of(":");
					sub_str = column.substr(0, index);
					int minute = atoi(column.c_str());

					column = column.substr(index+1);
					int second = atoi(column.c_str());

					//날짜 시간 나누는거 */
