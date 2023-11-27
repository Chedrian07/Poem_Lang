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
    char* context;
    int line_count;
} Stanza;

typedef struct {
    char* title;
    char* author;
    Stanza* stanzas;
    int stanza_count;
} Poem;

Stanza* initStanza(Poem* poem, char* context, int cur){
    poem->stanza_count = 1;
    printf("%d\n", cur);
    while (context[cur] == '\n' || context[cur] == ' ' || context[cur] == '\t'){
        cur++;
    }
    int cnt = cur;
    while (context[cur] != '\0'){
        if (context[cur] == '\n' && context[cur+1] == '\n'){
            poem->stanza_count++;
        }
        cur++;
    }

    printf("%d\n", poem->stanza_count);
    Stanza* stanza[poem->stanza_count];

    for (int i = 0; i < poem->stanza_count; i++){
        stanza[i]->context = (char*)malloc(sizeof(char)*1000);
        stanza[i]->line_count = 0;
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
    poem->stanzas = initStanza(poem, context,cur);
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
    printf("%d\n", poem->stanza_count);
    puts(poem->stanzas->lines[0].text);




    return 0;


}
