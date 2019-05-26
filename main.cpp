#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	std::ifstream csv("D:/연습작품/visual studio data/cplus/test4.csv");
	csv.ignore(500, '\n'); //첫 줄(세로 index)을 무시한다.
	std::string line;
	
	vector <vector<float>> CDM_reg;
	if (csv.is_open()) {
		int row = 3; //배열의 인덱스를 세기위한 변수
		int col = 4; 
		CDM_reg.assign(row, vector<float>(col, 1));

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
				cout << stof(column.c_str()) << endl;
				CDM_reg[i][j] = stof(column.c_str());
				j++;
			}
			i++;
		}

		/************test용***************/
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << CDM_reg[i][j] << endl;
			}
		}
	}
	else {
		cout << "Unable to open file";
	}
}

