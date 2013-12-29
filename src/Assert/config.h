/*
 * Use this for global enums!
 */
enum LoggingLevel
{
	Info = 1,
	Warning,
	Error,
	Severe
};

/*
 * Use this for build flags!
 */
#define USE_ASSERT		1
#define DEBUG			1
#define LOGGING_ON		1
#define LOGGING_LEVEL	LoggingLevel::Info

