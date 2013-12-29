#include <assert.h>
#include "config.h"
#if (USE_ASSERT == 1)
#define Assert(expr)((expr)? __ASSERT_VOID_CAST (0):__assert_fail (__STRING(expr), __FILE__, __LINE__, __ASSERT_FUNCTION))
#endif
