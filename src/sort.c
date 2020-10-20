void sort(long long *unsorted_array, long long *result_array, int size_of_array){
    for (int i=0; i<size_of_array; i++){
        result_array[i]=unsorted_array[i];
    }
    long long replacer;
    for (int i=0; i<size_of_array; i++){
        for(int j=0; j<size_of_array; j++){
            if (result_array[j] > result_array[j+1]){
                replacer = result_array[j];
                result_array[j] = result_array[j+1];
                result_array[j+1] = replacer;
            }
        }
    }
}