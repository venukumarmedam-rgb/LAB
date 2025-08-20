#include <stdio.h>
#include <math.h>

long long sumSeries(int x, int n) {
    if(n == 0){
 return 1;
}
else
    return sumSeries(x, n - 1) + (long long)pow(x, n);
}

int main() {
    int x, n;
    scanf("%d %d", &x, &n);
    printf("%lld", sumSeries(x, n));
    return 0;
}
