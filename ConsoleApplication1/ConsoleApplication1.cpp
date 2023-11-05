/* LittleFall : Hello! */
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using Song = std::vector<std::pair<int, int>>;

/*** 数据结构部分 */

/** 预设常数:行,列,延时单位,最大游戏时间 */
const int R = 4, C = 20, LAG = 1000000, T = 1000;

/** 运行数据 */
char gameMap[R + 1][C + 1]; /* 游戏地图 */
int gameRunTime = 0; 	/* 游戏运行时间 */
int score = 0; 			/* 游戏分数 */
int maxScore = 0;			/* 历史最高分 */
int gameClass = 0;		/* 游戏选项 */

/** 使用队列记录音乐块 */
int block[R + 1][T], lim[R + 1];
void push(int r)
{
	block[r][lim[r]++] = gameRunTime;
}

/** 音乐播放模块,两只老虎 */
const int mnote[] = { 300,440,495,550,587,660,733,825,325 };
const Song TwinTiger =
{
	{1,4},{2,4},{3,4},{1,4},
	{1,4},{2,4},{3,4},{1,4},
	{3,4},{4,4},{5,4},{0,4},
	{3,4},{4,4},{5,4},{0,4},
	{5,3},{6,1},{5,3},{4,1},{3,4},{1,4},
	{5,3},{6,1},{5,3},{4,1},{3,4},{1,4},
	{3,4},{8,4},{1,4},{0,4},
	{3,4},{8,4},{1,4},{0,4},
};
int getRythm(int id) /* 由预设音乐得到音乐块位置,可设为随机数 */
{
	return (TwinTiger[id % TwinTiger.size()].first) % R + 1;
}
void playNote(int id) /* 播放音符 */
{
	int val = id % TwinTiger.size();
	Beep(mnote[TwinTiger[val].first], TwinTiger[val].second * 100);
}

/*** 流程算法部分 */

/** 初始化游戏 */
void init()
{
	gameRunTime = 0;
	score = 0;
	memset(lim, 0, sizeof(lim));
	memset(gameMap, ' ', sizeof(gameMap));
	memset(block, 0, sizeof(block));
}

/* 按键检测 */
int checkFail()
{
	while (_kbhit())
	{
		int row = _getch() - '0';

		if (gameMap[row][1] != ' ')
		{
			playNote(score++);
			gameMap[row][1] = ' ';
		}
		else
		{
			return 1;
		}
	}
	for (int r = 1; r <= R; ++r)
	{
		if (gameMap[r][1] != ' ')
		{
			return 1;
		}
	}
	return 0;
}

/** 界面显示 */
void delay(int t) /* 延时函数 */
{
	while (t--) for (int i = 0; i < LAG; ++i);
}
void showText() /* 展示界面 */
{
	system("cls");
	for (int r = 1; r <= R; ++r)
	{
		for (int c = 1; c <= C; ++c)
			putchar(gameMap[r][c]);
		putchar('\n');
	}
}
void printc(int r, int c, char ch) /* 在界面上打印字符 */
{
	gameMap[r][c] = ch;
	showText();
}
void prints(int r, int c, const char* str, int lag = 0) /*在界面上打印字符串*/
{
	if (lag == 0)
	{
		for (int i = 0; str[i]; ++i)
			gameMap[r][c + i] = str[i];
		showText();
	}
	else for (int i = 0; str[i]; ++i)
	{
		printc(r, c + i, str[i]);
		delay(lag);
	}
}
void showMap() /* 计算每个音乐块的位置并展示 */
{
	memset(gameMap, ' ', sizeof(gameMap));
	for (int r = 1; r <= R; ++r)
	{
		for (int i = lim[r] - 1; i >= 0 && block[r][i] - gameRunTime + C >= 1; --i)
		{
			gameMap[r][block[r][i] - gameRunTime + C] = '*';
			if (gameMap[r][1] != ' ')
				gameMap[r][1] = '#';
		}
	}
	showText();
	printf("%d\n", score);
}


/** 选歌功能
 */
void chooseSongs(int now)
{
	gameClass = now;

	memset(gameMap, 0, sizeof(gameMap));
	prints(2, 3, "Choose Songs:");
	if (now == 0)
		prints(4, 1, "←  Twin Tigers  →");
	else
		prints(4, 1, "←TwinTigerEndless→");

	while (_kbhit()) _getch();
	if (_getch() == 13)
		return;
	else
		return chooseSongs(now ^ 1);
}

int main(void)
{
	while (1)
	{
		init();
		prints(2, 3, "RythmMaster 1.0", 10);
		prints(4, 1, "Press Enter To Start", 10);
		_getch();

		chooseSongs(0);

		int fail = 0;
		for (++gameRunTime;
			gameRunTime < T && (gameClass == 1 || score < (int)TwinTiger.size());
			++gameRunTime)
		{
			if (gameRunTime % 2 == 0)
				push(getRythm(gameRunTime / 2));
			showMap();

			delay(gameRunTime < C - 3 ? 50 : 300); //延迟,缩短无用时间

			if (checkFail())
			{
				fail = 1;
				break;
			}
		}

		maxScore = max(score, maxScore);
		if (fail)
		{
			Beep(400, 1200); //失败提示
			printf("Your Score : %d\nMax  Score : %d\n", score, maxScore);
		}
		else
		{
			Beep(700, 20);
			printf("Well Done!\n");
			printf("Your Score : %d\n", score);
		}
		printf("Press any key to continue\n");
		while (_kbhit()) _getch();
		_getch();
	}
	system("pause");
	return 0;
}