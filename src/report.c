#include "report.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#define COLOR_INFO "\033[1;32m" // green
#define COLOR_WARN "\033[1;33m" // yellow
#define COLOR_ERROR "\033[1;31m" // Red
#define COLOR_RESET "\033[0m" // RESET
#else
#define COLOR_INFO ""
#define COLOR_WARN ""
#define COLOR_ERROR ""
#define COLOR_RESET ""

#endif

void print_summary(const AnalysisResult *result , int error_only) {
    if (!result) return;

    if (error_only) {
        printf(COLOR_ERROR "Errros Summary\033[0m\n");
        printf("------------------\n");
        printf("Total Errors: %d\n" , result->error_count);
    } else {
        printf("Log Summary\n");
        printf("----------------\n");
        printf("Total lines : %'d\n", result->total_line);
        printf(COLOR_INFO "INFO               : %'d\033[0m\n", result->info_count); 
        printf(COLOR_INFO "WARN               : %'d\033[0m\n", result->warn_count);
        printf(COLOR_INFO "ERROR               : %'d\033[0m\n", result->error_count);
    }
}


void print_top_errors(const AnalysisResult * result , int top_n){
    if (!result || top_n <= 0) return;

    if (result->error_count_unique == 0) {
        printf("\nNo erros found.\n");
        return;
    }

    ErrorEntry *top_erros = malloc(top_n * sizeof(ErrorEntry));
    if (!top_erros) return;

    get_top_errors(result , top_n , top_erros);

    printf("\nTop %d Errors:\n", top_n);
    printf("------------\n");

    for (int i = 0 ; i < top_n && result->error_count_unique ; i++) {
        printf("%d. %s (%d Occurrences)\n", i + 1 ,top_erros[i].message , top_erros[i].count);
    }

    free(top_erros);

}

