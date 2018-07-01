#ifndef __BASIC_LOGGER_H__
#define __BASIC_LOGGER_H__

#define LOG_TABLE \
X(Debug,"Debug") \
X(Error,"Error")
#define X(a,b) a,
enum LogType {
	LOG_TABLE
};
/*If not using Windows, Replace \\ with / */
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 0 : __FILE__)
#define blog(debugType,...) \
	_blog(__FILENAME__,__LINE__,debugType,__VA_ARGS__)

void _blog(char *f, int l, LogType type, char *msg,...);
#endif
