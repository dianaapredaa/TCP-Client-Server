#ifndef _HELPERS_
#define _HELPERS_

#define BUFLEN 4096
#define LINELEN 1000

// enum commands {
//     register_client,
//     login_client,
//     enter_library,
//     get_books,
//     get_book,
//     add_book,
//     delete_book,
//     logout_client,
//     exit_client,
//     invalid_command
// }typedef commands;

// static std::unordered_map<std::string,commands> const table = 
//     { {"register",commands::register_client}, {"login",commands::login_client},
//       {"enter_library",commands::enter_library}, {"exit",commands::exit_client}, 
//       {"get_books",commands::get_books}, {"get_book",commands::get_book},
//       {"add_book",commands::add_book}, {"delete_book",commands::delete_book},
//       {"logout",commands::logout_client}};

// shows the current error
void error(const char *msg);

// adds a line to a string message
void compute_message(char *message, const char *line);

// opens a connection with server host_ip on port portno, returns a socket
int open_connection(char *host_ip, int portno, int ip_type, int socket_type, int flag);

// closes a server connection on socket sockfd
void close_connection(int sockfd);

// send a message to a server
void send_to_server(int sockfd, char *message);

// receives and returns the message from a server
char *receive_from_server(int sockfd);

// extracts and returns a JSON from a server response
char *basic_extract_json_response(char *str);

#endif
