// Copyright 2022-2023 Preda Diana 324CA
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split_string(string str, string delimiter);
string create_credentials_json();
string create_book_json();
void print_books(string payload);
void print_book(string payload);
bool is_in_vector(vector<string> v, string s);

#endif