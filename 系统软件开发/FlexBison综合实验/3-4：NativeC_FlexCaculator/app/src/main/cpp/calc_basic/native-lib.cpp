#include <jni.h>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#define CALC_MAX_LENGTH  (2000)

enum calc_error {
    NO_ERROR = 0,
    EXPR_ERROR = -1,
    EXPR_TOO_LONG = -2
};

extern int  calc(const char* expr, double* ans);


#ifdef __cplusplus
}
#endif

extern "C" JNIEXPORT jstring JNICALL
Java_com_xiwen_flexcaculator_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_xiwen_flexcaculator_Caculate_calc(JNIEnv *env, jclass thiz, jstring expr) {
    // TODO: implement calc()
    const char* s = env->GetStringUTFChars(expr, 0);
    jdouble ans = 0;
    int err  = calc(s, &ans);
//    (*env)->ReleaseStringUTFChars(env, expr, s);

    return ans;
}