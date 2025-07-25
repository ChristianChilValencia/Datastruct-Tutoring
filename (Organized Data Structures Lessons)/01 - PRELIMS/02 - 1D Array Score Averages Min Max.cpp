//Minimum, Maximum, Average by Gym scores
#include <stdio.h>
int maxf(int scores[], int n) {
    int maxs = scores[0];
    for (int i = 1; i < n; i++) {
        if (scores[i] > maxs) {
            maxs = scores[i];
        }
    }return maxs;
}

int minf(int scores[], int n) {
    int mins = scores[0];
    for (int i = 1; i < n; i++) {
        if (scores[i] < mins) {
            mins = scores[i];
        }
    }return mins;
}

int avercalc(int scores[], int n) {
    int maxs = maxf(scores, n);
    int mins = minf(scores, n);
    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (scores[i] != maxs && scores[i] != mins) {
            sum += scores[i];
        }
    }return sum / (n - 2);
}

int main() {
    int scores[7];
    printf("The scores of these judges are:\n");
    for (int i = 0; i < 7; i++) {
        scanf("%d", &scores[i]);
    }
    
    int maxs = maxf(scores, 7);
    int mins = minf(scores, 7);
    int ave = avercalc(scores, 7);
    
    printf("=========================\n[SCORES IN ALL]\n");
    printf("Maximum: %d\n", maxs);
    printf("Average: %d\n", ave);
    printf("Minimum: %d\n", mins);
    
    return 0;
}
