#include "file_reader.h"
#include <stdlib.h>
#include <string.h>

FileReader* open_file(const char *filename){
    FileReader *reader = malloc(sizeof(FileReader));
    if(!reader) return NULL;

    reader->file = fopen(filename,"r");
    if (!reader->file){
        free(reader);
        return NULL;
    }
    return reader;
}

char* read_line(FileReader *reader , char *line , size_t max_len){
    if(!reader || !reader->file || !line) return NULL;
    return fgets(line,max_len, reader->file);
}

void close_file(FileReader *reader){
    if(reader){
        if(reader->file) fclose(reader->file);
        free(reader);
    }
}
