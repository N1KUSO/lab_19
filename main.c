#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct {
    char name[MAX_SIZE];
    double unit_price;
    double total_price;
    int quantity;
} Product;

typedef struct {
    char name[MAX_SIZE];
    int quantity;
} Order;

typedef struct Polynomial {
    int power;
    double coefficient;
} Polynomial;

typedef struct {
    char name[MAX_SIZE];
    int best_result;
} Athlete;

int calculate(int op1, char operator, int op2) {
    switch (operator) {
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

bool is_symmetric(const int *matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i * n + j] != matrix[j * n + i]) {
                return false;
            }
        }
    }
    return true;
}

void transpose(int *matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int temp = matrix[i * n + j];
            matrix[i * n + j] = matrix[j * n + i];
            matrix[j * n + i] = temp;
        }
    }
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

void task7() {
    FILE *input_file = fopen("../input.bin", "rb");
    FILE *output_file = fopen("../output.bin", "wb");

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    int count = file_size / sizeof(int);
    int *numbers = (int *)malloc(file_size);

    fread(numbers, sizeof(int), count, input_file);
    fclose(input_file);

    int *positive_numbers = (int *)malloc(file_size);
    int *negative_numbers = (int *)malloc(file_size);
    int pos_count = 0, neg_count = 0;

    for (int i = 0; i < count; ++i) {
        if (numbers[i] > 0) {
            positive_numbers[pos_count++] = numbers[i];
        } else {
            negative_numbers[neg_count++] = numbers[i];
        }
    }

    fwrite(positive_numbers, sizeof(int), pos_count, output_file);
    fwrite(negative_numbers, sizeof(int), neg_count, output_file);
    fclose(output_file);

    free(numbers);
    free(positive_numbers);
    free(negative_numbers);
}

void generate_input_output_task7() {
    FILE *input_file = fopen("../input.bin", "wb");
    FILE *excepted_file = fopen("../excepted.bin", "wb");

    int numbers[] = {1,2,-3,5,-9,8,12};
    fwrite(numbers, sizeof(int), 1, input_file);

    int exc_numbers[] = {-3,-9,1,2,5,8,12};
    fwrite(exc_numbers, sizeof(int), 1, excepted_file);

    fclose(input_file);
    fclose(input_file);
}

void task8() {
    FILE *input_file = fopen("../input.bin", "rb");
    FILE *output_file = fopen("../output.bin", "wb");

    int n = 3;

    int *matrix = (int *)malloc(n * n * sizeof(int));

    while (fread(matrix, sizeof(int), n * n, input_file) == n * n) {
        if (!is_symmetric(matrix, n)) {
            transpose(matrix, n);
        }
        fwrite(matrix, sizeof (int), n * n, output_file);
    }

    free(matrix);
    fclose(input_file);
    fclose(output_file);
}

void generate_input_output_task8() {
    FILE *input_file = fopen("../input.bin", "wb");
    FILE *excepted_file = fopen("../excepted.bin", "wb");

    int n = 3;

    int matrix1[3][3] = {
            {1, 2, 3},
            {2, 4, 5},
            {3, 5, 6}
    };

    int matrix2[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    fwrite(matrix1, sizeof(int), n * n, input_file);
    fwrite(matrix2, sizeof(int), n * n, input_file);

    int matrix1_processed[3][3] = {
            {1, 2, 3},
            {2, 4, 5},
            {3, 5, 6}
    };

    int matrix2_processed[3][3] = {
            {1, 4, 7},
            {2, 5, 8},
            {3, 6, 9}
    };

    fwrite(matrix1_processed, sizeof(int), n * n, excepted_file);
    fwrite(matrix2_processed, sizeof(int), n * n, excepted_file);

    fclose(input_file);
    fclose(excepted_file);
}

int compare_athletes(const void *a, const void *b) {
    Athlete *athleteA = (Athlete *)a;
    Athlete *athleteB = (Athlete *)b;
    return athleteB->best_result - athleteA->best_result;
}

void task9() {
    FILE *input_file = fopen("../input.bin", "rb");
    FILE *output_file = fopen("../output.bin", "wb");

    int n = 3;

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    int count_athletes = file_size / sizeof(Athlete);
    Athlete *athletes = (Athlete *) malloc(file_size);

    fread(athletes, sizeof(Athlete), count_athletes, input_file);
    qsort(athletes, count_athletes, sizeof(Athlete), compare_athletes);

    fwrite(athletes, sizeof(Athlete), n < count_athletes ? n : count_athletes, output_file);

    free(athletes);
    fclose(input_file);
    fclose(output_file);
}

void generate_input_output_task9() {
    FILE *input_file = fopen("../input.bin", "wb");
    FILE *excepted_file = fopen("../excepted.bin", "wb");

    Athlete athletes[] = {
            {"Andrey 1", 300},
            {"Test 2", 400},
            {"Kto-to 3", 250},
            {"Eshe 4", 350},
            {"Number 5", 450}
    };

    fwrite(athletes, sizeof(Athlete), sizeof(athletes) / sizeof(Athlete), input_file);

    Athlete athletes_best[] = {
            {"Number 5", 450},
            {"Test 2", 400},
            {"Eshe 4", 350}
    };

    fwrite(athletes_best, sizeof(Athlete), sizeof(athletes) / sizeof(Athlete), excepted_file);

    fclose(input_file);
    fclose(excepted_file);
}

void task10() {
    FILE *f = fopen("../input.bin", "rb");
    FILE *g = fopen("../input_g.bin", "rb");

    fseek(g, 0, SEEK_END);
    long g_size = ftell(g);
    fseek(g, 0, SEEK_SET);
    int num_orders = g_size / sizeof(Order);
    Order *orders = (Order *)malloc(g_size);

    fread(orders, sizeof(Order), num_orders, g);
    fseek(f, 0, SEEK_END);

    long f_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    int num_products = f_size / sizeof(Product);
    Product *products = (Product *)malloc(f_size);

    fread(products, sizeof(Product), num_products, f);

    for (int i = 0; i < num_orders; i++) {
        for (int j = 0; j < num_products; j++) {
            if (strcmp(orders[i].name, products[j].name) == 0) {
                products[j].quantity -= orders[i].quantity;
                if (products[j].quantity < 0) {
                    products[j].quantity = 0;
                }
                products[j].total_price = products[j].quantity * products[j].unit_price;
                break;
            }
        }
    }

    FILE *output = fopen("../output.bin", "wb");

    for (int i = 0; i < num_products; i++) {
        if (products[i].quantity > 0) {
            fwrite(&products[i], sizeof(Product), 1, output);
        }
    }

    free(products);
    free(orders);

    fclose(output);
    fclose(f);
    fclose(g);
}

void generate_input_output_task10() {
    FILE *input_file = fopen("../input.bin", "wb");
    FILE *input_g_file = fopen("../input_g.bin", "wb");
    FILE *excepted_file = fopen("../excepted.bin", "wb");

    Product products[] = {
            {"Laptop", 1000.0, 5000.0, 5},
            {"Phone", 500.0, 2500.0, 5},
            {"Tablet", 300.0, 900.0, 3}
    };

    Order orders[] = {
            {"Laptop", 2},
            {"Phone", 1},
            {"Tablet", 4} // Обратите внимание, что заказываем больше, чем есть на складе
    };

    Product updated_products[] = {
            {"Laptop", 1000.0, 3000.0, 3},
            {"Phone", 500.0, 2000.0, 4}
    };

    fwrite(products, sizeof(Product), sizeof(products) / sizeof(Product), input_file);
    fwrite(orders, sizeof(Order), sizeof(orders) / sizeof(Order), input_g_file);
    fwrite(updated_products, sizeof(Order), sizeof(orders) / sizeof(Order), excepted_file);
}


void test_task10() {
    generate_input_output_task10();
    task10();

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
        printf("Test failed! Task 10\n");
    }
}

void test_task9() {
    generate_input_output_task9();
    task9();

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
        printf("Test failed! Task 9\n");
    }
}

void test_task8() {
    generate_input_output_task8();
    task8();

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
        printf("Test failed! Task 8\n");
    }
}

void test_task7() {
    generate_input_output_task7();
    task7();

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
        printf("Test failed! Task 7\n");
    }
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
        printf("Test failed! Task 6\n");
    }
}


int main() {
    test_task6();
    test_task7();
    test_task8();
    test_task9();
    test_task10();

    return 0;
}
