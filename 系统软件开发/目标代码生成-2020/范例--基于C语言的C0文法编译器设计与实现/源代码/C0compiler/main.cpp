//
//  main.cpp
//  Compiler
//
//  Created by Yang Hu on 2017/11/21.
//  Copyright © 2017年 Yang Hu. All rights reserved.
//

#include "global.h"

using namespace std;

ofstream mipsWrite,mdcdWrite,errWrite,mdcdWrite2;


int main(int argc, const char * argv[]) {

    mipsWrite.open("ZmipsWrite.asm");
    mdcdWrite.open("ZmdcdWrite.txt");
    errWrite.open("ZerrWrite.txt");

    mdcdWrite2.open("ZmdcdWriteBetter.txt");

    FiletoString();

/*
    while(pin<text.length())
    {
        getsym();
    }
*/
    {
        getsym();
        program();


        for(int i=0;i<fvcnt;i++){
            mdcdWrite << midcode[i].op << '\t' <<midcode[i].var1 << '\t' << midcode[i].var2 << '\t' << midcode[i].var3 << endl;
        }

        Tomips();

        OPT=1;
        mipsWrite.close();
        mipsWrite.open("ZmipsWriteBetter.asm");
        Tomips();

        //优化后的四元式
        better();
        for(int i=0;i<fvcnt;i++){
            mdcdWrite2 << midcode[i].op << '\t' <<midcode[i].var1 << '\t' << midcode[i].var2 << '\t' << midcode[i].var3 << endl;
        }

        mipsWrite.close();
        mdcdWrite.close();
        errWrite.close();

        mdcdWrite2.close();


    }


    return 0;
}
