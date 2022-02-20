#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "protocols.h"

void scan_paths(char* str, char* delim)
{
    FILE* file;
    file = fopen("input.txt", "r");
    fscanf(file, "%s", delim);
    fscanf(file, "%s", str);
    fclose(file);
}

char* refresh(char* path, char* delim)
{
    if (!path)
        return NULL;
    char* paths[10];
    int pathsCount;
    pathsCount = stok(path, delim[0], paths);
    char* tokens[10];
    char* new_paths[10];
    int tokensCount;
    int npathCount = 0;
    int error = 0;
    for (int i = 0; i < pathsCount; i++) {
        tokensCount = stok(paths[i], '/', tokens);

        char* buf = calloc(20,1);
        scpy(buf, tokens[2]);
        error = 0;
        char* url_parts[4];
        int url_p_count = stok(buf, '.', url_parts);
        if (url_p_count == 2) {
            if (scmp(url_parts[1], domains[0]) && scmp(url_parts[1], domains[1]) && scmp(url_parts[1], domains[2])) {
                error = 1;
            }
        } else if (url_p_count == 4) {
            int t, num;
            for (int j = 0; j < 4; j++) {
                t = 0;
                num = m_atoi(url_parts[j], t);
                if (num < 0 || num > 255) {
                    error = 1;
                }
            }
        }

        if (!error && (!scmp(tokens[0], protocols[0]) || !scmp(tokens[0], protocols[1]))) {

            char* temp = calloc(MAX_PATH,1);
            temp = scat(temp, "\\");
            for (int j = 2; j < tokensCount; j++) {

                temp = scat(temp, "\\");
                temp = scat(temp, tokens[j]);
            }
            new_paths[npathCount] = temp;
            npathCount++;
        }
    }

    char* res = calloc(LENGTH,1);
    res = scat(res, new_paths[0]);
    for (int i = 1; i < npathCount; i++) {
        res = scat(res, "+");
        res = scat(res, new_paths[i]);
    }
    return res;
}