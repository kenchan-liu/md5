#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))              //F函数
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))              //G函数
#define H(x, y, z) ((x) ^ (y) ^ (z))                         //H函数
#define I(x, y, z) ((y) ^ ((x) | (~z)))                      //I函数
#define LEFTSHIFT(x, n) (((x) << (n)) | ((x) >> (32-(n)))) 

#define FF(a, b, c, d, x, s, ac) { (a) += F ((b), (c), (d)) + (x) + ac; (a) = LEFTSHIFT ((a), (s)); (a) += (b); }
#define GG(a, b, c, d, x, s, ac) { (a) += G ((b), (c), (d)) + (x) + ac; (a) = LEFTSHIFT ((a), (s)); (a) += (b); }
#define HH(a, b, c, d, x, s, ac) { (a) += H ((b), (c), (d)) + (x) + ac; (a) = LEFTSHIFT ((a), (s)); (a) += (b); }
#define II(a, b, c, d, x, s, ac) { (a) += I ((b), (c), (d)) + (x) + ac; (a) = LEFTSHIFT ((a), (s)); (a) += (b); }

#define T(i) 4294967296 * abs(sin(i))
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <streambuf>
using namespace std;


class MD5 {
public:
    void getanduse(const string &str); // 对给定长度的字符串进行MD5运算
    void getanduse(ifstream &in); // 对文件中的内容进行MD5运算
    string Tostring(); // 将MD5摘要以字符串形式输出

private:
    void Reset(); 
    void md5func(vector<uint8_t> input); 
    void Transform(const vector<uint8_t> block); // 对一个512比特的消息分组进行MD5运算
    vector<uint32_t> decoding(const vector<uint8_t>input); // 将64byte的数据块划分为16个32bit大小的子分组
    string dec2hex(uint32_t decimal); //32位十进制转成16进制，用8个字母的string表示
    vector<uint8_t> ToUint8(uint64_t num); // 将1个64位int转成vector<uint8_t>

private:
    uint32_t state[4]; // 用于表示4个初始向量
};