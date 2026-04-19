#define _CRT_SECURE_NO_WARNINGS 1
#include <easyx.h>
#include <time.h>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<graphics.h>

/*游戏界面绘制*/
void gamePaint();
/*游戏初始化绘制*/
void gameInit();
/*游戏定时处理*/
void gameInterval();
/*游戏键盘按下*/
void gameKeypress(int key);
/*游戏鼠标按下*/
void gameMouseDown(int mouseX, int mouseY);
/*游戏鼠标右键按下*/
void gameMouseRightDown(int mouseX, int mouseY);
/*游戏鼠标抬起*/
void gameMouseUp(int mouseX, int mouseY);
/*游戏鼠标移动*/
void gameMousemove(int mouseX, int mouseY);

/*
含透明的图的绘制
x为要载入图片的X坐标，y为Y坐标
*/
void drawImage(int  picture_x, int picture_y, IMAGE* picture);
/*调整图片透明度
  角度转弧度：PI/180*角度
  弧度转角度：180/PI*弧度
*/
void drawImageAlpha(int x0, int y0, IMAGE* img, double f);
/*两个矩形碰撞检测
即两个矩形是否相交。
 x1, y1, w1， h1是第一个矩形的xy宽高的四个参数
 x2, y2, w2， h2是第二个矩形的xy宽高的四个参数
 返回0代表不相交 返回1代表相交
*/
int testHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

/*设置100即每隔100毫秒刷新以下界面绘图。*/
int interval = 100;//TODO: 1 设置定时器时间间隔（单位毫秒）
// TODO: 1 设置窗口: 宽度 高度
int screenWidth = 600;
int screenHeight = 600;
int stop = 0;//是否停止游戏
//-----------------------------------//
int times = 0;
/*初始化游戏 */
void initgame()
{
	srand((unsigned)time(NULL));//随机数初始化
	setbkcolor(NULL);//背景色
	setbkmode(TRANSPARENT);// 设置背景混合模式: TRANSPARENT为透明
	gameInit();
}
/*
	界面绘图演示案例
*/


/*绘制显示游戏界面*/
void paint()
{
	BeginBatchDraw();//打开双缓冲
	cleardevice();// 清屏

	gamePaint();
	//-----------------------------//
	EndBatchDraw();//关闭双缓冲
}



/*游戏运行*/
void run()
{
	ExMessage msg;
	//ExMessage key;
	while (1)	// 游戏主循环  可借助break 结束循环
	{
		if (peekmessage(&msg, -1, true))
		{
			switch (msg.message)
			{
			case WM_MOUSEMOVE://鼠标移动
				gameMousemove(msg.x, msg.y);
				break;
			case WM_LBUTTONDOWN://左键按下
				gameMouseDown(msg.x, msg.y);
				break;
			case WM_LBUTTONUP://左键抬起
				gameMouseUp(msg.x, msg.y);
				break;
			case WM_LBUTTONDBLCLK://左键双击

				break;
			case WM_RBUTTONDOWN://右键按下

				break;
			case WM_RBUTTONUP://右键抬起
				gameMouseRightDown(msg.x, msg.y);
				break;
			case WM_RBUTTONDBLCLK://右键双击

				break;
			case WM_KEYDOWN:
				gameKeypress(msg.vkcode);
				break;
			}
			paint();
			continue;
		}


		//------时间处理 勿动-----------//
		Sleep(1);
		times++;
		if (times % (interval / 10) != 0) {
			continue;
		}
		times = 0;
		if (stop)
		{
			break;
		}
		gameInterval();

		//-------------------------------//
		paint();// 刷新显示游戏界面
	}
}



/*绘制透明背景图*/
void drawImage(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				if (dstX < 0) continue;
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
/*调整图片透明度*/
void drawImageAlpha(int x0, int y0, IMAGE* img, double f)
{
	//获得图片尺寸
	int qwidth, qheight;
	qwidth = img->getwidth();
	qheight = img->getheight();


	//P图为背景图,RS为目标图片
	static IMAGE RS(qwidth, qheight);
	static IMAGE P(qwidth, qheight);


	//背景图的绘制
	getimage(&P, x0, y0, qwidth, qheight);


	//获取指针，作为透明度计算
	DWORD* M = GetImageBuffer(&P);
	DWORD* N = GetImageBuffer(img);
	DWORD* R = GetImageBuffer(&RS);


	// 开启批量绘图模式，解决闪烁问题
	BeginBatchDraw();


	//计算与赋值
	int i, j;
	for (i = 0; i < qheight; i++) {
		for (j = 0; j < qwidth; j++) {
			int r, g, b;
			int ij;
			//计算
			ij = i * qwidth + j;
			r = (int)((GetRValue(N[ij])) * (1 - f) + GetRValue(M[ij]) * f);
			g = (int)((GetGValue(N[ij])) * (1 - f) + GetGValue(M[ij]) * f);
			b = (int)((GetBValue(N[ij])) * (1 - f) + GetBValue(M[ij]) * f);
			R[ij] = RGB(r, g, b);
		}
	}


	//贴出图片并释放内存
	putimage(x0, y0, &RS);
	FlushBatchDraw();// 绘制
}
//检测两个矩形是否相碰撞
int testHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return !(x1 + w1 < x2 ||
		y1 + h1 < y2 ||
		x2 + w2 < x1 ||
		y2 + h2 < y1);
}
// 主函数，开启游戏
int main()
{
	initgraph(screenWidth, screenHeight, SHOWCONSOLE);
	initgame();					// 初始化游戏
	paint();// 刷新显示游戏界面

	flushmessage();		// 清空鼠标缓冲区
	while (_kbhit()) _getch();	// 清空键盘缓冲区
	run();						// 开始游戏
	closegraph();//关闭图形环
	return 0;
}


//--------------优雅的警戒线 以上为雷区 非专业 勿进------------------// 
//TODO: 2 全局变量声明位置 
IMAGE imgBG;
IMAGE imgApple;
IMAGE imgBody;
IMAGE imgHead[4];
int appleLie = 5;
int appleHang = 4;
int snakeLie[100] = { 10,10,10,10,10 };
int snakeHang[100] = { 10,11,12,13,14 };
int snakeLen = 5;
int fangXiang = 1;
//TODO: 3 游戏初始化位置  
void gameInit()
{
	loadimage(&imgBG, L".\\she\\bg.bmp");
	loadimage(&imgApple, L".\\she\\apple.bmp");
	loadimage(&imgBody, L".\\she\\body.bmp");
	TCHAR str[100];
	for (int i = 0; i < 4; i++)
	{
		_stprintf(str, L".\\she\\head%d.bmp", i);
		loadimage(&imgHead[i], str);
	}
	appleLie = rand() % 14 + 3;
	appleHang = rand() % 14 + 3;
}
//TODO: 4 绘图处理位置  
void gamePaint()
{
	
	putimage(0, 0, &imgBG);

	putimage(appleLie * 30, appleHang * 30, &imgApple);

	putimage(snakeLie[0] * 30, snakeHang[0] * 30, &imgHead[fangXiang]);
	for (int i = 1; i < snakeLen; i++)
	{
		putimage(snakeLie[i] * 30, snakeHang[i] * 30, &imgBody);
	}

	//putimage(3 * 30, 6 * 30, &imgBody);
}
//TODO: 5 定时处理位置
void gameInterval()
{
	//todo: 爬行
	/*snakeHang[4] = snakeHang[3];
	snakeLie[4] = snakeLie[3];
	snakeHang[3] = snakeHang[2];
	snakeLie[3] = snakeLie[2];
	snakeHang[2] = snakeHang[1];
	snakeLie[2] = snakeLie[1];
	snakeHang[1] = snakeHang[0];
	snakeLie[1] = snakeLie[0];*/
	for (int jie = snakeLen - 1; jie >= 1; jie--)
	{
		snakeHang[jie] = snakeHang[jie - 1];
		snakeLie[jie] = snakeLie[jie - 1];

	}
	switch (fangXiang)
	{
		
	case 0:
		snakeLie[0]++;
		break;
	case 1:
		snakeHang[0]--;
		break;
	case 2:
		snakeLie[0]--;
		break;
	case 3:
		snakeHang[0]++;
		break;
	}

	if (appleHang==snakeHang[0]&&appleLie==snakeLie[0] /*todo:能吃到苹果*/)
	{
		/*todo:变成*/
		snakeLen++;
		appleLie = rand() % 14 + 3;
		appleHang = rand() % 14 + 3;
		/*todo:生新苹果*/
	}
	if (snakeHang[0]==0||snakeLie[0]==0||snakeHang[0]==19||snakeLie[0] == 19 /*todo:能撞墙*/)
	{
		/*todo:gameover*/
		stop = 1;
	}
	int neng = 0;
	for (int j = 1; j < snakeLen; j++)
	{
		if (snakeHang[0]==snakeHang[j]&&snakeLie[0]==snakeLie[j]/*todo:能咬自己*/)
		{
			/*todo:gameover*/
			neng = 1;
			break;
		}
		if (neng)
		{
			stop = 1;
		}
	}
}
//TODO: 6 处理键盘控制位置
void gameKeypress(int key)
{
	switch (key)
	{
	case VK_LEFT:
		fangXiang = 2;
		break;
	case VK_RIGHT:
		fangXiang = 0;
		break;
	case VK_UP:
		fangXiang = 1;
		break;
	case VK_DOWN:
		fangXiang = 3;
		break;
	}


}

//TODO: 7 处理鼠标控制位置
void gameMouseDown(int mouseX, int mouseY)
{
	// 获取蛇头的实际像素坐标
	int headX = snakeLie[0] * 30 + 15; // +15 是为了取方块中心点
	int headY = snakeHang[0] * 30 + 15;

	// 计算点击位置与蛇头的偏移量
	int dx = mouseX - headX;
	int dy = mouseY - headY;

	// 根据点击的相对位置判断转向
	// 绝对值判断：如果横向偏移大于纵向偏移，说明玩家想左右转
	if (abs(dx) > abs(dy))
	{
		if (dx > 0 && fangXiang != 2) // 点击在右侧，且当前不是向左走
		{
			fangXiang = 0; // 向右
		}
		else if (dx < 0 && fangXiang != 0) // 点击在左侧，且当前不是向右走
		{
			fangXiang = 2; // 向左
		}
	}
	else // 纵向偏移更大，说明玩家想上下转
	{
		if (dy > 0 && fangXiang != 1) // 点击在下方，且当前不是向上走
		{
			fangXiang = 3; // 向下
		}
		else if (dy < 0 && fangXiang != 3) // 点击在上方，且当前不是向下走
		{
			fangXiang = 1; // 向上
		}
	}

}
void gameMouseUp(int mouseX, int mouseY)
{

}
void gameMousemove(int mouseX, int mouseY)
{

}

void gameMouseRightDown(int mouseX, int mouseY)
{

}