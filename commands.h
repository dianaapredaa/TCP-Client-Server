// Copyright 2022-2023 Preda Diana 324CA
#ifndef COMMS_H
#define COMMS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string get_login_request();
string get_register_request();
string get_enter_library_request(string cookie);
string get_get_books_request(string token, string cookie);
string get_get_book_request(string token, string cookie);
string get_add_book_request(string token, string cookie);
string get_delete_book_request(string token, string cookie);
string get_logout_request(string cookie);

#endif