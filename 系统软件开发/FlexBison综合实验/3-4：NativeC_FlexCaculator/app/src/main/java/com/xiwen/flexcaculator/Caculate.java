package com.xiwen.flexcaculator;

public class Caculate {
    static {
        System.loadLibrary("native-lib-flex");
//        System.out.println(calc("1+2*3;"));
    }
    public static native String calc(String expr);
}
