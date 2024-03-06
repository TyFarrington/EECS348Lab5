#include <stdio.h>

int main() {
    int score;
    printf("Enter 0 or 1 to STOP\n");
    printf("Enter the NFL score: ");
    scanf("%d", &score);

    while(score > 1) {
        printf("Possible combinations of scoring plays for the score %d:\n", score);
        
        for(int td2pt = 0; td2pt*8 <= score; ++td2pt) {
            for(int tdFg = 0; tdFg*7 + td2pt*8 <= score; ++tdFg) {
                for(int td = 0; td*6 + tdFg*7 + td2pt*8 <= score; ++td) {
                    for(int fg = 0; fg*3 + td*6 + tdFg*7 + td2pt*8 <= score; ++fg) {
                        int remainingScore = score - (td2pt*8 + tdFg*7 + td*6 + fg*3);
                        if(remainingScore % 2 == 0) {
                            int safety = remainingScore / 2;
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td2pt, tdFg, td, fg, safety);
                        }
                    }
                }
            }
        }
        
        printf("Enter the NFL score (Enter 0 or 1 to STOP): ");
        scanf("%d", &score);
    }

    return 0;
}