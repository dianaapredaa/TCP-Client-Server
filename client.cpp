// Copyright 2022-2023 Preda Diana 324CA
#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

#include "server_communication.h"
#include "imported_lab/helpers.h"
#include "ServerRequest.h"
#include "ServerResponse.h"
#include "utils.h"
#include "commands.h"

#include "nlohmann/json.hpp"

using namespace std;

int main()
{
    string server_ip = "34.254.242.81";
    int server_port = 8080;

    // Create arrays with possible status codes
    vector<string> ok_status_codes = {"200", "201", "202"};

    // Storage for session cookie
    string cookie;

    // Storage for jwt token
    string jwt;

    // Infinite loop until exit
    while (1) {
        // Read user input
        string command;
        getline(cin, command);

        // Check if user wants to exit
        if (command == "exit") {
            break;
        } else if (command == "register") {
            // Check to see if user is already logged in
            if (cookie.length() > 0) {
                cout << "You are already logged in!" << endl;
                continue;
            }

            // Create request
            string request = get_register_request();
            if (request == "") {
                continue;
            }

            // Send request to server
            int server_sockfd = open_connection(server_ip.data(), server_port, AF_INET, SOCK_STREAM, 0);
            send_to_server(server_sockfd, request.data());

            // Receive response from server
            char* response_c_str = receive_from_server(server_sockfd);
            string response(response_c_str);
            close_connection(server_sockfd);

            // Parse response
            ServerResponse server_response;
            server_response.deserialize(response);

            // Get response code and message
            string response_code = server_response.status_code;
            string response_message = server_response.status_message;

            // Check if response is ok
            if (is_in_vector(ok_status_codes, response_code)) {
                cout << response_code << " " << response_message << " " << "User registered succesfully!" << endl;
            } else {
                nlohmann::json error_json = nlohmann::json::parse(server_response.body_data);
                cout << response_code << " " << response_message << " " << error_json["error"] << endl;
            }
            free(response_c_str);
        } else if (command == "login") {
            if (cookie.length() > 0) {
                cout << "Already logged in!" << endl;
                continue;
            }

            // Create request
            string request = get_login_request();
            if (request == "") {
                continue;
            }

            // Send request to server
            int server_sockfd = open_connection(server_ip.data(), server_port, AF_INET, SOCK_STREAM, 0);
            send_to_server(server_sockfd, request.data());

            // Receive response from server
            char* response_c_str = receive_from_server(server_sockfd);
            string response(response_c_str);
            close_connection(server_sockfd);

            // Parse response
            ServerResponse server_response;
            server_response.deserialize(response);

            // Get response code and message
            string response_code = server_response.status_code;
            string response_message = server_response.status_message;

            // Check if login was successful
            if (is_in_vector(ok_status_codes, response_code)) {
                cout << response_code << " " << response_message << " " << "Logged in succesfully!" << endl;
            } else {
                nlohmann::json error_json = nlohmann::json::parse(server_response.body_data);
                cout << response_code << " " << response_message << " " << error_json["error"] << endl;
                free(response_c_str);
                continue;
            }

            // Store cookie
            string cookie_tmp = server_response.get_sid_cookie();
            if (cookie_tmp == "") {
                // Should never happen
                cout << "Cookie not found" << endl;
                continue;
            }

            cookie = cookie_tmp;
            free(response_c_str);
        } else if (command == "enter_library") {
            // Check to see if the user can complete the command
            if (cookie.length() == 0) {
                cout << "You are not logged in!" << endl;
                continue;
            }

            // Create request
            string request = get_enter_library_request(cookie);
            if (request == "") {
                continue;
            }

            // Send request to server
            int server_sockfd = open_connection(server_ip.data(), server_port, AF_INET, SOCK_STREAM, 0);
            send_to_server(server_sockfd, request.data());

            // Receive response from server
            char* response_c_str = receive_from_server(server_sockfd);
            string response(response_c_str);
            close_connection(server_sockfd);

            // Parse response
            ServerResponse server_response;
            server_response.deserialize(response_c_str);

            // Get response code and message
            string response_code = server_response.status_code;
            string response_message = server_response.status_message;

            // Check if login was successful
            if (is_in_vector(ok_status_codes, response_code)) {
                cout << response_code << " " << response_message << " " << "You are inside the library!" << endl;
            } else {
                nlohmann::json error_json = nlohmann::json::parse(server_response.body_data);
                cout << response_code << " " << response_message << " " << error_json["error"] << endl;
                free(response_c_str);
                continue;
            }

            // Store JWT token
            string token_tmp = server_response.get_jwt();
            if (token_tmp == "") {
                // Should never happen
                cout << "JWT token not found" << endl;
                continue;
            }

            jwt = token_tmp;
            free(response_c_str);
        } else if (command == "get_books") {
            // Check to see if the user can complete the command
            if (cookie.length() == 0) {
                cout << "You are not logged in!" << endl;
                continue;
            }
            if (jwt.length() == 0) {
                cout << "You are not inside the library!" << endl;
                continue;
            }

            // Create request
            string request = get_get_books_request(jwt, cookie);
            if (request == "") {
                continue;
            }

            // Send request to server
            int server_sockfd = open_connection(server_ip.data(), server_port, AF_INET, SOCK_STREAM, 0);
            send_to_server(server_sockfd, request.data());

            // Receive response from server
            char* response_c_str = receive_from_server(server_sockfd);
            string response(response_c_str);
            close_connection(server_sockfd);

            // Parse response
            ServerResponse server_response;
            server_response.deserialize(response_c_str);

            // Get response code and message
            string response_code = server_response.status_code;
            string response_message = server_response.status_message;

            // Check if login was successful
            if (is_in_vector(ok_status_codes, response_code)) {
                cout << response_code << " " << response_message << " " << "Books received succesfully!" << endl;
            } else {
                nlohmann::json error_json = nlohmann::json::parse(server_response.body_data);
                cout << response_code << " " << response_message << " " << error_json["error"] << endl;
                free(response_c_str);
                continue;
            }

            // Print books
            print_books(server_response.body_data);
            free(response_c_str);
        } else if (command == "get_book") {
            // Check to see if the user can complete the command
            if (cookie.length() == 0) {
                cout << "You are not logged in!" << endl;
                continue;
            }
            if (jwt.length() == 0) {
                cout << "You are not inside the library!" << endl;
                continue;
            }

            // Create request
            string request = get_get_book_request(jwt, cookie);
            if (request == "") {
                continue;
            }

            // Send request to server
            int server_sockfd = open_connection(server_ip.data(), server_port, AF_INET, SOCK_STREAM, 0);
            send_to_server(server_sockfd, request.data());

            // Receive response from server
            char* response_c_str = receive_from_server(server_sockfd);
            string response(response_c_str);
            close_connection(server_sockfd);

            // Parse response
            ServerResponse server_response;
            server_response.deserialize(response_c_str);

            // Get response code and message
            string response_code = server_response.status_code;
            string response_message = server_response.status_message;

            // Check command was successful
            if (is_in_vector(ok_status_codes, response_code)) {
                cout << response_code << " " << response_message << " " << "Book received succesfully!" << endl;

                // Print book
                print_book(server_response.body_data);
            } else {
                nlohmann::json error_json = nlohmann::json::parse(server_response.body_data);
                cout << response_code << " " << response_message << " " << error_json["error"] << endl;
            }
            free(response_c_str);
        } else if (command == "add_book") {
            // Check to see if the user can complete the command
            if (cookie.length() == 0) {
                cout << "You are not logged in!" << endl;
                continue;
            }
            if (jwt.length() == 0) {
                cout << "You are not inside the library!" << endl;
                continue;
            }

            // Create request
            string request = get_add_book_request(jwt, cookie);
            if (request == "") {
                continue;
            }

            // Send request to server
            int server_sockfd = open_connection(server_ip.data(), server_port, AF_INET, SOCK_STREAM, 0);
            send_to_server(server_sockfd, request.data());

            // Receive response from server
            char* response_c_str = receive_from_server(server_sockfd);
            string response(response_c_str);
            close_connection(server_sockfd);

            // Parse response
            ServerResponse server_response;
            server_response.deserialize(response_c_str);

            // Get response code and message
            string response_code = server_response.status_code;
            string response_message = server_response.status_message;

            // Check command was successful
            if (is_in_vector(ok_status_codes, response_code)) {
                cout << response_code << " " << response_message << " " << "Book added succesfully!" << endl;
            } else {
                nlohmann::json error_json = nlohmann::json::parse(server_response.body_data);
                cout << response_code << " " << response_message << " " << error_json["error"] << endl;
            }
            free(response_c_str);
        } else if (command == "delete_book") {
            // Check to see if the user can complete the command
            if (cookie.length() == 0) {
                cout << "You are not logged in!" << endl;
                continue;
            }
            if (jwt.length() == 0) {
                cout << "You are not inside the library!" << endl;
                continue;
            }

            // Create request
            string request = get_delete_book_request(jwt, cookie);
            if (request == "") {
                continue;
            }

            if (request == "") {
                continue;
            } 

            // Send request to server
            int server_sockfd = open_connection(server_ip.data(), server_port, AF_INET, SOCK_STREAM, 0);
            send_to_server(server_sockfd, request.data());

            // Receive response from server
            char* response_c_str = receive_from_server(server_sockfd);
            string response(response_c_str);
            close_connection(server_sockfd);

            // Parse response
            ServerResponse server_response;
            server_response.deserialize(response_c_str);

            // Get response code and message
            string response_code = server_response.status_code;
            string response_message = server_response.status_message;

            // Check command was successful
            if (is_in_vector(ok_status_codes, response_code)) {
                cout << response_code << " " << response_message << " " << "Book deleted succesfully!" << endl;
            } else {
                nlohmann::json error_json = nlohmann::json::parse(server_response.body_data);
                cout << response_code << " " << response_message << " " << error_json["error"] << endl;
            }
            free(response_c_str);
        } else if (command == "logout") {
            // Check to see if the user can complete the command
            if (cookie.length() == 0) {
                cout << "You are not logged in!" << endl;
                continue;
            }

            // Create request
            string request = get_logout_request(cookie);

            // Send request to server
            int server_sockfd = open_connection(server_ip.data(), server_port, AF_INET, SOCK_STREAM, 0);
            send_to_server(server_sockfd, request.data());

            // Receive response from server
            char* response_c_str = receive_from_server(server_sockfd);
            string response(response_c_str);
            close_connection(server_sockfd);

            // Parse response
            ServerResponse server_response;
            server_response.deserialize(response_c_str);

            // Get response code and message
            string response_code = server_response.status_code;
            string response_message = server_response.status_message;

            // Check if logout was successful
            if (is_in_vector(ok_status_codes, response_code)) {
                cout << response_code << " " << response_message << " " << "Logged out succesfully!" << endl;

                // Delete cookie and JWT token
                cookie = "";
                jwt = "";
            } else {
                nlohmann::json error_json = nlohmann::json::parse(server_response.body_data);
                cout << response_code << " " << response_message << " " << error_json["error"] << endl;
            }
            free(response_c_str);
        } else {
            // 
            cout << "Inexistent command!" << endl;
            continue;
        }
        
    }

    return 0;
}