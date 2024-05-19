#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numTerms;
    int numDocuments;
    int **termDocMatrix;
} TermDocumentMatrix;

TermDocumentMatrix createTermDocumentMatrix(int num_terms, int num_documents) {
    TermDocumentMatrix tdm;
    tdm.numTerms = num_terms;
    tdm.numDocuments = num_documents;

    tdm.termDocMatrix = (int **)malloc(num_terms * sizeof(int *));
    for (int i = 0; i < num_terms; i++) {
        tdm.termDocMatrix[i] = (int *)calloc(num_documents, sizeof(int));
    }

    return tdm;
}

void updateTermFrequency(TermDocumentMatrix *tdm, int term_index, int document_index, int frequency) {
    if (term_index >= 0 && term_index < tdm->numTerms && document_index >= 0 && document_index < tdm->numDocuments) {
        tdm->termDocMatrix[term_index][document_index] = frequency;
    }
}

int getTermFrequency(TermDocumentMatrix *tdm, int term_index, int document_index) {
    if (term_index >= 0 && term_index < tdm->numTerms && document_index >= 0 && document_index < tdm->numDocuments) {
        return tdm->termDocMatrix[term_index][document_index];
    } else {
        return 0;
    }
}

int getDocumentFrequency(TermDocumentMatrix *tdm, int term_index) {
    if (term_index >= 0 && term_index < tdm->numTerms) {
        int count = 0;
        for (int i = 0; i < tdm->numDocuments; i++) {
            if (tdm->termDocMatrix[term_index][i] > 0) {
                count++;
            }
        }
        return count;
    } else {
        return 0;
    }
}

int getTotalTermsInDocument(TermDocumentMatrix *tdm, int document_index) {
    if (document_index >= 0 && document_index < tdm->numDocuments) {
        int count = 0;
        for (int i = 0; i < tdm->numTerms; i++) {
            count += tdm->termDocMatrix[i][document_index];
        }
        return count;
    } else {
        return 0;
    }
}

typedef struct {
    int numRows;
    int numCols;
    int **data;
} SparseMatrix;

SparseMatrix toSparseMatrix(TermDocumentMatrix *tdm) {
    SparseMatrix sparseMatrix;
    int a = 0;
    for(int i = 0; i<tdm->numTerms; i++){
        int b = getDocumentFrequency(tdm, i);
        a = a + b;
        b = 0;
    }
    sparseMatrix.numRows = a;
    sparseMatrix.numCols = 3;
    
    sparseMatrix.data = (int **)malloc(a * sizeof(int *));
    for (int i = 0; i < a; i++) {
        sparseMatrix.data[i] = (int *)malloc(3 * sizeof(int));
    }

    printf("The sparse matrix is \n");
    printf("D T V\n");
    for(int i = 0, m = 0; i<tdm->numTerms && m<a; i++){
        for(int j = 0; j<tdm->numDocuments;  j++){
            if(tdm->termDocMatrix[i][j] != 0){   
                sparseMatrix.data[m][0] = j;
                sparseMatrix.data[m][1] = i;
                sparseMatrix.data[m][2] = tdm->termDocMatrix[i][j];
                m++;
            }
        }
    } 
    for(int i = 0; i<a; i++){
        for(int j = 0; j<3; j++){
            printf("%d ", sparseMatrix.data[i][j]);
        }
        printf("\n");
    }
    return sparseMatrix;
}

int print(TermDocumentMatrix *tdm){
     for(int i = 0; i<tdm->numTerms; i++){
        for(int j = 0; j<tdm->numDocuments; j++){
            printf("%d  ", tdm->termDocMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
int main() {
    TermDocumentMatrix tdm = createTermDocumentMatrix(5, 10);
    print(&tdm);
    printf("\n");
    updateTermFrequency(&tdm, 0, 0, 1);
    updateTermFrequency(&tdm, 1, 0, 2);
    updateTermFrequency(&tdm, 2, 1, 3);
    print(&tdm);

    printf("Term Frequency for term 0 in document 0: %d\n", getTermFrequency(&tdm, 0, 0));
    printf("Document Frequency for term 1: %d\n", getDocumentFrequency(&tdm, 1));
    printf("Total Terms in document 0: %d\n", getTotalTermsInDocument(&tdm, 0));

    toSparseMatrix(&tdm);
    printf("Sparse Matrix Representation:\n");

    return 0;
}
