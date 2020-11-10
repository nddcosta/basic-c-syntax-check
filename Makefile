CC = gcc
MAIN = basic_syntax_check
SRCS = ex_1_24.c errors.c quote.c comment.c symbol.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -I -g -Wall

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

*.o : *.c *.h
	$(CC) $(CFLAGS) -c $<

clean: 
	rm *.o $(MAIN)
