#include <stdio.h>

#define MAX_SIZE 100

void task2() {
    FILE *input_file = fopen("../input.txt", "r");
    FILE *temp_file = fopen("../temp.txt", "w");

    float num;
    while(fscanf(input_file, "%f", &num) == 1) {
        fprintf(temp_file, "%.2f ", num);
    }

    fclose(input_file);
    fclose(temp_file);

    remove("../input.txt");
    rename("../temp.txt", "../input.txt");
}

void task1() {
    FILE *input_file = fopen("../input.txt", "r");
    FILE *temp_file = fopen("../temp.txt", "w");

    int n;
    while (fscanf(input_file, "%d", &n) == 1) {
        int matrix[MAX_SIZE][MAX_SIZE];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fscanf(input_file, "%d", &matrix[i][j]);
            }
        }

        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                fprintf(temp_file, "%d ", matrix[i][j]);
            }
            fprintf(temp_file, "\n");
        }
    }

    fclose(input_file);
    fclose(temp_file);

    remove("../input.txt");
    rename("../temp.txt", "../input.txt");
}

int main() {
    task2();

    return 0;
}
