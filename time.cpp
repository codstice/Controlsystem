#include <iostream>
#include <ctime>

using namespace std;

int time_check(int mode, int time[]) {
	switch (mode) { // 시간 비교
	case 1:
		if ((time[3] >= 23 && time[4] >= 30) || 5 > time[3]) { // 오후 11시 30분부터 오전 5시까지 통금시간
			std::cout << "통금 시간입니다." << std::endl;
			return true;
		}
		break;
	default:
		std::cout << "추가 예정" << std::endl;
		break;
	}
	return false;
}

int main()
{
	time_t now;
	struct tm *current_tm;
	int time_arr[6] = {'\0'};
	now = time(NULL);
	std::cout << "현재 시각: " << now << std::endl;

	while (1) {
		now = time(NULL);
		current_tm = localtime(&now);

		time_arr[0] = current_tm->tm_year + 1900; // 년도
		time_arr[1] = current_tm->tm_mon + 1; // 달
		time_arr[2] = current_tm->tm_mday; // 일
		time_arr[3] = current_tm->tm_hour; // 시
		time_arr[4] = current_tm->tm_min; // 분
		time_arr[5] = current_tm->tm_sec; // 초

		if (time_check(1, time_arr)) break;
	}
}
