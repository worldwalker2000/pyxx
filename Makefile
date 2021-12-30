CC = clang++
CFLAGS = -Wall -Wextra -Wshadow -Werror -g -std=c++17

pyxx: src/*.cpp
	$(CC) $(CFLAGS) src/*.cpp -o pyxx
