/*#include <omp.h>
#include <stdio.h>
#include <fstream>

using std::ifstream;

int main()
{
	const int size = 30000;
	const char* fileName = "fileName.txt";
	const char* toFind = "see";
	char** rows;
	double time;
	for (int k = 0; k < 10; ++k) {
		ifstream file("fileName.txt", std::ios_base::binary);
		if (!file) {
			printf("Cannot open the file %s!", fileName);
			return -1;
		}
		rows = new char*[size];
		char* row = new char[size];
		int index = 0;
		do {
			file.getline(row, size);
			if (index < size) {
				char ch = row[0];
				int i = 0;
				rows[index] = new char[size];
				while (ch != '\n' && ch != '\0' && ch != '\r') {
					rows[index][i] = row[i++];
					ch = row[i];
				}
				rows[index][i] = '\0';
			}
			else {
				printf("Too big file %s!", fileName);
				return -2;
			}
			++index;
		} while (!file.eof());
		int length = index;
		int _min_i = size, _min_j = size;

		time = omp_get_wtime();

#pragma omp parallel for schedule(static)
		for (int i = 0; i < length; ++i)
		{
			char ch1, ch2;
			int j = 0;
			bool isFound = false;
			do {
				ch1 = rows[i][j];
				ch2 = toFind[0];
				if (ch1 == ch2) {
					for (int l = 1; l < size; ++l) {
						ch1 = rows[i][j + l];
						ch2 = toFind[l];
						if (ch2 == '\0') isFound = true;
						if (ch1 != ch2 || ch1 == '\0') {
							ch1 = rows[i][j];
							ch2 = toFind[0];
							break;
						}
					}
				}
				if (isFound) {
#pragma omp critical
					if (i < _min_i) {
						_min_i = i;
						_min_j = j;
					}
					break;
				}
				else {
					++j;
				}
			} while (ch1 != '\0');
		}

		time = omp_get_wtime() - time;

		printf("time is %f seconds; ", time);
		if (_min_i == size) printf("not found!\n");
		else printf("i = % i, j = % i; \n", _min_i, _min_j);
		for (int i = 0; i < length; ++i) {
			delete rows[i];
		}
		delete[] rows;
	}
	return 0;
}*/