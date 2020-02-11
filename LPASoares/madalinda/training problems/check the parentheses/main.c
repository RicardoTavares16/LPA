#include <string.h>

// ( = 40
// ) = 41
// [ = 91
// ] = 93

int eat(char * str, int pos) {
    int res;
    char current;

    if (str[pos] == '\0') {

    }

    if (str[pos] == 40 || str[pos] == 91) { //str[pos] is an opening bracket
        current = str[pos];
        res = eat(str, pos++);
    }

    else return pos;

    if (res == -1) return 1;

    else {
        if (str[res] ==
    }

}


int main(int argc, char **argv){
    int n;
    chat str[128];

    scanf("%d", &n);
    int res;

    printf("n = %d\n", n);

    for (int i=0; i<n; i++) {
        scanf("%[^\n]",str);
        res = eat(str, 0)
    }
}