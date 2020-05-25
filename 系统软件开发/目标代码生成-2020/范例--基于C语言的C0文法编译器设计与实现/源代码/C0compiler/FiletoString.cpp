//
//  FiletoString.cpp
//  Compiler
//
//  Created by Yang Hu on 2017/11/28.
//  Copyright © 2017年 Yang Hu. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <cassert>


using namespace std;
fstream infile;

string text="";
int pin=0;

void FiletoString(){

 //   string file;
    string file= "mytest.txt";//文件路径
   // cin >> file;


    infile.open(file.data());   //将文件流对象与文件连接起来
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行

    // text.clear();

    char temp;
    while(true)
    {
        if(infile.eof()) break;
        infile.get(temp);
        text+=temp;
    }
    text=text.substr(0,text.length()-1);

     infile.close();

}
