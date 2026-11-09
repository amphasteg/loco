#ifndef STRING
#define STRING

/** A basic string representation. Contains a char pointer as well as the size
 * of the string including the null terminator
 *
 * @var unsigned string_size
 * Size of the string including null terminator '\0'
 * @var char* string*/
struct string {
  unsigned string_size;
  char *string;
};

#endif
