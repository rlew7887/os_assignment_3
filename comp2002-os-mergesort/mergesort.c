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
	int rightsize = rightend - rightstart + 1;

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
void mergesort(int left, int right){
	if (left >= right) return;	/*if array has 1 or 0 elements, its already sorted*/
	int mid = (left + right) / 2; /*find midpoint*/
	mergesort(left, mid);
	mergesort(mid + 1, right);
	merge(left, mid, mid + 1, right); /*merge two sorted halves*/
}


/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
	pthread_t p1, p2;	
	


	
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	argument* arg = (argument*)malloc(sizeof(argument));
	arg->left = left;
	arg->right = right;
	arg->level = level;
	return arg;
}


