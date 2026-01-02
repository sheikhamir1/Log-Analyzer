#ifndef PARSER_H
#define PARSER_H

#define MAX_MESSAGE_LEN 1024

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_ERROR 2
#define LOG_LEVEL_UNKNOWN -1

typedef struct {
    char timestamp[20];  // "2025-01-01 12:30:35"
    int level; // error , warn , info 
    char message[MAX_MESSAGE_LEN]; // "Database Connection Failed"
}LogEntry;

int parse_log_line(const char *line , LogEntry *entry); // "2025-01-01 12:30:35 Error Disk full"


#endif