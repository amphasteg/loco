#ifndef LOCO_TEST_MACROS

#define LOCO_TEST_MACROS

#ifdef MOCK_IMPL
#define malloc mock_malloc
#define gethostname mock_gethostname
#define realloc mock_realloc
#include MOCK_IMPL
#undef malloc
#undef mock_gethostname
#undef realloc
#undef MOCK_IMPL
#endif

#endif
