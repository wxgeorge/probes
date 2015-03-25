#include <stdio.h>

#define DEBUG 0
#define INFO 1

//printf("%s\n", expr);
#define Logger_DEBUG(expr) \
#if MIN_LOG_LEVEL == DEBUG \
	printf("%s\n", expr); \
#endif

#define MIN_LOG_LEVEL DEBUG
int main() {

	Logger_DEBUG("Do I print?");
}

#define MIN_LOG_LEVEL_DEBUG
#include "Logger.h"


#ifdef MIN_LOG_LEVEL_DEBUG
#define LOG_DEBUG
#define LOG_INFO
#define LOG_WARN
#define LOG_ERROR
#define LOG_FATAL
#endif

#ifdef LOG_DEBUG
#define Logger_DEBUG(expr) Really_Log_Debug()
#else
#define Logger_DEBUG(expr)
#endif