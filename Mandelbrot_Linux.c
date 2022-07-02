/**
 * @file  Mandelbrot_Linux
 * @author  Peng Pai
 * @date  July 1 2022
 *
 * @brief ��Linux�����е��������²�����ͼ���ļ���C����Դ���룬����ѧϰʹ�ã����������κ�ʵ����;���������Ը���
 *
 *
 */

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
    uint8_t fR,fG,fB;
    uint8_t bR,bG,bB;
    uint8_t gR,gG,gB;
    printf("Enter a positive integer N, which will determine the size of the picture.\n");
    printf("The picture size is (N*1536)*(N*1024), so N should not be too large, preferably single digits:");
	scanf("%d",&N);	//����������N���佫����ͼƬ��С��ͼƬ��СΪ(N*1536)*(N*1024)������N���˹������Ϊ��λ��
    printf("Enter the number of iterations:");scanf("%d",&Times);							//�����������
    printf("Do you want to set a gradient? 1 for yes and 0 for no. \n");
    printf("Gradient is not supported at Windows. If so, please enter 0 or use the Windows edition of the program:");
    scanf("%d",(int*)&Gradient);											//�Ƿ����ý���ɫ(���ܲ�֧�ֽ���ɫ)
    
    printf("Enter the red intensity of the body(0-255):");scanf("%d",(int*)&fR);		//���������ɫŨ��
    printf("Enter the green intensity of the body(0-255):");scanf("%d",(int*)&fG); 		//����������ɫŨ�� 
    printf("Enter the blue intensity of the body(0-255):");scanf("%d",(int*)&fB); 		//����������ɫŨ��
    printf("Enter the red intensity of the background(0-255):");scanf("%d",(int*)&bR);		//���뱳����ɫŨ��
    printf("Enter the green intensity of the background(0-255):");scanf("%d",(int*)&bG);	//���뱳����ɫŨ��
    printf("Enter the blue intensity of the background(0-255):");scanf("%d",(int*)&bB);		//���뱳����ɫŨ��
    if(Gradient){
    	printf("Enter the gradient red intensity(0-255):");scanf("%d",(int*)&gR);		//���뽥���ɫŨ��
    	printf("Enter the gradient green intensity(0-255):");scanf("%d",(int*)&gG);		//���뽥����ɫŨ��
    	printf("Enter the gradient blue intensity(0-255):");scanf("%d",(int*)&gB);		//���뽥����ɫŨ��
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
				*p++=(n*gG+(255-n)*bG)/255;			//�����޸Ĵ˴��ı佥�䷽ʽ
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
