CPPFLAGS = -O2

all: test8

test8: test8.o 
	g++ $(CPPFLAGS) -o test8 test8.o 

clean:
	rm -f test8; rm -f test8.o
	
test8.o: test8.cpp ExpressionTree.cpp ExpressionTree.h
