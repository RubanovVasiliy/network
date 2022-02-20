#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGHT 80

typedef struct Set {
    int len;
    char name;
    char *str;
} Set;

void insertionSort(char arr[], int lenght) {
    int temp;
    int j = 0;
    for (int i = 1; i < lenght; i++) {
	temp = arr[i];
	j = i;

	while (j > 0 && arr[j - 1] > temp) {
	    arr[j] = arr[j - 1];
	    arr[j - 1] = temp;
	    j--;
	}
    }
}

int binarySearch(char arr[], int l, int r, char x) {
    if (r >= l) {
	int mid = l + (r - l) / 2;

	if (arr[mid] == x) {
	    return mid;
	}

	if (arr[mid] > x) {
	    return binarySearch(arr, l, mid - 1, x);
	}
	return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

char *unique_copy(char arr[], int lenght) {
    insertionSort(arr, strlen(arr));
    int j = 1;
    char *var = malloc(sizeof(int) * lenght + 1);
    var[1] = arr[0];
    for (int i = 1; i < lenght + 1; i++) {
	if (arr[i] != var[j]) {
	    var[j + 1] = arr[i];
	    j++;
	}
    }
    var[0] = j;

    char *v = malloc(sizeof(int) * j);
    for (int i = 0; i < j; i++) {
	v[i] = var[i + 1];
    }
    free(var);
    var = NULL;

    return v;
}

void inputElements(char *str) { // Input set with keyboard
    int c;
    while ((c = getchar()) != '\n') {
	if (isalpha(c)) {
	    *str++ = c;
	}
    };
    *str = '\0';
}

Set createSet(char name) { // Create set with settings
    Set M;
    printf("VVedite mnojestvo %c: ", name);
    char *str = (char *)malloc(sizeof(char) * LENGHT);
    inputElements(str);
    int len = strlen(str);
    M.name = name;
    M.str = unique_copy(str, len);
    M.len = strlen(M.str);
    return M;
}

void printFormat(Set M) { // Output set
    printf("Mnojestvo %c: ", M.name);
    for (int i = 0; i < M.len; i++) {
	printf(" %c", toupper(M.str[i]));
    }
    printf("\n");
    printf("Lenght: %d \n\n", M.len);
}

int isIncluded(Set A, Set B) { // Check including A in B
    if (A.len > B.len) {
	return 0;
    }
    int isIncluded = 1;
    for (int i = 0; i < A.len; i++) {
	if (binarySearch(B.str, 0, B.len - 1, A.str[i]) == -1) {
	    printf(" %c net v B\n", toupper(A.str[i]));
	    isIncluded = 0;
	}
    }
    return isIncluded;
}

void include(Set A, Set B) { // Print result of including
    if (isIncluded(A, B)) {
	printf("%c vhodit v %c\n", A.name, B.name);
    } else {
	printf("%c ne vhodit v %c\n", A.name, B.name);
    }
}

Set unionM(Set A, Set B) { // Create union set
    Set R = {.name = 'U', .len = A.len + B.len};
    char *temp = malloc(sizeof(int) * R.len);
    for (int i = 0; i < A.len; i++) {
	temp[i] = A.str[i];
    }

    for (int i = A.len, j = 0; i < R.len; i++, j++) {
	temp[i] = B.str[j];
    }

    R.str = unique_copy(temp, R.len);
    R.len = strlen(R.str);
    return R;
}

void printUnion(Set A, Set B) { // Print union set
    Set R = unionM(A, B);
    printf("Obedinenie mnojestv %c U %c: ", A.name, B.name);
    for (int i = 0; i < R.len; i++) {
	printf(" %c", toupper(R.str[i]));
    }
    printf("\n");
}

Set intersectionOfSets(Set A, Set B) {
    char *temp = malloc(sizeof(int) * A.len);
    for (int i = 0, j = 0; i < A.len; i++) {
	if (binarySearch(B.str, 0, B.len - 1, A.str[i]) != -1) {
	    temp[j] = A.str[i];
	    j++;
	}
    }
    Set R = {.name = 'I', .len = strlen(temp), .str = temp};
    return R;
}

void printIntersectionOfSets(Set A, Set B) { // Print symmetric difference set
    Set R = intersectionOfSets(A, B);
    printf("Peresechenie  mnojestv %c ^ %c: ", A.name, B.name);
    for (int i = 0; i < R.len; i++) {
	printf(" %c", toupper(R.str[i]));
    }
    printf("\n");
}

Set differenceOfSets(Set A, Set B) {
    char *temp = malloc(sizeof(int) * A.len);
    for (int i = 0, j = 0; i < A.len; i++) {
	if (binarySearch(B.str, 0, B.len - 1, A.str[i]) == -1) {
	    temp[j] = A.str[i];
	    j++;
	}
    }
    Set R = {.name = 'D', .len = strlen(temp), .str = temp};

    return R;
}

void printDifferenceOfSets(Set A, Set B) { // Print symmetric difference set
    Set R = differenceOfSets(A, B);
    printf("Raznost %c \\ %c: ", A.name, B.name);
    for (int i = 0; i < R.len; i++) {
	printf(" %c", toupper(R.str[i]));
    }
    printf("\n");
}

Set symmetricDifference(Set A, Set B) {
    Set D1 = differenceOfSets(A, B);
    Set D2 = differenceOfSets(B, A);
    Set R = unionM(D1, D2);
    return R;
}

void printSymmetricDifference(Set A, Set B) { // Print symmetric difference set
    Set R = symmetricDifference(A, B);
    printf("Symmetric raznost %c \\ %c: ", A.name, B.name);
    for (int i = 0; i < R.len; i++) {
	printf(" %c", toupper(R.str[i]));
    }
    printf("\n");
}

void printAllOperations(Set A, Set B) {
    include(A, B);
    printUnion(A, B);
    printIntersectionOfSets(A, B);
    printDifferenceOfSets(A, B);
    printDifferenceOfSets(B, A);
    printSymmetricDifference(A, B);
    include(B, A);
}

void printOperations(Set A, Set B) { // Print menu with optoins
    printf(
	"Viberitr operatsiuy:\n"
	"1) vhojdenie     %cc%c\n"
	"2) obedinenie    %c i %c\n"
	"3) peresechenie  %c i %c\n"
	"4) raznost       %c \\ %c\n"
	"5) raznost       %c \\ %c\n"
	"6) symmetric raznost %c \\ %c\n"
	"7) vhojdenie     %cc%c\n"
	"8) Vse operatsii\n"
	"\n",
	A.name,
	B.name,
	A.name,
	B.name,
	A.name,
	B.name,
	A.name,
	B.name,
	B.name,
	A.name,
	A.name,
	B.name,
	B.name,
	A.name);
    int c = getchar();
    if (!isdigit(c)) {
	printf("erorr\n");
    } else {
	switch (c) {
	case '1':
	    include(A, B);
	    break;
	case '2':
	    printUnion(A, B);
	    break;
	case '3':
	    printIntersectionOfSets(A, B);
	    break;
	case '4':
	    printDifferenceOfSets(A, B);
	    break;
	case '5':
	    printDifferenceOfSets(B, A);
	    break;
	case '6':
	    printSymmetricDifference(A, B);
	    break;
	case '7':
	    include(B, A);
	    break;
	case '8':
	    printOperations(A, B);
	    break;
	default:
	    printf("No option selected");
	}
    }
}

int main(void) {
    Set A = createSet('A');
    printFormat(A);

    Set B = createSet('B');
    printFormat(B);

    // printOperations(A, B);

    include(A, B);
    printUnion(A, B);
    printIntersectionOfSets(A, B);
    printDifferenceOfSets(A, B);
    printDifferenceOfSets(B, A);
    printSymmetricDifference(A, B);
    include(B, A);

    return 0;
}