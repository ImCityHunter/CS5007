/*
 * problem2.c
 *
 * Problem 2:
 * This problem is to write the supporting functions that
 * enable a version of Insertion Sort to sort the integer
 * values in a random-access binary file.
 */
#include <stdio.h>
#include <stdlib.h>


/**
 * Get the value at the index position in the array file.
 * @param f the array file
 * @param index the index position
 * @return the value at the position
 */
int getValueAt(FILE* f, size_t index) {
	if(f==NULL) printf("File Is Null\n");
	int check = fseek(f,index*sizeof(int),SEEK_SET);
	if(check == -1) printf("error\n");
	int a;
	fread(&a,sizeof(int),1,f);
	return a;

}

/**
 * Set the value at the index position in the array file.
 * @param f the array file
 * @param index the index position
 * @param the value to set
 */
void setValueAt(FILE* f, size_t index, int value) {
	if(f==NULL) printf("File Is Null\n");
	int check = fseek(f,index*sizeof(int),SEEK_SET);
	if(check==-1) printf("error\n");
	fwrite(&value,sizeof(int),1,f);
}

/**
 * Get the number of elements in the array file.
 * @param f the array file
 * @return the number of elements
 */
size_t getArraySize(FILE* f) {
	if(f==NULL) printf("File Is Null\n");
	fseek(f, 0, SEEK_END); // seek to end of file
	size_t size = ftell(f); // get current file pointer
	fseek(f, 0, SEEK_SET); // seek back to beginning of file
	return size/sizeof(int);
	// your code here
}

/**
 * Write the input array to the file.
 * @param f the array file
 * @param the array values
 * @param the array size
 */
void writeArray(FILE* f, int values[], size_t size) {
	if(f==NULL) printf("File Is Null\n");
	for(int i=0;i<size;i++){
		fwrite(&values[i],sizeof(int),1,f);
	}
}

/**
 * Print the array, one element per line:
 *   0: 14
 *   1: -8
 *   2: 9
 *    ...
 * @param f the array file
 */
void printArray(FILE* f) {
	if(f==NULL) printf("File Is Null");
	size_t size = getArraySize(f);
	for(int i =0;i<size;i++){
		int value = getValueAt(f,i);
		printf("%d: %d\n",i,value);
	}
	//printf("size is %d \n",getArraySize(f));
	// your code here
}

/**
 * Insertion Sort inserts each element of the array into
 * its proper position, leaving progressively larger
 * stretches of the array sorted.
 *
 * @param f file the array file
 */
void insertionSort(FILE* f) {
	size_t nValues = getArraySize(f);
	for (int i=1; i < nValues; i++) {
		// slide values up array to make "hole" for value
		int hole = i;
		int val = getValueAt(f, hole);
		int preval;  // value at hole-1
		while(hole > 0 && (preval = getValueAt(f, hole-1)) > val) {
			setValueAt(f, hole, preval);
			hole--;
		}
		// put value in "hole" position
		setValueAt(f, hole, val);
	}
}

#if defined __MINGW32__
#include <string.h>
// mingw tmpfile() creates files in "C:\" => no permission
FILE *tmpfile() {
	char tmppath[FILENAME_MAX];
	sprintf(tmppath,"%s\\problem2.tmp",getenv("TEMP"));
	return fopen(tmppath, "w+b");
}
#endif

/**
 * This program sorts an array of integers using
 * a file-based version of insertion sort.
 */
int main(void) {
	printf("Start problem 2\n");

	// array to sort
	int a[] = {4, 3, 1, 5, 2};

	// write array to a binary temp file that is
	// automatically removed when it is closed
	FILE* f = tmpfile();

	if (f == NULL) {
		perror("cannot open temp file");
		fflush(stdout);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	writeArray(f, a, 5);

	// print unsorted array
	printf("unsorted:\n");
	printArray(f);

	// sort the array
	insertionSort(f);

	// print sorted array
	printf("\nsorted:\n");
	printArray(f);

	// close the temp file
	fclose(f);

	printf("End problem 2\n");

	return EXIT_SUCCESS;
}
