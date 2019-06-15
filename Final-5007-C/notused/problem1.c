/*
 * problem1.c
 *
 * Problem 1:
 * This problem is to write a set of C functions that
 * perform specified operations on files and directories
 * that require determining and using information about
 * files, directories and directory entries.
 *
 */
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#if defined _WIN32 || defined __CYGWIN__
const char* FILE_NAME = "C:\\Windows\\notepad.exe";
const char* DIR_NAME = "C:\\Windows";
const char PATH_SEPARATOR = '\\';

#else
const char* FILE_NAME = "/usr/include/stdlib.h";
const char* DIR_NAME = "/usr/include";
const char PATH_SEPARATOR = '/';
#endif

/**
 * Returns string representation of a boolean value.
 * @param b boolean
 * @return "true" or "false"
 */
const char* boolToS(bool b) {
	return b ? "true" : "false";
}

/**
 * Creates a file from a directory path and a file name
 * @param dirName the directory path
 * @param the file name
 * @param buffer to write the new path
 * @return pointer to the new path
 */
char* makePath(const char* dirName, const char* fName, char* pathName) {
	sprintf(pathName, "%s%c%s", dirName, PATH_SEPARATOR,fName);
	return pathName;
}


/**
 * Count the directories within the specified directory if
 * it exists, or -1 if not a directory or does not exist.
 * Does not count "." and "..".
 *
 * @param dirName name of directory
 * @return number of sub-directories
 */
long countDirectories(const char* dirName) {
	// your code here
	// hint: get entry type from inode
	// hint: use makePath above to make path
	struct stat s;
	if(stat(dirName,&s)!=0) return -1;
	if(!S_ISDIR(s.st_mode)) return -1;
	long count = 0;
	struct dirent *dp;
	DIR *dirp = opendir(dirName);   // open directory for reading
	if (dirp == NULL) return -1;
	while ((dp = readdir(dirp)) != NULL) {
		if(dp->d_type==DT_DIR) count++;
	}
	closedir(dirp);
	return count;
}

/**
 * Returns the size of a regular file if it exists,
 * or -1 if it is not a regular file or does not exist.
 *
 * @param fname the name of the file
 * @return size of regular file or -1
 */
long fileSize(const char* fname) {
	struct stat s;
	int fd = stat(fname,&s);
	if(fd!=0 || !S_ISREG(s.st_mode)) {
		return -1;
	}
	else{
		return s.st_size;
	}

	// your code here
}

/**
 * Returns the total size of all the regular files
 * within a specified directory if it exists, or -1
 * if not a directory or does not exist.
 *
 * @param dirName name of directory
 * @return total size of all regular files
 */
long fileSizes(const char* dirName) {
	long totalSize = 0;

	struct dirent *dp;
	DIR *dirp = opendir(dirName);
	if (dirp == NULL) {
		//fprintf(stderr, "file sizes, Cannot open directory %s\n", dirName);
		return -1;
	}
	while ((dp = readdir(dirp)) != NULL) {
		if(dp->d_type == DT_REG){
			struct stat s;
			char* pathName = malloc(256);
			makePath(dirName,dp->d_name,pathName);
			stat(pathName,&s);
			totalSize+=s.st_size;
		}

	}
	closedir(dirp);
	return totalSize;


	// your code here
	// hint: get entry type from inode
	// hint: use makePath above to make path
}

/**
 * Determines whether the two names refer to the same file
 * or directory. Comparing names is *not* sufficient because
 * the names could be links to the same file or directory.
 *
 * Uses file inodes for comparison.
 *
 * @param fname1 the first file or directory
 * @param fname2 the second file or directory
 * @return true of both files or directories exist and
 * 	are the same one, and false otherwise
 */
bool isSameFile(const char* fname1, const char* fname2) {
	struct stat s1;
	struct stat s2;
	int fd1 = stat(fname1,&s1);
	int fd2 = stat(fname2,&s2);
	bool result = false;
	if(fd1!=0 ||fd2!=0){
		printf("\nfiles do not exist\n");
		result= false;
	}
	else if(S_ISDIR(s1.st_mode) && S_ISDIR(s2.st_mode)){
		result= (s1.st_ino == s2.st_ino);

	}
	else if(S_ISREG( s1.st_mode)&&S_ISREG( s2.st_mode)){
		result= (s1.st_ino == s2.st_ino);
	}
	return result;
}

int main() {
	printf("Start problem 1\n");

	// count directories
	long count;

	// count directories tests: directory name and file name
	printf("\n");
	count = countDirectories(DIR_NAME);
	printf("countDirectories(%s): %ld\n", DIR_NAME, count);
	count = countDirectories(FILE_NAME);  // expect -1
	printf("countDirectories(%s): %ld  (expect -1)\n", FILE_NAME, count);

	// get size of file tests: file name and directory
	printf("\n");
	count = fileSize(FILE_NAME);
	printf("fileSize(%s): %ld\n", FILE_NAME, count);
	count = fileSize(DIR_NAME); // expect -1
	printf("fileSize(%s): %ld  (expect -1)\n", DIR_NAME, count);

	// get total size of files tests: directory name and file name
	printf("\n");
	count = fileSizes(DIR_NAME);
	printf("fileSizes(%s): %ld\n", DIR_NAME, count);
	count = fileSizes(FILE_NAME);	// expect -1
	printf("fileSizes(%s): %ld  (expect -1)\n", FILE_NAME, count);

	bool b;

	// determine same file: files, directories, file and directory
	printf("\n");
	b= isSameFile(FILE_NAME, FILE_NAME);	// expect true
	printf("isSameFile(%s, %s): %s (expect true)\n", FILE_NAME, FILE_NAME, boolToS(b));
	b= isSameFile(DIR_NAME, DIR_NAME);	// expect true
	printf("isSameFile(%s, %s): %s (expect true)\n", DIR_NAME, DIR_NAME, boolToS(b));
	b= isSameFile(FILE_NAME, DIR_NAME);	// expect false
	printf("isSameFile(%s, %s): %s (expect false)\n", FILE_NAME, DIR_NAME, boolToS(b));

	return EXIT_SUCCESS;

	printf("End problem 1\n");
}

