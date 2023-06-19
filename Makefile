#
# A simple Makefile to build 'esh'
#

CFLAGS= -std=c99 -O3

all : singleThread hyperthread 

 singleThread :
	gcc-12 $(CFLAGS) -o singleThreadTest SingleThreadRunner.c utils/multiplyMatrices.c utils/multiplyMatrices.h utils/matrixUtils.c utils/matrixUtils.h utils/TimeSpecUtils.c utils/TimeSpecUtils.h

 hyperthread : 
	gcc-12 $(CFLAGS) -pthread -o hyperthreadTest HyperthreadRunner.c utils/multiplyMatrices.c \
		utils/multiplyMatrices.h utils/matrixUtils.c utils/matrixUtils.h \
		utils/TimeSpecUtils.c utils/TimeSpecUtils.h

clean : 
	rm singleThreadTest
	rm hyperthreadTest
