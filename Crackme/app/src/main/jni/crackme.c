#include "crackeme.h"
#include "log.h"
#include "md5.h"

#define DEBUG 0

#define CLASSNAME "com/learning/crackme/MainActivity"

static jboolean isValid(JNIEnv *env, jobject obj, jstring name, jstring serial) {
    jboolean ret = JNI_FALSE;
    char *username = (*env)->GetStringUTFChars(env, name, 0);
    char *password = (*env)->GetStringUTFChars(env, serial, 0);
    unsigned char dest[16] = { 0 };

    MD5_CTX context = { 0 };
    MD5Init(&context);
    MD5Update(&context, username, strlen(username));
    MD5Final(&context, dest);

    if(strlen(password) != 8) {
//        LOGD("Current length: %d\n", strlen(password));
        LOGD("Wrong password length (should be 8)......");
        return ret;
    }

    int i = 0;

#if DEBUG
    for (i = 0; i < 16; ++i) {
        LOGD("%d", dest[i] % 10);
    }
#endif

    for (i = 0; i < 8; ++i) {
        if(dest[2*i] % 10 != (password[i] - '0') % 10)
            return ret;
    }
    ret = JNI_TRUE;
    (*env)->ReleaseStringUTFChars(env, name, username);
    (*env)->ReleaseStringUTFChars(env, serial, password);
    return ret;
}

static JNINativeMethod gMethods[] = {
        {"isValid", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)isValid},
};

static int registerNativeMethods(JNIEnv* env, const char* className, JNINativeMethod* gMethods,
                                 int numMethods) {
    jclass clazz;
    clazz = (*env)->FindClass(env, className);

    if(clazz == NULL)
        return JNI_FALSE;

    if((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0)
        return JNI_FALSE;

    return JNI_TRUE;
}

static int registerNatives(JNIEnv* env) {

    if(!registerNativeMethods(env, CLASSNAME, gMethods, sizeof(gMethods) / sizeof(gMethods[0])))
        return JNI_FALSE;

    return JNI_TRUE;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void* reserved) {
    JNIEnv *env = NULL;
    jint result = JNI_ERR;

    if((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }

    assert(env != NULL);

    if(!registerNatives(env)) {
        LOGE("Register native methods failed!");
        return result;
    }

    return JNI_VERSION_1_6;
}


