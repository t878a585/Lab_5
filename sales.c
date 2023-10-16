#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Returns null if newline is the first character
char * strip_Newline(char * string) {
	int n = 0;
	char * new_String;

	while (string[n] != '\n') {
		n++;
	}

	if (n == 0) return (char *) 0;
	
	new_String = malloc(sizeof(char) * (n + 1));
	strncpy(new_String, string, n);
	new_String[n] = '\0';

	return new_String;
}

FILE * get_File() {
	char * filename = (char *) 0;
	char * filename_Processed;
	size_t n;

	printf("Please Input the filename:");
	
	getline(&filename, &n, stdin);

	filename_Processed = strip_Newline(filename);
	
	free(filename);
	
	if (filename_Processed == (char *) 0) {
		free(filename_Processed);
		printf("No filename provided\n");
		exit(-1);
	}
	
	FILE * file = fopen(filename_Processed, "r");
	free(filename_Processed);
	
	if (file == NULL) {
		printf("Error opening file\n");
		exit(-1);
	}

	return file;
}

char ** get_Sales_Numbers(FILE * file) {
	char ** list = malloc(sizeof(char *) * 12);

	for (int i = 0; i < 12; i++) {
		char * current_Line = (char *) 0;
		size_t n;

		getline(&current_Line, &n, file);
		list[i] = current_Line;
	}

	return list;
}

double * get_Sales_Numbers_Doubles(char ** sales_Numbers) {
	double * sales_Numbers_Doubles = malloc(sizeof(double) * 12);

	for (int i = 0; i < 12; i++) {
		sales_Numbers_Doubles[i] = atof(sales_Numbers[i]);
	}

	return sales_Numbers_Doubles;
}

void free_Sales_Numbers(char ** sales_Numbers) {
	for (int i = 0; i < 12; i++) {
		free(sales_Numbers[i]);
	}

	free(sales_Numbers);
}

struct sales_Stats {
	int minimum_Sales, maximum_Sales;

	double average_Sales, moving_Average[7];
	
	int ascending_Order[12];
};

void bubble_Sort_Ascending(double * sales_Numbers_Doubles, struct sales_Stats * stats) {
	int sorted = 0;

	while (!sorted) {
		sorted = 1;

		for (int i = 0; i < 11; i++) {
			if (sales_Numbers_Doubles[stats->ascending_Order[i]] > sales_Numbers_Doubles[stats->ascending_Order[i+1]]) {
				sorted = 0;
				double tmp = stats->ascending_Order[i];
				stats->ascending_Order[i] = stats->ascending_Order[i + 1];
				stats->ascending_Order[i + 1] = tmp;
			}
		}
	}
	
	return;
}

void find_Moving_Averages(double * sales_Numbers_Doubles, struct sales_Stats * stats) {
	
	for (int start_Month = 0; start_Month < 7; start_Month++) {
		stats->moving_Average[start_Month] = 0;

		for (int i = start_Month; i < start_Month + 6; i++) {
			stats->moving_Average[start_Month] += sales_Numbers_Doubles[i];
		}

		stats->moving_Average[start_Month] /= 6;
	}

}

struct sales_Stats get_Sales_Stats(double * sales_Numbers_Doubles) {
	struct sales_Stats stats = {.ascending_Order = {0,1,2,3,4,5,6,7,8,9,10,11}};

	stats.average_Sales = 0;
	stats.minimum_Sales = 0;
	stats.maximum_Sales = 0;

	for (int i = 0; i < 12; i++) {
		stats.average_Sales += sales_Numbers_Doubles[i];
		
		if (sales_Numbers_Doubles[i] < sales_Numbers_Doubles[stats.minimum_Sales]) {
			stats.minimum_Sales = i;
		}

		if (sales_Numbers_Doubles[i] > sales_Numbers_Doubles[stats.maximum_Sales]) {
			stats.maximum_Sales = i;
		}
	}

	stats.average_Sales /= 12;
	
	find_Moving_Averages(sales_Numbers_Doubles, &stats);
	bubble_Sort_Ascending(sales_Numbers_Doubles, &stats);

	return stats;
}

void print_Sales_Report(double * sales_Numbers_Doubles) {
	printf("Monthly sales report for: %d\n", 2023);
	printf("Month\t\tSales\n\n");

	char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	
	for (int i = 0; i < 12; i++) {
		if ((i >= 2 && i <= 7) || i == 9 || i == 0) {
			printf("%s\t\t$%.2f\n", months[i], sales_Numbers_Doubles[i]);
		} else {
			printf("%s\t$%.2f\n", months[i], sales_Numbers_Doubles[i]);
		}
	}
	
	struct sales_Stats stats = get_Sales_Stats(sales_Numbers_Doubles);
	
	printf("\n");	
	printf("Sales summary:\t\n\n");
	printf("Minimum sales:\t$%.2f (%s)\n", sales_Numbers_Doubles[stats.minimum_Sales], months[stats.minimum_Sales]);
	printf("Maximum sales:\t$%.2f (%s)\n", sales_Numbers_Doubles[stats.maximum_Sales], months[stats.maximum_Sales]);
	printf("Average sales:\t$%.2f\n\n", stats.average_Sales);
	
	printf("Six-Month Moving Average Report:\n\n");

	for (int i = 0; i < 7; i++) {
		if (i == 1) {
			printf("%s\t-\t%s $%.2f\n", months[i], months[i + 5], stats.moving_Average[i]);
		} else {
			printf("%s\t\t-\t%s $%.2f\n", months[i], months[i + 5], stats.moving_Average[i]);
		}
	}
	
	printf("Sales Report (Highest to Lowest):\n\n");
	printf("Month\t\tSales\n");

	for  (int i = 11; i >= 0; i--)	{ 
		
		if ((stats.ascending_Order[i] >= 2 &&  stats.ascending_Order[i] <= 7) || stats.ascending_Order[i] == 9 || stats.ascending_Order[i] == 0) {
			printf("%s\t\t$%.2f\n", months[stats.ascending_Order[i]], sales_Numbers_Doubles[stats.ascending_Order[i]]);
		} else {
			printf("%s\t$%.2f\n", months[stats.ascending_Order[i]], sales_Numbers_Doubles[stats.ascending_Order[i]]);
		}

	}
}

int main(int argc, char ** argv) {
	FILE * file = get_File();
	char ** sales_Numbers = get_Sales_Numbers(file);
	
	fclose(file);

	double * sales_Numbers_Doubles = get_Sales_Numbers_Doubles(sales_Numbers);	
	free_Sales_Numbers(sales_Numbers);

	print_Sales_Report(sales_Numbers_Doubles);
	free(sales_Numbers_Doubles);
	
	exit(0);
}
