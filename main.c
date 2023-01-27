#include <SDL2/SDL.h>

#define GRAPHICS_IMPLEMENTATION
#include "graphics.h"

#define BITMAP_IMPLEMENTATION
#include "bitmap.h"

#define CANVAS_FILE "output.txt"

int w = 32;
int h = 32;
int s = 32;
int ps = 128;

bool grid = true;
int color = 0;

bool inrect(int x, int y, int rx, int ry, int rw, int rh)
{
	return x >= rx && x <= rx + rw && y >= ry && y <= ry + rh;
}

void DrawGrid(int *b, int x, int y, int w, int h, int s)
{
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			int k = b[j * w + i];

			double yiq = ((colors[k].r * 299) + (colors[k].g * 587) + (colors[k].b * 114)) / 1000;
			if (yiq >= 128)
				SetColor(colors[0]);
			else
				SetColor(colors[12]);
			DrawRect(i * s + x, j * s + y, s, s);
		}
	}
}

void DrawPalette(int x, int y, int w, int h, int s)
{
	for (int k = 0; k < numColors; k++)
	{
		int i = k % 8;
		int j = k / 8;

		SetColor(colors[k]);
		FillRect(i * s + x, j * s + y, s, s);

		if (k == color)
		{
			SetColor(colors[12]);
			for (int l = 0; l < 5; l++)
				DrawRect(i * s + x + l, j * s + y + l, s - l * 2, s - l * 2);
			SetColor(colors[0]);
			for (int l = 5; l < 10; l++)
				DrawRect(i * s + x + l, j * s + y + l, s - l * 2, s - l * 2);
		}
	}
}

int main(void)
{
	int *b = NULL;

	srand(time(NULL));

	LoadBitmap(CANVAS_FILE, &b, &w, &h);

	if (b == NULL)
	{
		b = malloc(sizeof(int) * (w * h));
		for (int i = 0; i < w * h; i++)
			b[i] = color;
	}

	Screen(320, 240);

	int cx = (SCREEN_WIDTH - w * s) / 2;
	int cy = 16;

	int pcx = (SCREEN_WIDTH - 8 * ps) / 2;
	int pcy = SCREEN_HEIGHT - 2 * ps - 8;

	while (!quit)
	{
		Events();

		SetColor(colors[0]);

		ClearScreen();

		DrawBitmap(b, w, h, cx, cy, s, 0);

		if (grid)
			DrawGrid(b, cx, cy, w, h, s);
		else
		{
			SetColor(colors[12]);
			DrawRect(cx, cy, w * s, h * s);
		}

		DrawPalette(pcx, pcy, w, h, ps);

		if (touchDown && inrect(touchX, touchY, cx, cy, w * s, h * s))
		{
			int x = (touchX - cx) / s;
			int y = (touchY - cy) / s;
			b[y * w + x] = color;

			SaveBitmap(CANVAS_FILE, b, w, h);
		}

		if (touchDown && inrect(touchX, touchY, pcx, pcy, 8 * ps, 2 * ps))
		{
			int x = (touchX - pcx) / ps;
			int y = (touchY - pcy) / ps;
			color = y * 8 + x;
		}

		DrawBitmap(b, w, h, cx + w * s - w * 4, cy + w * s + 32, 4, -1);

		SetColor(colors[0]);

		Update();

		SDL_Delay(1000 / 60);
	}

	Clean();

	return 0;
}
