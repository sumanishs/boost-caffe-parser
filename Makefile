########################################################################
## Author: Sumanish <sumanish.cse.jgec@gmail.com>                     ##
## Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                ##
##                                                                    ##  
## This source code can be downloaded, use, modify, distribute        ##
## freely with this headed intact. Please don't delete this header.   ##
######################################################################## 

CC=g++
IPATHS=-I. -I/home/sumanish/Boost_1.68/boost_1_68_0 
CFLAGS=-g -w
LPATHS=-L/home/sumanish/Boost_1.68/boost_1_68_0/stage/lib
LFLAGS=
DEPS = caffeparserfunctors.hpp	\
	   caffeparsergrammar.hpp	\
	   caffereader.hpp			

OBJS = caffereader.o	\
	   main.o	

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(IPATHS)

CaffeParse: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LPATHS) $(LFLAGS)

clean:
	rm -f *.o *.log CaffeParse
