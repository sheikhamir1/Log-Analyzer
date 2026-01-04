#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_reader.h"
#include "parser.h"
#include "analyzer.h"
#include "report.h"

#define VERSION "1.0.0" //loganalyzer --version

void print_usage(const char *program_name) {
    printf("Usage: %s <log file> [option]\n", program_name);
    // Usage: ./loganalyzer server.log [option]
    printf("Options: \n");
    printf("   --errors-only           show only error Summary\n");
    printf("   --top-errors N          show top N most frequent errors ( default: 10)\n");
    printf("   --help                  show this help message\n");
    printf("   --version               show version\n");
    printf("\nExmaple:\n");
    printf(" %s server.log\n", program_name);
    printf(" %s server.log --errors-only  --top-errors 5\n", program_name);
}

int main (int argc , char *argv[]) {
    if (argc < 2){
        print_usage(argv[0]);
        return 1;
    }
    // parse argument
    const char *filename = NULL;
    int errors_only = 0;
    int top_n = 10;

    for (int i = 0 ; i < argc ; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--version") == 0) {
            printf("Loganalyzer version %s\n", VERSION);
            return 0;
        } else if (strcmp(argv[i], "--errors-only") == 0) {
            errors_only = 1;
        } else if (strcmp(argv[i], "--top-errors")==0 ) {
            if (i + 1 < argc) {
                top_n = atoi(argv[++i]);
                if ( top_n <= 0) top_n = 10;
            }
        } else if (argv[i][0] != '-') {
            filename = argv[i];  // ./loganalyzer server.log --errors-only
        }
    }

    if (!filename) {
        fprintf(stderr, "Error: No log file specified\n");
        print_usage(argv[0]);
        return 1;
    }

    // open file 
    FileReader *reader = open_file(filename);
    if (!reader) {
        fprintf(stderr, "Error: Could not open file'%s'\n", filename);
        return 1;
    }

    //initailize analyzer
    AnalysisResult *result = init_analyzer();
    if (!result) {
        fprintf(stderr, "Error: Memory Allocation Failed\n");
        close_file(reader);
        return 1;
    }

    // Process file line by line
    char line[2048];
    LogEntry entry;
    int processed_lines = 0;

    printf("Analyzing log files: %s\n", filename);
    printf("Press Ctrl+C to abort...: \n\n");

    while (read_line(reader,line, sizeof(line))) {
        if (parse_log_line(line , &entry) == 0) {
            process_log_line(result , &entry);
            processed_lines++;

            // progress indecator
            if (processed_lines % 10000 == 0) {
                printf("\rProcessed %'d Lines...", processed_lines);
                fflush(stdout);
            }
        }
    }

    printf("\rProcessed %'d lines.... Done!   \n\n", processed_lines);
    // Generate report
    print_summary(result , errors_only);

    if (!errors_only || result->error_count > 0) {
        print_top_errors(result , top_n);
    }
    // cleanup
    cleanup_analyzer(result);
    close_file(reader);
    return 0;
}


