#include "game.h"

void Display(char arr[COLS][ROWS], int col, int row) //打印雷盘
{
	int i = 0;
	int j = 0;
	printf(" ");
	for (i = 1; i < col-1; ++i) //打印显示行坐标提示
	{
		printf("%2d ", i);
	}

	printf("\n");

	for (i = 1; i < col - 1; ++i)
	{
		printf("%d", i); //打印显示列坐标提示
		for (j = 1; j < row - 1; ++j)
		{
			printf("%2c ", arr[i][j]);
		}
		printf("\n");
	}
}

void set_mine(char mine[COLS][ROWS], int col, int row) //设置雷
{
	
	int count = MAX;
	while (count)
	{
		int i = rand() % (col - 2) + 1;
		int j = rand() % (row - 2) + 1;
		if (mine[i][j] != '1')
		{
			mine[i][j] = '1';
			count--;
		}
	}
}

void reset_mine(char mine[COLS][ROWS], int col, int row, int x, int y)  //重新设置雷
{
	mine[x][y] = '0';
	int count = 1;
	while (count)
	{
		int i = rand() % (col - 2) + 1;
		int j = rand() % (row - 2) + 1;
		if ((mine[i][j] != '1') && (i != x) && (j != y))
		{
			mine[i][j] = '1';
			count--;
		}
	}
}

int get_mine_count(char mine[COLS][ROWS], int x, int y)  //计算坐标（x，y）周围八个位置雷的个数并以int型返回
{
	return mine[x+1][y  ] +
		   mine[x+1][y-1] +
		   mine[x  ][y-1] +
		   mine[x-1][y-1] +
		   mine[x-1][y  ] +
		   mine[x-1][y+1] +
		   mine[x  ][y+1] +
		   mine[x+1][y+1] -8 * '0';
}

void extend(char mine[COLS][ROWS], int x, int y, int* win, char show[COLS][ROWS]) //排雷扩展
{
	int i = -1;
	int j = -1;
	for (i = -1; i < 2; ++i)
	{
		for (j = -1; j < 2; ++j)
		{
			if ((i != 0) || (j != 0))   
			{
				if (x + i >= 1 && x + i <= COLS-2 && y + j >= 1 && y + j <= ROWS-2)  
				{
					if (show[x + i][y + j] == '*')
					{
						int count = get_mine_count(mine, x + i, y + j);
						if (count != 0)
						{
							show[x + i][y + j] = count + '0';
							(*win)++;
						}
						else if (0 == count)
						{
							show[x + i][y + j] = '0';
							(*win)++;
							extend(mine, x + i, y + j, win, show);
						}
					}
				}
			}
		}
	}
}
