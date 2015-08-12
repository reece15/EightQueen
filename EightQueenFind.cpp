//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//   �˻ʺ�����ݹ����
//   easyX 2014    VC++6.0
//   by 0xcch
//   2015 04 24
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>

//��ͼ�ĸߺͿ�
#define WIDTH 8
#define HEIGHT 8

void InitMap(int map[][WIDTH]);
void EightQueen(int h,  int map[][8]);
void DrawQueen(int map[][8]);
void MapCopy(int MapTmp[][8], int map[][8]);
int CanStay(int h, int w, int map[][8]);
void DrawText(int h, int w, int size, char * str);

//////////////////////////////////////////////////////////////////////////
//ȫ�ֱ���

IMAGE ImBg; //���̱���    
IMAGE ImA, ImB; //�ʺ�

//////////////////////////////////////////////////////////////////////////


//������
int main(void)
{
	int map[HEIGHT][WIDTH];
	initgraph(480, 480);
	InitMap(map);
	EightQueen(0, map);
	DrawText(5, 460, 16, "����ʾ���о���!��������˳�!");
	//printf("\nDone!");
	getch();
	closegraph();
	return 0;
}

//�ݹ��ҿ��еİ˻ʺ��ŷ���
//����h:��h��
//����map[][8]:��ͼ
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
		//printf("��%d��\n", count);
		DrawQueen(map);
		sprintf(buf, "��%d�־������ҵ�!", count);
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

//�����ַ���
//����h:�����
//����w:�����
//����size:�����С
//����str:�ַ���ָ��
void DrawText(int h, int w, int size, char * str)
{
	LOGFONT f;
	
	setcolor(BLACK);
	getfont(&f);                          
	f.lfHeight = size;                     
	strcpy(f.lfFaceName, "����");        
	f.lfQuality = ANTIALIASED_QUALITY;    
	setfont(&f);                          // ����������ʽ
	outtextxy(h, w, str);
}

//���ƻʺ�
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

//���浽��ʱ����
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

//�жϻʺ��Ƿ���Դ���(h,w)���������
int CanStay(int h, int w, int map[][8])
{
	int i, j;

	//�����
	for (i = 0; i < WIDTH; i++)
	{
		if (map[h][i] == 1 && i != w)
		{
			return 0;
		}
	}
	//�����
	for (i = 0; i < HEIGHT; i++)
	{
		if (map[i][w] == 1 && i != h)
		{
			return 0;
		}
	}
	//�������
	for (i = h - 1, j = w - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (map[i][j] == 1)
		{
			return 0;
		}
	}
	//�������
	for (i = h - 1, j = w + 1; i >= 0 && j < 8; i--, j++)
	{
		if (map[i][j] == 1)
		{
			return 0;
		}
	}
	//�������
	for (i = h + 1, j = w - 1; i < 8 && j >= 0; i++, j--)
	{
		if (map[i][j] == 1)
		{
			return 0;
		}
	}
	//�������
	for (i = h + 1, j = w + 1; i < 8 && j < 8; i++, j++)
	{
		if (map[i][j] == 1)
		{
			return 0;
		}
	}
	return 1;
}



//��ʼ����ͼ
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
	DrawText(200, 5, 16, "�˻ʺ�");
	DrawText(150, 20, 16 , "���������ʾ��һ��ͼ��");
}