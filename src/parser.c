#include "parser.h"
#include <string.h>
#include <stdio.h>

int parse_log_line(const char *line, LogEntry *entry){
    if (!line || !entry) return -1;

    memset(entry, 0 , sizeof(LogEntry));

    if(strlen(line) < 20) return -1;

    strncpy(entry->timestamp , line , 19);
    entry->timestamp[19] = '\0';

    const char *level_start = line + 20;

    if (strncmp(level_start, "INFO", 4)== 0){
        entry->level = LOG_LEVEL_INFO;
        level_start +=5;

    }else if(strncmp(level_start , "WARN", 4)== 0 ){
        entry->level = LOG_LEVEL_WARN;
        level_start +=5;
        
    }else if (strncmp(level_start, "ERROR", 5) == 0) {
        entry->level = LOG_LEVEL_ERROR;
        level_start +=6;

    }else{
        entry->level = LOG_LEVEL_UNKNOWN;
        return -1;
    }

    strncpy(entry->message , level_start , MAX_MESSAGE_LEN - 1);

    size_t len = strlen(entry->message);
    if (len > 0 && entry->message[len - 1] == '\n'){
        entry->timestamp[19] = '\0';

    }

    return 0;
}

