#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "./regex-matcher.h"

 
regex_match *match (char *string, char *patrn) {
        unsigned int begin;
        unsigned int end;
        int i, w = 0, len;
        char *word = NULL;
        regex_t rgT;
        regmatch_t match;
        regcomp(&rgT,patrn,REG_EXTENDED);
        if ((regexec(&rgT,string,1,&match,0)) == 0) {
                begin = (int)match.rm_so;
                end = (int)match.rm_eo - 1;
                len = end-begin;
                word=malloc(len+1);
                for (i=begin; i<end+1; i++) {
                        word[w] = string[i];
                        w++; }
                word[w]=0;
        }
        regfree(&rgT);
        regex_match *matched = matched = malloc(sizeof(matched) + sizeof(char) * strlen(word));
        matched->matched_substr = word;
        matched->start_index = begin;
        matched->end_index = end;
        return matched;
}
 
 
int main() {
    char value[] = "this and7 that";
    regex_match *matched=match(value,"[a-z]+[0-9]");
    //printf("->%s<-\n(a=%d b=%d\nStart:%c\nEnd:%c)\n",matched,a,b,value[5], value[8]);
    return 0;
}