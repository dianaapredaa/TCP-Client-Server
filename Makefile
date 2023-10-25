CC=g++
FLAGS=-std=c++17 -Wall -Wextra -g

build:
	$(CC) $(FLAGS) -o client client.cpp imported_lab/helpers.c imported_lab/buffer.c server_communication.cpp ServerRequest.cpp ServerResponse.cpp utils.cpp commands.cpp

clean:
	rm -f client

run: build
	./client

.PHONY: clean run build