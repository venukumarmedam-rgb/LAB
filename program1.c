#include <stdio.h>
#include <math.h>
int main() {
    int n, x, i;
    long long sum = 0, term = 1;
    scanf("%d %d", &x, &n);
    for(i = 0; i <= n; i++) {
        sum += term;
        term *= x;
    }
    printf("%lld", sum);
    return 0;
}
