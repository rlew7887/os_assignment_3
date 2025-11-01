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
	int total_size = leftsize + rightsize;

	int *B = (int*)malloc(total_size * sizeof(int)); //allocates local temp array- each thread gets its own
    if (B == NULL) {
        fprintf(stderr, "memory allocation failed in merge\n"); //error checking
        exit(EXIT_FAILURE);
    }

	int i, j;
	for (i=0; i<leftsize; i++) {
		B[i] = A[leftstart + i]; //left subarray
	}
	for (j=0; j<rightsize; j++) {
		B[leftsize + j] = A[rightstart + j]; //right subarray
	}

	// merge temp array B back into original array A
	i = 0;
	j = 0;
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

	// copy remaining elements of left subarray, if any
	while (i < leftsize) {
		A[k] = B[i];
		i++;
		k++;
	}

	// copy remaining elements of right subarray, if any
	while (j < rightsize) {
		A[k] = B[leftsize + j];
		j++;
		k++;
	}

	free(B); //frees local temp array
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	if (left >= right) return;	// if array has 1 or 0 elements, its already sorted
	int mid = (left + right) / 2; // find midpoint
	my_mergesort(left, mid);
	my_mergesort(mid + 1, right);
	merge(left, mid, mid + 1, right); // merge two sorted halves
}


/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
	struct argument* a = (struct argument*)arg;
	pthread_t p1, p2;	
	if(a->left >= a->right || a->level >= cutoff) {
		my_mergesort(a->left, a->right);
		return NULL;
	}
	int mid = (a->left + a->right) / 2;
	struct argument* arg1 = buildArgs(a->left, mid, a->level + 1); // build arguments for calling parallel_mergesort
	struct argument* arg2 = buildArgs(mid+1, a->right, a->level + 1);
	pthread_create(&p1, NULL, parallel_mergesort, arg1); // creates threads that run parallel_mergesort again
	pthread_create(&p2, NULL, parallel_mergesort, arg2);
	pthread_join(p1, NULL); // threads wait until the base case
	pthread_join(p2, NULL);
	merge(a->left, mid, mid + 1, a->right); // merge halves up the stack
	
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	struct argument* arg = (struct argument*)malloc(sizeof(struct argument));
	arg->left = left;
	arg->right = right;
	arg->level = level;
	return arg;
}


