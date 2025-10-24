/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	int leftsize = leftend - leftstart + 1;
	int rightsize = rightend - rightstart;

	for (int i=0; i<leftsize; i++) 
		B[i] = A[leftstart + i]; /*left subarray*/
	for (int j=0; j<rightsize; j++)
		B[leftsize + j] = A[rightstart + j]; /*right subarray*/

	/*merge temp array B back into original array A*/
	int i = 0;
	int j = 0;
	int k = leftstart;
	while (i<leftsize && j<rightsize) {
		if (B[i] <= B[leftsize + j]) {
			A[k] = B[i];
			i++;
		} else {
			A[k] = B[leftsize + j];
			j++;
		}
		k++;
	}

	/*copy remaining elements of left subarray, if any*/
	while (i < leftsize) {
		A[k] = B[i];
		i++;
		k++;
	}

	/*copy remaining elements of right subarray, if any*/
	while (j < rightsize) {
		A[k] = B[leftsize + j];
		j++;
		k++;
	}
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

