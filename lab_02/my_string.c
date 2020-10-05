#include <string.h>

#include "my_string.h"

size_t my_strlen(const char *const str)
{
    size_t count = 0;
    size_t len = 0;

    while (str[count] != '\0')
    {
        len++;
        count++;

        if (str[count] < 0 || str[count] > 127)
            count++;
    }

    return len;
}

