#include "android-out.hpp"

android androidOut(ANDROID_LOG_DEBUG, "AO");
android androidErr(ANDROID_LOG_ERROR, "AE");
std::ostream aout(&androidOut);
std::ostream aerr(&androidErr);