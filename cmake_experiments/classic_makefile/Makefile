
# A variable assignment
FOO = ONE
FOO += TWO
BAR = ONE
BAR := $(BAR)THREE

# print in a make
$(info FOO=$(FOO))
$(info BAR=$(BAR))

# le ? set la variable globale si elle n'a pas encore ete definie
CC ?= gcc

CFLAGS += -Wall

compile: src/hello_world.c
	$(CC) src/hello_world.c -o bin/hello_world

.PHONY: run
run: compile 
	bin/hello_world

#main does not need manual compilation (if makefile in same dir) 
main: main.c

test.txt:
	echo HEYO > $@

# and $^ gives all the names of the prerequisites (on the same line as the name of the command) 
#
## CLASSICAL COMMAND ARCHITECTURE ##
# target : prerequisite
#					 recipe
#

#Prefix with - with not stop make if failure of command
clean:
	-rm *.o
	-rm program
	-rm hello_world
	-rm main
	-rm test.txt


# .PHONY prevents make to look for files with the same name but rather a meta target that builds multiple things at once
#
.PHONY: all

all: run test.txt


## object files are files that can be compiled separately but run together
# builds an o file from a c file
%.o: src/%.c
	$(CC) -c $< -o $@

OBJ_FILES = hello_world.o main.o
program: $(OBJ_FILES)
	$(CC) -o $@ $^


hidden_msg:
	@# Using @ hides the command used
	@echo hidden command
