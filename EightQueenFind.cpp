//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//   八皇后问题递归求解
//   easyX 2014    VC++6.0
//   by 0xcch
//   2015 04 24
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>

//地图的高和宽
#define WIDTH 8
#define HEIGHT 8

void InitMap(int map[][WIDTH]);
void EightQueen(int h,  int map[][8]);
void DrawQueen(int map[][8]);
void MapCopy(int MapTmp[][8], int map[][8]);
int CanStay(int h, int w, int map[][8]);
void DrawText(int h, int w, int size, char * str);

//////////////////////////////////////////////////////////////////////////
//全局变量

IMAGE ImBg; //棋盘背景    
IMAGE ImA, ImB; //皇后

//////////////////////////////////////////////////////////////////////////


//主函数
int main(void)
{
	int map[HEIGHT][WIDTH];
	initgraph(480, 480);
	InitMap(map);
	EightQueen(0, map);
	DrawText(5, 460, 16, "已显示所有局面!按任意键退出!");
	//printf("\nDone!");
	getch();
	closegraph();
	return 0;
}

//递归找可行的八皇后安排方法
//参数h:第h行
//参数map[][8]:地图
void EightQueen(int h, int map[][8])
{
	int i, j;
	static int count = 0;
	int MapTmp[HEIGHT][WIDTH];
	char buf[50];
	
	loadimage(&ImA, "images/Queen.jpg");
	loadimage(&ImB, "images/Queen2.jpg");
	MapCopy(MapTmp,map);
	if (h == 8)
	{
		count += 1;
		//printf("第%d个\n", count);
		DrawQueen(map);
		sprintf(buf, "第%d种局面已找到!", count);
		DrawText(290, 460, 16, buf);
		getch();
	}
	else
	{
		for (i = 0; i < WIDTH; i++)
		{
			if (CanStay(h, i, map) == 1)
			{
				for (j = 0; j < WIDTH; j++)
				{
					MapTmp[h][j] = 0;
				}
				MapTmp[h][i] = 1;
				EightQueen(h + 1, MapTmp);
			}
		}
		
	}
}

//绘制字符串
//参数h:坐标高
//参数w:坐标宽
//参数size:字体大小
//参数str:字符串指针
void DrawText(int h, int w, int size, char * str)
{
	LOGFONT f;
	
	setcolor(BLACK);
	getfont(&f);                          
	f.lfHeight = size;                     
	strcpy(f.lfFaceName, "宋体");        
	f.lfQuality = ANTIALIASED_QUALITY;    
	setfont(&f);                          // 设置字体样式
	outtextxy(h, w, str);
}

//绘制皇后
void DrawQueen(int map[][8])
{
	int i, j;

	BeginBatchDraw();
	putimage(40, 40, &ImBg);
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == 1)
			{
				putimage(40 + j * 50, 40 + i * 50, &ImA, SRCAND);
				putimage(40 + j * 50, 40 + i * 50, &ImB, SRCPAINT);
			}
			//printf("%d ", map[i][j]);
		}
		//printf("\n");
	}
	EndBatchDraw();
	//printf("\n");
}

//保存到临时数组
void MapCopy(int MapTmp[][8], int map[][8])
{
	int i, j;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			MapTmp[i][j] = map[i][j];
		}
	}
}

//判断皇后是否可以待在(h,w)这个坐标上
int CanStay(int h, int w, int map[][8])
{
	int i, j;

	//检测行
	for (i = 0; i < WIDTH; i++)
	{
		if (map[h][i] == 1 && i != w)
		{
			return 0;
		}
	}
	//检测列
	for (i = 0; i < HEIGHT; i++)
	{
		if (map[i][w] == 1 && i != h)
		{
			return 0;
		}
	}
	//检测左上
	for (i = h - 1, j = w - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (map[i][j] == 1)
		{
			return 0;
		}
	}
	//检测右上
	for (i = h - 1, j = w + 1; i >= 0 && j < 8; i--, j++)
	{
		if (map[i][j] == 1)
		{
			return 0;
		}
	}
	//检测左下
	for (i = h + 1, j = w - 1; i < 8 && j >= 0; i++, j--)
	{
		if (map[i][j] == 1)
		{
			return 0;
		}
	}
	//检测右下
	for (i = h + 1, j = w + 1; i < 8 && j < 8; i++, j++)
	{
		if (map[i][j] == 1)
		{
			return 0;
		}
	}
	return 1;
}



//初始化地图
void InitMap(int map[][WIDTH])
{
	int i, j, k = 0;
	
	setbkcolor(RGB(153, 153, 51));
	cleardevice();
	setcolor(RGB(255, 153, 0));
	for (i = 40; i <= 440; i += 50)
	{
		line(40, i, 440, i);
		line(i, 40, i, 440);
	}
	for (i = 44; i < 440; i += 50)
	{
		for(j = 44; j < 440; j += 50)
		{
			if (k % 2 == 1)
			{
				setfillcolor(RGB(102, 51, 0));
				floodfill(i, j, RGB(255, 153, 0));
			}
			else
			{
				setfillcolor(RGB(255, 153, 0));
				floodfill(i, j, RGB(255, 153, 0));
			}
			++k;
		}
		++k;
	}
	getimage(&ImBg, 40, 40, 440, 440);
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			map[i][j] = 0;
		}
	}
	DrawText(200, 5, 16, "八皇后");
	DrawText(150, 20, 16 , "按任意键显示下一个图像");
}