#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>

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

Stanza* initStanza(char* context){
    Stanza* stanza = (Stanza*)malloc(sizeof(Stanza));
    stanza->lines = (Line*)malloc(sizeof(Line)*100);
    stanza->line_count = 0;
    int cnt = 0;

    while(context[cnt] != '\0'){
        if (context[cnt] == '\n' && context[cnt+1] == '\n'){
            stanza->line_count++;
        }
        cnt++;
    }

    return stanza;
}

Poem* initPoem(char* context){
    Poem* poem = (Poem*)malloc(sizeof(Poem));
    poem->title = (char*)malloc(sizeof(char)*100);
    int cur = 0;
    while (context[cur] != '\n'){                                   
        poem->title[cur] = context[cur];
        cur++;
    }
    poem->title[cur] = '\0';
    cur++;
    poem->author = (char*)malloc(sizeof(char)*100);
    while (context[cur] == ' '|| context[cur] == '\n' || context[cur] == '\t'){
        printf("%d, %x\n", cur, context[cur]);
        cur++;
    }
    int author_cur = 0;
    while (context[cur] != '\n'){
        poem->author[author_cur] = context[cur];
        cur++;
        author_cur++;
    }
    poem->author[cur] = '\0';
    cur++;
    poem->stanzas = initStanza(context+cur);
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
    puts(poem->author);
    printf("%d\n", poem->stanzas->line_count);  

    
    

    return 0;   


}