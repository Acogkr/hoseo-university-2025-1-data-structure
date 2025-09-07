#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define INPUT_NODES 11
#define HIDDEN_NODES 8
#define OUTPUT_NODES 1

#define MAX_SAMPLES 5000  // 충분히 크게 잡음
#define TRAIN_RATIO 0.8

#define LEARNING_RATE 0.01
#define EPOCHS 5000

typedef struct {
    double inputs[INPUT_NODES];
    double label;
} Sample;

Sample dataset[MAX_SAMPLES];
int sample_count = 0;
int train_count = 0, test_count = 0;

double hidden_weights[HIDDEN_NODES][INPUT_NODES];
double hidden_bias[HIDDEN_NODES];
double output_weights[OUTPUT_NODES][HIDDEN_NODES];
double output_bias[OUTPUT_NODES];

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

int load_data(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("파일 열기 실패: %s\n", filename);
        return 0;
    }

    char line[512];
    fgets(line, sizeof(line), fp);

    sample_count = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *token;
        token = strtok(line, ";");

        for (int i = 0; i < INPUT_NODES; i++) {
            if (token == NULL) break;
            dataset[sample_count].inputs[i] = atof(token);
            token = strtok(NULL, ";");
        }

        if (token == NULL) break;
        dataset[sample_count].label = atof(token);

        sample_count++;
        if (sample_count >= MAX_SAMPLES) break;
    }

    fclose(fp);
    return 1;
}

void normalize_data() {
    double min_val[INPUT_NODES], max_val[INPUT_NODES];
    for (int i = 0; i < INPUT_NODES; i++) {
        min_val[i] = dataset[0].inputs[i];
        max_val[i] = dataset[0].inputs[i];
    }
    for (int i = 1; i < sample_count; i++) {
        for (int j = 0; j < INPUT_NODES; j++) {
            if (dataset[i].inputs[j] < min_val[j]) min_val[j] = dataset[i].inputs[j];
            if (dataset[i].inputs[j] > max_val[j]) max_val[j] = dataset[i].inputs[j];
        }
    }

    for (int i = 0; i < sample_count; i++) {
        for (int j = 0; j < INPUT_NODES; j++) {
            if (max_val[j] - min_val[j] != 0)
                dataset[i].inputs[j] = (dataset[i].inputs[j] - min_val[j]) / (max_val[j] - min_val[j]);
            else
                dataset[i].inputs[j] = 0;
        }
        dataset[i].label = (dataset[i].label - 3.0) / (10.0 - 3.0);
    }
}

void initialize_weights() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < INPUT_NODES; j++) {
            hidden_weights[i][j] = ((double)rand() / RAND_MAX) * 0.2 - 0.1; // -0.1 ~ 0.1
        }
        hidden_bias[i] = ((double)rand() / RAND_MAX) * 0.2 - 0.1;
    }
    for (int i = 0; i < OUTPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            output_weights[i][j] = ((double)rand() / RAND_MAX) * 0.2 - 0.1;
        }
        output_bias[i] = ((double)rand() / RAND_MAX) * 0.2 - 0.1;
    }
}

void forward(double inputs[], double hidden_out[], double *output) {
    for (int i = 0; i < HIDDEN_NODES; i++) {
        double sum = hidden_bias[i];
        for (int j = 0; j < INPUT_NODES; j++) {
            sum += hidden_weights[i][j] * inputs[j];
        }
        hidden_out[i] = sigmoid(sum);
    }

    for (int i = 0; i < OUTPUT_NODES; i++) {
        double sum = output_bias[i];
        for (int j = 0; j < HIDDEN_NODES; j++) {
            sum += output_weights[i][j] * hidden_out[j];
        }
        *output = sigmoid(sum);
    }
}

void backward(double inputs[], double hidden_out[], double output, double label) {
    double output_error = (label - output) * sigmoid_derivative(output);

    double hidden_errors[HIDDEN_NODES];
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden_errors[i] = output_error * output_weights[0][i] * sigmoid_derivative(hidden_out[i]);
    }

    for (int i = 0; i < OUTPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            output_weights[i][j] += LEARNING_RATE * output_error * hidden_out[j];
        }
        output_bias[i] += LEARNING_RATE * output_error;
    }

    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < INPUT_NODES; j++) {
            hidden_weights[i][j] += LEARNING_RATE * hidden_errors[i] * inputs[j];
        }
        hidden_bias[i] += LEARNING_RATE * hidden_errors[i];
    }
}

void train() {
    int epochs = EPOCHS;
    double hidden_out[HIDDEN_NODES];
    for (int e = 0; e < epochs; e++) {
        double total_loss = 0;
        for (int i = 0; i < train_count; i++) {
            double output;
            forward(dataset[i].inputs, hidden_out, &output);
            backward(dataset[i].inputs, hidden_out, output, dataset[i].label);
            double loss = pow(dataset[i].label - output, 2);
            total_loss += loss;
        }
        if (e % 500 == 0) {
            printf("Epoch %d, MSE: %.6f\n", e, total_loss / train_count);
        }
    }
}

void test() {
    double hidden_out[HIDDEN_NODES];
    double total_loss = 0;
    printf("\n테스트 결과 (예측값 vs 실제값):\n");
    for (int i = train_count; i < sample_count; i++) {
        double output;
        forward(dataset[i].inputs, hidden_out, &output);
        double loss = pow(dataset[i].label - output, 2);
        total_loss += loss;
        printf("예측: %.3f, 실제: %.3f\n", output * 7 + 3, dataset[i].label * 7 + 3);  // 정규화 역변환
    }
    printf("테스트 MSE: %.6f\n", total_loss / test_count);
}
ㅅ
int main() {
    if (!load_data("/Users/acog/Documents/hoseo-university/2025-1학기/2025-1학기-자료구조/winequality-white.csv")) {
        return 1;
    }
    normalize_data();

    train_count = (int)(sample_count * TRAIN_RATIO);
    test_count = sample_count - train_count;

    initialize_weights();

    train();
    test();

    return 0;
}