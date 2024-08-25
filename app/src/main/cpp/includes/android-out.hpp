#ifndef ANDROIDGLINVESTIGATIONS_ANDROIDOUT_H
#define ANDROIDGLINVESTIGATIONS_ANDROIDOUT_H

#include <android/log.h>
#include <sstream>

/*!
 * Use this to log strings out to logcat. Note that you should use std::endl to commit the line
 *
 * ex:
 *  aout << "Hello World" << std::endl;
 */
extern std::ostream aout;
extern std::ostream aerr;

/*!
 * Use this class to create an output stream that writes to logcat. By default, a global one is
 * defined as @a aout
 */
class android: public std::stringbuf {
public:
    /*!
     * Creates a new output stream for logcat
     * @param kLogTag the log tag to output
     */
    inline explicit android(int32_t prio, const char* kLogTag) : prio(prio), logTag_(kLogTag){}

protected:
    int sync() override {
        __android_log_print(prio, logTag_, "%s", str().c_str());
        str("");
        return 0;
    }

private:
    int32_t prio;
    const char* logTag_;
};

#endif //ANDROIDGLINVESTIGATIONS_ANDROIDOUT_H