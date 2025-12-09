#include "header.h"

int main(void) {
    FILE *fp = fopen("input", "r");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    char buf[2048];    
    if (!fgets(buf, sizeof(buf), fp)) {
        printf("읽을 수식이 없습니다.\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    Token *tokens = trans_token(buf);

    return 0;
}