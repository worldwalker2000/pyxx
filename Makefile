.POSIX:

.SUFFIXES:
.SUFFIXES: .o .cpp

CXX = c++

CXXFLAGS = -g
CPPFLAGS = -Wall -Wextra -Wshadow -Werror -std=c++17

TARG = pyxx
OFILES = src/main.o

all: ${TARG}

${TARG}: ${OFILES}
	${CXX} -o $@ ${CXXFLAGS} ${OFILES} ${LDFLAGS}

.cpp.o:
	${CXX} -c ${CXXFLAGS} ${CPPFLAGS} $< -o $*.o

clean:
	rm -f ${TARG} ${OFILES}

.PHONY: all clean
