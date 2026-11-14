#ifndef LOCO_TESTING_MOCKS
#define LOCO_TESTING_MOCKS
#include <stddef.h>

void set_mock_malloc_errno(int errnum);
void set_gethostname_mocks(int error_num, char *mock_hostname, int mock_hostname_len);
void set_realloc_errno(int errnum);

void *mock_malloc(size_t ptr_size);
void *mock_realloc(void *p, size_t size);
int mock_gethostname(char *name, size_t name_len);
#endif
