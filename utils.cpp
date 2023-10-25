// Copyright 2022-2023 Preda Diana 324CA
#include <iostream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

using namespace std;

// Split string by delimiter
vector<string> split_string(string str, string delimiter)
{
    vector<string> result;

    // Find first delimiter
    size_t pos = str.find(delimiter);

    // While delimiter is found
    while (pos != string::npos) {
        // Add substring before delimiter to result
        result.push_back(str.substr(0, pos));

        // Remove substring before delimiter from string
        str.erase(0, pos + delimiter.length());

        // Find next delimiter
        pos = str.find(delimiter);
    }

    // Add last substring to result
    result.push_back(str);

    return result;
}

string create_credentials_json()
{
    string username, password;

    cout << "username=";
    getline(cin, username);
    cout << "password=";
    getline(cin, password);

    // Check to see that username and password have no spaces
    if (username.find(" ") != string::npos || password.find(" ") != string::npos) {
        cout << "Username and password must not contain spaces" << endl;
        return "";
    }

    nlohmann::json json;
    json["username"] = username;
    json["password"] = password;

    return json.dump();
}

string create_book_json()
{
    string title, author, genre, publisher, page_count;

    // Get book information
    cout << "title=";
    getline(cin, title);
    cout << "author=";
    getline(cin, author);
    cout << "genre=";
    getline(cin, genre);
    cout << "publisher=";
    getline(cin, publisher);
    cout << "page_count=";
    getline(cin, page_count);

    // Verify page_count is a number
    bool is_number = page_count.find_first_not_of("0123456789") == string::npos;
    if (!is_number) {
        cout << "The number of pages must be a number" << endl;
        return "";
    }

    // Create JSON object
    nlohmann::json json;
    json["title"] = title;
    json["author"] = author;
    json["genre"] = genre;
    json["publisher"] = publisher;
    json["page_count"] = page_count;

    return json.dump();
}

void print_books(string payload)
{
    // Parse payload
    nlohmann::json json = nlohmann::json::parse(payload);
    cout << json.dump(4) << endl;    
}

void print_book(string payload)
{
    // Parse payload
    nlohmann::json json = nlohmann::json::parse(payload);
    cout << json.dump(4) << endl;
}

bool is_in_vector(vector<string> v, string s)
{
    for (auto elem : v) {
        if (elem == s) {
            return true;
        }
    }
    
    return false;
}
