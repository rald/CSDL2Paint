#ifndef BITMAP_H
#define BITMAP_H

void SaveBitmap(char *filename, int *b, int w, int h);

void LoadBitmap(char *filename, int **b, int *w, int *h);

#ifdef BITMAP_IMPLEMENTATION

void SaveBitmap(char *filename, int *b, int w, int h)
{
	FILE *fout = fopen(filename, "w");

	fprintf(fout, "%d,%d\n\n", w, h);

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			int k = b[j * w + i];
			fprintf(fout, "%2d,", k);
		}
		fprintf(fout, "\n");
	}

	fclose(fout);
}

void LoadBitmap(char *filename, int **b, int *w, int *h)
{
	FILE *fin = fopen(filename, "r");
	
	if(!fin) return;

	fscanf(fin, "%d,%d\n\n", w, h);

	*b = calloc(*w * *h, sizeof(int));

	for (int j = 0; j < *h; j++)
	{
		for (int i = 0; i < *w; i++)
		{
			int k;
			fscanf(fin, "%2d,", &k);
			(*b)[j * *w + i] = k;
		}
		fprintf(fin, "\n");
	}

	fclose(fin);
}

void DrawBitmap(int *b, int w, int h, int x, int y, int s, int t)
{
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			int k = b[j * w + i];
			if (k != t)
			{
				SetColor(colors[k]);
				FillRect(i * s + x, j * s + y, s, s);
			}
		}
	}
}

#endif

#endif
