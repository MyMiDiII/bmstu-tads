#ifndef __CARS_H__

#define __CARS_H__

#include <stdio.h>

#define MAX_BRAND_LEN 30
#define MAX_COUNTRY_LEN 30
#define MAX_COLOR_LEN 30
#define MAX_PRICE_LEN 10
#define MAX_CONDITION_LEN 4
#define MAX_WARRANTY_LEN 3
#define MAX_YEAR_LEN 4
#define MAX_MILEAGE_LEN 7
#define MAX_REPAIRS_NUM_LEN 3
#define MAX_OWNERS_NUM_LEN 3
#define MAX_TABLE_LEN 55
#define MAX_TABLE_STR_LEN 135

typedef enum condition
{
    NEW,
    USED
} condition_t;

typedef struct
{
    short unsigned int warranty;
} new_car_t;

typedef struct
{
    short unsigned int year;
    unsigned int mileage;
    short unsigned int repairs_num;
    short unsigned int owners_num;
} used_car_t;


typedef union
{
    new_car_t new_car;
    used_car_t used_car;
} info_t;

typedef struct
{
    char brand[MAX_BRAND_LEN + 1];
    char country[MAX_COUNTRY_LEN + 1];
    char color[MAX_COLOR_LEN + 1];
    unsigned int price;
    condition_t condition;
    info_t more_info;
} car_t;

typedef struct
{
    car_t table[MAX_TABLE_LEN];
    size_t len;
} car_table_t;

int upload_from_file(car_table_t *table);

void print_cars(car_table_t *table);

#endif