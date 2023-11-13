#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

typedef struct{
    char* text;
    int text_length;
} Line;

typedef struct{
    Line lines;
    int line_count;
} Stanza;

typedef struct {
    char* title;
    char* author;
    Stanza stanzas[];
} Poem;



char* open_and_read_file(const char* filename) {
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (buffer == NULL) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int main(){

    printf("시 파일 경로 입력 <파일확장자:txt> : ");
    char filename[100];
    scanf("100%s", filename);
    open_and_read_file(filename);

}