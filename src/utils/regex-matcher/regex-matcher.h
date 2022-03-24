typedef struct regex_match{
    char *matched_substr;
    unsigned int start_index;
    unsigned int end_index;
} regex_match;

regex_match *regex_matcher (char *string, char *patrn);