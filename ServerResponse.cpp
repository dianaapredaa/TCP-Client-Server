// Copyright 2022-2023 Preda Diana 324CA
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"
#include "ServerResponse.h"

#include "nlohmann/json.hpp"

using namespace std;

// Constructor
ServerResponse::ServerResponse(string status_code, string status_message, string content_length, string content_type, string body_data, vector<string> cookies, vector<string> headers) {
    this->status_code = status_code;
    this->status_message = status_message;
    this->content_length = content_length;
    this->content_type = content_type;
    this->body_data = body_data;
    this->cookies = cookies;
    this->headers = headers;
}

// Default constructor
ServerResponse::ServerResponse() {
    this->status_code = "";
    this->status_message = "";
    this->content_length = "";
    this->content_type = "";
    this->body_data = "";
    this->cookies = {};
    this->headers = {};
}

// Parse response
void ServerResponse::deserialize(string response) {
    // Split response by \r\n
    vector<string> response_lines = split_string(response, "\r\n");

    // Get status code and message
    vector<string> status_line = split_string(response_lines[0], " ");

    string status_code = status_line[1];
    string status_message = status_line[2];

    // Get content length and type
    string content_length = "";
    string content_type = "";
    for (size_t i = 1; i < response_lines.size(); i++) {
        vector<string> header = split_string(response_lines[i], ": ");
        if (header[0] == "Content-Length") {
            content_length = header[1];
        }
        if (header[0] == "Content-Type") {
            content_type = header[1];
        }
    }

    // Get body data
    string body_data = "";
    for (size_t i = 1; i < response_lines.size(); i++) {
        // If line is empty, next line is body data
        if (response_lines[i] == "") {
            body_data = response_lines[i + 1];
            break;
        }
    }

    // Get cookies
    vector<string> cookies;
    for (size_t i = 1; i < response_lines.size(); i++) {
        // Split header by ': ' to get cookie name and value
        vector<string> header = split_string(response_lines[i], ": ");
        // Add cookie to cookies vector
        if (header[0] == "Set-Cookie") {
            cookies.push_back(header[1]);
        }
    }

    // Get headers
    vector<string> headers;
    for (size_t i = 1; i < response_lines.size(); i++) {
        // Split header by ': ' to get header name and value
        vector<string> header = split_string(response_lines[i], ": ");
        // Add header to headers vector
        if (header[0] != "Set-Cookie") {
            headers.push_back(response_lines[i]);
        }
    }

    // Set object fields
    this->status_code = status_code;
    this->status_message = status_message;
    this->content_length = content_length;
    this->content_type = content_type;
    this->body_data = body_data;
    this->cookies = cookies;
    this->headers = headers;
}

// Get cookies
vector<string> ServerResponse::get_cookies() {
    return this->cookies;
}

// Get Sid cookie
string ServerResponse::get_sid_cookie() {
    for (size_t i = 0; i < this->cookies.size(); i++) {
        vector<string> cookie = split_string(this->cookies[i], ";");

        for (size_t j = 0; j < cookie.size(); j++) {
            vector<string> cookie_name_value = split_string(cookie[j], "=");
            if (cookie_name_value[0] == "connect.sid") {
                return cookie[j];
            }
        }
    }
    return "";
}

// Get JWT cookie
string ServerResponse::get_jwt() {
    // Get token from payload
    string payload = this->body_data;

    // Parse payload as JSON
    nlohmann::json json_payload = nlohmann::json::parse(payload);

    // Get token from payload
    string token = json_payload["token"];

    // Return token
    return token;
}
