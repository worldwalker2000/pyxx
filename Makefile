CC = clang++
CFLAGS = -Wall -Wextra -Wshadow -Werror -g

pyxx: src/*.cpp
	$(CC) $(CFLAGS) src/*.cpp -o pyxx
