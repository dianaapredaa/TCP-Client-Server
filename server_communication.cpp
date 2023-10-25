// Copyright 2022-2023 Preda Diana 324CA
#include <iostream>
#include <string>
#include <vector>

#include "server_communication.h"
#include "imported_lab/helpers.h"
#include "ServerRequest.h"

using namespace std;

string compute_get_request(string url, string host, vector<string> cookies, vector<string> headers)
{
    // Default values for GET request
    string method = "GET";
    string type = "HTTP/1.1";
    string content_length = "0";
    string content_type = "";
    string body_data = "";

    ServerRequest req(method, url, type, host, content_length, content_type, body_data, cookies, headers);
    string request = req.serialize();

    return request;
}

string compute_post_request(string url, string host, string content_type, string content_length, string body_data, vector<string> cookies, vector<string> headers)
{
    // Default values for POST request
    string method = "POST";
    string type = "HTTP/1.1";

    ServerRequest req(method, url, type, host, content_length, content_type, body_data, cookies, headers);    
    string request = req.serialize();

    return request;
}

string compute_delete_request(string url, string host, vector<string> cookies, vector<string> headers)
{
    // Default values for DELETE request
    string method = "DELETE";
    string type = "HTTP/1.1";
    string content_length = "0";
    string content_type = "";
    string body_data = "";

    ServerRequest req(method, url, type, host, content_length, content_type, body_data, cookies, headers);
    string request = req.serialize();

    return request;
}
