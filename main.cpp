#include "MD5.h"
#include<map>
#include<iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <streambuf>

using namespace std;

void help(int argc,char *argv[]) {
    
    cout << "usage：" << "\t" << "[-h] --help information " << endl;
    cout << "\t" << "[-t] --test MD5 application" << endl;
    cout << "\t" << "[-c] [file path of the file computed]" << endl;
    cout << "\t" << "\t" <<"--compute MD5 of the given file" << endl;
    cout << "\t" << "[-v] [file path of the file validated]" << endl;
    cout << "\t" << "\t" <<"--validate the integrality of a given file by manual input MD5 value" << endl;
    cout << "\t" << "[-f] [file path of the file validated] [file path of the .md5 file]" << endl;
    cout << "\t" << "\t" <<"--validate the integrality of a given file by read MD5 value from .md5 file" << endl;
}

// test the md5 function
void funct(int argc,char *argv[]) {
    if (2 != argc) {
        cout << "wrong params" << endl;
    }
    vector<string> str = {"", "a", "abc", "message", "qqqqwweeerrrt", "ABCDEFGHIJKLMNOPQ", "qwertyuiop1234567890"};
    MD5 md5;
    for (int i = 0; i < str.size(); ++i) { 
        md5.Update(str[i]);
        cout << "MD5(\"" + str[i] + "\") = " << md5.Tostring() << endl;
    }
}

void funcc(int argc,char *argv[]) {
    if (3 != argc) {
        cout << "wrong params" << endl;
    }
    string filePath = argv[2];
    ifstream fileStream(filePath);
    MD5 md5;
    md5.Update(fileStream);
    cout << "Md5 of file(\"" << filePath << "\") is " << md5.Tostring() << endl;
}

void funcv(int argc,char *argv[]) {
    if (3 != argc) {
        cout << "wrong params" << endl;
    }
    string filePath = argv[2];
    cout << "from file(\"" << filePath << "\")..." << endl;
    string input;
    cin >> input;
    ifstream fileStream(filePath);
    MD5 md5;
    md5.Update(fileStream);
    string genMD5 = md5.Tostring();
    cout << "The new MD5 value of file(\"" << filePath << "\") that has computed is" << endl << genMD5 << endl;
    if (!genMD5.compare(input)) {
        cout << "all correct!" << endl;
    }
    else {
        cout << "The file has been modified!" << endl;
    }
}

// 程序读取.md5摘要，重新计算被测文件的MD5，最后将两者逐位比较
void funcf(int argc, char *argv[]) {
    if (4 != argc) {
        cout << "wrong params" << endl;
    }
    string filePath = argv[2];
    string md5Path = argv[3];
    ifstream md5Stream(md5Path);
    string oriMD5((istreambuf_iterator<char>(md5Stream)), istreambuf_iterator<char>());
    cout << "The old MD5 value of file(\"" << filePath << "\") in " << md5Path << " is " << endl << oriMD5 << endl;

    ifstream fileStream(filePath);
    MD5 md5;
    md5.Update(fileStream);
    string genMD5 = md5.Tostring();
    cout << "The new MD5 value of file(\"" << filePath << "\") that has computed is" << endl << genMD5 << endl;
    if (!genMD5.compare(oriMD5)) {
        cout << "OK! The file is integrated" << endl;
    }
    else {
        cout << "WRONG!!" << endl;
    }
}
int main(int argc,char *argv[]) {
    string op = argv[1];
    switch(argv[1][1]){
        case 't':
            funct(argc,argv);
            break;
        case 'h':
            help(argc,argv);
            break;
        case 'c':
            funcc(argc,argv);
            break;
        case 'v':
            funcv(argc,argv);
            break;
        case 'f':
            funcf(argc,argv);
            break;
        default:
            cout<<"wrong params"<<endl;
    }
    return 0;
}