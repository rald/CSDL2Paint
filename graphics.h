#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include <time.h>
#include <math.h>

#define ClearScreen() SDL_RenderClear(renderer);

#define SetColor(c) Graphics_SetColor(renderer,c)

#define DrawPoint(x, y) SDL_RenderDrawPoint(renderer, x, y);

#define DrawLine(x0, y0, x1, y1) SDL_RenderDrawLine(renderer, x0, y0, x1, y1);

#define DrawRect(x, y, w, h) SDL_RenderDrawRect(renderer, &(SDL_Rect){x, y, w, h})

#define FillRect(x, y, w, h) SDL_RenderFillRect(renderer, &(SDL_Rect){x, y, w, h})

#define DrawCircle(x,y,r) Graphics_DrawCircle(renderer,x,y,r) 

#define FillCircle(x,y,r) Graphics_FillCircle(renderer,x,y,r) 

#define Update() SDL_RenderPresent(renderer);

SDL_Color colors[] = {
	{26, 28, 44},
	{93, 39, 93},
	{177, 62, 83},
	{239, 125, 87},
	{255, 205, 117},
	{167, 240, 112},
	{56, 183, 100},
	{37, 113, 121},
	{41, 54, 111},
	{59, 93, 201},
	{65, 166, 246},
	{115, 239, 247},
	{244, 244, 244},
	{148, 176, 194},
	{86, 108, 134},
	{51, 60, 87}};
	
int numColors=16;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

bool quit = false;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;

double touchX=0,touchY=0;
bool touchDown=false;

void Graphics_SetColor(SDL_Renderer *renderer, SDL_Color c);

void Graphics_DrawCircle(SDL_Renderer *renderer, int x, int y, int radius);

void Graphics_FillCircle(SDL_Renderer *renderer, int x, int y, int radius);

#ifdef GRAPHICS_IMPLEMENTATION

void Graphics_SetColor(SDL_Renderer *renderer, SDL_Color c)
{
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

void Graphics_DrawCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;

	offsetx = 0;
	offsety = radius;
	d = radius - 1;

	while (offsety >= offsetx)
	{
		SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
		SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
		SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
		SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
		SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
		SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
		SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
		SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

		if (d >= 2 * offsetx)
		{
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety))
		{
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else
		{
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}
}

void Graphics_FillCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;

	offsetx = 0;
	offsety = radius;
	d = radius - 1;

	while (offsety >= offsetx)
	{
		SDL_RenderDrawLine(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
		SDL_RenderDrawLine(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
		SDL_RenderDrawLine(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
		SDL_RenderDrawLine(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

		if (d >= 2 * offsetx)
		{
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety))
		{
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else
		{
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}
}

void Screen(int w, int h)
{	
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_GetRendererOutputSize(renderer, &SCREEN_WIDTH, &SCREEN_HEIGHT);
}

void Events()
{
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			default:
				break;
			}
			break;
		case SDL_FINGERDOWN:
			touchX=event.tfinger.x*SCREEN_WIDTH;		
			touchY=event.tfinger.y*SCREEN_HEIGHT;
			touchDown=true;		
		break;
		case SDL_FINGERUP:
			touchX=event.tfinger.x*SCREEN_WIDTH;		
			touchY=event.tfinger.y*SCREEN_HEIGHT;
			touchDown=false;		
		break;
		case SDL_FINGERMOTION:
			touchX=event.tfinger.x*SCREEN_WIDTH;		
			touchY=event.tfinger.y*SCREEN_HEIGHT;
		break;
		default:
			break;
		}
	}
}

void Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	window = NULL;
	renderer = NULL;

	SDL_Quit();
}

#endif /* GRAPHICS_IMPLEMENTATION */

#endif /* GRAPHICS_H */
