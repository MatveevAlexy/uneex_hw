#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAXGR 100

void bagging(char *res, int *res_idx, char *string, regmatch_t *bags, int n) {
    if (bags[n].rm_so == -1) {
        printf("Error\n");
        exit(1);
    }
    strncpy(&res[*res_idx], &string[bags[n].rm_so], bags[n].rm_eo - bags[n].rm_so);
    *res_idx += bags[n].rm_eo - bags[n].rm_so;
}

int main(int argc, char **argv) 
{
    if (argc < 4) {
        printf("Too few arguments\n");
        return 1;
    }
    char *regexpr = argv[1], *sub = argv[2], *string = argv[3];
    regex_t regex;
    regmatch_t bags[MAXGR];
    if (regcomp(&regex, regexpr, REG_EXTENDED)) {
        printf("Error in regcomp\n");
        return 1;
    }
    int ret_val = regexec(&regex, string, MAXGR, bags, 0);
    if (ret_val == REG_NOMATCH) {
        printf("%s\n", string);
    } else if (ret_val) {
        printf("Error in regexec\n");
        return 1;
    }
    char prev_sym = '\0', *res = malloc((strlen(string) + strlen(sub)) * sizeof(*res));
    int res_idx = bags[0].rm_so;
    strncpy(res, string, bags[0].rm_so);
    for (size_t i = 0; i < strlen(sub); i++) {
        if (prev_sym == '\\') {
            if (sub[i] == '\\') {
                res[res_idx++] = '\\';
            } else if (sub[i] >= '0' && sub[i] <= '9') {
                bagging(res, &res_idx, string, bags, sub[i] - '0');
            } else {
                printf("Error\n");
                return -1;
            }
            prev_sym = '\0';
            continue;
        } else if (prev_sym != '\0') {
            res[res_idx++] = prev_sym;
        }
        prev_sym = sub[i];
    }
    if (prev_sym == '\\') {
        printf("Error\n");
        return -1;
    } else if (prev_sym != '\0') {
        res[res_idx++] = prev_sym;
    }
    strncpy(&res[res_idx], &string[bags[0].rm_eo], strlen(string) - bags[0].rm_eo);
    res_idx += strlen(string) - bags[0].rm_eo;
    res[res_idx] = '\0';
    printf("%s\n", res);
    regfree(&regex);
    free(res);
    return 0;
}
