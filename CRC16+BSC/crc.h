#ifndef C_R_C_H
#define C_R_C_H

const int blockLength = 1024 / 8;//消息位
//定义一些常数
const int A = 48271;
const long M = 2147483647;
const int Q = M / A;
const int R = M % A;

class CRC16 {
private:
	long int state;//默认种子
	unsigned char num[blockLength + 2];
	unsigned char crc[2]; //存储16位校验位
	unsigned char crc_dec[blockLength + 2];//经过信道后的码
	bool is_change;
	bool is_error;
public:
	CRC16(int a);//获取信息位并随机生成字符串
	void get_crc();
	void add_crc();
	double Uniform();
	void after_bsc_channel(double prob);
	void check_error();
	void free();
	bool is_errors();//消息是否出错
	bool is_changes();//bit是否出错
	unsigned char* val2() {
	return crc_dec;
	}
	unsigned char* val1() {
		return num;
	}
};


#endif // !C_R_C_H

