#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Matrix {
    float **mat;
    int rows;
    int cols;
};

// return max of two integers
int getMax(int num1, int num2){
    return (num1 > num2) ? num1 : num2;
}

// return max of two integers
int getMin(int num1, int num2){
    return (num1 < num2) ? num1 : num2;
}

void printSign(struct Matrix mat, int pos){
    if(mat.mat[1][pos] > 0)
        printf("+ ");
    else if(mat.mat[1][pos] < 0)
        printf("- ");
}

// displays the polynomial in format entered by user
void showPolynomial(struct Matrix mat){
    
    printf("\n");
    
    for(int i = 0; i < mat.cols; i++){
        
        if(i == 0){
            printf("%.0fx ", mat.mat[1][i]);
        }
        else if(mat.mat[1][i] == 0)
            continue;
        else{
            printSign(mat, i);
            printf("%dx^%.0f ", abs((int)mat.mat[1][i]), mat.mat[0][i]);
        }
    }
    printf("\n\n");
}

void addPolynomials(struct Matrix mat1, struct Matrix mat2, struct Matrix *result){
    int i = 0;
    for(; i < getMin(mat1.cols, mat2.cols); i++)
    {
        result->mat[1][i] = mat1.mat[1][i] + mat2.mat[1][i];
    }
    for(; i < getMax(mat1.cols, mat2.cols); i++)
    {
        if(mat1.cols > mat2.cols)
            result->mat[1][i] = mat1.mat[1][i];
        else if(mat2.cols > mat1.cols)
            result->mat[1][i] = mat2.mat[1][i];
    }
}

void subtractPolynomials(struct Matrix mat1, struct Matrix mat2, struct Matrix *result){
    // loop through and subtract coefficients arr[1][i]
    int i = 0;
    for(; i < getMin(mat1.cols, mat2.cols); i++)
    {
        result->mat[1][i] = mat1.mat[1][i] - mat2.mat[1][i];
    }
    for(; i < getMax(mat1.cols, mat2.cols); i++)
    {
        if(mat1.cols > mat2.cols)
            result->mat[1][i] = mat1.mat[1][i];
        else if(mat2.cols > mat1.cols)
            result->mat[1][i] = mat2.mat[1][i];
    }
}

// returns the coefficient of a token string
int getCoefficient(char input[])
{
    int coefficient = 0, x_pos = 0;
    
    for(int i=0; i < strlen(input); i++)
    {
        if(input[i] == 'x')
            x_pos = i;
    }
    
    int multiplier = 1;
    for(int j= 0; j < x_pos; j++)
    {
        coefficient += multiplier * atoi(&input[j]);
        multiplier *= 10;
    }
    
    return coefficient;
}

// returns the exponent value of a token string
int getExponent(char input[])
{
    int exponent = 0, x_pos = 0, carat_pos = 0;
    
    for(int i=0; i < strlen(input); i++)
    {
        if(input[i] == 'x')
            x_pos = i;
        else if(input[i] == '^')
            carat_pos = i;
    }
    
    if(carat_pos == 0)
        return 0;
    
    int multiplier = 1;
    for(int j= x_pos + 2; j < strlen(input); j++)
    {
        exponent += multiplier * atoi(&input[j]);
        multiplier *= 10;
    }
    
    return exponent;
}


// parse input "polynomial" string and store values in the Matrix
void populateMatrix(struct Matrix * matrix, char input[]){
    
    int signage = 1, exponent = 0, coefficient = 0;
    
    char copy[strlen(input)];
    strcpy(copy, input);
    char * whitespace_token = strtok(copy, " ");
    
    // populate matrix->mat 2d array
    // 1. tokenize the input
    // 2. get exponent, index = exponent
    // 3. get coefficient store in
    
    while(whitespace_token != NULL){
        
        if (*whitespace_token != '+' && *whitespace_token != '-')
        {
            coefficient = getCoefficient(whitespace_token);
            exponent = getExponent(whitespace_token);

            matrix->mat[1][exponent] = signage*coefficient;
        }

        if(*whitespace_token == '+')
            signage = 1;
        else if (*whitespace_token == '-')
            signage = -1;
        
        whitespace_token = strtok(NULL, " ");
    }
    
}

// return number of elements should be value of max exponent
int getColumns(char input[]){
    char copy[strlen(input)];
    strcpy(copy, input);
    
    // tokenize by whitespace
    char * whitespace_token = strtok(copy, " ");
    int max = 0;

    while(whitespace_token != NULL){
        if (*whitespace_token != '+' && *whitespace_token != '-')
            max = getMax(max, getExponent(whitespace_token));
        whitespace_token = strtok(NULL, " ");
    }
    return max;
}

// 1. Parse input string and store col values in Matrix Struct
// 2. Dynamically allocate memory of size rows x cols and initialize array
// 3. Store pointer to array pointer in Matrix struct
void initMatrix(struct Matrix * mat, float *array[], int columns)
{
    mat->cols = columns;
    mat->rows = 2;
    
    array = malloc(sizeof(float*) * mat->rows);
    
    for(int i =0; i < mat->rows; i++)
        array[i] = malloc(sizeof(float) * mat->cols);
    
    mat->mat = array;
    
    for(int i = 0; i < mat->cols; i++)
    {
        mat->mat[0][i] = i;
    }
     
}

// frees memory allocated for all matrices
void cleanMemory(struct Matrix mat1, struct Matrix mat2, struct Matrix mat3){
    if(mat1.mat != NULL)
        free(mat1.mat);
    if(mat2.mat != NULL)
        free(mat2.mat);
    if(mat3.mat != NULL)
        free(mat3.mat);
}

int main(int argc, const char * argv[]) {
    
    // three matrices polynomial1 polynomial2 and result polynomial
    int menu_choice = 3;
    char input1[100], input2[100];
    struct Matrix mat1, mat2, result_mat;
    float **array1 = NULL, **array2 = NULL, **result_array = NULL;
    mat1.mat = array1; mat2.mat = array2; result_mat.mat = result_array;
    
    // recurring menu till user exits
    while (menu_choice != 4)
    {
        switch (menu_choice) {
            case 1:
                initMatrix(&result_mat, result_array, getMax(mat1.cols, mat2.cols));
                addPolynomials(mat1, mat2, &result_mat);
                showPolynomial(result_mat);
                free(result_mat.mat);
                break;
            case 2:
                initMatrix(&result_mat, result_array, getMax(mat1.cols, mat2.cols));
                subtractPolynomials(mat1, mat2, &result_mat);
                free(result_mat.mat);
                break;
            case 3:
                cleanMemory(mat1, mat2, result_mat);
                // TODO: refactor cleanup into another function, error handling for malformed input
                printf("Please enter a polynomial in the format 2x + 3x^2 - 4x^4: \n");
                fgets(input1, 100, stdin);
                initMatrix(&mat1, array1, getColumns(input1) + 1);
                populateMatrix(&mat1, input1);
                
                fflush(stdin);
                
                printf("Please enter a second polynomial in the format 2x + 3x^2 - 4x^4: \n");
                fgets(input2, 100, stdin);
                initMatrix(&mat2, array2, getColumns(input2) + 1);
                populateMatrix(&mat2,input2);
                
                break;
            case 4:
                cleanMemory(mat1, mat2, result_mat);
                break;
        }
        
        printf("Please enter choice (1 2 3 etc.)\n");
        printf("(1) Addition\n(2) Subtraction\n(3) Enter 2 new polynomials\n(4) Exit\n");
        scanf("%d", &menu_choice);
        fflush(stdin);
    }
    
    cleanMemory(mat1, mat2, result_mat);
    return 0;
}
