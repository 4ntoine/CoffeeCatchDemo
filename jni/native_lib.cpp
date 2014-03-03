#include "native_lib.h"

#include "coffeecatch/coffeecatch.h"
#include "coffeecatch/coffeejni.h"

#include <android/log.h>

void debug(const char *format, ... ) {
    va_list argptr;
    va_start(argptr, format);
    __android_log_vprint(ANDROID_LOG_ERROR, "NATIVE_LIB", format, argptr);
    va_end(argptr);
}

/*
 * Class:     com_example_CoffeeCatchDemo_native_lib
 * Method:    native_func
 * Signature: (F)I
 */
JNIEXPORT jint JNICALL Java_com_example_CoffeeCatchDemo_native_1lib_native_1func(JNIEnv *env, jobject obj, jfloat a)
{
    COFFEE_TRY() {
    	debug("testing crash\n");
    	char *ptr = NULL;
    	*ptr = '!'; // ERROR HERE!
    	debug("unreachable\n");
    } COFFEE_CATCH() {
    	const char*const message = coffeecatch_get_message();
        debug("** FATAL ERROR: %s\n", message);

        // throw exception
        coffeecatch_throw_exception(env);
    } COFFEE_END();

    debug("finished\n");
}