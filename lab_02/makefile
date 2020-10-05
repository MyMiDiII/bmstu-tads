main : main.o menu.o my_string.o print_cars.o read_cars.o

main.o : main.c menu.h cars.h

menu.o : menu.c menu.h cars.h read_cars.h print_cars.h

my_string.o : main.c my_string.h

print_cars.o : main.c cars.h print_cars.h

read_cars.o : main.c cars.h read_cars.h