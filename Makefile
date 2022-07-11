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

$(LIBSOURCE)/$(DYN_LIB): $(LIBOFILES)
	$(LD) -shared -o $@ $^
	export LD_LIBRARY_PATH+=${LIBSOURCE}

$(EXEC): $(OFILES) $(LIBSOURCE)/$(DYN_LIB)
	$(LD) -o $@ -L$(LIBSOURCE) -l$(DYN_LIB_NAME) $(FLAGS) -lrt

run1: $(EXEC)
	./$(EXEC))
