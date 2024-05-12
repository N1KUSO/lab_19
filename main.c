#include <stdio.h>
#include <string.h>
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

int isRoot(Polynomial poly, float x) {
    float result = 0;
    float power_of_x = 1;
    for (int i = 0; i <= poly.power; i++) {
        result += poly.coefficient * power_of_x;
        power_of_x *= x;
    }
    return result == 0;
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
    FILE *temp_file = fopen("../temp.bin", "wb");

    Polynomial poly;
    float x = 2; // input x

    while (fread(&poly, sizeof(Polynomial), 1, input_file)) {
        if (!isRoot(poly, x)) {
            fwrite(&poly, sizeof(Polynomial), 1, temp_file);
        }
    }

    fclose(input_file);
    fclose(temp_file);

    remove("../input.bin");
    rename("../temp.bin", "../input.bin");
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

int main() {
    task7();

    return 0;
}
