#ifndef __STRUCTURES_H__

#define __STRUCTURES_H__

#define MAX_BRAND_LEN 20;
#define MAX_COUNTRY_LEN 20;
#define MAX_COLOR_LEN 20;

typedef enum condition
{
    NEW,
    USED
} condition_t;

typedef struct
{
    char brand[MAX_BRAND_LEN + 1];
    char country[MAX_COUNTRY_LEN + 1];
    unsigned int price;
    char color[MAX_COLOR_LEN + 1];
    condition_t condition;
    union
    {
        // * тут должно быть что-то ;)
    }
} car_t;

#endif