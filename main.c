#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

typedef struct{
    char* text;
    int text_len;
} Line;

typedef struct{
    Line* lines;
    int line_count;
} Stanza;

typedef struct {
    char* title;
    char* author;
    Stanza* stanzas;
    int stanza_count;
} Poem;

Poem* initPoem(char* context){
    Poem* poem = (Poem*)malloc(sizeof(Poem));
    int cur = 0;
    while (context+cur != '\n'){
        poem->title[cur] = context[cur];
        cur++;
    }
    poem->title[cur] = '\0';
    cur++;
    while (context+cur != '\n'){
        poem->author[cur] = context[cur];
        cur++;
    }
    poem->author[cur] = '\0';
    cur++;
    int stanza_count = 0;
    Stanza* stanzas = NULL;
    return poem;
}

char* ReadFile(char* filename) {
    FILE* rfile = fopen(filename, "r");
    if (rfile == NULL) {
        return NULL;
    }

    fseek(rfile, 0, SEEK_END);
    long length = ftell(rfile);
    fseek(rfile, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (buffer == NULL) {
        fclose(rfile);
        return NULL;
    }

    fread(buffer, 1, length, rfile);
    buffer[length] = '\0';

    fclose(rfile);
    return buffer;
}




int main(){

    printf("시 파일 경로 입력 <파일확장자:txt> : ");
    char* filename = (char*)malloc(100);
    scanf("%100s", filename);
    char* context = ReadFile(filename);
    free(filename);
    puts(context);
    Poem* poem = initPoem(context);
    puts(poem->title);

    
    

    return 0;   


}
