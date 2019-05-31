#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Target.cpp"
#include "readlog.cpp"
using namespace std;

int main() {
	Printer printer1;
	Aircon aircon1;
	Door door1;
	cout<< "Start Central Control System Program..." <<endl;
	_sleep(1000);
	read_csv_log(&printer1, &aircon1, &door1);
	printer1.GPIO_CDM=7;
	printer1.manCtl(&printer1.GPIO_CDM,1);
	printer1.status(); //예시임
	printer1.autoCtl();
	_sleep(2000);
}

