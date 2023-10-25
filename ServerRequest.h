// Copyright 2022-2023 Preda Diana 324CA
#ifndef SERVER_REQ_H
#define SERVER_REQ_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ServerRequest {
public:
    string method;
    string url;
    string type;
    string host;
    string content_length;
    string content_type;
    string body_data;
    vector<string> cookies;
    vector<string> headers;

    // Constructor
    ServerRequest(string method, string url, string type, string
                    host, string content_length, string content_type, string body_data,
                    vector<string> cookies, vector<string> headers);

    // Serialize request
    string serialize();
};

#endif