#include <stdio.h>
#include <stdlib.h>

void print_Single_Score(int touchdown_Twos, int touchdown_Ones, int touchdowns, int field_Goals, int safeties) {
	printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", touchdown_Twos, touchdown_Ones, touchdowns, field_Goals, safeties);
}

void print_Score_Combinations(int score) {
	int max_Touchdown_Twos = score / 8;
	int max_Touchdown_Ones = score / 7;
	int max_Touchdowns = score / 6;
	int max_Field_Goals = score / 3;
	int max_Safeties = score / 2;

	for (int i = 0; i <= max_Touchdown_Twos; i++) {
		for (int j = 0; j <= max_Touchdown_Ones; j++) {
			for (int k = 0; k <= max_Touchdowns; k++) {
				for (int l = 0; l <= max_Field_Goals; l++) {
					for (int m = 0; m <= max_Safeties; m++) {
						if (i * 8 + j * 7 + k * 6 + l * 3 + m * 2 == score) {
							print_Single_Score(i,j,k,l,m);
						}
					}
				}
			}
		}
	}
}

int main() {
	printf("Welcome to the NFL Combination calculator\n");
	printf("Enter a score to get all possible combinations of scoring plays\n");
	printf("Enter 0 or 1 at the score prompt to stop\n");

	while (1) {
		int score;
		printf("Score:");
		scanf("%d", &score);

		if (score <= 1) {
			printf("Exit requested (or invalid score given)\n");
			exit(0);
		}
		
		print_Score_Combinations(score);
	}

	exit(-1);
}
