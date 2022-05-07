void free_array(int** matrix, int n){
    for (int i = 0; i < n; i++)
        delete [] matrix[i];
    delete [] matrix;
}

int* compress(int** matrix, int n, int m) {
    int *arr = new int[3 * n];
    int idx = 0;
    for (int in = 0; in < n; in++) {
        int count = 0;
        for (int im = 0; im < m; im++){
           if (matrix[in][im]) {
               if (idx < 3 * n)
                   arr[idx] = matrix[in][im];
               else
                   free_array(matrix, n);
               idx++;
               count++;
           }
        }
        if (count - 3){
            free_array(matrix, n);
            delete [] arr;
            return nullptr;
        }
    }
    free_array(matrix, n);
    return arr;
}
