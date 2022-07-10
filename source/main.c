#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct tm tm;

void seatMake()
{
	system("cls");
	getchar(); //입력 버퍼 클리어
	char seat[100][100]; // 책상 배치 배열
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			seat[i][j] = NULL;
	//char output[10000];

	int num_max = 0, lim_count[50] = { 0, };// num_max = 전체 인원 수, lim_count = 각 행별 최대 책상 수

	printf("자리 배치를 입력하십시오\n>");
	bool Bbreak = false; // 한번에 두개 break할떄 쓰는 용도
	for (int i = 0; i < 100; i++) //자리 입력
	{
		for (int j = 0; j < 100; j++)
		{
			scanf("%c", &seat[i][j]);
			if (seat[i][j] == '.')
			{
				Bbreak = true;
				for (int k = 0; k < 100; k++)
				{
					seat[i + 1][k] = '.';
				}
				break;
			}
			else if (seat[i][j] == ',') break;
		}
		if (Bbreak == true) break;
	}
	
	Bbreak = false;
	for (int j = 0; j < 100; j+=2) //자리 배치 프린트용 열별 자리 갯수 세기
	{
		for (int i = 0; i < 100; i++)
		{
			if (seat[i][j] == '.')break;
			else if(seat[i][j] != NULL)
			{
				if (seat[i][j] - 48 > lim_count[j/2]) lim_count[j/2] = seat[i][j] - 48;

				num_max+= seat[i][j] - 48;
			}
		}
	}

	/*DEBUG
	printf("%d, ", num_max);
	for (int i = 0; i < 50; i++)
	{
		printf("%d",lim_count[i]);
	}*/

	Bbreak = false;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j+=2)
		{
			if (seat[i][j] == NULL) break;
			if (seat[i][j] == '.')
			{
				Bbreak = true;
				break;
			}
			for (int k = 0; k < lim_count[j / 2]; k++)
			{
				if (k+1 <= seat[i][j]-48)
					printf("[ o ]");
				else
					printf("     ");
			}
			printf("  ");
		}
		printf("\n");
		if (Bbreak == true) break;
	}
	printf("인원수: %d명\n", num_max);
	//system("pause");
	printf("계속하려면 1,다시 입력하려면 0을 입력하십시오.\n>");
	int TempInput;
	scanf("%d", &TempInput);
	if (!(bool)TempInput)
	{
		system("cls");
		seatMake();
		return;
	}
	system("cls");

	int TempNum[10000] = { 0, };
	for (int i = 0; i <= num_max; i++)
	{
		TempNum[i] = i;
	}
	srand(time(NULL));
	int RandNum[10000] = { 0, };
	for (int i = num_max; i >= 1; i--) // 중복없는 난수 생성
	{
		int ran = rand() % i + 1;

		RandNum[i] = TempNum[ran];
		for (int j = ran; j <= num_max; j++)
		{
			TempNum[j] = TempNum[j + 1];
		}
	}

	printf("[자리배치표]\n");
	int countRandNum = 1;
	Bbreak = false;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j += 2)
		{
			if (seat[i][j] == NULL) break;
			if (seat[i][j] == '.')
			{
				Bbreak = true;
				break;
			}
			for (int k = 0; k < lim_count[j / 2]; k++)
			{
				if (k + 1 <= seat[i][j] - 48)
				{
					if (RandNum[countRandNum] >= 10)
					{
						if(RandNum[countRandNum]>=100)
							printf("[%d]",RandNum[countRandNum]);
						else
							printf("[ %d]", RandNum[countRandNum]);
					}
					else
						printf("[ %d ]", RandNum[countRandNum]);
					countRandNum++;
				}
				else
					printf("     ");
			}
			printf("  ");
		}
		printf("\n");
		if (Bbreak == true) break;
	}
	
	char TempInput2 = '.';
	do
	{
		getchar();
		printf("자리배치표를 저장하시겠습니까? ( y / n )\n>");
		scanf("%c", &TempInput2);
	} while (TempInput2 != 'y' && TempInput2 != 'n');

	if (TempInput2 == 'y')
	{
		time_t now;
		tm * curr;
		time(&now);
		curr = (localtime(&now));

		FILE* fp;
		fp = fopen("자리배치output.txt", "a");

		fprintf(fp,"\n[자리배치표(%d-%02d-%02d  %d:%02d:%02d)]\n",curr->tm_year+1900,curr->tm_mon+1,curr->tm_mday, curr->tm_hour, curr->tm_min, curr->tm_sec);
		int countRandNum = 1;
		Bbreak = false;
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j += 2)
			{
				if (seat[i][j] == NULL) break;
				if (seat[i][j] == '.')
				{
					Bbreak = true;
					break;
				}
				for (int k = 0; k < lim_count[j / 2]; k++)
				{
					if (k + 1 <= seat[i][j] - 48)
					{
						if (RandNum[countRandNum] >= 10)
						{
							if (RandNum[countRandNum] >= 100)
								fprintf(fp, "[%d]", RandNum[countRandNum]);
							else
								fprintf(fp, "[ %d]", RandNum[countRandNum]);
						}
						else
							fprintf(fp, "[ %d ]", RandNum[countRandNum]);
						countRandNum++;
					}
					else
						fputs("     ",fp);
				}
				fputs("  ",fp);
			}
			fputs("\n",fp);
			if (Bbreak == true) break;
		}

		fclose(fp);

		printf("\n파일을 저장했습니다.\n");
		system("pause");
		system("cls");
	}
	else
	{
		system("pause");
		system("cls");
	}
	return;
}

void howTo()
{
	system("cls");
	printf("명령어:\nexit   프로그램을 종료합니다\nhelp   도움말을 불러옵니다\nstart  자리배치 입력을 시작합니다\n");
	printf("\n\n페이지 1 / 2\n");
	system("pause");
	system("cls");
	printf("자리 배치 사용 설명서:\n숫자:같이 붙는 자리의 갯수, 공백(띄어쓰기): 같은 열끼리의 자리를 구분할 때 사용\n");
	printf("쉼표(,):행을 구분할 때 사용, 마침표(.):모든 자리 입력이 끝났을 때 사용\n\n입력 예시1 >2 2 2,2 2 2,2 2 2.\n");
	printf("결과:\n[ 1 ][ 2 ]  [ 3 ][ 4 ]  [ 5 ][ 6 ]\n[ 7 ][ 8 ]  [ 9 ][ 10]  [ 11][ 12]\n[ 13][ 14]  [ 15][ 16]  [ 17][ 18]");
	printf("\n\n입력 예시2 >1 2,2 2,1 1\n");
	printf("결과:\n[ 1 ]       [ 2 ][ 3 ]\n[ 4 ][ 5 ]  [ 6 ][ 7 ]\n[ 8 ]       [ 9 ]\n");
	printf("\n\n페이지 2 / 2\n");
	system("pause");
	system("cls");
	return;
}

int main(void)
{
	char input[10];
	while (true)
	{
		for (int i = 0; i < 10; i++) input[i] = NULL;
		printf("명령어를 입력하십시오. 도움말이 필요하다면 help를 입력하십시오.\n>");
		scanf("%s", &input);
		if (!strcmp(input, "help"))
			howTo();
		else if (!strcmp(input, "exit"))
			break;
		else if (!strcmp(input, "start"))
		{
			printf("work in progress. . .\n");
			seatMake();
		}
		else if (!strcmp(input, "cls"))
			system("cls");
		else
			printf("잘못된 입력입니다.\n");
		getchar();
	}

	return 0;
}