// Copyright 2022-2023 Preda Diana 324CA
#include <iostream>
#include <string>
#include <vector>

#include "server_communication.h"
#include "nlohmann/json.hpp"
#include "utils.h"
#include "server_communication.h"

using namespace std;

string get_login_request()
{
    // Create credentials json
    string credentials_json = create_credentials_json();

    // Set host
    string host = "34.254.242.81:8080";

    // Set content type
    string content_type = "application/json";

    // Set content length
    string content_length = to_string(credentials_json.length());

    // Set url
    string url = "/api/v1/tema/auth/login";

    // Create request
    string request = compute_post_request(url, host, content_type, content_length, credentials_json, {}, {});

    return request;
}

string get_register_request()
{
    // Create credentials json
    string credentials_json = create_credentials_json();

    // Set host
    string host = "34.254.242.81:8080";

    // Set content type
    string content_type = "application/json";

    // Set content length
    string content_length = to_string(credentials_json.length());

    // Set url
    string url = "/api/v1/tema/auth/register";

    // Create request
    string request = compute_post_request(url, host, content_type, content_length, credentials_json, {}, {});

    return request;
}

string get_enter_library_request(string cookie)
{
    // Set host
    string host = "34.254.242.81:8080";

    // Create cookies vector
    vector<string> cookies = {cookie};

    // Set url
    string url = "/api/v1/tema/library/access";

    // Create request
    string request = compute_get_request(url, host, cookies, {});

    return request;        
}

string get_get_books_request(string token, string cookie)
{
    // Set host
    string host = "34.254.242.81:8080";

    // Create cookies vector
    vector<string> cookies = {cookie};

    // Create token header (JWT)
    string token_header = "Authorization: Bearer " + token;
    vector<string> headers = {token_header};

    // Set url
    string url = "/api/v1/tema/library/books";

    // Create request
    string request = compute_get_request(url, host, cookies, headers);

    return request;
}

string get_get_book_request(string token, string cookie)
{
    // Set host
    string host = "34.254.242.81:8080";

    // Create cookies vector
    vector<string> cookies = {cookie};

    // Create token header (JWT)
    string token_header = "Authorization: Bearer " + token;
    vector<string> headers = {token_header};

    // Read book id
    string book_id;
    cout << "id=";
    getline(cin, book_id);

    // Check if book id is a number
    bool is_number = book_id.find_first_not_of("0123456789") == string::npos;
    if (!is_number)
    {
        cout << "Book id must be a number!" << endl;
        return "";
    }

    // Set url
    string url = "/api/v1/tema/library/books/" + book_id;

    // Create request
    string request = compute_get_request(url, host, cookies, headers);

    return request;
}

string get_add_book_request(string token, string cookie)
{
    // Set host
    string host = "34.254.242.81:8080";

    // Create cookies vector
    vector<string> cookies = {cookie};

    // Create token header (JWT)
    string token_header = "Authorization: Bearer " + token;
    vector<string> headers = {token_header};

    // Set url
    string url = "/api/v1/tema/library/books";

    // Create json
    string json = create_book_json();

    // Set content type
    string content_type = "application/json";

    // Set content length
    string content_length = to_string(json.length());

    // Create request
    string request = compute_post_request(url, host, content_type, content_length, json, cookies, headers);

    return request;
}

string get_delete_book_request(string token, string cookie)
{
    // Set host
    string host = "34.254.242.81:8080";

    // Create cookies vector
    vector<string> cookies = {cookie};

    // Create token header (JWT)
    string token_header = "Authorization: Bearer " + token;
    vector<string> headers = {token_header};

    // Read book id
    string book_id;
    cout << "id=";
    getline(cin, book_id);

    // Check if book id is a number
    bool is_number = book_id.find_first_not_of("0123456789") == string::npos;
    if (!is_number)
    {
        cout << "Book id must be a number!" << endl;
        return "";
    }

    // Set url
    string url = "/api/v1/tema/library/books/" + book_id;

    // Create request
    string request = compute_delete_request(url, host, cookies, headers);

    return request;
}

string get_logout_request(string cookie)
{
    // Set host
    string host = "34.254.242.81:8080";

    // Create cookies vector
    vector<string> cookies = {cookie};

    // Set url
    string url = "/api/v1/tema/auth/logout";

    // Create request
    string request = compute_get_request(url, host, cookies, {});

    return request;
}