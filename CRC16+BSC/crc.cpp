#include"crc.h"
#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>

using namespace std;

//从文本读入
//CRC16::CRC16() {
//	ifstream fin ("test.txt");
//	if (!fin.is_open()) {
//		cout << "error";
//		exit(-1);
//	}
//	fin.getline((char*)num, blockLength);
//	cout << num << endl;
//}

CRC16::CRC16(int a) {
	int i;
	for (i = 0; i<blockLength-1; ++i)
	{
		switch ((a % 3))
		{
		case 1:
			num[i] = 'A' + a % 26;
			break;
		case 2:
			num[i] = 'a' + a % 26;
			break;
		default:
			num[i] = '0' + a % 10;
			break;
		}
	}
	num[i] = '\0';
	is_change = false;//初始化为false
	is_error = false;
	state = a;
}

void CRC16::get_crc() {
	unsigned short tmp = (unsigned short)(0xFFFF);//初始化16个寄存器为1
	for (int i = 0; i<blockLength; i++)
	{
		tmp ^= (unsigned short)(num[i]);
		for (int j = 0; j<8; j++)
		{
			if (tmp & 1)
			{
				tmp >>= 1;
				tmp ^= 0xA001;//0x8005的反向生成式
			}
			else
			{
				tmp >>= 1;
			}
		}
	}
	crc[1] = tmp&0x00FF;//CRC低位
	crc[0] = (tmp >> 8) & 0xFF;//CRC高位
}

void CRC16::add_crc() {//将CRC码加在后两字节
	num[blockLength] = crc[1];//低位在前
	num[blockLength + 1] = crc[0];//高位在后，这里被坑了很久
}

/**************************************************************************
函数：Uniform()
功能：产生0-1间均匀分布的随机数
***************************************************************************/

double CRC16::Uniform()
{
	double u;
	int tmpState = A * (state % Q) - R * (state / Q);
	if (tmpState >= 0)
		state = tmpState;
	else
		state = tmpState + M;
	u = state / (double)M;
	return u;
}

void CRC16::after_bsc_channel(double prob) {//经过BSC信道
	for (int i = 0; i < blockLength + 2; i++) {
		unsigned char byte = 0;
		for (int j = 0; j < 8; j++) {
			unsigned char tmp = num[i] & (0x80 >> j);
			unsigned char check = Uniform() < prob;//重要一步 
			unsigned char check1 = (check)<<(7-j);
			byte = (tmp^check1) | byte;
			if (check == 1)//0变1或1变0的情况
				is_change = true;
		}
		crc_dec[i] = byte;
	}
}


void CRC16::check_error() {
	unsigned short tmp = (unsigned short)(0xFFFF);//初始化16个寄存器为1
	for (int i = 0; i<blockLength+2; i++)
	{
		tmp ^= (unsigned short)(crc_dec[i]);
		for (int j = 0; j<8; j++)
		{
			if (tmp & 1)
			{
				tmp >>= 1;
				tmp ^= 0xA001;//0x8005的反向生成式
			}
			else
			{
				tmp >>= 1;
			}
		}
	}
	if (tmp == 0) //余式为0，校验无差错
		is_error = false;
	else
		is_error = true;
}

bool CRC16::is_errors() {
	return is_error;
}

bool CRC16::is_changes() {//bit是否出错
	return is_change;
}

void CRC16::free() {
	
}
