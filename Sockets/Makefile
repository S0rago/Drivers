compile:
	clear
	gcc -Wall -g3 -fsanitize=address -pthread server.c -o server
	gcc -Wall -g3 -fsanitize=address -pthread client.c -o client
check:
	clear
	cppcheck --enable=all --inconclusive --std=posix server.c
	cppcheck --enable=all --inconclusive --std=posix client.c
