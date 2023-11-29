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
    char *stanza_num;
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

    //Debugging 코드
    printf("연의 갯수 : %d\n", poem->stanza_count);
    puts("");
    Stanza* stanza[poem->stanza_count];

    //Devide Stanza
    for (int i = 0; i < poem->stanza_count; i++){
    stanza[i] = (Stanza*)malloc(sizeof(Stanza));
    stanza[i]->context = (char*)malloc(sizeof(char)*1000);
    if (stanza[i]->context == NULL) {
        //Debugging Code
        printf("%d Stanza is NULL !!\n",i);
    }
    stanza[i]->line_count = 0;
}

    int stanza_cnt = 0;
    int stanza_context_cnt = 0;

    while(context[cnt] != '\0'){
    if(context[cnt] == '\n' && context[cnt+1] == '\n'){
        stanza[stanza_cnt]->context[stanza_context_cnt] = '\0';
        stanza_cnt ++;
        stanza_context_cnt = 0;
        stanza[stanza_cnt]->line_count = 0;
    }else if(context[cnt] == '\n'){
        stanza[stanza_cnt]->line_count++;
        //stanza_num[stanza_cnt][stanza[stanza_cnt]->line_count] = context[cnt-1];
    }else{
        stanza[stanza_cnt]->context[stanza_context_cnt] = context[cnt];
        stanza_context_cnt++;
    }
    cnt++;
}


//Debugging Code
for(int i=0;i<poem->stanza_count;i++){
    printf("stanza[i]의 줄 갯수: %d\n", stanza[i]->line_count);
    for(int j=0;j<strlen(stanza[i]->context); j++){
        if(stanza[i]->context[j] == '\n'){
            printf("\n");
        }
        printf("%c", stanza[i]->context[j]);
    }
    printf("\n");
}

//Save Stanza_Numbers (운율)
for(int i=0;i<poem->stanza_count;i++){
    stanza[i]->stanza_num = (char*)malloc(sizeof(char)*stanza[i]->line_count);
    int stanza_num_cnt = 0;
    for(int j=0;j<strlen(stanza[i]->context); j++){
        if(stanza[i]->context[j] == '\n'){
            stanza[i]->stanza_num[stanza_num_cnt] = stanza[i]->context[j-1];
            printf("%c", stanza[i]->stanza_num[stanza_num_cnt]);
            stanza_num_cnt++;
        }
    }

}

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
    //puts(poem->stanzas->lines[0].text);

    return 0;


}
