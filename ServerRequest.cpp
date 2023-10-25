// Copyright 2022-2023 Preda Diana 324CA
#include <iostream>
#include <string>
#include <vector>

#include "ServerRequest.h"

using namespace std;

// Constructor
ServerRequest::ServerRequest(string method, string url, string type,
                string host, string content_length,
                string content_type, string body_data,
                vector<string> cookies, vector<string> headers) {
    this->method = method;
    this->url = url;
    this->type = type;
    this->host = host;
    this->content_length = content_length;
    this->content_type = content_type;
    this->body_data = body_data;
    this->cookies = cookies;
    this->headers = headers;
}

// Serialize request (each line finished with \r\n)
string ServerRequest::serialize() {
    string request = "";

    // Add method, url, type and host
    request += this->method + " " + this->url + " " + this->type + "\r\n";
    request += "Host: " + this->host + "\r\n";

    // Add content length and type if there is payload
    if (this->body_data != "") {
        request += "Content-Length: " + this->content_length + "\r\n";
        request += "Content-Type: " + this->content_type + "\r\n";
    }

    // Add cookies if there are any
    if (this->cookies.size() > 0) {
        request += "Cookie: ";
        for (size_t i = 0; i < this->cookies.size(); i++) {
            request += this->cookies[i];
            // Add ; between cookies except for the last one
            if (i != this->cookies.size() - 1) {
                request += "; ";
            }
        }
        request += "\r\n";
    }

    // Add headers if there are any
    if (this->headers.size() > 0) {
        for (size_t i = 0; i < this->headers.size(); i++) {
            request += this->headers[i] + "\r\n";
        }
    }

    // Add \r\n at the end of the request
    request += "\r\n";

    // Add body data if there is any
    if (this->body_data != "") {
        request += this->body_data;
    }

    return request;
}
