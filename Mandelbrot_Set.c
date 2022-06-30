#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "svpng.h"								//�ļ���svpng.h����������png�ļ����ļ�����https://github.com/miloyip/svpng/blob/master/svpng.inc 

int Times;										// 
bool Gradient;									//���������䣬�����Ƿ�ʹ�ý���ɫ 
typedef struct color{							//�ṹ���ͣ���ɫ������RGBģʽ 
	uint8_t R;									//��ɫŨ�� 
	uint8_t G;									//��ɫŨ�� 
	uint8_t B;									//��ɫŨ�� 
}Color;											//

double mandelbrot(double x, double y) {			//�������ж�һ�����Ƿ��������²����ϣ��Լ����ĵݹ���� 
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
    printf("����������N���佫����ͼƬ��С��ͼƬ��СΪ(N*1536)*(N*1024)������N���˹������Ϊ��λ����");scanf("%d",&N);
    printf("����ݹ������");scanf("%d",&Times);
    printf("�Ƿ����ý���ɫ��1 for yes and 0 for no��");scanf("%d",&Gradient);
    printf("�����������ɫŨ��(0-255)��");scanf("%d",&f.R);
    printf("������������ɫŨ��(0-255)��");scanf("%d",&f.G);
    printf("������������ɫŨ��(0-255)��");scanf("%d",&f.B);
    printf("�����뱳����ɫŨ��(0-255)��");scanf("%d",&b.R);
    printf("�����뱳����ɫŨ��(0-255)��");scanf("%d",&b.G);
    printf("�����뱳����ɫŨ��(0-255)��");scanf("%d",&b.B);
    if(Gradient){
    	printf("�����뽥���ɫŨ��(0-255)��");scanf("%d",&g.R);
    	printf("�����뽥����ɫŨ��(0-255)��");scanf("%d",&g.G);
    	printf("�����뽥����ɫŨ��(0-255)��");scanf("%d",&g.B);
	}
	printf("����ͼƬ��\n");
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
	printf("ͼƬ�������"); 
    return 0;
}
