#ifndef REPORT_H
#define REPORT_H

#include "analyzer.h"

void print_summary(const AnalysisResult *result , int error_only);
void print_top_errors(const AnalysisResult *result , int top_n);


#endif