#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <limits.h>

#define Pc 0.7//½»²æ¸ÅÂÊ

int n=3,m=3;


int randsign(float p){  //°´¸ÅÂÊp·µ»Ø1
    srand((double)time(NULL));
    if((double)rand() > (p * INT_MAX) )
        return 0;
    else
        return 1;
}

int randbit(int i,int j){  //²úÉúÔÚiÓëjÖ®¼äµÄÒ»¸öËæ»úÊý
    srand(time(NULL));
    int a;
    a=i+(rand()%(j-i+1));
    //a= ((int)(rand()%1000)/1000)*(j-i)+i;
    return a;
}

int **makeList(const int *gene){    //½«Ã¿¸ö¹¤¼þµÄ¹¤ÐòºÅÐ´ÔÚÈ¾É«Ìå¶ÔÓ¦»ùÒòÏÂ£¬ÐÎ³Élist
    int i,j;
    int k=0;//¼ÇÂ¼¹¤Ðò
    int s=6;
    int **list = (int **)malloc(2 * sizeof(int *));
    for(i=0;i<2;i++)
        list[i] = (int *)malloc(s*sizeof(int)); //Õâ¸öÖ¸ÕëÊý×éµÄÃ¿¸öÖ¸ÕëÔªËØÓÖÖ¸ÏòÒ»¸öÊý×é
    for (i=0;i<s;i++)  //iÎªÈ¾É«Ìå»ùÒò¸öÊý
        list[0][i] = gene[i];  //½«È¾É«Ìå¸´ÖÆ½ølistÖÐ
    for (j=1;j<=n; j++){    //jÎª¹¤¼þÊý
        for(i=0;i<s;i++){
            if(j==list[0][i]){
                k++;
                list[1][i]=k;
            }
        }
        k=0;
    }
    return list;//?????µ½µ×Ò»¸öÁ½¸ö*£¬ÎÒÒ²¸ã²»Çå£¡£¡£¡£¡
}

void FreeTDA(int **list) {   //ÊÍ·Å¶¯Ì¬¶þÎ¬Êý×éÄÚ´æ
    int i;
    for(i = 0; i < 2; i++)
        free(list[i]);
    free(list);
}

int *Crossover (int *p1, int *p2){  //Order Crossover£¨OX£©
    int **list1,**list2;
    list1 =  makeList(p1);//Í¬ÉÏ£¬Ò»¸öÁ½¸ö*µÄÃ»¸ãÇå
    list2 =  makeList(p2);
    int s=6;
    int *child=(int *)malloc(6* sizeof(int));
    if(randsign(Pc)==1) { //°´ÕÕcrossover probability½»²æ¸ÅÂÊ¶ÔÑ¡ÔñµÄÈ¾É«Ìå½øÐÐ½»²æ²Ù×÷
        int a, b;    //a£¬bÎªÔÚp1ÖÐËæ»úÑ¡È¡µÄÆ¬¶ÎÊ¼Ä©µã
        a = randbit(0, s-2);
        Sleep(2000);   //ÑÓÊ±2Ãë
        b = randbit(0, s-1);
        while (b<=a)
            b = randbit(0, s-1);
        int i, x;  //ÓÃÔÚp1£¬p2ÀïµÄ¼ÆÊýÆ÷
        int k = 0;       //ÓÃÔÚchildÀïµÄ¼ÆÊýÆ÷
        for (i = a; i <= b; i++)    //ÔÚp1ÖÐËæ»úÈ¡Ò»¸öÆ¬¶Î£¬¶ÔÓ¦Î»ÖÃ¡°ÒÅ´«¡±¸ø×Ó´úchild
            child[i] = p1[i];
        
        for (i = 0; i < s; i++){
        	int flag=1;//¶¼²»Ò»Ñù 
        	for (x = a; x <= b; x++){
        		if ((list2[0][i] == list1[0][x]) && (list2[1][i] == list1[1][x])) {
        			flag=0;
				}
			}
			if (flag=1){
				if(k!=a){
					child[k] = list2[0][i];
					k++;
				}
				else{
					if(b!=(s-1)) {
				        k = b + 1;	
				        child[k] = list2[0][i];
				        k++;
				    }
				    else
				        break;
				}
			}
		} 	
        FreeTDA(list1);
        FreeTDA(list2);
    }
    else
        child=p1;
    return child;
}

int main() {
    int i;
    int p1[]={1,2,1,3,1,2};
	int p2[]={2,3,1,1,2,1};
	int *child;
    child=Crossover(p1,p2);
    for (i = 0; i < 6; i++)
        printf("%d ",*(child+i));
    return 0;
}
