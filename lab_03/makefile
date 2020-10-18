INCDIR := ./inc/
SRCDIR := ./src/
OUTDIR := ./out/

vpath %.c $(SRCDIR)

CC := gcc
PATHFLAG := -I$(INCDIR)
CFLAGS := -std=c99 $(PATHFLAG) -Wall -Werror -Wpedantic

SRCS := $(wildcard $(SRCDIR)*.c)
OBGS := $(patsubst $(SRCDIR)%.c,$(OUTDIR)%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBGS))

app.exe : $(OBGS) 
	$(CC) $^ -o $@

$(OUTDIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)%.d : %.c
	@mkdir -p $(@D)
	@$(CC) $(PATHFLAG) -M $< | sed "s^$*.o^$(OUTDIR)$*.o^" > $@

include $(DEPS)

.PHONY : clean

clean :
	rm -fv *.exe
	rm -frv $(OUTDIR)