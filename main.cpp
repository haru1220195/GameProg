#include "DxLib.h"
#include "hed.h"
#include <time.h>
#include <math.h>
double px=200;
double sx=200;
double sy=420;
double ss=0;
double sa=0;
int puzcor[10]={0,0,0,0,0,0,0,0,0,0};
int li=0;
int mstep=0;
int smenu=0;
int putup=0,putdown=0,putleft=0,putright=0;
int putkeyz=0,putkeyx=0;
int up=0,down=0,left=0,right=0;
int keyz=0,keyx=0;

struct orbdata{
	double orbx;
	double orby;
	double orbang;
	double orbspe;
	int orbpos;
	int orbgra;
	int flg;
};
struct orbdata tama1[1024];


void start(int gra[]){
	int i=0;
	srand((unsigned) time(NULL));
}

int mi=0;
void mainloop(int gra[],int mgra[]){
	keycheck();
	while(1){
		if(mstep==0){
			DrawGraph ( 0 , 0 , gra[1] , TRUE );
			if(putup==1){
				smenu-=1;
			}
			if(putdown==1){
				smenu+=1;
			}
			
			if(smenu>2){
				smenu=0;
			}
			if(smenu<0){
				smenu=2;
			}
			
			if(smenu==0){
				DrawGraph ( 244 , 252 , gra[2] , TRUE );
			}
			if(smenu==1){
				DrawGraph ( 244 , 294 , gra[3] , TRUE );
			}
			if(smenu==2){
				DrawGraph ( 244 , 335 , gra[4] , TRUE );
			}
/*			if(smenu==3){
				DrawGraph ( tama1[oi].orbx-16 , tama1[oi].orby-16 , tama1[oi].orbgra , TRUE );
			}*/
			if(putkeyz==1){
				mstep=smenu+1;
				smenu=0;
				break;
			}
		}
	
		if(mstep==1){
			DrawGraph ( 0 , 0 , gra[7] , TRUE );
			for(mi=0;mi<12;mi++){
				DrawGraph ( 245 , mi*40 , gra[mi*2+9] , TRUE );
			}
			if(putup==1){
				smenu-=1;
			}
			if(putdown==1){
				smenu+=1;
			}

			if(smenu>11){
				smenu=0;
			}
			if(smenu<0){
				smenu=11;
			}

			DrawGraph ( 245 , smenu*40 , gra[smenu*2+8] , TRUE );

			if(putkeyx==1){
				mstep=0;
				smenu=0;
				break;
			}
			if(putkeyz==1){
				mstep=4;
				smenu=0;
				break;
			}
		}




		break;
	}
}

void keycheck(void){
	putup=0;
	putdown=0;
	putleft=0;
	putright=0;
	putkeyz=0;
	putkeyx=0;
	if(CheckHitKey(KEY_INPUT_UP)==1){
		if(up==0){
			up=1;
			putup=1;
		}
	}else{
		up=0;
	}

	if(CheckHitKey(KEY_INPUT_DOWN)==1){
		if(down==0){
			down=1;
			putdown=1;
		}
	}else{
		down=0;
	}

	if(CheckHitKey(KEY_INPUT_LEFT)==1){
		if(left==0){
			left=1;
			putleft=1;
		}
	}else{
		left=0;
	}

	if(CheckHitKey(KEY_INPUT_RIGHT)==1){
		if(right==0){
			right=1;
			putright=1;
		}
	}else{
		right=0;
	}

	if(CheckHitKey(KEY_INPUT_Z)==1){
		if(keyz==0){
			keyz=1;
			putkeyz=1;
		}
	}else{
		keyz=0;
	}

	if(CheckHitKey(KEY_INPUT_X)==1){
		if(keyx==0){
			keyx=1;
			putkeyx=1;
		}
	}else{
		keyx=0;
	}

}

void orbcre(double x,double y,double a,double s,int g){
	int i;
	for(i=0;i<1024;i++){
		if(tama1[i].flg==0){
			break;
		}
	}
	if(i>1023){i=0;}
	tama1[i].orbx=x;
	tama1[i].orby=y;
	tama1[i].orbang=a;
	tama1[i].orbspe=s;
	tama1[i].orbgra=g;
	tama1[i].flg=1;
}

int oi=0;
void orb(int gra[]){
	for(oi=0;oi<1024;oi++){
		if(tama1[oi].flg==1){
			DrawGraph ( tama1[oi].orbx-16 , tama1[oi].orby-16 , tama1[oi].orbgra , TRUE );
			tama1[oi].orbx+=cos(tama1[oi].orbang)*tama1[oi].orbspe;
			tama1[oi].orby+=sin(tama1[oi].orbang)*tama1[oi].orbspe;
			if(tama1[oi].orbx<32||tama1[oi].orbx>268){tama1[oi].orbang=3.141592-tama1[oi].orbang;}
			if(tama1[oi].orby>448){
				tama1[oi].flg=0;
			}
		}
	}
}

void player(int gra){
	DrawGraph ( px-16 , 404 , gra , TRUE );
	if(CheckHitKey(KEY_INPUT_RIGHT)==1){
		if(px<268){px+=5;}
	}
	if(CheckHitKey(KEY_INPUT_LEFT)==1){
		if(px>32){px-=5;}
	}
}

void shot(int gra){
	DrawGraph ( sx-8 , sy-8 , gra , TRUE );
	if(400.0>abs((sx-px)*(sx-px))+abs((sy-420)*(sy-420))){
		sx=px;
		sy=420;
		if(CheckHitKey(KEY_INPUT_X)==1){
			sx=px;
			sy=399;
			ss=-7.0;
			sa=3.141592/2;
		}
	}
	else{
		ss+=0.1;
		if(ss>0.0){
			sa=atan2f(420-sy,px-sx);
		}
		sx=sx+cos(sa)*ss;
		sy=sy+sin(sa)*ss;
	}
	if(sx<32){sa=3.141592-sa;sx=32;}
	if(sx>268){sa=3.141592-sa;sx=268;}
	if(sy>448){sa=-sa;sy=448;}
}

