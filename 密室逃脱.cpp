#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
void move(char a[][50], char m, int* money, int* x, int* y,int* stronger)  /*控制人物移动，获得金币，拾取道具*/
{

	if (m == 's' && a[*x + 1][*y] == ' ')
	{

		a[*x][*y] = ' ';
		(*x)++;
		a[*x][*y] = 'o';
	}
	else if (m == 's'&& (a[*x + 1][*y] == '$'||a[*x + 1][*y] == '!'))
	{
		if (a[*x+1 ][*y] == '!')
		{
			(* stronger)++;
		}
		a[*x][*y] = ' ';
		(*x)++;
		a[*x][*y] = 'o';
		(*money)++;
	}
	 else if (m == 'w' && a[*x - 1][*y] == ' ')
	{

		a[*x][*y] = ' ';
		(*x)--;
		a[*x][*y] = 'o';
	}
	else if (m == 'w' && (a[*x - 1][*y] == '$'||a[*x - 1][*y] == '!'))
	{

		if (a[*x-1][*y] == '!')
		{
			(*stronger)++;
		}
		a[*x][*y] = ' ';
		(*x)--;
		a[*x][*y] = 'o';
		(*money)++;
	}
	else if (m == 'a' && a[*x][*y - 1] == ' ')
	{
		a[*x][*y] = ' ';
		(*y)--;
		a[*x][*y] = 'o';
	}
	else if (m == 'a' && (a[*x][*y - 1] == '$'|| a[*x][*y - 1] == '!'))
	{

		if (a[*x ][*y-1] == '!')
		{
			(*stronger)++;
		}
		a[*x][*y] = ' ';
		(*y)--;
		a[*x][*y] = 'o';
		(*money)++;
	}
	else if (m == 'd' && a[*x][*y + 1] == ' ')
	{
		a[*x][*y] = ' ';
		(*y)++;
		a[*x][*y] = 'o';
	}
	else if (m == 'd' &&( a[*x][*y + 1] == '$'|| a[*x][*y + 1] == '!'))
	{
		if (a[*x][*y +1] == '!')
		{
			(*stronger)++;
		}
		a[*x][*y] = ' ';
		(*y)++;
		a[*x][*y] = 'o';
		(*money)++;
	}
}
void prop(char a[][50], char m, int* x, int* y)     /*道具效果，无视#部分墙体*/
{
	
		if (m == 's'&& a[*x + 1][*y] != 'x'&& a[*x + 1][*y] != '|')
		{

			a[*x][*y] = ' ';
			(*x)++;
			a[*x][*y] = 'o';

		}
		else if (m == 'w'&& a[*x -1][*y] != 'x'&& a[*x - 1][*y] != '|')
		{

			a[*x][*y] = ' ';
			(*x)--;
			a[*x][*y] = 'o';
		}
		else if (m == 'a'&& a[*x ][*y-1] != 'x'&& a[*x][*y - 1] != '|')
		{
			a[*x][*y] = ' ';
			(*y)--;
			a[*x][*y] = 'o';
		}
		else if (m == 'd'&& a[*x ][*y+1] != 'x'&& a[*x][*y + 1] != '|')
		{
			a[*x][*y] = ' ';
			(*y)++;
			a[*x][*y] = 'o';
		}
}
void put1(char a[][50],int count,int money)     /*屏幕输出游戏场景*/
	{
		printf("剩余%d步\n金币数量：%d,你需要三个金币才能开启大门\n", 80 - count, money);
		int i = 0;
		for (i = 0; i < 12; i++)
			puts(a[i]);
	}
void introduction(int count,int money)  /*游戏介绍*/
{
	printf("请使用英文输入法！\n操作方式：上下左右=wsad\n o 代表你操作的人物， # 代表墙体,x为边界，$为金币，！为神秘道具且能增加金币数量。\n");
	Sleep(4000);
	system("cls");
	printf("游戏任务：在规定步数内，你需要捡到3个金币开启大门并走向终点为获胜\n");
	printf("温馨提示：触发道具效果后金币数量不再增加哦!\n开始你的游戏吧！\n\n\n");
	Sleep(4000);
	system("cls");
}
int main()
{
	char a[50][50] =     {"xxxxxxxxxxxxxxxxxxxxxxxxxxxx",
		                  "x o# ### # ###    ####    |  终点",
						  "x  # # $##    # ##     #  #x",
						  "x  #  #  # #  #  #   ##### x",
					  	  "x#  #  #   # $# ####    #  x",
						  "x     ##  #####     #   #  x",
						  "x ## #  # ##   # # ## ##!  x",
	                      "x#   #   $   ### # #   ### x",
		                  "x  # ###  ### #   ####     x",
		                  "x  #      #      #       # x",
		                  "x   #####   ###     ##  # #x",
	                      "xxxxxxxxxxxxxxxxxxxxxxxxxxxx"};     /*密室地图*/
	int  x = 1, y = 2;
	char ch;
	int count = 0,money=0,stronger=0;
	introduction(count, money);
	put1(a,count,money);
	
	while (x != 1 || y != 27)
	{
		ch = _getch();
		count++;
		if (stronger == 0)                          /*判定是否获取道具*/
		{	
			move(a, ch, &money, &x, &y, &stronger);
		}
		else if (stronger == 1)
		{
			prop(a, ch, &x, &y);
		}
		system("cls");
		if (money ==3&&a[1][26]!='o')        /*解锁大门判定*/
		{
			a[1][26] = ' ';
		}
		put1(a,count,money);
		if (x == 1 && y == 27)          /*逃脱成功判定*/
		{
			system("cls");
			printf("闯关成功!!!\n");
			break;
		}
		if (count >= 80)              /*逃脱失败判定*/
		{
			system("cls");
			printf("步数已用完，你输了！");
			break;
		}
	}
	Sleep(5000);
	return 0;
}

