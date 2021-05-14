#include <jni.h>
#include <string>
#include <cstring>
#include <stdio.h>

using namespace std;
#ifdef __cplusplus
extern "C" {
#endif
#define CALC_MAX_LENGTH  (2000)

enum calc_error {
    NO_ERROR = 0,
    EXPR_ERROR = -1,
    EXPR_TOO_LONG = -2
};

extern char* calc(const char* expr);
#ifdef __cplusplus
}
#endif

extern "C"
JNIEXPORT jstring JNICALL
Java_com_xiwen_flexcaculator_Caculate_calc(JNIEnv *env, jclass thiz, jstring expr) {
    // TODO: implement calc()
    const char* s = env->GetStringUTFChars(expr, 0);
    jdouble ans = 0;

    return env->NewStringUTF(calc(s));
//    (*env)->ReleaseStringUTFChars(env, expr, s);
//    else return env->NewStringUTF(res);
}
