// Copyright 2022-2023 Preda Diana 324CA
#ifndef SERVER_COMM_H
#define SERVER_COMM_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string compute_get_request(string url, string host, vector<string> cookies, vector<string> headers);
string compute_post_request(string url, string host, string content_type, string content_length, string body_data, vector<string> cookies, vector<string> headers);
string compute_delete_request(string url, string host, vector<string> cookies, vector<string> headers);

#endif
