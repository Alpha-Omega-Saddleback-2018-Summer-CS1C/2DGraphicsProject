# Makefile for C++
# 7/15/2017 

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

clean:
	@echo "Removing object files and executable..."
	@rm *.o $(MAIN)
	@echo "Done."

tar:
	@echo "Creating tarball..."
	@tar cfz $(MAIN).tar.gz $(wildcard *.h) $(SRCS) $(wildcard *.scr) Makefile
	@echo "Done."

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
