#
#	This is the makefile for the shell emulator project
#					made by Piotr Wojtowicz
#				Cracow | Jagiellonian Univeristy
#
#

#Save the object files
.PRECIOUS: %.o

#Linker and compiler //both gcc
CC = gcc
LD = $(CC)

#Compilation flags
FLAGS = -Wall -std=c99 --pedantic
INCFLAG = $(foreach D, $(LIBSOURCE), -I$(D))
DFLAGS = -fPIC

#Locals
WHEREAMI = ~/CodeProjects
CSOURCE = $(WHEREAMI)
LIBSOURCE = $(WHEREAMI)/lib
SOURCE = $(CSOURCE) $(LIBSOURCE)
INCLUDE = $(WHEREAMI)/include
BIN = $(WHEREAMI)/bin

#Wildcards for source files
CFILES = $(foreach D, $(SOURCE), $(wildcard $(D)/*.c))
#Specific wildcards
LIBCFILES = $(foreach D, $(LIBSOURCE), $(wildcard $(D)/*.c))
SRCCFILES = $(foreach D, $(CSOURCE), $(wildcard $(D)/*.c)) 

#Patsub to create object dependencies
OFILES = $(patsubst %.c, %.o, $(CFILES))
LIBOFILES = $(patsubst %.c, %.o, $(LIBCFILES))
SRCOFILES = $(patsubst %.c, %.o, $(SRCCFILES))

#Emulator variables
MAIN = main
EXEC = $(MAIN).x

#Create/update object files
%.o: %.c
	$(CC) $(FLAGS) $(INCFLAG) -c -o $@ $<

$(LIBOFILES): $(LIBCFILES)
	$(CC) $(FLAGS) $(DFLAGS) -c -o $@ $(patsubst %.o, %.c, $@)

#Create/update dyn. lib files
#Lib name
DYN_LIB = libmy_emulator.so
DYN_LIB_NAME = my_emulator

$(INCLUDE)/$(DYN_LIB): $(LIBOFILES)
	$(LD) -shared -o $@ $^

$(EXEC): $(OFILES) $(INCLUDE)/$(DYN_LIB)
	$(LD) $(foreach D, $(SRCOFILES), $(D)) $(FLAGS) -lrt -L/home/user_me/CodeProjects/include -l$(DYN_LIB_NAME) -o $@ 

run1: $(EXEC)
	(export LD_LIBRARY_PATH+="/home/user_me/CodeProjects/include":${LD_LIBRARY_PATH}; \
	./$(EXEC))

.PHONY: clean
clean:
	rm -f ./*.o ./lib/*.o

everything: clean
	rm ./*.x