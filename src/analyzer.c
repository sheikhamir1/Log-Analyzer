#include "analyzer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AnalysisResult* init_analyzer(){
    AnalysisResult *result = malloc(sizeof(AnalysisResult));
    if(!result) return NULL;

    result->total_line = 0;
    result->info_count = 0;
    result->warn_count = 0;
    result->error_count_unique = 0;
    result->error_capacity = 100;
    
    result->error_entries = calloc(result->error_capacity, sizeof(ErrorEntry));
    if (!result->error_entries){
        free(result);
        return NULL;
    }

    return result;
}


static void add_error_message(AnalysisResult *result , const char *message) {
    // check if message already exists
    for ( int i = 0 ; i < result->error_count_unique ; i++){
        if(strcmp(result->error_entries[i].message, message) == 0) {
            result->error_entries[i].count++;
            return;
        }
    }
    // new error message - check capacity
    if(result->error_count_unique >= result->error_capacity){
        // double the capacity
        int new_capacity = result->error_capacity * 2;
        ErrorEntry *new_entries = realloc(result->error_entries, new_capacity * sizeof(ErrorEntry));
        if (!new_entries) return;

        result->error_entries = new_entries;
        result->error_capacity = new_capacity;
    }

    // add new entry
    snprintf(result->error_entries[result->error_count_unique].message, MAX_MESSAGE_LEN, "%s", message);

    result->error_entries[result->error_count_unique].count = 1;
    result->error_count_unique++;

}

void process_log_line(AnalysisResult *result , const LogEntry *entry) {
    if (!result || !entry) return;

    result->total_line++;

    switch(entry->level) {
        case LOG_LEVEL_INFO:
        result->info_count++;
        break;

        case LOG_LEVEL_WARN:
        result->warn_count++;
        break;

        case LOG_LEVEL_ERROR:
        result->error_count++;
        add_error_message(result, entry->message);
        break;
    }
}


void get_top_errors(const AnalysisResult *result , int top_n, ErrorEntry *top_errors) {
    if (!result || !top_errors) return;

    int n = result->error_count_unique < top_n ? result->error_count_unique : top_n ;

    // create a copy to avoid modifying original
    ErrorEntry *temp = malloc(result->error_count_unique * sizeof(ErrorEntry));
    if (!temp) return ;

    memcpy(temp , result->error_entries , result->error_count_unique * sizeof(ErrorEntry));

    // selection sort (descending by count)
    for (int i = 0 ; i< n ; i++) {
        int max_idx = i;
        for (int j = i + 1 ; j < result->error_count_unique ; j ++) {
            if (temp[j].count > temp[max_idx].count) {
                max_idx = j;
            }
        }
        // swap
        ErrorEntry swap = temp[i];
        temp[i] = temp[max_idx];
        temp[max_idx] = swap;
    }
    // copy top N
    memcpy(top_errors , temp , n * sizeof(ErrorEntry));
    free(temp);
}


void cleanup_analyzer(AnalysisResult *result) {
    if (result) {
        if (result->error_entries) {
            free(result->error_entries);
        }
        free(result);
    }
}


