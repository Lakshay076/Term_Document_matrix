public class TDM {
    static int num_documents = 9;
    static int num_terms = 4;
    static int[][] arr = new int[num_documents + 1][num_terms + 1];

    static void create_TDM() {
        for (int i = 0; i < num_documents + 1; i++) {
            arr[i][0] = i;
        }
        for (int j = 0; j < num_terms + 1; j++) {
            arr[0][j] = j;
        }
        for (int i = 1; i < num_documents + 1; i++) {
            for (int j = 1; j < num_terms + 1; j++) {
                arr[i][j] = 0;
            }
        }
    }

    static void updatetermfrequency(int document_index, int term_index, int frequency) {
        arr[document_index][term_index] = frequency;
    }

    static int gettermfrequency(int document_index, int term_index) {
        return arr[document_index][term_index];
    }

    static int getdocumentfrequency(int term_index) {
        int sum = 0;
        for (int i = 1; i < num_documents + 1; i++) {
            if (arr[i][term_index] != 0) {
                sum++;
            }
        }
        return sum;
    }

    static int get_total_terms_in_document(int document_index) {
        int sum = 0;
        for (int j = 1; j < num_terms + 1; j++) {
            sum += arr[document_index][j];
        }
        return sum;
    }

    static void print_TDM() {
        for (int i = 0; i < num_documents + 1; i++) {
            for (int j = 0; j < num_terms + 1; j++) {
                System.out.print(arr[i][j] + "  ");
            }
            System.out.println();
        }
    }

    static void tosparsematrix() {
        int a = 0;
        for (int i = 1; i < num_terms + 1; i++) {
            int b = getdocumentfrequency(i);
            a += b;
            b = 0;
        }
        int[][] sparsematrix = new int[a][3];
        System.out.println("The sparse matrix is");
        System.out.println("D T V");
        for (int i = 1, m = 0; i < num_documents + 1; i++) {
            for (int j = 1; j < num_terms + 1; j++) {
                if (arr[i][j] != 0) {
                    sparsematrix[m][0] = i;
                    sparsematrix[m][1] = j;
                    sparsematrix[m][2] = arr[i][j];
                    m++;
                }
            }
        }
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < 3; j++) {
                System.out.print(sparsematrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        create_TDM();
        System.out.println("The Term Document matrix is");
        print_TDM();
        System.out.println();
        updatetermfrequency(3, 2, 7);
        updatetermfrequency(3, 1, 8);
        updatetermfrequency(2, 3, 5);
        updatetermfrequency(1, 3, 9);
        updatetermfrequency(3, 3, 9);
        System.out.println("The TDM after updating the term frequencies");
        print_TDM();
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        System.out.print("Enter the term whose document frequency you want to get = ");
        int a = scanner.nextInt();
        System.out.println("The document frequency of " + a + " term is " + getdocumentfrequency(a));
        System.out.print("Enter the number of the document and term whose term frequency you want to get = ");
        int b = scanner.nextInt();
        int c = scanner.nextInt();
        System.out.println("The Doc " + b + " term " + c + ", term frequency is " + gettermfrequency(b, c));
        System.out.print("Enter the document number whose total terms you want to get = ");
        int e = scanner.nextInt();
        System.out.println("The total number of terms in the Doc" + e + " is " + get_total_terms_in_document(e));
        tosparsematrix();
        scanner.close();
    }
}

