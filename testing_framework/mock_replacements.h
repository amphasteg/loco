#ifndef LOCO_TEST_MACROS

#define LOCO_TEST_MACROS

#ifdef MOCK_IMPL
#define malloc mock_malloc
#define gethostname mock_gethostname
#define realloc mock_realloc
#define getaddrinfo mock_getaddrinfo
#include MOCK_IMPL
#undef malloc
#undef mock_gethostname
#undef realloc
#undef getaddrinfo
#undef MOCK_IMPL
#endif

#endif
