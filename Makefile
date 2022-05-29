NAME = server
.DEFAULT_GOAL = all
# Compilation flags
CC = g++
LD = g++
CFLAGS   += -O2 -Wall -Werror

OBJS_S = MD5.o main.o

md5.o : 
	@$(CC) -c MD5.cpp
main.o :
	@$(CC) -c main.cpp



md5:$(OBJS_S)
	@echo + LD $@
	@$(LD) $(OBJS_S) -o md5c



clean:
	@rm -rf $(OBJS_S) $(OBJS_C) md5c
