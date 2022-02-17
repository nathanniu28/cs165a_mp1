CXX = g++

CXXFLAGS = -std=c++11 #-Wall -Wextra -Werror

BINARIES = bayes

all: ${BINARIES}

#bayes: bayes.o continuous.o discrete.o
#	${CXX} $^ -o $@

bayes: bayes.o classifier.o continuous.o discrete.o
	${CXX} $(CXXFLAGS) -o bayes $^

bayes.o: bayes.cpp classifier.h continuous.h discrete.h

classifier.o: classifier.cpp classifier.h continuous.h

continuous.o: continuous.cpp continuous.h

discrete.o: discrete.cpp discrete.h

#bayes: bayes.o classifier.o
#	${CXX} $^ -o bayes bayes.o classifier.o

#bayes.o: bayes.cpp classifier.h
#	${CXX} $^ -c bayes.cpp

#classifier.o: classifier.cpp continuous.h discrete.h
#	${CXX} $^ -c classifier.cpp

#continuous.o: continuous.h continuous.cpp
#	${CXX} $^ -c continuous.cpp

#discrete.o: discrete.h discrete.cpp
#	${CXX} $^ -c discrete.cpp

clean:
	/bin/rm -f ${BINARIES} *.o
