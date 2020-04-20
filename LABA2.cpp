#include <math.h>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>


int main() {
	short matrix[8][8], i, j;
	long int sum, result = 0, mmx = 0;		
	long res = 0;
	clock_t time1, time2;
	bool flag = true;


	do {
		/*do {
			printf("Enter the ranges of the interval: ");
			if (!scanf_s("%f", &a)) {
				printf("repeat input pls\n");
				rewind(stdin);
				continue;
			}
			if (!scanf_s("%f", &b)) {
				printf("repeat input pls\n");
				rewind(stdin);
				continue;
			}
			printf("Enter the increment step: ");
			if (!scanf_s("%f", &d)) {
				printf("repeat input pls\n");
				rewind(stdin);
				continue;
			}
			flag = false;
		} while (flag);
*/
		sum = 0;
		time1 = clock();
		for (i = 0; i < 8; i++)
			for (j = 0; j < 8; j++) {
				matrix[i][j] = rand() + 1;
				sum += pow(matrix[i][j], 2);
			}
		printf("sum = %ld\n", sum);
		time2 = clock();
		float ctime = (float)(time2 - time1);
		printf("time work on C: %f ms\n", ctime);

		sum = 0;

		/*long int matrix2[64];

		for (i = 0; i < 8; i++)
			for (j = 0; j < 8; j++) {
				matrix2[i*8+j] = matrix[i][j];
			}

		_asm finit

		time1 = clock();

		for (i = 0; i < 64; i++)
				_asm {
					xor ebx, ebx
					xor esi, esi
					xor eax, eax
					mov esi, i
					mov eax, matrix2[esi]
					mul eax
					mov ebx, eax
					add result, ebx

					fwait
				}


		printf("result = %ld\n", result);
		result = 0;
		time2 = clock();
		float asstime = (float)(time2 - time1);
		printf("time work on Asm: %f ms\n", asstime);*/

		short matrix2[64];

		for (i = 0; i < 8; i++)
			for (j = 0; j < 8; j++) {
				matrix2[i * 8 + j] = matrix[i][j];
			}

		_asm finit

		time1 = clock();

		_asm {
			pusha
			xor esi, esi
			pxor MM7, MM7
		}

		for (i = 0; i < 16; i++)
			_asm {
				movq MM0, matrix2[esi]
				movq MM1, matrix2[esi]
				pmaddwd MM0, MM1
				paddd MM7, MM0
				add esi, 8
			}
		_asm {
			movq MM0, MM7
			psrlq MM7, 32;
			paddd MM7, MM0;
			movq res, MM7
			emms
			popa
		}
			mmx += res;

		printf("mmx = %ld\n", mmx);
		result = 0;
		time2 = clock();
		float assmmxtime = (float)(time2 - time1);
		printf("time work on Asm_mmx: %f ms\n", assmmxtime);
		printf("Do you want to continue? y/n: ");
		rewind(stdin);

	} while (getchar() != 'n');
	return 0;
}
