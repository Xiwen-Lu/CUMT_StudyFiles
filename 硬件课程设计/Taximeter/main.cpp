#include<stdio.h>
#include<conio.h>
#include"ApiExUsb.h"
#include<iostream>
using namespace std;
#pragma comment(lib,"ApiExUsb.lib")

#include"TAXIMETER.h"

int main(){
	if(!Startup()) {	/*打开设备*/
		printf("ERROR: Open Device Error!\n");
		return 0;
	}
	TAXIMETER taximeter;
	Cleanup();
	return 0;
}