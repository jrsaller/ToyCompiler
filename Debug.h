//debug.h
#define ShowMessages 0 //0 or 0

#include <iostream>

#if ShowMessages
#define MSG(X) std::cout << X << std::endl;
#else
#define MSG(X)
#endif