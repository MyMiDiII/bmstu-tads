#ifndef __PRINT_CARS_H__

#define __PRINT_CARS_H__

#include "cars.h"

void print_column_line(const int line_len);

void print_str(const char *const str, const int max_len);

void print_header(void);

void print_down_line(void);

void print_record(const car_t *const record);

void print_cars(car_table_t *table);

#endif