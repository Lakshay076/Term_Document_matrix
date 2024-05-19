import java.util.*;
public class SparseMatrix {
    static int Row = 5;
    static int Col = 3;
    static int[][] sparseArray = new int[Row][Col];

    static void create() {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                sparseArray[i][j] = 0;
            }
        }
    }

    static void printSparse() {
        System.out.println("\nD T V");
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                System.out.print(sparseArray[i][j] + " ");
            }
            System.out.println();
        }
    }

    static void setValue(int doc, int term, int value) {
        for (int i = 0; i < Row; i++) {
            if (sparseArray[i][0] == 0) {
                sparseArray[i][0] = doc;
                sparseArray[i][1] = term;
                sparseArray[i][2] = value;
                break;
            }
        }
    }

    static int getValue(int doc, int term) {
        for (int i = 0; i < Row; i++) {
            if (sparseArray[i][0] == doc && sparseArray[i][1] == term) {
                return sparseArray[i][2];
            }
        }
        return -1; // Return -1 if value not found
    }

    static void addValue(int doc, int term, int value) {
        for (int i = 0; i < Row; i++) {
            if (sparseArray[i][0] == doc && sparseArray[i][1] == term) {
                sparseArray[i][2] += value;
            }
        }
    }

    static void removeValue(int doc, int term) {
        for (int i = 0; i < Row; i++) {
            if (sparseArray[i][0] == doc && sparseArray[i][1] == term) {
                sparseArray[i][2] = 0;
            }
        }
    }

    static void transpose() {
        System.out.println("Document Term Value");
        for (int j = 0; j < Col; j++) {
            for (int i = -1; i < Row; i++) {
                if (i == -1 && j == 0) System.out.print("Document ");
                else if (i == -1 && j == 1) System.out.print("Term     ");
                else if (i == -1 && j == 2) System.out.print("Value    ");
                else System.out.print(sparseArray[i][j] + " ");
            }
            System.out.println();
        }
    }

    static void dense(int totalDoc, int totalTerms) {
        int[][] arr = new int[totalDoc + 1][totalTerms + 1];
        for (int i = 0; i < totalDoc + 1; i++) {
            for (int j = 0; j < totalTerms + 1; j++) {
                if (i == 0) arr[i][j] = j;
                else if (j == 0) arr[i][j] = i;
                else arr[i][j] = 0;
            }
        }
        for (int i = 0; i < Row; i++) {
            arr[sparseArray[i][0]][sparseArray[i][1]] = sparseArray[i][2];
        }
        for (int i = 0; i < totalDoc + 1; i++) {
            for (int j = 0; j < totalTerms + 1; j++) {
                System.out.print(arr[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        create();
        printSparse();
        setValue(1, 3, 9);
        setValue(2, 3, 5);
        setValue(3, 1, 8);
        setValue(3, 2, 7);
        setValue(3, 3, 9);
        printSparse();
        int a, b;
        System.out.print("Enter the doc and term whose value you want to get = ");
        Scanner scanner = new Scanner(System.in);
        a = scanner.nextInt();
        b = scanner.nextInt();
        System.out.println("\nThe value of Doc" + a + " Term" + b + " = " + getValue(a, b));
        addValue(2, 3, 1);
        System.out.println("\nAfter adding 1 to the value of doc2 and term3, the sparse matrix becomes \n");
        printSparse();
        System.out.println("The transpose of the Sparse matrix is \n");
        transpose();
        System.out.println("The dense matrix is\n");
        dense(9, 4);
    }
}
