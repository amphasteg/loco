#ifndef LOCO_TEST_MACROS

#define LOCO_TEST_MACROS
#define malloc mock_malloc
#define gethostname mock_gethostname
#ifdef MOCK_IMPL
#include MOCK_IMPL
#endif

#endif
