void mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	 
	if (low < high){
		int mid = low +((high - low) / 2);
		mergesort(array, scratch, low, mid);
		mergesort(array, scratch, mid + 1, high);
		int L = low;
		int H = mid + 1;
		for (int i = low; i <= high; ++i){
			if (L <= mid && (H > high || array[L] <= array[H])){
				scratch[i] = array[L];
				L++;
			}else{
				scratch[i] = array[H];
				H++;

			}
		}
		for (int i = low; i <= high; ++i){
			array[i] = scratch[i];
		}
	}
}

