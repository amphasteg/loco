#ifndef LOCO_TESTING_MOCKS
#define LOCO_TESTING_MOCKS
void set_mock_malloc_errno(int errnum);
void set_gethostname_mocks(int error_num, char *mock_hostname, int mock_hostname_len);
void set_realloc_errno(int errnum);
#endif
