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


int InputNumber(int *mnu_counter);/* サイズ選択 */
int Ini(int **data, int size);/* 初期化 */
int Meiro(int **data, int size);/* 迷路作成部分 */
void RoopMaker(int **data, int size);
int Print(int **data, int size);/* 出力 */
int Move(int **data, int size, int dir, struct gchar *_me);/* 動く */
int WaitKey(int *dir);/* 方向入力 */

struct Character {
	char name[255]; //名前
	int HP; //体力
	int MP; //魔力
	int DF; //防御力
	int STR; //攻撃力
	int LUCK; //運
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
	int dir; /* 方向 */
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

	/* 1次元確保 */
	if ((data = (int **)malloc(size * sizeof(int *))) == NULL)
	{
		printf("Malloc Error !!\n");
		return 2;
	}

	/* 2次元確保 */
	for (i = 0; i < size; i++)
	{
		if ((data[i] = (int *)malloc(size * sizeof(int))) == NULL)
		{
			printf("Malloc Error2 !!\n");
			return 3;
		}
	}

	/* 初期化 */
	if (Ini(data, size))
	{
		printf("初期化エラー !!\n");
		return 2;
	}

	/* 迷路作成部分 */
	if (Meiro(data, size))
	{
		printf("迷路作成エラー !!\n");
		return 2;
	}

	/* Player */
	data[me.y][me.x] = 4;

	/* GOAL */
	data[size - 2][size - 2] = 2;

	/* 出力 */
	if (Print(data, size))
	{
		printf("出力エラー !!\n");
		return 2;
	}
	printf("6:→ 2: ↓ 4: ← 8: ↑\n");
	do
	{




		if (WaitKey(&dir) != 0)
		{
			printf("Input Number Error !!\n");
			return 1;
		}

		/* 動く */
		tmp = Move(data, size, dir, &me);
		turn++;
		system("cls");
		/* 出力 */
		if (Print(data, size))
		{
			printf("出力エラー !!\n");
			return 2;
		}
		printf("6:→ 2: ↓ 4: ← 8: ↑\n");
		if (tmp == 1)
		{
			printf("その方向へは動けません。\n");
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
			printf("敵が現れた！！\n");


			rewind(stdin);
			getchar();
			system("cls");

			strcpy(enemy->name, "スライム");
			CharaSet(enemy, 40, ((12 + makeRandNum(1, 6)) * 5), (12 + makeRandNum(1, 6)), (12 + makeRandNum(1, 6)), (4 + makeRandNum(1, 6)));

			while ((PC->HP > 0) && (enemy->HP > 0)) {

				PrintChar(PC);
				PrintChar(enemy);

				printf("%sはどうする？\n", PC->name);
				PrintMenu();
				scanf("%d", &com);
				system("cls");
				switch (com) {
				case 1:Atack(PC, enemy); break;
				case 2:Guard(PC, enemy); break;
				case 3:Heal(PC, enemy); break;
				case 4:Escape(PC, enemy); break;
				default:printf("それはできない！\n"); break;
				}
			}

			if (PC->HP <= 0)
			{
				printf("%sは倒れた\n", PC->name);
				printf("GAMME OVER...\n");

				rewind(stdin);
				getchar();

				exit(0);
			}


			turn = 0;

			Print(data, size);
			printf("6:→ 2: ↓ 4: ← 8: ↑\n");
		}



	} while (data[size - 2][size - 2] != 3);

	/* メモリ開放*/
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
		printf("名前を入力してね:");
		scanf("%s", chr->name);
		printf("\n「%s」であってる？\nYES：0　NO：1\n", chr->name);
		scanf("%d", &ans);
	} while (ans == 1);


	do
	{
		printf("難易度はどうする？\n");
		printf(" 1:Easy 2:Nomal 3:Hard\n");
		scanf("%d", &enh);
		if ((enh <= 0) || (enh >= 4))
		{
			printf("三つの中から選んで！\n");
			ans = 1;
		}else {
			printf("%d番で合ってる？\nYES：0　NO：1\n", enh);
			scanf("%d", &ans);
		}
	} while (ans == 1);

	do
	{
		printf("役職を選んでね！\n");
		printf(" 1:剣士(攻撃力:高 魔力量:中 防御力:中)\n 2:騎士(攻撃力:中 魔力量:中 防御力:高)\n 3:魔術師(攻撃力:中 魔力量:高 防御力:中)\n");
		scanf("%d", &Job);
		if ((Job <= 0) || (Job >= 4))
		{
			printf("三つの中から選んで！\n");
			ans = 1;
		}
		else {
			printf("%d番で合ってる？\nYES：0　NO：1\n", Job);
			scanf("%d", &ans);
		}
	} while (ans == 1);

	

	if (Job == 1)
		CharaSet(chr, 200, ((12 + makeRandNum(1, 6)) * 5), (12 + makeRandNum(1, 6)), (18 + makeRandNum(1, 6)), (4 + makeRandNum(1, 6)));
	else if (Job == 2)
		CharaSet(chr, 200, ((12 + makeRandNum(1, 6)) * 5), (18 + makeRandNum(1, 6)), (12 + makeRandNum(1, 6)), (4 + makeRandNum(1, 6)));
	else if (Job == 3)
		CharaSet(chr, 200, ((18 + makeRandNum(1, 6)) * 5), (12 + makeRandNum(1, 6)), (12 + makeRandNum(1, 6)), (4 + makeRandNum(1, 6)));

	printf("いま %s の ぼうけん が はじまる !!!\n", chr->name);
	
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
	printf("名前:%s \n", chr->name);
	printf("HP:%7d \n", chr->HP);
	printf("MP:%7d \n", chr->MP);
	printf("防御力:%3d \n", chr->DF);
	printf("攻撃力:%3d \n", chr->STR);
	printf("運:%3d \n", chr->LUCK);
	printf("---------------------- \n");
}

void PrintMenu() {

	printf("------------\n");
	printf(" １：攻撃 \n ２：防御 \n ３：回復(MP:5) \n ４：逃げる \n");
	printf("------------\n");

}

void Atack(Character * chr, Character * enemy)
{
	int rand,Damage = chr->STR;


	printf("%sの攻撃！！\n", chr->name);

	if (makeRandNum(1, 100) <= chr->LUCK)
	{
		Damage = (chr->STR) * 2;
		printf("クリティカルヒット！\n");

	}
	rand = makeRandNum(8, 12);
	printf("%dのダメージを与えた！\n", (((Damage*Damage) / enemy->DF)*rand)/10);
	enemy->HP = enemy->HP - ((((Damage*Damage) / chr->DF)*rand / 10));
	
	if (enemy->HP <= 0)
	{
		printf("%sは倒れた\n", enemy->name);

		rewind(stdin);
		getchar();
		system("cls");

		return;
	}

	Damage = enemy->STR;

	printf("%sの攻撃！！\n", enemy->name);

	if (makeRandNum(1, 100) <= enemy->LUCK)
	{
		Damage = (enemy->STR) * 2;
		printf("クリティカルヒット！\n");

	}
	rand = makeRandNum(8, 12);
	printf("%dのダメージを与えた！\n", (((Damage*Damage) / chr->DF)*rand) / 10);
	chr->HP = chr->HP - ((((Damage*Damage) / chr->DF)*rand) / 10);

	rewind(stdin);
	getchar();

}

void Guard(Character * chr, Character * enemy)
{
	int rand;
	int Damage = enemy->STR;
	int Gua = chr->DF * 2;

	printf("%sは防御の姿勢をとった！\n", chr->name);

	
	printf("%sの攻撃！\n", enemy->name);

	if (makeRandNum(1, 100) <= enemy->LUCK)
	{
		Damage = (enemy->STR) * 2;
		printf("クリティカルヒット！\n");

	}
	rand = makeRandNum(8, 12);
	printf("%dのダメージを与えた！\n", (((Damage*Damage) / Gua)*rand) / 10);
	chr->HP = chr->HP - ((((Damage*Damage) / Gua)*rand) / 10);

	rewind(stdin);
	getchar();
}

void Heal(Character * chr, Character * enemy)
{
	int rand;
	int Damage = chr->STR;


	printf("%sは回復した！\n", chr->name);
	rand = makeRandNum(8, 12);
	chr->MP = chr->MP - 5;
	chr->HP = chr->HP + (((((Damage*Damage) / chr->DF)*rand) / 10)*2);
	if (chr->HP > 200)
	{
		chr->HP = 200;
	}
	printf("1のHPが%dになった\n",chr->HP);


	printf("%sの攻撃！！\n", enemy->name);

	Damage = enemy->STR;

	if (makeRandNum(1, 100) <= enemy->LUCK)
	{
		Damage = (enemy->STR) * 2;
		printf("クリティカルヒット！\n");

	}
	rand = makeRandNum(8, 12);
	printf("%dのダメージを与えた！\n", (((Damage*Damage) / chr->DF)*rand) / 10);
	chr->HP = chr->HP - ((((Damage*Damage) / chr->DF)*rand) / 10);
	
	rewind(stdin);
	getchar();
}

void Escape(Character * chr, Character * enemy)
{
	int rand;
	int Damage = enemy->STR;
	int Esc;

	printf("%sは逃げ出した！\n", chr->name);
	Esc = chr->LUCK * 8;

	if (makeRandNum(1, 100) <= Esc)
	{
		enemy->HP = 0;

		rewind(stdin);
		getchar();
		system("cls");

		return;
	}

	printf("しかし逃げられなかった！\n");

	printf("%sの攻撃！！\n", enemy->name);

	if (makeRandNum(1, 100) <= enemy->LUCK)
	{
		Damage = (enemy->STR) * 2;
		printf("クリティカルヒット！\n");

	}
	rand = makeRandNum(8, 12);
	printf("%dのダメージを与えた！\n", (((Damage*Damage) / chr->DF)*rand) / 10);
	chr->HP = chr->HP - ((((Damage*Damage) / chr->DF)*rand) / 10);

	rewind(stdin);
	getchar();
}

/* サイズ選択 */
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

/* 初期化 */
int Ini(int **data, int size)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			/* 外枠かどうか */
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
			/* 外枠の場合 */
			else
			{
				data[i][j] = 0;
			}
		}
	}

	return 0;
}

/* 迷路作成部分 */
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

/* 出力 */
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
				printf("■");
				break;
			case 1:
				printf("・");
				break;
			case 2:
				printf("Ｇ");
				break;
			case 3:
				printf("　");
				break;
			default:
				printf("人");
			}
		}
		printf("\n");
	}

	return 0;
}

/* 動く */
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

/* 方向 */
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
