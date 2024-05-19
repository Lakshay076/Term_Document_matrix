#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numRows;
    int numCols;
    int **data;
} SparseArray;

SparseArray createSparseArray(int rows, int cols) {
    SparseArray sparseArray;
    sparseArray.numRows = rows;
    sparseArray.numCols = cols;

    sparseArray.data = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        sparseArray.data[i] = (int *)calloc(cols, sizeof(int));
    }

    return sparseArray;
}

void setValue(SparseArray *sparseArray, int row, int col, int value) {
    if (row >= 0 && row < sparseArray->numRows && col >= 0 && col < sparseArray->numCols) {
        sparseArray->data[row][col] = value;
    }
}

int getValue(SparseArray *sparseArray, int row, int col) {
    if (row >= 0 && row < sparseArray->numRows && col >= 0 && col < sparseArray->numCols) {
        return sparseArray->data[row][col];
    } else {
        return 0;
    }
}

void addValue(SparseArray *sparseArray, int row, int col, int value) {
    if (row >= 0 && row < sparseArray->numRows && col >= 0 && col < sparseArray->numCols) {
        sparseArray->data[row][col] += value;
    }
}

void removeValue(SparseArray *sparseArray, int row, int col) {
    if (row >= 0 && row < sparseArray->numRows && col >= 0 && col < sparseArray->numCols) {
        sparseArray->data[row][col] = 0;
    }
}

int getNumRows(SparseArray *sparseArray) {
    return sparseArray->numRows;
}

int getNumCols(SparseArray *sparseArray) {
    return sparseArray->numCols;
}

SparseArray transpose(SparseArray *sparseArray) {
    SparseArray transposed = createSparseArray(sparseArray->numCols, sparseArray->numRows);
    for (int i = 0; i < sparseArray->numRows; ++i) {
        for (int j = 0; j < sparseArray->numCols; ++j) {
            setValue(&transposed, j, i, getValue(sparseArray, i, j));
        }
    }
    return transposed;
}

void multiplyScalar(SparseArray *sparseArray, int factor) {
    for (int i = 0; i < sparseArray->numRows; ++i) {
        for (int j = 0; j < sparseArray->numCols; ++j) {
            setValue(sparseArray, i, j, getValue(sparseArray, i, j) * factor);
        }
    }
}

void add(SparseArray *sparseArray1, SparseArray *sparseArray2) {
    if (sparseArray1->numRows == sparseArray2->numRows && sparseArray1->numCols == sparseArray2->numCols) {
        for (int i = 0; i < sparseArray1->numRows; ++i) {
            for (int j = 0; j < sparseArray1->numCols; ++j) {
                addValue(sparseArray1, i, j, getValue(sparseArray2, i, j));
            }
        }
    }
}

void multiply(SparseArray *sparseArray1, SparseArray *sparseArray2) {
    if (sparseArray1->numCols == sparseArray2->numRows) {
        SparseArray result = createSparseArray(sparseArray1->numRows, sparseArray2->numCols);
        for (int i = 0; i < sparseArray1->numRows; ++i) {
            for (int j = 0; j < sparseArray2->numCols; ++j) {
                int sum = 0;
                for (int k = 0; k < sparseArray1->numCols; ++k) {
                    sum += getValue(sparseArray1, i, k) * getValue(sparseArray2, k, j);
                }
                setValue(&result, i, j, sum);
            }
        }
        *sparseArray1 = result;
    }
}

int **toDenseArray(SparseArray *sparseArray) {
    int **denseArray = (int **)malloc(sparseArray->numRows * sizeof(int *));
    for (int i = 0; i < sparseArray->numRows; ++i) {
        denseArray[i] = (int *)malloc(sparseArray->numCols * sizeof(int));
        for (int j = 0; j < sparseArray->numCols; ++j) {
            denseArray[i][j] = getValue(sparseArray, i, j);
        }
    }
    return denseArray;
}

void freeSparseArray(SparseArray *sparseArray) {
    for (int i = 0; i < sparseArray->numRows; ++i) {
        free(sparseArray->data[i]);
    }
    free(sparseArray->data);
    sparseArray->numRows = 0;
    sparseArray->numCols = 0;
}

int main() {
    SparseArray sparseArray = createSparseArray(3, 3);
    setValue(&sparseArray, 0, 0, 1);
    setValue(&sparseArray, 1, 1, 2);
    setValue(&sparseArray, 2, 2, 3);

    printf("Value at (0, 0): %d\n", getValue(&sparseArray, 0, 0));
    printf("Value at (1, 1): %d\n", getValue(&sparseArray, 1, 1));
    printf("Value at (2, 2): %d\n", getValue(&sparseArray, 2, 2));

    addValue(&sparseArray, 0, 0, 1);
    printf("New value at (0, 0) after adding: %d\n", getValue(&sparseArray, 0, 0));

    removeValue(&sparseArray, 1, 1);
    printf("Value at (1, 1) after removal: %d\n", getValue(&sparseArray, 1, 1));

    printf("Number of rows: %d\n", getNumRows(&sparseArray));
    printf("Number of columns: %d\n", getNumCols(&sparseArray));

    SparseArray transposed = transpose(&sparseArray);
    printf("Transpose of the sparse array:\n");
    for (int i = 0; i < transposed.numRows; ++i) {
        for (int j = 0; j < transposed.numCols; ++j) {
            printf("%d ", getValue(&transposed, i, j));
        }
        printf("\n");
    }

    multiplyScalar(&sparseArray, 2);
    printf("Sparse array after multiplying by scalar:\n");
    for (int i = 0; i < sparseArray.numRows; ++i) {
        for (int j = 0; j <         sparseArray.numCols; ++j) {
            printf("%d ", getValue(&sparseArray, i, j));
        }
        printf("\n");
    }

    SparseArray sparseArray2 = createSparseArray(3, 3);
    setValue(&sparseArray2, 0, 0, 1);
    setValue(&sparseArray2, 1, 1, 2);
    setValue(&sparseArray2, 2, 2, 3);

    add(&sparseArray, &sparseArray2);
    printf("Sparse array after adding another sparse array:\n");
    for (int i = 0; i < sparseArray.numRows; ++i) {
        for (int j = 0; j < sparseArray.numCols; ++j) {
            printf("%d ", getValue(&sparseArray, i, j));
        }
        printf("\n");
    }

    multiply(&sparseArray, &sparseArray2);
    printf("Sparse array after multiplication with another sparse array:\n");
    for (int i = 0; i < sparseArray.numRows; ++i) {
        for (int j = 0; j < sparseArray.numCols; ++j) {
            printf("%d ", getValue(&sparseArray, i, j));
        }
        printf("\n");
    }

    int **denseArray = toDenseArray(&sparseArray);
    printf("Dense array representation:\n");
    for (int i = 0; i < sparseArray.numRows; ++i) {
        for (int j = 0; j < sparseArray.numCols; ++j) {
            printf("%d ", denseArray[i][j]);
        }
        printf("\n");
    }

    // Free memory
    freeSparseArray(&sparseArray);
    freeSparseArray(&sparseArray2);
    for (int i = 0; i < sparseArray.numRows; ++i) {
        free(denseArray[i]);
    }
    free(denseArray);

    return 0;
}

