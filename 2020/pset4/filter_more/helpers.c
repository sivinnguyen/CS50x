#include "helpers.h"
#include <math.h>
#include <stdio.h>

int capped(int x);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int haft = ceil(width / 2);
    RGBTRIPLE tmp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < haft; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int count, R, G, B;
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            count = 0;
            R = 0;
            G = 0;
            B = 0;

            for (int m = i - 1; m <= i + 1; m++)
            {
                for (int n = j - 1; n <= j + 1; n++)
                {
                    // check if pixel at the edge
                    if ((m >= 0 && m < height) && (n >= 0 && n < width))
                    {
                        // then count
                        count ++;
                        // and caculate pixels
                        R += image[m][n].rgbtRed;
                        G += image[m][n].rgbtGreen;
                        B += image[m][n].rgbtBlue;
                    }
                }
            }

            tmp[i][j].rgbtRed = round(R / (float) count);
            tmp[i][j].rgbtGreen = round(G / (float) count);
            tmp[i][j].rgbtBlue = round(B / (float) count);
        }
    }


    // Neu khong dung mot bien thay the tmp thi khi tinh toan se dung du lieu moi cua RGB lam sai ket qua
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l] = tmp[k][l];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float rx, gx, bx, ry, gy, by, r, g, b;
    int red, green, blue;
    RGBTRIPLE tmp[height][width];

    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rx = 0;
            gx = 0;
            bx = 0;

            ry = 0;
            gy = 0;
            by = 0;

            for (int m = i - 1; m <= i + 1; m++)
            {
                for (int n = j - 1; n <= j + 1; n++)
                {
                    // check if pixel at the edge
                    if ((m >= 0 && m < height) && (n >= 0 && n < width))
                    {
                        // and caculate pixels
                        rx += (image[m][n].rgbtRed * Gx[m - i + 1][n - j + 1]);
                        gx += (image[m][n].rgbtGreen * Gx[m - i + 1][n - j + 1]);
                        bx += (image[m][n].rgbtBlue * Gx[m - i + 1][n - j + 1]);

                        ry += (image[m][n].rgbtRed * Gy[m - i + 1][n - j + 1]);
                        gy += (image[m][n].rgbtGreen * Gy[m - i + 1][n - j + 1]);
                        by += (image[m][n].rgbtBlue * Gy[m - i + 1][n - j + 1]);
                    }
                }
            }

            r = sqrt((rx * rx) + (ry * ry));
            g = sqrt((gx * gx) + (gy * gy));
            b = sqrt((bx * bx) + (by * by));

            red = round(r);
            green = round(g);
            blue = round(b);

            tmp[i][j].rgbtRed = capped(red);
            tmp[i][j].rgbtGreen = capped(green);
            tmp[i][j].rgbtBlue = capped(blue);
        }
    }

    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l] = tmp[k][l];
            // printf("(%i, %i, %i)\t", image[k][l].rgbtRed, image[k][l].rgbtGreen, image[k][l].rgbtBlue);
        }
        // printf("\n");
    }

    return;
}

int capped(int x)
{
    if (x > 255)
    {
        return 255;
    }

    return x;
}