#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
if (!((p) = malloc(s))) { \
    fprintf(stderr, "Insufficient memory.\n"); \
    exit(EXIT_FAILURE); \
}

int binSearch(int ary[], int from, int to, int value);

int main(void)
{
    int n, i;
    int * ary;

    FILE * fp = NULL;

    fp = fopen("input_sorted.txt", "r");

    fscanf(fp, "%d", &n);
    ary = (int *) malloc(sizeof(*ary) * n);

    for(i = 0 ; i < n ; i++){
        fscanf(fp, "%d", &ary[i]);
    }
    fclose(fp);
    printf("%d에 있습니다. \n", binSearch(ary, 0, n - 1, 1424238767));
}

int binSearch(int ary[], int from, int to, int value)
{
    int mid = (from + to) / 2;
    static int count = 0;

    count ++;

    if (from > to) {
        return -1;
    }

    printf("[DEBUG] : %d's function call : from = %d, to =%d \n", count, from, to);

    if (ary[mid] == value) {
        return mid;
    }
    else if (ary[mid] < value) {
        return binSearch(ary, mid + 1, to, value);
    }
    else {
        return binSearch(ary, from, mid - 1, value);
    }
}
