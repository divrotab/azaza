/* ==========================
	Класс "прямая труба"

	Усовершенствованный SDL_Rect
	который знает координату своего центра
	длину и ширину
*/

#include "std_lib_facilities.h"
#include "SDL.h"

const int SCREEN_WIDTH=700;
const int SCREEN_HEIGHT=700;

//генератор последовательности случайных чисел для генерации последовательности случайных чисел для случайного спавна трубы :D

class DPipe {
public:
	DPipe(int xcent,int ycent,int wid,int heig);

	void default_create1(SDL_Renderer *ren,string a);
	void default_create(SDL_Renderer* ren,string a);
	void spin(SDL_Renderer* ren);

	void upgrade(SDL_Renderer* ren);

	int width() {return Pipe.w;}
	int width1() {return Pipe1.w;}

	int height() {return Pipe.h;}
	int height1() {return Pipe1.h;}

	SDL_Point center();
	SDL_Rect tryba() {return Pipe;}
private:

	int uses;
	SDL_Rect Pipe1;
	SDL_Rect Pipe;
}; 

//создаем трубу по указанию центра
DPipe::DPipe(int xcent,int ycent,int wid,int heig)
{
	uses=1;

	Pipe.x=xcent-0.5*wid;
	Pipe.y=ycent-0.5*heig;
	Pipe.w=wid;
	Pipe.h=heig;

	Pipe1.x=xcent-0.5*heig;
	Pipe1.y=ycent-0.5*wid;
	Pipe1.w=heig;
	Pipe1.h=wid;
}

SDL_Point DPipe::center()
{
	SDL_Point centr={Pipe.x+0.5*Pipe.w,Pipe.y+0.5*Pipe.h};
	return centr;
}


void DPipe::default_create(SDL_Renderer* ren,string a)
{

	SDL_Surface *BMP_DPipe=SDL_LoadBMP(a.c_str());
	if (BMP_DPipe == nullptr)
	{
	    cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
	}
	SDL_Texture *DPipe = SDL_CreateTextureFromSurface(ren, BMP_DPipe);

	SDL_RenderCopy(ren, DPipe, NULL, &Pipe);
}

void DPipe::default_create1(SDL_Renderer* ren,string a)
{

	SDL_Surface *BMP_DPipe=SDL_LoadBMP(a.c_str());
	if (BMP_DPipe == nullptr)
	{
	    cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
	}
	SDL_Texture *DPipe = SDL_CreateTextureFromSurface(ren, BMP_DPipe);

	SDL_RenderCopy(ren, DPipe, NULL, &Pipe1);
}


void DPipe::spin(SDL_Renderer* ren)
{
	uses+=1;
	if(uses ==1)
		default_create(ren,"text1.bmp");
	else if(uses==2)
		default_create1(ren,"text2.bmp");
	else if(uses==3)
		default_create(ren,"text3.bmp");
	else if(uses==4)
		default_create1(ren,"text4.bmp");
	else if(uses==5)
	{
		uses-=4;
		default_create(ren,"text1.bmp");
	}
} 

void DPipe::upgrade(SDL_Renderer *ren)
{
	if(uses ==1)
		default_create(ren,"text1.bmp");
	else if(uses==2)
		default_create1(ren,"text2.bmp");
	else if(uses==3)
		default_create(ren,"text3.bmp");
	else if(uses==4)
		default_create1(ren,"text4.bmp");
	else if(uses==5)
	{
		uses-=4;
		default_create(ren,"text1.bmp");
	}
}

int main(int argc,char** argv)
{
	DPipe tryba1_rect(200,200,100,40);
	DPipe tryba2_rect(400,400,100,40);
	DPipe background_rect(350,350,700,700);
	DPipe kletka_rect(200,200,100,100);
	DPipe kletka2_rect(400,400,100,100);


	setlocale(LC_ALL,"RUSSIAN");
	//------создаем окно с фоном и парой труб--------//
	SDL_DisplayMode displayMode;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
    cout << "SDL_Init Error: " << SDL_GetError() << endl;
    return 1;
	}

	int request = SDL_GetDesktopDisplayMode(0,&displayMode);

	//создаем монитор
	SDL_Window *win = SDL_CreateWindow("Trubi", 300, 300,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
	    return 1;
	}

	//создаем рендерер
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
	    return 1;
	}

	SDL_Surface *BMP_TRYBA=SDL_LoadBMP("kletka.bmp");
	if (BMP_TRYBA == nullptr)
	{
	    cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
		return 1;
	}
	SDL_Texture *TRYBA = SDL_CreateTextureFromSurface(ren, BMP_TRYBA);

	SDL_RenderClear(ren);
	background_rect.default_create(ren,"project.bmp");
	kletka_rect.default_create(ren,"kletka.bmp");
	kletka2_rect.default_create(ren,"kletka.bmp");
	tryba1_rect.default_create(ren,"text1.bmp");
	tryba2_rect.default_create(ren,"text1.bmp");
	SDL_RenderPresent(ren); 

	SDL_Event event;
	bool quit=false;
	int trybi=2;
	while(!quit)
	{
		 while(SDL_PollEvent(&event))
		 {
			SDL_PumpEvents(); // обработчик событий.
			
			//крестик
			if(event.type == SDL_QUIT)
				quit=true;
			else if(event.type==SDL_MOUSEBUTTONDOWN &&  event.button.button==SDL_BUTTON_LEFT)
			{
				if((event.button.x>=kletka_rect.center().x-kletka_rect.width()/2 && event.button.x<=kletka_rect.center().x+kletka_rect.width()/2) && 
					(event.button.y>=kletka_rect.center().y-kletka_rect.height()/2 && event.button.y<=kletka_rect.center().y+kletka_rect.height()/2))
				{
						SDL_RenderClear(ren);
						background_rect.default_create(ren,"project.bmp");
						kletka_rect.default_create(ren,"kletka.bmp");
						kletka2_rect.default_create(ren,"kletka.bmp");
						tryba2_rect.upgrade(ren); 
						tryba1_rect.spin(ren);
						SDL_RenderPresent(ren); 
				}
				else if((event.button.x>=kletka2_rect.center().x-kletka2_rect.width()/2 && event.button.x<=kletka2_rect.center().x+kletka2_rect.width()/2) && 
					(event.button.y>=kletka2_rect.center().y-kletka2_rect.height()/2 && event.button.y<=kletka2_rect.center().y+kletka2_rect.height()/2))
				{
						SDL_RenderClear(ren);
						background_rect.default_create(ren,"project.bmp");
						kletka_rect.default_create(ren,"kletka.bmp");
						kletka2_rect.default_create(ren,"kletka.bmp");
						tryba1_rect.upgrade(ren);
						tryba2_rect.spin(ren);
						SDL_RenderPresent(ren); 
				}
						
			}
		 }
	}
	return 1;
}

