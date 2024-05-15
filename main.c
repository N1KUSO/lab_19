#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct Polynomial {
    int power;
    double coefficient;
} Polynomial;

int calculate(int op1, char opetator, int op2) {
    switch (opetator) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
        default:
            printf("operator error");
    }
}

void get_longest_word(char *line, char* longest_word) {
    char word[MAX_SIZE];
    char max_word[MAX_SIZE];
    int max_length = 0;

    char *token = strtok(line, " ");
    while (token != NULL) {
        strcpy(word, token);

        if (strlen(word) > max_length) {
            max_length = strlen(word);
            strcpy(max_word, word);
        }

        token = strtok(NULL, " ");
    }

    strcpy(longest_word, max_word);
}

int isSymmetric(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

void transpose(int **matrix, int n) {
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

void task8() {
    FILE *input_file = fopen("../input.bin", "rb");
    FILE *temp_file = fopen("../temp.bin", "wb");

    int n = fread(&n, sizeof(int), 1, input_file);

    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    while (fread(matrix[0], sizeof(int), n * n, input_file) != 0) {
        if (!isSymmetric(matrix, n)) {
            transpose(matrix, n);
        }
        fwrite(matrix[0], sizeof(int), n * n, temp_file);
    }

    fclose(input_file);
    fclose(temp_file);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    remove("../input.bin");
    rename("../temp.bin", "../input.bin");
}

void task7() {
    FILE *input_file = fopen("../input.bin", "rb");
    FILE *temp_file = fopen("../temp.bin", "wb");

    int number;
    while (fread(&number, sizeof(int), 1, input_file) != 0) {
        if (number >= 0) {
            fwrite(&number, sizeof(int), 1, temp_file);
        }
    }

    rewind(input_file);

    while (fread(&number, sizeof(int), 1, input_file) != 0) {
        if (number < 0) {
            fwrite(&number, sizeof(int), 1, temp_file);
        }
    }

    fclose(input_file);
    fclose(temp_file);

    remove("../input.bin");
    rename("../temp.bin", "../input.bin");
}

void task6() {
    FILE *input_file = fopen("../input.bin", "rb");
    FILE *output_file = fopen("../output.bin", "wb");
    
    double x = 2.0;

    while (!feof(input_file)) {
        int term_count;
        if (fread(&term_count, sizeof(int), 1, input_file) != 1)
            break;

        Polynomial *polys = (Polynomial *)malloc(term_count * sizeof(Polynomial));
        fread(polys, sizeof(Polynomial), term_count, input_file);

        double sum = 0.0;
        for (int i = 0; i < term_count; ++i) {
            sum += polys[i].coefficient * pow(x, polys[i].power);
        }

        if (sum != 0) {
            fwrite(&term_count, sizeof(int), 1, output_file);
            fwrite(polys, sizeof(Polynomial), term_count, output_file);
        }

        free(polys);
    }

    fclose(input_file);
    fclose(output_file);
}

void generate_input_output_task6() {
    FILE *input_file = fopen("../input.bin", "wb");
    FILE *excepted_file = fopen("../excepted.bin", "wb");

    int power = 3;
    Polynomial poly1[] = {{2, 3}, {1, -12}, {0, 12}};
    fwrite(&power, sizeof(int), 1, input_file);
    fwrite(poly1, sizeof(Polynomial), power, input_file);

    power = 4;
    Polynomial poly2[] = {{3, 14}, {2, -24}, {1, 48}, {0, -32}};
    fwrite(&power, sizeof(int), 1, input_file);
    fwrite(poly2, sizeof(Polynomial), power, input_file);

    fwrite(&power, sizeof(int), 1, excepted_file);
    fwrite(poly2, sizeof(Polynomial), power, excepted_file);

    fclose(input_file);
    fclose(input_file);
}

void task5() {
    FILE *input_file = fopen("../input.txt", "r");
    FILE *temp_file = fopen("../temp.txt", "w");

    char line[MAX_SIZE];
    char longest_word[MAX_SIZE];

    while(fgets(line, sizeof(line), input_file) != NULL) {
        get_longest_word(line, longest_word);
        fprintf(temp_file, "%s", longest_word);
    }


    fclose(input_file);
    fclose(temp_file);

    remove("../input.txt");
    rename("../temp.txt", "../input.txt");
}

void task4() {
    FILE *input_file = fopen("../input.txt", "r");
    FILE *temp_file = fopen("../temp.txt", "w");

    const char *sequence = "abc";
    char word[MAX_SIZE];

    while(fscanf(input_file, "%s", word) != EOF) {
        if(strstr(word, sequence) != NULL) {
            fprintf(temp_file, "%s\n", word);
        }
    }

    fclose(input_file);
    fclose(temp_file);

    remove("../input.txt");
    rename("../temp.txt", "../input.txt");
}

void task3() {
    FILE *input_file = fopen("../input.txt", "r+");

    int op1, op2;
    char operator;
    fscanf(input_file, "%d %c %d", &op1, &operator, &op2);

    int result = calculate(op1, operator, op2);

    if (fscanf(input_file, " %c %d", &operator, &op2) == 2) {
        result = calculate(result, operator, op2);
    }

    fseek(input_file, 0, SEEK_END);
    fprintf(input_file, " = %d\n", result);

    fclose(input_file);
}

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

void print_polynomials(const char* filename) {
    FILE* file = fopen(filename, "rb");

    int num_terms;
    while (fread(&num_terms, sizeof(int), 1, file) == 1) {
        Polynomial *poly = (Polynomial*)malloc(num_terms * sizeof(Polynomial));
        fread(poly, sizeof(Polynomial), num_terms, file);

        for (int i = 0; i < num_terms; ++i) {
            printf("%+.2fx^%d ", poly[i].coefficient, poly[i].power);
        }
        printf("\n");

        free(poly);
    }

    fclose(file);
}


void test_task6() {
    generate_input_output_task6();
    task6();

    FILE *output_file = fopen("../output.bin", "rb");
    FILE *excepted_file = fopen("../excepted.bin", "rb");

    int num1, num2;
    int error = 0;
    while (fread(&num1, sizeof(int), 1, output_file) == 1 && fread(&num2, sizeof(int), 1, excepted_file) == 1) {
        if (num1 != num2) {
            error = 1;
            break;
        }
    }

    fclose(output_file);
    fclose(excepted_file);

    if (error) {
        printf("Test failed!\n");
    }
}

int main() {
    test_task6();

    return 0;
}
