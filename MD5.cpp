#include "MD5.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <streambuf>
using namespace std;
//getanduse
void MD5::getanduse(const string &str) {
    Reset();
    vector<uint8_t> input;
    for (int i = 0; i < str.size(); ++i) {
        input.push_back(str[i]);
    }
    md5func(input);
}

// 对文件中的内容进行MD5运算
void MD5::getanduse(ifstream &in) {
    Reset();
    string str((istreambuf_iterator<char>(in)), istreambuf_iterator<char>()); 
    vector<uint8_t> input;
    for (int i = 0; i < str.size(); ++i) {
        input.push_back(str[i]);
    }
    md5func(input);
}

void MD5::md5func(vector<uint8_t> input) {
    // 消息填充
    vector<uint8_t> padding(64, (uint8_t)0);


    vector<uint8_t> lenn = ToUint8(input.size() * 8);
    padding[0] = (uint8_t)128;
    
    if (input.size() * 8 % 512 == 448) {
        input.insert(input.end(), padding.begin(), padding.end());
    }
    else {
        int index = 0;
        while(input.size() * 8 % 512 != 448) {
            input.push_back(padding[index++]);
        }
    }
    input.insert(input.end(), lenn.begin(), lenn.end());

    // 开始MD5运算，每次512bit=8*64
    int count = input.size() / 64;
    for (int i = 0; i < count; ++i) {
        vector<uint8_t> md5input;
        md5input.insert(md5input.end(), input.begin() + i * 64, input.begin() + (i + 1) * 64); 
        Transform(md5input);
    }
}

void MD5::Reset() {
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
}

string MD5::Tostring() {
    string strResult;
    for(int i = 0; i < 4; ++i) {
        strResult += dec2hex(htobe32(state[i]));
    }
    return strResult;
}

void MD5::Transform(const vector<uint8_t> block) {
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
    vector<uint32_t> x = decoding(block);
    FF(a, b, c, d, x[0],  7, T(1)); 
    FF(d, a, b, c, x[1],  12, T(2)); 
    FF(c, d, a, b, x[2],  17, T(3)); 
    FF(b, c, d, a, x[3],  22, T(4)); 
    FF(a, b, c, d, x[4],  7, T(5)); 
    FF(d, a, b, c, x[5],  12, T(6)); 
    FF(c, d, a, b, x[6],  17, T(7)); 
    FF(b, c, d, a, x[7],  22, T(8)); 
    FF(a, b, c, d, x[8],  7, T(9)); 
    FF(d, a, b, c, x[9],  12, T(10)); 
    FF(c, d, a, b, x[10], 17, T(11)); 
    FF(b, c, d, a, x[11], 22, T(12));
    FF(a, b, c, d, x[12], 7, T(13)); 
    FF(d, a, b, c, x[13], 12, T(14)); 
    FF(c, d, a, b, x[14], 17, T(15)); 
    FF(b, c, d, a, x[15], 22, T(16)); 
    
    //第 2 轮 
    GG (a, b, c, d, x[1],  5, T(17));
    GG (d, a, b, c, x[6],  9, T(18)); 
    GG (c, d, a, b, x[11], 14, T(19)); 
    GG (b, c, d, a, x[0],  20, T(20)); 
    GG (a, b, c, d, x[5],  5, T(21)); 
    GG (d, a, b, c, x[10], 9, T(22)); 
    GG (c, d, a, b, x[15], 14, T(23)); 
    GG (b, c, d, a, x[4],  20, T(24)); 
    GG (a, b, c, d, x[9],  5, T(25)); 
    GG (d, a, b, c, x[14], 9, T(26)); 
    GG (c, d, a, b, x[3],  14, T(27)); 
    GG (b, c, d, a, x[8],  20, T(28)); 
    GG (a, b, c, d, x[13], 5, T(29)); 
    GG (d, a, b, c, x[2],  9, T(30)); 
    GG (c, d, a, b, x[7],  14, T(31)); 
    GG (b, c, d, a, x[12], 20, T(32)); 

    // 第 3 轮 
    HH (a, b, c, d, x[5],  4, T(33)); 
    HH (d, a, b, c, x[8],  11, T(34)); 
    HH (c, d, a, b, x[11], 16, T(35)); 
    HH (b, c, d, a, x[14], 23, T(36)); 
    HH (a, b, c, d, x[1],  4, T(37)); 
    HH (d, a, b, c, x[4],  11, T(38)); 
    HH (c, d, a, b, x[7],  16, T(39)); 
    HH (b, c, d, a, x[10], 23, T(40)); 
    HH (a, b, c, d, x[13], 4, T(41)); 
    HH (d, a, b, c, x[0],  11, T(42)); 
    HH (c, d, a, b, x[3],  16, T(43)); 
    HH (b, c, d, a, x[6],  23, T(44)); 
    HH (a, b, c, d, x[9],  4, T(45)); 
    HH (d, a, b, c, x[12], 11, T(46)); 
    HH (c, d, a, b, x[15], 16, T(47)); 
    HH (b, c, d, a, x[2],  23, T(48)); 
    
    //  第 4 轮 
    II (a, b, c, d, x[0],  6, T(49));
    II (d, a, b, c, x[7],  10, T(50));
    II (c, d, a, b, x[14], 15, T(51));
    II (b, c, d, a, x[5],  21, T(52));
    II (a, b, c, d, x[12], 6, T(53));
    II (d, a, b, c, x[3],  10, T(54));
    II (c, d, a, b, x[10], 15, T(55));
    II (b, c, d, a, x[1],  21, T(56));
    II (a, b, c, d, x[8],  6, T(57));
    II (d, a, b, c, x[15], 10, T(58));
    II (c, d, a, b, x[6],  15, T(59));
    II (b, c, d, a, x[13], 21, T(60));
    II (a, b, c, d, x[4],  6, T(61));
    II (d, a, b, c, x[11], 10, T(62));
    II (c, d, a, b, x[2],  15, T(63));
    II (b, c, d, a, x[9],  21, T(64));
    
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}
//coding
vector<uint32_t> MD5::decoding(const vector<uint8_t>input) {
    // input的4个8bit数字合并成一个output的32bit数字，但是要反过来，ABCD->DCBA
    vector<uint32_t> output;
    for (int i = 0; i < input.size() / 4; ++i) {
        uint32_t temp = 0;
        for (int j = 3; j >= 0; --j) {
            temp += input[i * 4 + j];
            if (j != 0) {
                temp = temp << 8;
            }
        }
        output.push_back(temp);
    }
    return output;
}

string MD5::dec2hex(uint32_t decimal) {
    string hex;
    uint32_t help = 4026531840;
    map<int, string> mapping = { {0, "0"},  {1, "1"},  {2, "2"},  {3, "3"},{4, "4"},  {5, "5"},  {6, "6"},  {7, "7"},{8, "8"},  {9, "9"},  {10, "a"}, {11, "b"}, {12, "c"}, {13, "d"}, {14, "e"}, {15, "f"} };
    for (int i = 0; i < 8; ++i) {
        int tempResult = (decimal & help) >> 28;
        hex += mapping[tempResult];
        decimal = decimal << 4;
    }
    return hex;
}

// 将1个64位int转成vector<uint8_t>
vector<uint8_t> MD5::ToUint8(uint64_t num) {
    vector<uint8_t> result(8);
    uint8_t help = 255;
    for (int i = 0; i < 8; ++i) {
        result[i] = num & help;
        num = num >> 8;
    }
    return result;
}
