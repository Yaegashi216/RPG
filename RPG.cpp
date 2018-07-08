#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <conio.h>

int makeRandNum(int min, int max);
int SetUp(struct Character *chr);
void CharaSet(struct Character *chr, int hp, int mp, int df, int str, int luck);
void PrintChar(struct Character *chr);
void PrintMenu();
void Atack(struct Character *chr, struct Character *enemy);
void Guard(struct Character *chr, struct Character *enemy);
void Heal(struct Character *chr, struct Character *enemy);
void Escape(struct Character *chr, struct Character *enemy);


int InputNumber(int *mnu_counter);/* �T�C�Y�I�� */
int Ini(int **data, int size);/* ������ */
int Meiro(int **data, int size);/* ���H�쐬���� */
void RoopMaker(int **data, int size);
int Print(int **data, int size);/* �o�� */
int Move(int **data, int size, int dir, struct gchar *_me);/* ���� */
int WaitKey(int *dir);/* �������� */

struct Character {
	char name[255]; //���O
	int HP; //�̗�
	int MP; //����
	int DF; //�h���
	int STR; //�U����
	int LUCK; //�^
};

struct gchar
{
	int x, y;
};

int main()
{
	int enh, com;

	struct Character *PC;
	struct Character *enemy;

	PC = (struct Character*)malloc(sizeof(struct Character));
	enemy = (struct Character*)malloc(sizeof(struct Character));
	

	int **data;
	int i;
	int size;
	int dir; /* ���� */
	int turn = 0;

	int tmp = 0;
	struct gchar *enemys;
	struct gchar me = { 1, 1 };

	srand((unsigned int)time(NULL));

	enh = SetUp(PC);

	rewind(stdin);
	getchar();

	if (enh == 1)
		size = 15;
	else if(enh == 2)
		size = 23;
	else if(enh == 3)
		size = 33;

	system("cls");

	/* 1�����m�� */
	if ((data = (int **)malloc(size * sizeof(int *))) == NULL)
	{
		printf("Malloc Error !!\n");
		return 2;
	}

	/* 2�����m�� */
	for (i = 0; i < size; i++)
	{
		if ((data[i] = (int *)malloc(size * sizeof(int))) == NULL)
		{
			printf("Malloc Error2 !!\n");
			return 3;
		}
	}

	/* ������ */
	if (Ini(data, size))
	{
		printf("�������G���[ !!\n");
		return 2;
	}

	/* ���H�쐬���� */
	if (Meiro(data, size))
	{
		printf("���H�쐬�G���[ !!\n");
		return 2;
	}

	/* Player */
	data[me.y][me.x] = 4;

	/* GOAL */
	data[size - 2][size - 2] = 2;

	/* �o�� */
	if (Print(data, size))
	{
		printf("�o�̓G���[ !!\n");
		return 2;
	}
	printf("6:�� 2: �� 4: �� 8: ��\n");
	do
	{




		if (WaitKey(&dir) != 0)
		{
			printf("Input Number Error !!\n");
			return 1;
		}

		/* ���� */
		tmp = Move(data, size, dir, &me);
		turn++;
		system("cls");
		/* �o�� */
		if (Print(data, size))
		{
			printf("�o�̓G���[ !!\n");
			return 2;
		}
		printf("6:�� 2: �� 4: �� 8: ��\n");
		if (tmp == 1)
		{
			printf("���̕����ւ͓����܂���B\n");
		}
		else if (tmp == 0 && data[size - 2][size - 2] == 4)
		{
			printf("Goal !!\n");
		}
		else if (tmp == 0)
		{
			printf("\n");
		}
		else if (tmp != 0)
		{
			printf("Move Error !!Error Number % d\n", tmp);
			return 2;
		}

		if (makeRandNum(1, 100) <= (turn * 10)) {
			printf("�G�����ꂽ�I�I\n");


			rewind(stdin);
			getchar();
			system("cls");

			strcpy(enemy->name, "�X���C��");
			CharaSet(enemy, 40, ((12 + makeRandNum(1, 6)) * 5), (12 + makeRandNum(1, 6)), (12 + makeRandNum(1, 6)), (4 + makeRandNum(1, 6)));

			while ((PC->HP > 0) && (enemy->HP > 0)) {

				PrintChar(PC);
				PrintChar(enemy);

				printf("%s�͂ǂ�����H\n", PC->name);
				PrintMenu();
				scanf("%d", &com);
				system("cls");
				switch (com) {
				case 1:Atack(PC, enemy); break;
				case 2:Guard(PC, enemy); break;
				case 3:Heal(PC, enemy); break;
				case 4:Escape(PC, enemy); break;
				default:printf("����͂ł��Ȃ��I\n"); break;
				}
			}

			if (PC->HP <= 0)
			{
				printf("%s�͓|�ꂽ\n", PC->name);
				printf("GAMME OVER...\n");

				rewind(stdin);
				getchar();

				exit(0);
			}


			turn = 0;

			Print(data, size);
			printf("6:�� 2: �� 4: �� 8: ��\n");
		}



	} while (data[size - 2][size - 2] != 3);

	/* �������J��*/
	for (i = 0; i < size; i++)
	{
		free(data[i]);
	}
	free(data);

	return 0;

	free(PC);
	
	free(enemy);
}

int makeRandNum(int min, int max)
{
	return(min + (int)(rand()*(max - min + 1.0) / (RAND_MAX + 1.0)));
}

int SetUp(struct Character *chr)
{
	int Job, enh, ans = 1;

	do
	{
		printf("���O����͂��Ă�:");
		scanf("%s", chr->name);
		printf("\n�u%s�v�ł����Ă�H\nYES�F0�@NO�F1\n", chr->name);
		scanf("%d", &ans);
	} while (ans == 1);


	do
	{
		printf("��Փx�͂ǂ�����H\n");
		printf(" 1:Easy 2:Nomal 3:Hard\n");
		scanf("%d", &enh);
		if ((enh <= 0) || (enh >= 4))
		{
			printf("�O�̒�����I��ŁI\n");
			ans = 1;
		}else {
			printf("%d�Ԃō����Ă�H\nYES�F0�@NO�F1\n", enh);
			scanf("%d", &ans);
		}
	} while (ans == 1);

	do
	{
		printf("��E��I��łˁI\n");
		printf(" 1:���m(�U����:�� ���͗�:�� �h���:��)\n 2:�R�m(�U����:�� ���͗�:�� �h���:��)\n 3:���p�t(�U����:�� ���͗�:�� �h���:��)\n");
		scanf("%d", &Job);
		if ((Job <= 0) || (Job >= 4))
		{
			printf("�O�̒�����I��ŁI\n");
			ans = 1;
		}
		else {
			printf("%d�Ԃō����Ă�H\nYES�F0�@NO�F1\n", Job);
			scanf("%d", &ans);
		}
	} while (ans == 1);

	

	if (Job == 1)
		CharaSet(chr, 200, ((12 + makeRandNum(1, 6)) * 5), (12 + makeRandNum(1, 6)), (18 + makeRandNum(1, 6)), (4 + makeRandNum(1, 6)));
	else if (Job == 2)
		CharaSet(chr, 200, ((12 + makeRandNum(1, 6)) * 5), (18 + makeRandNum(1, 6)), (12 + makeRandNum(1, 6)), (4 + makeRandNum(1, 6)));
	else if (Job == 3)
		CharaSet(chr, 200, ((18 + makeRandNum(1, 6)) * 5), (12 + makeRandNum(1, 6)), (12 + makeRandNum(1, 6)), (4 + makeRandNum(1, 6)));

	printf("���� %s �� �ڂ����� �� �͂��܂� !!!\n", chr->name);
	
	PrintChar(chr);

	return enh;
}

void CharaSet(struct Character *chr, int hp, int mp, int df, int str, int luck)
{
	chr->HP = hp;
	chr->MP = mp;
	chr->DF= df;
	chr->STR = str;
	chr->LUCK = luck;
}

void PrintChar(struct Character *chr)
{

	printf("---------------------- \n");
	printf("���O:%s \n", chr->name);
	printf("HP:%7d \n", chr->HP);
	printf("MP:%7d \n", chr->MP);
	printf("�h���:%3d \n", chr->DF);
	printf("�U����:%3d \n", chr->STR);
	printf("�^:%3d \n", chr->LUCK);
	printf("---------------------- \n");
}

void PrintMenu() {

	printf("------------\n");
	printf(" �P�F�U�� \n �Q�F�h�� \n �R�F��(MP:5) \n �S�F������ \n");
	printf("------------\n");

}

void Atack(Character * chr, Character * enemy)
{
	int rand,Damage = chr->STR;


	printf("%s�̍U���I�I\n", chr->name);

	if (makeRandNum(1, 100) <= chr->LUCK)
	{
		Damage = (chr->STR) * 2;
		printf("�N���e�B�J���q�b�g�I\n");

	}
	rand = makeRandNum(8, 12);
	printf("%d�̃_���[�W��^�����I\n", (((Damage*Damage) / enemy->DF)*rand)/10);
	enemy->HP = enemy->HP - ((((Damage*Damage) / chr->DF)*rand / 10));
	
	if (enemy->HP <= 0)
	{
		printf("%s�͓|�ꂽ\n", enemy->name);

		rewind(stdin);
		getchar();
		system("cls");

		return;
	}

	Damage = enemy->STR;

	printf("%s�̍U���I�I\n", enemy->name);

	if (makeRandNum(1, 100) <= enemy->LUCK)
	{
		Damage = (enemy->STR) * 2;
		printf("�N���e�B�J���q�b�g�I\n");

	}
	rand = makeRandNum(8, 12);
	printf("%d�̃_���[�W��^�����I\n", (((Damage*Damage) / chr->DF)*rand) / 10);
	chr->HP = chr->HP - ((((Damage*Damage) / chr->DF)*rand) / 10);

	rewind(stdin);
	getchar();

}

void Guard(Character * chr, Character * enemy)
{
	int rand;
	int Damage = enemy->STR;
	int Gua = chr->DF * 2;

	printf("%s�͖h��̎p�����Ƃ����I\n", chr->name);

	
	printf("%s�̍U���I\n", enemy->name);

	if (makeRandNum(1, 100) <= enemy->LUCK)
	{
		Damage = (enemy->STR) * 2;
		printf("�N���e�B�J���q�b�g�I\n");

	}
	rand = makeRandNum(8, 12);
	printf("%d�̃_���[�W��^�����I\n", (((Damage*Damage) / Gua)*rand) / 10);
	chr->HP = chr->HP - ((((Damage*Damage) / Gua)*rand) / 10);

	rewind(stdin);
	getchar();
}

void Heal(Character * chr, Character * enemy)
{
	int rand;
	int Damage = chr->STR;


	printf("%s�͉񕜂����I\n", chr->name);
	rand = makeRandNum(8, 12);
	chr->MP = chr->MP - 5;
	chr->HP = chr->HP + (((((Damage*Damage) / chr->DF)*rand) / 10)*2);
	if (chr->HP > 200)
	{
		chr->HP = 200;
	}
	printf("1��HP��%d�ɂȂ���\n",chr->HP);


	printf("%s�̍U���I�I\n", enemy->name);

	Damage = enemy->STR;

	if (makeRandNum(1, 100) <= enemy->LUCK)
	{
		Damage = (enemy->STR) * 2;
		printf("�N���e�B�J���q�b�g�I\n");

	}
	rand = makeRandNum(8, 12);
	printf("%d�̃_���[�W��^�����I\n", (((Damage*Damage) / chr->DF)*rand) / 10);
	chr->HP = chr->HP - ((((Damage*Damage) / chr->DF)*rand) / 10);
	
	rewind(stdin);
	getchar();
}

void Escape(Character * chr, Character * enemy)
{
	int rand;
	int Damage = enemy->STR;
	int Esc;

	printf("%s�͓����o�����I\n", chr->name);
	Esc = chr->LUCK * 8;

	if (makeRandNum(1, 100) <= Esc)
	{
		enemy->HP = 0;

		rewind(stdin);
		getchar();
		system("cls");

		return;
	}

	printf("�������������Ȃ������I\n");

	printf("%s�̍U���I�I\n", enemy->name);

	if (makeRandNum(1, 100) <= enemy->LUCK)
	{
		Damage = (enemy->STR) * 2;
		printf("�N���e�B�J���q�b�g�I\n");

	}
	rand = makeRandNum(8, 12);
	printf("%d�̃_���[�W��^�����I\n", (((Damage*Damage) / chr->DF)*rand) / 10);
	chr->HP = chr->HP - ((((Damage*Damage) / chr->DF)*rand) / 10);

	rewind(stdin);
	getchar();
}

/* �T�C�Y�I�� */
int InputNumber(int *mnu_counter)
{
	char *ch;
	if ((ch = (char *)malloc(256 * sizeof(char))) == NULL)
	{
		printf("Malloc Error !!\n");
		return 1;
	}

	scanf("%15d", &*mnu_counter);
	gets_s(ch, 15);
	free(ch);

	return 0;
}

/* ������ */
int Ini(int **data, int size)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			/* �O�g���ǂ��� */
			if (i != 0 && j != 0 && i != size - 1 && j != size - 1)
			{
				if (i % 2 == 1 || j % 2 == 1)
				{
					data[i][j] = 1;
				}
				else
				{
					data[i][j] = 0;
				}
			}
			/* �O�g�̏ꍇ */
			else
			{
				data[i][j] = 0;
			}
		}
	}

	return 0;
}

/* ���H�쐬���� */
int Meiro(int **data, int size)
{
	int i, j;
	int ran;

	srand((unsigned)time(NULL));

	for (i = 2; i < size - 2; i = i + 2)
	{
		for (j = 2; j < size - 2; j = j + 2)
		{
			if (i == 2)
			{
				ran = rand() % 4;
				if (ran == 0)
				{
					data[i - 1][j] = 0;
				}
				else if (ran == 1)
				{
					data[i][j + 1] = 0;
				}
				else if (ran == 2)
				{
					data[i + 1][j] = 0;
				}
				else
				{
					data[i][j - 1] = 0;
				}
			}
			else
			{
				ran = rand() % 3;
				if (ran == 0)
				{
					data[i][j + 1] = 0;
				}
				else if (ran == 1)
				{
					data[i + 1][j] = 0;
				}
				else
				{
					data[i][j - 1] = 0;
				}
			}
		}
	}
	//RoopMaker(data,size);
	return 0;
}

void RoopMaker(int **data, int size)
{
	int k;
	int ranx, rany;
	int rnum;

	srand((unsigned)time(NULL));

	rnum = rand() % (size * size / 3);
	for (k = 0; k < rnum; k++)
	{
		ranx = rand() % size;
		rany = rand() % size;
		if (ranx != 0 && rany != 0 && ranx != size - 1 && rany != size - 1)
		{
			if (data[ranx][rany] == 0)
			{
				data[ranx][rany] = 1;
			}
		}
	}
}

/* �o�� */
int Print(int **data, int size)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			switch (data[i][j])
			{
			case 0:
				printf("��");
				break;
			case 1:
				printf("�E");
				break;
			case 2:
				printf("�f");
				break;
			case 3:
				printf("�@");
				break;
			default:
				printf("�l");
			}
		}
		printf("\n");
	}

	return 0;
}

/* ���� */
int Move(int **data, int size, int dir, struct gchar *mychar)
{
	int x, y;
	x = mychar->x;
	y = mychar->y;
	if (dir == 6 || dir == 0x4d)
	{
		if (data[y][x + 1] == 1 || data[y][x + 1] == 2 || data[y][x + 1] == 3)
		{
			data[y][x] = 3;
			data[y][x + 1] = 4;
			mychar->x = x + 1;
		}
		else if (data[y][x + 1] == 0)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else if (dir == 2 || dir == 0x50)
	{
		if (data[y + 1][x] == 1 || data[y + 1][x] == 2 || data[y + 1][x] == 3)
		{
			data[y][x] = 3;
			data[y + 1][x] = 4;
			mychar->y = y + 1;
		}
		else if (data[y + 1][x] == 0)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else if (dir == 4 || dir == 0x4b)
	{
		if (data[y][x - 1] == 1 || data[y][x - 1] == 2 || data[y][x - 1] == 3)
		{
			data[y][x] = 3;
			data[y][x - 1] = 4;
			mychar->x = x - 1;
		}
		else if (data[y][x - 1] == 0)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else if (dir == 8 || dir == 0x48)
	{
		if (data[y - 1][x] == 1 || data[y - 1][x] == 2 || data[y - 1][x] == 3)
		{
			data[y][x] = 3;
			data[y - 1][x] = 4;
			mychar->y = y - 1;
		}
		else if (data[y - 1][x] == 0)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	return 0;
}

/* ���� */
int WaitKey(int *dir)
{
	char tmpch;

	do
	{
		tmpch = _getch();
	} while (tmpch != '2' && tmpch != '4' && tmpch != '6' && tmpch != '8' && tmpch != 0x4b && tmpch != 0x50 && tmpch != 0x4d && tmpch != 0x48);

	if (tmpch == '2' || tmpch == '4' || tmpch == '6' || tmpch == '8')
	{
		*dir = (int)tmpch - 48;
	}
	else
	{
		*dir = (int)tmpch;
	}

	return 0;
}
