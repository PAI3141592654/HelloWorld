/**
 * @file  Mandelbrot_Linux
 * @author  Peng Pai
 * @date  July 1 2022
 *
 * @brief 在Linux上运行的生成曼德博集合图像文件的C语言源代码，仅供学习使用，请勿用于任何实际用途，否则后果自负！
 *
 *
 */

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
    uint8_t fR,fG,fB;
    uint8_t bR,bG,bB;
    uint8_t gR,gG,gB;
    printf("Enter a positive integer N, which will determine the size of the picture.\n");
    printf("The picture size is (N*1536)*(N*1024), so N should not be too large, preferably single digits:");
	scanf("%d",&N);	//输入正整数N，其将决定图片大小，图片大小为(N*1536)*(N*1024)，所以N不宜过大，最好为个位数
    printf("Enter the number of iterations:");scanf("%d",&Times);							//输入迭代次数
    printf("Do you want to set a gradient? 1 for yes and 0 for no. \n");
    printf("Gradient is not supported at Windows. If so, please enter 0 or use the Windows edition of the program:");
    scanf("%d",(int*)&Gradient);											//是否设置渐变色(可能不支持渐变色)
    
    printf("Enter the red intensity of the body(0-255):");scanf("%d",(int*)&fR);		//输入主体红色浓度
    printf("Enter the green intensity of the body(0-255):");scanf("%d",(int*)&fG); 		//输入主体绿色浓度 
    printf("Enter the blue intensity of the body(0-255):");scanf("%d",(int*)&fB); 		//输入主体蓝色浓度
    printf("Enter the red intensity of the background(0-255):");scanf("%d",(int*)&bR);		//输入背景红色浓度
    printf("Enter the green intensity of the background(0-255):");scanf("%d",(int*)&bG);	//输入背景绿色浓度
    printf("Enter the blue intensity of the background(0-255):");scanf("%d",(int*)&bB);		//输入背景蓝色浓度
    if(Gradient){
    	printf("Enter the gradient red intensity(0-255):");scanf("%d",(int*)&gR);		//输入渐变红色浓度
    	printf("Enter the gradient green intensity(0-255):");scanf("%d",(int*)&gG);		//输入渐变绿色浓度
    	printf("Enter the gradient blue intensity(0-255):");scanf("%d",(int*)&gB);		//输入渐变蓝色浓度
	}
	printf("Generating a picture...\n");
    int Width=N*1536;
    int Height=N*1024;
    uint8_t *data=(uint8_t*)malloc(Width*Height*3),*p=data;
    g.R=gR;g.G=gG;g.B=gB;
    for(i = 0; i < Height; ++i) {
        for(j = 0; j < Width; ++j) {
            uint8_t n = mandelbrot(j / (512.0*N) - 2, i / (512.0*N) - 1) * 255;
            if(n==255){
            	*p++=fR;
            	*p++=fG;
            	*p++=fB;
			}
			else if(Gradient==0){
				*p++=bR;
            	*p++=bG;
            	*p++=bB;
			}
			else{
				*p++=(n*gR+(255-n)*bR)/255;			//#######################
				*p++=(n*gG+(255-n)*bG)/255;			//可以修改此处改变渐变方式
				*p++=(n*gB+(255-n)*bB)/255;			//#######################
			}
        }
    }
    FILE* file = fopen("Mandelbrot.png", "wb");
    svpng(file, Width, Height, data, 0);
    fclose(file);
    free(data);
	printf("Finished."); 
    return 0;
}
