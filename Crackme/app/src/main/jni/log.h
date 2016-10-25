//
// Created by 王力 on 10/24/16.
//

#ifndef CRACKME_LOG_H
#define CRACKME_LOG_H

#define NATIVE_TAG "Crackme"
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, NATIVE_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,NATIVE_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,NATIVE_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,NATIVE_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,NATIVE_TAG,__VA_ARGS__)

#endif //CRACKME_LOG_H
