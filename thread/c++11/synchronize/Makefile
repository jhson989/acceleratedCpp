CC = g++
INCS = utils.hpp 
OBJS = 
MAIN = main.cpp 
OPTION =  -O0 -lpthread
PROGRAM = reduction


${PROGRAM} : ${MAIN} ${OBJS} ${INCS} Makefile
	${CC} -o ${PROGRAM} ${MAIN} ${OBJS} ${OPTION}

clean : 
	rm ${PROGRAM}

