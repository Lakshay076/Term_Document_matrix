#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class SparseArray {
private:
    unordered_map<int, unordered_map<int, int>> data;
    int numRows;
    int numCols;

public:
    SparseArray(int rows, int cols) : numRows(rows), numCols(cols) {}

    void setValue(int row, int col, int value) {
        data[row][col] = value;
    }

    int getValue(int row, int col) {
        if (data.find(row) != data.end() && data[row].find(col) != data[row].end()) {
            return data[row][col];
        } else {
            return 0;
        }
    }

    void addValue(int row, int col, int value) {
        data[row][col] += value;
    }

    void removeValue(int row, int col) {
        if (data.find(row) != data.end() && data[row].find(col) != data[row].end()) {
            data[row].erase(col);
        }
    }

    int getNumRows() {
        return numRows;
    }

    int getNumCols() {
        return numCols;
    }

    SparseArray transpose() {
        SparseArray transposed(numCols, numRows);
        for (auto it1 = data.begin(); it1 != data.end(); ++it1) {
            for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
                transposed.setValue(it2->first, it1->first, it2->second);
            }
        }
        return transposed;
    }

    void multiplyScalar(int factor) {
        for (auto it1 = data.begin(); it1 != data.end(); ++it1) {
            for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
                it2->second *= factor;
            }
        }
    }

    void add(const SparseArray& other) {
        for (auto it1 = other.data.begin(); it1 != other.data.end(); ++it1) {
            for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
                data[it1->first][it2->first] += it2->second;
            }
        }
    }

    void multiply(const SparseArray& other) {
        SparseArray result(numRows, other.numCols);
        for (auto it1 = data.begin(); it1 != data.end(); ++it1) {
            for (auto it2 = other.data.begin(); it2 != other.data.end(); ++it2) {
                int sum = 0;
                for (auto it3 = it1->second.begin(); it3 != it1->second.end(); ++it3) {
                    if (it2->second.find(it3->first) != it2->second.end()) {
                        sum += it3->second * it2->second.at(it3->first);
                    }
                }
                result.setValue(it1->first, it2->first, sum);
            }
        }
        data = result.data;
        numCols = result.numCols;
    }

    vector<vector<int>> toDenseArray() {
        vector<vector<int>> dense(numRows, vector<int>(numCols, 0));
        for (auto it1 = data.begin(); it1 != data.end(); ++it1) {
            for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
                dense[it1->first][it2->first] = it2->second;
            }
        }
        return dense;
    }
};

class TermDocumentMatrix {
private:
    vector<vector<int>> termDocMatrix;
    int numTerms;
    int numDocuments;

public:
    TermDocumentMatrix(int num_terms, int num_documents) : numTerms(num_terms), numDocuments(num_documents) {
        termDocMatrix.resize(numTerms, vector<int>(numDocuments, 0));
    }

    void updateTermFrequency(int term_index, int document_index, int frequency) {
        if (term_index >= 0 && term_index < numTerms && document_index >= 0 && document_index < numDocuments) {
            termDocMatrix[term_index][document_index] = frequency;
        }
    }

    int getTermFrequency(int term_index, int document_index) {
        if (term_index >= 0 && term_index < numTerms && document_index >= 0 && document_index < numDocuments) {
            return termDocMatrix[term_index][document_index];
        } else {
            return 0;
        }
    }

    int getDocumentFrequency(int term_index) {
        if (term_index >= 0 && term_index < numTerms) {
            int count = 0;
            for (int i = 0; i < numDocuments; ++i) {
                if (termDocMatrix[term_index][i] > 0) {
                    count++;
                }
            }
            return count;
        } else {
            return 0;
        }
    }

    int getTotalTermsInDocument(int document_index) {
        if (document_index >= 0 && document_index < numDocuments) {
            int count = 0;
            for (int i = 0; i < numTerms; ++i) {
                count += termDocMatrix[i][document_index];
            }
            return count;
        } else {
            return 0;
        }
    }

    SparseArray toSparseMatrix() {
        SparseArray sparse(numTerms, numDocuments);
        for (int i = 0; i < numTerms; ++i) {
            for (int j = 0; j < numDocuments; ++j) {
                if (termDocMatrix[i][j] != 0) {
                    sparse.setValue(i, j, termDocMatrix[i][j]);
                }
            }
        }
        return sparse;
    }
};

int main() {
    TermDocumentMatrix tdm(3, 2);
    tdm.updateTermFrequency(0, 0, 1);
    tdm.updateTermFrequency(1, 0, 2);
    tdm.updateTermFrequency(2, 1, 3);

    cout << "Term Frequency for term 0 in document 0: " << tdm.getTermFrequency(0, 0) << endl;
    cout << "Document Frequency for term 1: " << tdm.getDocumentFrequency(1) << endl;
    cout << "Total Terms in document 1: " << tdm.getTotalTermsInDocument(1) << endl;

    SparseArray sparse = tdm.toSparseMatrix();
    cout << "Sparse Matrix Representation:" << endl;
    for (int i = 0; i < sparse.getNumRows(); ++i) {
        for (int j = 0; j < sparse.getNumCols(); ++j) {
            cout << sparse.getValue(i, j) << " ";
        }
        cout << endl;
    }

    return 0;
}
