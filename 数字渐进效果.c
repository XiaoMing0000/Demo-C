#include <stdio.h>
#include <windows.h>

static void SetPoint (int x,int y)
{
	COORD point ={x,y};//����һ��COORD���ͱ���������λ��
	HANDLE OutPoint = GetStdHandle(STD_OUTPUT_HANDLE);//ʹ��GetStdHandle(STD_OUTPUT_HANDLE)������ȡ��׼����ľ��
	SetConsoleCursorPosition(OutPoint, point);//���ù��λ��
}

unsigned char memory[16] = {0};
/**
unsigned char memory[16] = {
    0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    };

*/


void color(short x)	//自定义函根据参数改变颜色
{
    if(x>=0 && x<=15)//参数在0-15的范围颜色
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色
    else//默认的颜色白色
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void display() {
	int i=0, j =0 ;
	SetPoint(0, 0);
	for(i=0; i<16; i++) {
		for(j=7; j>=0; j--) {
		    unsigned int bit = memory[i] >> j & 0x01;
            if(bit) {
                color(7);
            } else {
                color(1);
            }
            printf("%d ", (memory[i] >> j & 0x01 ));
		}
		printf("\n");
	}
}

void change(unsigned char X, unsigned char Y) {
    unsigned char bit = (memory[Y] >> (7 - X)) & 0x01;
    if(bit ==0 ) {
        memory[Y] = (memory[Y] & (~(0x80 >> X))) | (0x01 << (7 - X));
    }
    else {
      memory[Y] = memory[Y] & (~(0x80 >> X));
    }
    /** 方案 2
    unsigned char bit = (memory[Y] >> (7 - X)) & 0x01;
    if(bit ==0 ) bit = 1;
    else bit = 0;
    memory[Y] = (memory[Y] & (~(0x80 >> X))) | (bit << (7 - X));
    */
}


int main(int argc, char** argv) {
    int i=0;
    // 初始 1
    for(i=1; i<7; i++) {
        change(7, i);
        change(7, 7+i);
    }
    display();
    Sleep(1000);

    // 显示 2
    for(i=1; i<7; i++) {
        change(7-i, 0);
        change(7-i, 7);
        change(7, 7+i);
        change(7-i, 14);
        change(0, 7+i);
        display();
        Sleep(100);
    }
    Sleep(500);
    // 显示 3
    for(i=1; i<7; i++) {
        change(0, 7+i);
        change(7, 14-i);
        display();
        Sleep(100);
    }
    Sleep(500);
    // 显示 4
    for(i=1; i<7; i++) {
        change(7-i, 0);
        change(0, i);
        change(i, 14);
        display();
        Sleep(100);
    }
    Sleep(500);
    // 显示 5
    for(i=1; i<7; i++) {
        change(i, 0);
        //change(0, 7-i);
        change(7, i);
        change(7-i, 14);
        display();
        Sleep(300);
    }
    // change(0, 0);
    // change(1, 0);
    display();
	return 0;
}
