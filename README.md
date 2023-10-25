*Copyright 2022-2023 Preda Diana 324CA*

# Project: REST API Client in C/C++ for HTTP Library Server

## Project Description

This project is a REST API client for a HTTP library server. It takes commands
from the user, creates a request and sends it to the server. The server
will then respond with the result of the command. The connection is created
and closed for every command.

## Structure

The project is structured in the following way:
- **client.cpp** - main file
- **server_communication.cpp** - contains that create the requests
- **commands.cpp** - contains the functions that create the requests
for each command
- **utils.cpp** - contains utility functions
- **ServerResponse.cpp** - contains the ServerResponse class methods
- **ServerRequest.cpp** - contains the ServerRequest class methods
- **all** according header files
- **Makefile** - makefile for the project
- **README.md** - this file
- **imported_lab/** - contains the files from the laboratory that were imported in the project

## Control Flow

The basic flow of the program is:
- read command from user
- get request for command
- send request
- receive response from server
- extract result and usefull information from response
- print result

## Possible Commands

    - login {username} {password} - login to the server with username and password
    - logout - logout from the server
    - register {username} {password} - register new user with username and password
    - exit - exit the program
    - enter_library - enter the library (gets acces to commands bellow)
    - get_books - get all books
    - get_book {book_id} - get book with id
    - add_book {book_title} {book_author} {book_genre} {book_publisher} {book_page_count} - add book to library
    - delete_book {book_id} - delete book with id

## Build

    make build - builds the project
    make clean - removes the executable file

## JSON Library

I chose to use the nlohmann json library because it is easy to use and
very well documented. It also has a lot of features that make it very
convenient and concise to use.

## Possible Improvements

- More efficient way to parse the response from the server (space-wise)
- Clean up the code (main is a bit messy)

## References

nlohmann json library: https://github.com/nlohmann/json

server communication: Laboratory 9 Protocoale de Comunicatii
