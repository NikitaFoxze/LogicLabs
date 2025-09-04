#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

typedef struct {
	char familia[20];
	char imya[20];
	char fakultet[20];
	int zach_num;
} Student;

void findMaxMinDiff();
void randomInitArray();
void createDynamicArray();
void sumRowsColsMatrix(int rows, int cols);
void searchStudentByName();

int main() {
	setlocale(LC_ALL, "Russian");

	int choice;

	do {
		printf("\n���� ������ ��������:\n"
			"1. ����� ������� ����� ���������� � ��������� �������\n"
			"2. ���������������� ������ ���������� �������\n"
			"3. ������� ������ ������������� �������\n"
			"4. ����������� ������ � ������� �������\n"
			"5. ������ �������� �� �����\n"
			"0. �����\n"
			"\n��� �����: ");
		scanf_s("%d", &choice);

		switch (choice) {
		case 1:
			findMaxMinDiff(); break;
		case 2:
			randomInitArray(); break;
		case 3:
			createDynamicArray(); break;
		case 4:
			sumRowsColsMatrix(3, 3); break;
		case 5:
			searchStudentByName(); break;
		case 0:
			printf("���������� ������...\n");
			break;
		default:
			printf("������������ �����. ��������� �������.\n");
		}
	} while (choice != 0);

	return 0;
}

// ������� ���������� ������� ����� ������������ � ����������� ��������� ������� 1
void findMaxMinDiff() {
	const int N = 5;
	int arr[N] = { 10, 20, 30, 40, 50 };
	int max = arr[0], min = arr[0], diff;

	for (int i = 1; i < N; i++) {
		if (arr[i] > max) max = arr[i];
		else if (arr[i] < min) min = arr[i];
	}

	diff = max - min;
	printf("������������ ��������: %d\n����������� ��������: %d\n�������: %d\n", max, min, diff);
}

// ������� ���������� ������� ���������� ������� 2
void randomInitArray() {
	const int N = 10;
	int arr[N];
	srand(time(NULL));

	for (int i = 0; i < N; i++) {
		arr[i] = rand() % 100 + 1; // ����� �� 1 �� 100
	}

	printf("��������� ������: ");
	for (int i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// ������� �������� ������� ������������� ������� 3
void createDynamicArray() {
	int* arr;
	int size, i;

	printf("������� ������ �������: ");
	scanf_s("%d", &size);

	arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL) {
		printf("������ ��������� ������!\n");
		return;
	}

	for (i = 0; i < size; i++) {
		printf("������� ������� #%d: ", i + 1);
		scanf_s("%d", &arr[i]);
	}

	printf("\n����������� ������: ");
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	free(arr);
}

// ������� ������������ ����� � �������� ������� � ������������ ������� 4
void sumRowsColsMatrix(int rows, int cols) {
	int** mat = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; ++i) {
		mat[i] = (int*)malloc(cols * sizeof(int));
	}

	int value = 1;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			mat[r][c] = value++;
		}
	}

	int* rowSums = (int*)calloc(rows, sizeof(int));
	int* colSums = (int*)calloc(cols, sizeof(int));

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			rowSums[r] += mat[r][c];
		}
	}

	for (int c = 0; c < cols; c++) {
		for (int r = 0; r < rows; r++) {
			colSums[c] += mat[r][c];
		}
	}

	printf("������� (%dx%d):\n", rows, cols);
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			printf("%d\t", mat[r][c]);
		}
		printf("\n");
	}

	printf("\n����� �����: ");
	for (int r = 0; r < rows; r++) {
		printf("%d ", rowSums[r]);
	}

	printf("\n����� ��������: ");
	for (int c = 0; c < cols; c++) {
		printf("%d ", colSums[c]);
	}
	printf("\n");

	for (int i = 0; i < rows; ++i) free(mat[i]); // ����������� ������ ������
	free(mat);                                   // ����������� ��� ������ ����������
	free(rowSums);                               // ����������� ����� �����
	free(colSums);                               // ����������� ����� ��������
}

// ������� ������ �������� �� ������� 5
void searchStudentByName() {
	Student students[] = {
		{"Ivanov", "����", "���.", 12345},
		{"Petrov", "����", "���.", 54321},
		{"Sidorov", "������", "���.", 67890}
	};

	char searchFamilia[20];
	int found = 0;

	printf("������� ������� �������� ��� ������: ");
	scanf_s("%s", searchFamilia, sizeof(searchFamilia));

	for (int i = 0; i < 3; i++) {
		if (strcmp(students[i].familia, searchFamilia) == 0) {
			printf("\n������� ������:\n"
				"�������: %s\n���: %s\n���������: %s\n�������� ������: %d\n",
				students[i].familia, students[i].imya,
				students[i].fakultet, students[i].zach_num);

			found = 1;
			break;
		}
	}

	if (!found) {
		printf("������� � ��������� �������� �� ������.\n");
	}
}