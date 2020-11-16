#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Matrix{
    float **mat;
    int rows;
    int cols;
    
};

// 1. Parse input string and store row/col values in Matrix Struct
// 2. Dynamically allocate memory of size rows x cols and initialize array
// 3. Store pointer to array pointer in Matrix struct
void initMatrix(struct Matrix * mat, char input[], float *array[])
{
    char * token = strtok(input, "x");
    int row_col[2], count=0;
    
    // refactor atoi to use native method
    while(token != NULL)
    {
        row_col[count] = atoi(token);
        token = strtok(NULL, "x");
        count++;
    }
    
    mat->rows = row_col[0];
    mat->cols = row_col[1];
    
    array = malloc(sizeof(float*) * mat->rows);
    
    for(int i =0; i < mat->rows; i++)
        array[i] = malloc(sizeof(float) * mat->cols);
    
    mat->mat = array;
     
}

// Print out all values of matrix sequentially
void printMatrix(struct Matrix * mat)
{
    for(int i=0; i < mat->rows; i++){
        for(int j=0; j < mat->cols; j++){
            printf("%.3f\t", mat->mat[i][j]);
        }
    puts("");
    }
}

// Take user input to populate matrix elements
void populateMatrixElements(struct Matrix * mat)
{
    int elements = mat->rows*mat->cols, count =1;
    printf("Please enter %d elements: \n", elements);
    for(int i=0; i < mat->rows; i++){
        for(int j=0; j < mat->cols; j++){
            printf("%d:", count);
            scanf("%f", &mat->mat[i][j]);
            count++;
        }
    }
}

// Dot product of two matrices
void multiplyMatrices(struct Matrix mat_prod, struct Matrix mat1, struct Matrix mat2)
{
    for(int i=0; i < mat1.rows; i++){
        for(int j=0; j < mat2.cols; j++){
            for(int k=0; k < mat1.cols; k++){
                mat_prod.mat[i][j] += mat1.mat[i][k] * mat2.mat[k][j];
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    char s1[10], s2[10], result[10];
    struct Matrix mat1, mat2, mat_prod;
    float **array1 = NULL, **array2 = NULL, **prod_array = NULL;
    
    // read in two numbers in format NxM and parse N and M
    // struct.rows = N srtuct.cols = M
    printf("Enter the dimensions of the 1st matrix (e.g NxM): ");
    scanf("%s",s1);
    initMatrix(&mat1, s1, array1);
    
    printf("Enter the dimensions of the 2nd matrix (e.g NxM): ");
    scanf("%s",s2);
    initMatrix(&mat2, s2, array2);
    
    // error if incompatible matrices
    if (mat1.cols != mat2.rows){
        printf("\nError multiplying Matrices incomatible rows and columns.\n");
        exit(1);
    }
    
    // populate matrix with integers
    populateMatrixElements(&mat1);
    populateMatrixElements(&mat2);
    
    // initialize input string for resultant matrix and initalize memory
    snprintf(result, sizeof(result), "%dx%d", mat1.rows, mat2.cols);
    initMatrix(&mat_prod, result, prod_array);
    
    multiplyMatrices(mat_prod, mat1, mat2);
    
    printMatrix(&mat_prod);

    // free memory define function and pass all three matrices
    free(mat1.mat); free(mat2.mat); free(mat_prod.mat);
    
}
