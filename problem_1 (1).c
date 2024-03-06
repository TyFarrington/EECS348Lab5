#include <stdio.h>
#include <stdlib.h>

#define NUM_MONTHS 12

typedef struct {
    char month[20];
    double sale;
} SaleData;

int main() {
    SaleData sales[NUM_MONTHS] = { {"January", 0}, {"February", 0}, {"March", 0}, {"April", 0}, {"May", 0}, {"June", 0}, {"July", 0}, {"August", 0}, {"September", 0}, {"October", 0}, {"November", 0}, {"December", 0}
    };

    // Opens the file for reading
    FILE* file = fopen("sales_data.txt", "r");
    if (!file) {
        perror("Unable to open the file");
        return 1;
    }

    // Reads the sales data from the file
    for (int i = 0; i < NUM_MONTHS; ++i) {
        if (fscanf(file, "%lf", &sales[i].sale) != 1) {
            fprintf(stderr, "Failed to read sales data for %s.\n", sales[i].month);
            fclose(file);
            return 1;
        }
    }

    fclose(file); // Closes the file

    // Prints Monthly Sales Report
    printf("Monthly Sales Report for 2022:\n");
    for (int i = 0; i < NUM_MONTHS; ++i) {
        printf("%-9s: $%.2f\n", sales[i].month, sales[i].sale);
    }

    // Calculates and Prints Sales Summary
    double minSale = sales[0].sale, maxSale = sales[0].sale, totalSales = 0.0, averageSale;
    for (int i = 0; i < NUM_MONTHS; ++i) {
        if (sales[i].sale < minSale) minSale = sales[i].sale;
        if (sales[i].sale > maxSale) maxSale = sales[i].sale;
        totalSales += sales[i].sale;
    }
    averageSale = totalSales / NUM_MONTHS;
    printf("\nSales Summary:\n");
    printf("Minimum Sale: $%.2f\n", minSale);
    printf("Maximum Sale: $%.2f\n", maxSale);
    printf("Average Sale: $%.2f\n", averageSale);

    // Calculates and Prints Six-Month Moving Averages
    printf("\nSix-Month Moving Averages:\n");
    for (int i = 0; i <= NUM_MONTHS - 6; ++i) {
        double sum = 0;
        for (int j = i; j < i + 6; ++j) {
            sum += sales[j].sale;
        }
        printf("%-9s - %-9s: $%7.2f\n", sales[i].month, sales[i+5].month, sum / 6);
    }

    // Sorts Sales from Highest to Lowest
    for (int i = 0; i < NUM_MONTHS - 1; ++i) {
        for (int j = i + 1; j < NUM_MONTHS; ++j) {
            if (sales[i].sale < sales[j].sale) {
                SaleData temp = sales[i];
                sales[i] = sales[j];
                sales[j] = temp;
            }
        }
    }

    // Prints Sorted Sales
    printf("\nSales Sorted from Highest to Lowest:\n");
    for (int i = 0; i < NUM_MONTHS; ++i) {
        printf("%-9s: $%.2f\n", sales[i].month, sales[i].sale);
    }

    return 0;
}