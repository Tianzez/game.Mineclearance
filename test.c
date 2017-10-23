#include "game.h"


void game()
{
	int x = 0;
	int y = 0;
	int win = 0;   //记录找到非雷位置的次数
	//srand((unsigned int)time(NULL));             //随机数种子
	char mine[COLS][ROWS] = { '0' };
	memset(mine, '0', COLS*ROWS*sizeof(mine[0][0])); //利用memset函数把雷盘每个位置初始化为字符‘0’

	char show[COLS][ROWS] = { '0' };
	memset(show, '*', COLS*ROWS*sizeof(show[0][0]));   //把显示盘的每个位置初始化为字符‘*’
	Display(show,COLS,ROWS);

	printf("\n");

	set_mine(mine, COLS, ROWS);          //布雷，把MIX颗雷随机分布在雷盘中
	Display(mine, COLS, ROWS);

	while ( win<( (COLS-2)*(ROWS-2)-MAX ) )             //开始玩游戏的循环
	{
		printf("请输入排雷坐标：");
		scanf_s("%d%d", &x, &y);
		if ((x >= 1) && (x <= COLS-2) && (y >= 1) && (y <= ROWS-2))
		{
			if (show[x][y] == '*')
			{
				if (mine[x][y] == '1')
				{
					if (0 == win)  //如果第一次就踩到雷，为了玩家的游戏体验，把这个雷移走
					{
						reset_mine(mine,COLS,ROWS,x,y);   
						int count = get_mine_count(mine, x, y);
						if (count != 0)           //该位置有雷，那就不进行扩展
						{
							show[x][y] = count + '0';
							win++;
							system("cls");
							Display(show, COLS, ROWS);
						}
						else
						{
							show[x][y] = '0';
							win++;
							extend(mine, x, y, &win, show);
							system("cls");
							Display(show, COLS, ROWS);
						}
					}
					else
					{
						printf("你炸了，游戏结束！\n");  //非第一步踩到雷，游戏结束
						Display(mine, COLS, ROWS);
						break;
					}	
				}
				else
				{
					int count = get_mine_count(mine, x, y);
					if (count != 0)           //该位置有雷，那就不进行扩展
					{
						show[x][y] = count + '0';
						win++;
						system("cls");
						Display(show, COLS, ROWS);
					}
					else
					{
						show[x][y] = '0';
						win++;
						extend(mine, x, y, &win, show);
						system("cls");
						Display(show, COLS, ROWS);
					}			
				}
			}
			else
			{
				printf("这个位置已排查，请重新选择坐标\n");
			}
		}
		else
		{
			printf("坐标不合法，请重新输入\n");
		}
	}
	if (win == ((COLS - 2)*(ROWS - 2)) - MAX)
	{
		printf("排雷成功，游戏结束\n");
		Display(mine, COLS, ROWS);
	}
}

void menu()
{
	printf("*******************************\n");
	printf("***** 1. play      2. exit*****\n");
	printf("*******************************\n");
}

void test()
{
	do
	{
		menu();
		int input = 0;
		printf("请选择：");
		scanf_s("%d", &input);

		switch (input)
		{
		case 1:
			game();
			break;
		case 2:
			exit(0);
			break;
		default:
			printf("输入错误\n");
			break;
		}
	} while (1);
}

int main()
{
	test();
}
