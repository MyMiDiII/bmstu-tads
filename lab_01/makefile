main : main.o big_nums.o errors.o

main.o : main.c big_nums.h errors.h

big_nums.o : big_nums.c big_nums.h

errors.o : errors.c errors.h

.PHONY : clean

clean :
	rm *.o main
