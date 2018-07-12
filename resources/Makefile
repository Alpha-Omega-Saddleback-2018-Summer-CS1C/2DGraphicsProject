# C++ (Best) Makefile 

### Variables ###

CC = g++
CFLAGS = -Wall -g -std=c++14
LFLAGS =
INCLUDES =
LIBS =
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
MAIN = //// PUT EXECUTABLE NAME HERE ////

### Targets ###

all: $(MAIN)

run: $(MAIN)
	@echo "Running..."
	@echo "--- ##### ---"
	@echo
	@./$(MAIN)

# Add "-g" to CFLAGS to use !!!
debug: $(MAIN)
	@echo "Debugging..."
	@echo "--- ##### ---"
	@echo
	@gdb ./$(MAIN)

# Possible: Add "tar" as prerequisite
clean:
	@echo "Removing object files and executable..."
	@rm *.o $(MAIN)
	@echo "Done."

tar:
	@tar cfz $(MAIN).tar.gz $(wildcard *.h) $(SRCS) $(wildcard *.scr) Makefile

### Internal ###

$(MAIN): | compilehead $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
	@echo "EXE -> "$(MAIN)
	@echo "Done."
	
.cpp.o:
	@echo " >" $<
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

compilehead:
	@touch *
	@echo "--- Build Started ---" 
