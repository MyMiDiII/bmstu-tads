#ifndef __ERR_H__

#define __ERR_H__

#define OK 0
#define ERR_ARGS_NUM -1
#define ERR_OPEN_FILE -2
#define ERR_CLOSE_FILE -3
#define ERR_MEMORY -4
#define END_OF_FILE -5
#define ERR_NONANSWER -6
#define ERR_NONINTEGER -7
#define ERR_NONSIZE -8
#define ERR_TOO_BIG_SIZE -9

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[36m"

void print_err(const int code);

#endif
