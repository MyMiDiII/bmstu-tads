main : main.o menu.o my_string.o print_cars.o read_cars.o cars.o

main.o : main.c menu.h cars.h

menu.o : menu.c menu.h cars.h read_cars.h print_cars.h my_string.h

my_string.o : my_string.c my_string.h

print_cars.o : print_cars.c cars.h print_cars.h my_string.h

read_cars.o : read_cars.c cars.h read_cars.h errors.h my_string.h

cars.o : cars.c read_cars.h errors.h