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
	getchar(); //�Է� ���� Ŭ����
	char seat[100][100]; // å�� ��ġ �迭
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			seat[i][j] = NULL;
	//char output[10000];

	int num_max = 0, lim_count[50] = { 0, };// num_max = ��ü �ο� ��, lim_count = �� �ະ �ִ� å�� ��

	printf("�ڸ� ��ġ�� �Է��Ͻʽÿ�\n>");
	bool Bbreak = false; // �ѹ��� �ΰ� break�ҋ� ���� �뵵
	for (int i = 0; i < 100; i++) //�ڸ� �Է�
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
	for (int j = 0; j < 100; j+=2) //�ڸ� ��ġ ����Ʈ�� ���� �ڸ� ���� ����
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
	printf("�ο���: %d��\n", num_max);
	//system("pause");
	printf("����Ϸ��� 1,�ٽ� �Է��Ϸ��� 0�� �Է��Ͻʽÿ�.\n>");
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
	for (int i = num_max; i >= 1; i--) // �ߺ����� ���� ����
	{
		int ran = rand() % i + 1;

		RandNum[i] = TempNum[ran];
		for (int j = ran; j <= num_max; j++)
		{
			TempNum[j] = TempNum[j + 1];
		}
	}

	printf("[�ڸ���ġǥ]\n");
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
		printf("�ڸ���ġǥ�� �����Ͻðڽ��ϱ�? ( y / n )\n>");
		scanf("%c", &TempInput2);
	} while (TempInput2 != 'y' && TempInput2 != 'n');

	if (TempInput2 == 'y')
	{
		time_t now;
		tm * curr;
		time(&now);
		curr = (localtime(&now));

		FILE* fp;
		fp = fopen("�ڸ���ġoutput.txt", "a");

		fprintf(fp,"\n[�ڸ���ġǥ(%d-%02d-%02d  %d:%02d:%02d)]\n",curr->tm_year+1900,curr->tm_mon+1,curr->tm_mday, curr->tm_hour, curr->tm_min, curr->tm_sec);
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

		printf("\n������ �����߽��ϴ�.\n");
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
	printf("��ɾ�:\nexit   ���α׷��� �����մϴ�\nhelp   ������ �ҷ��ɴϴ�\nstart  �ڸ���ġ �Է��� �����մϴ�\n");
	printf("\n\n������ 1 / 2\n");
	system("pause");
	system("cls");
	printf("�ڸ� ��ġ ��� ����:\n����:���� �ٴ� �ڸ��� ����, ����(����): ���� �������� �ڸ��� ������ �� ���\n");
	printf("��ǥ(,):���� ������ �� ���, ��ħǥ(.):��� �ڸ� �Է��� ������ �� ���\n\n�Է� ����1 >2 2 2,2 2 2,2 2 2.\n");
	printf("���:\n[ 1 ][ 2 ]  [ 3 ][ 4 ]  [ 5 ][ 6 ]\n[ 7 ][ 8 ]  [ 9 ][ 10]  [ 11][ 12]\n[ 13][ 14]  [ 15][ 16]  [ 17][ 18]");
	printf("\n\n�Է� ����2 >1 2,2 2,1 1\n");
	printf("���:\n[ 1 ]       [ 2 ][ 3 ]\n[ 4 ][ 5 ]  [ 6 ][ 7 ]\n[ 8 ]       [ 9 ]\n");
	printf("\n\n������ 2 / 2\n");
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
		printf("��ɾ �Է��Ͻʽÿ�. ������ �ʿ��ϴٸ� help�� �Է��Ͻʽÿ�.\n>");
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
			printf("�߸��� �Է��Դϴ�.\n");
		getchar();
	}

	return 0;
}