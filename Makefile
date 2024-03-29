#
#	This is the makefile for the shell emulator project
#					made by Piotr Wojtowicz
#				Cracow | Jagiellonian Univeristy
#
#

#Save the object files
.PRECIOUS: %.o #Linker and compiler //both gcc
CC = gcc
LD = $(CC)

#Compilation flags
FLAGS = -Wall --pedantic -g -lncurses -lreadline
INCFLAG = $(foreach D, $(LIBSOURCE), -I$(D))
DFLAGS = -fPIC

#Locals
WHEREAMI = ~/Shel/Shel
FULLINCLUDEPATH = /home/user/Shel/Shel/include
XTERM = /home/user/.Xresources

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
	$(LD) $(foreach D, $(SRCOFILES), $(D)) $(FLAGS) -lrt -L$(FULLINCLUDEPATH) -l$(DYN_LIB_NAME) -o $@ 

run: $(EXEC)
	xrdb -merge $(XTERM)
	(export LD_LIBRARY_PATH+="$(FULLINCLUDEPATH)":${LD_LIBRARY_PATH}; \
	xterm -e ./$(EXEC)) 

test: $(EXEC)
	(export LD_LIBRARY_PATH+="$(FULLINCLUDEPATH)":${LD_LIBRARY_PATH}; \
	 gdb $(EXEC)) 

.PHONY: clean
clean:
	rm -f ./*.o ./lib/*.o

everything: clean
	rm ./*.x
	rm ./include/*.so
