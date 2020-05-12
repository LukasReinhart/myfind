# For a quick guide to make, please refer to: https://www.cs.bu.edu/teaching/cpp/writing-makefiles/
# For the advanced things used here, check this and its further reading: https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile#answer-2481326

CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

# Kind of important: source files listed here (separate by single spaces)
SRCS=myfind.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: myfind

myfind: $(OBJS)
	$(CXX) $(LDFLAGS) -o myfind $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend
