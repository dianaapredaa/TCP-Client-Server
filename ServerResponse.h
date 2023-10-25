// Copyright 2022-2023 Preda Diana 324CA
#ifndef SERVER_RES_H
#define SERVER_RES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ServerResponse {
public:
    string status_code;
    string status_message;
    string content_length;
    string content_type;
    string body_data;
    vector<string> cookies;
    vector<string> headers;

    // Constructor
    ServerResponse(string status_code, string status_message, string content_length,
                    string content_type, string body_data, vector<string> cookies,
                    vector<string> headers);

    // Default constructor
    ServerResponse();

    // Get cookies
    vector<string> get_cookies();

    // Get Sid cookie
    string get_sid_cookie();

    // Get JWT cookie
    string get_jwt();

    // Parse response
    void deserialize(string response);
};

#endif