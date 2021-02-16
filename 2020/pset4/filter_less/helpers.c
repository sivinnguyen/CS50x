#include <math.h>
#include <stdio.h>
#include "helpers.h"

// Convert image to grayscale
// take the average of the red, green, and blue values to determine what shade of grey to make the new pixel
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            /* image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg; */
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Convert image to sepia
// sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
// sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
// sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        BYTE oR, oG, oB;
        int sR, sG, sB;

        for (int j = 0; j < width; j++)
        {
            oR = image[i][j].rgbtRed;
            oG = image[i][j].rgbtGreen;
            oB = image[i][j].rgbtBlue;

            sR = round((0.393 * oR) + (0.769 * oG) + (0.189 * oB));
            sG = round((0.349 * oR) + (0.686 * oG) + (0.168 * oB));
            sB = round((0.272 * oR) + (0.534 * oG) + (0.131 * oB));

            image[i][j].rgbtRed =  sR < 255 ? sR : 255;
            image[i][j].rgbtGreen = sG < 255 ? sG : 255;
            image[i][j].rgbtBlue = sB < 255 ? sB : 255;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // int haft = ceil(width / 2);
    int haft = width / 2;
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
// The new value of each pixel would be the average of the values of all of the pixels that are within 1 row and column of the original pixel
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
