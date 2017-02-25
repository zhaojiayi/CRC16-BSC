#include"crc.h"
#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>

const int N = 100000;//次数

using namespace std;

int main() {
	srand(time(NULL));
	double prob = 0.00001;
	for (int i = 0; i < 4; i++) {
		prob = prob * 10;//0.0001 0.001 0.01 0.1
		int error_num = 0;//消息出错
		int change_num = 0;//bit出错
		for (int j = 0; j < N; j++) {
			CRC16 a(rand());
			a.get_crc();
			a.add_crc();
			a.after_bsc_channel(prob);
			a.check_error();
			if (a.is_errors()) {//只有消息出错
				error_num++;
			}
			else if (a.is_changes()) {//bit出错,但校验为0，漏检
				change_num++;
			}
			//cout << a.val1() << endl;
			//cout << a.val2() << endl;
		}
		cout << "for channel crossover probability is " << prob << ", the probabilites of undetected errors is "
			<< double(change_num) / N << endl;
	}
	system("pause");
	return 0;
}