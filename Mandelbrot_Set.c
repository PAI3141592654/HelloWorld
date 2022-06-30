#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "svpng.h"								//文件：svpng.h，用于生成png文件，文件来自https://github.com/miloyip/svpng/blob/master/svpng.inc 

int Times;										// 
bool Gradient;									//变量：渐变，决定是否使用渐变色 
typedef struct color{							//结构类型：颜色，采用RGB模式 
	uint8_t R;									//红色浓度 
	uint8_t G;									//绿色浓度 
	uint8_t B;									//蓝色浓度 
}Color;											//

double mandelbrot(double x, double y) {			//函数，判断一个点是否属于曼德博集合，以及它的递归次数 
	int i;
    double a = x, b = y;
    for( i = 0; i <Times; ++i) {
        double c = a * a - b * b + x, d = 2 * a * b + y;
        a = c, b = d;
        if(a * a + b * b > 4) return Gradient?i/(1.0*Times):0;
    }
    return 1;
}

int main(void) {
	int i,j;
    int N;
    Color f,b,g;
    printf("输入正整数N，其将决定图片大小，图片大小为(N*1536)*(N*1024)，所以N不宜过大，最好为个位数：");scanf("%d",&N);
    printf("输入递归次数：");scanf("%d",&Times);
    printf("是否设置渐变色？1 for yes and 0 for no：");scanf("%d",&Gradient);
    printf("请输入主体红色浓度(0-255)：");scanf("%d",&f.R);
    printf("请输入主体绿色浓度(0-255)：");scanf("%d",&f.G);
    printf("请输入主体蓝色浓度(0-255)：");scanf("%d",&f.B);
    printf("请输入背景红色浓度(0-255)：");scanf("%d",&b.R);
    printf("请输入背景绿色浓度(0-255)：");scanf("%d",&b.G);
    printf("请输入背景蓝色浓度(0-255)：");scanf("%d",&b.B);
    if(Gradient){
    	printf("请输入渐变红色浓度(0-255)：");scanf("%d",&g.R);
    	printf("请输入渐变绿色浓度(0-255)：");scanf("%d",&g.G);
    	printf("请输入渐变蓝色浓度(0-255)：");scanf("%d",&g.B);
	}
	printf("生成图片中\n");
    int Width=N*1536;
    int Height=N*1024;
    uint8_t *data=(uint8_t*)malloc(Width*Height*3),*p=data;
    for(i = 0; i < Height; ++i) {
        for(j = 0; j < Width; ++j) {
            uint8_t n = mandelbrot(j / (512.0*N) - 2, i / (512.0*N) - 1) * 255;
            if(n==255){
            	*p++=f.R;
            	*p++=f.G;
            	*p++=f.B;
			}
			else if(Gradient==0){
				*p++=b.R;
            	*p++=b.G;
            	*p++=b.B;
			}
			else{
				*p++=(n*g.R+(255-n)*b.R)/255;
				*p++=(n*g.G+(255-n)*b.G)/255;
				*p++=(n*g.B+(255-n)*b.B)/255;
			}
        }
    }
    FILE* file = fopen("Mandelbrot.png", "wb");
    svpng(file, Width, Height, data, 0);
    fclose(file);
    free(data);
	printf("图片生成完毕"); 
    return 0;
}
