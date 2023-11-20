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

char* regex(char* pattern, char* str){
    int ret;
    char pattern[128], str[128];

    int cflags = REG_EXTENDED;
    regex_t reg;

    printf("regexp(%s),string(%s)\n", pattern, str);
    // reg compile
    ret = regcomp(&reg, pattern, cflags);
    if (ret != 0) {
            char errStr[128];
            regerror(ret, &reg, errStr, sizeof(errStr));
            printf("regcomp error(%s)\n", errStr);
            exit(1);
    }

    int eflags = 0, len;
    int offset = 0, cnt = 1;
    // pattern matching
    regmatch_t pmatch;

    while((ret = regexec(&reg, str+offset, 1, &pmatch, eflags))== 0)
    {
            len = pmatch.rm_eo - pmatch.rm_so;
            printf("matched string(%d:%.*s)\n",
                    cnt, len, str+offset+pmatch.rm_so);
            offset += pmatch.rm_eo;
            cnt++;
    }
    regfree(&reg);
    return 0;
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
    //puts(context);
    Poem* poem = initPoem(context);
    puts(poem->title);

    
    

    return 0;   


}
