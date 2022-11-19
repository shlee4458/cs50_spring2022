#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    // loop through height
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    // loop through width
    // move the pointer from top left corner to bottom right corner
    //.rgbtBlue, Green, Red of each cell -> average(divide by 3.0)
    // round it
    // give that value to the image[height][width]
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through height 0 ~ height
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    // loop through width 0 ~ width/2 + 1
    // swap 1 and width, 2 and width - 1 until
    // width/2 + 1
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy of an image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // loop through height
    // loop through width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float count = 0;
            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i + m >= 0 && i + m < height && j + n >= 0 && j + n < width)
                    {
                        sumRed += copy[i + m][j + n].rgbtRed;
                        sumGreen += copy[i + m][j + n].rgbtGreen;
                        sumBlue += copy[i + m][j + n].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumRed / count);
            image[i][j].rgbtGreen = round(sumGreen / count);
            image[i][j].rgbtBlue = round(sumBlue / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copy of an image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // loop through height
    // loop through width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxRed = 0;
            int GxGreen = 0;
            int GxBlue = 0;
            int GyRed = 0;
            int GyGreen = 0;
            int GyBlue = 0;
            int GxGyRed = 0;
            int GxGyGreen = 0;
            int GxGyBlue = 0;
            int Gx_matrix[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int Gy_matrix[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i + m >= 0 && i + m < height && j + n >= 0 && j + n < width)
                    {
                        // Gx
                        GxRed += copy[i + m][j + n].rgbtRed * Gx_matrix[m + 1][n + 1];
                        GxGreen += copy[i + m][j + n].rgbtGreen * Gx_matrix[m + 1][n + 1];
                        GxBlue += copy[i + m][j + n].rgbtBlue * Gx_matrix[m + 1][n + 1];

                        // Gy
                        GyRed += copy[i + m][j + n].rgbtRed * Gy_matrix[m + 1][n + 1];
                        GyGreen += copy[i + m][j + n].rgbtGreen * Gy_matrix[m + 1][n + 1];
                        GyBlue += copy[i + m][j + n].rgbtBlue * Gy_matrix[m + 1][n + 1];
                    }
                }
            }
            GxGyRed = fmin(round(sqrt(GxRed * GxRed + GyRed * GyRed)), 255);
            GxGyGreen = fmin(round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen)), 255);
            GxGyBlue = fmin(round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue)), 255);

            // assign GxGy to image
            image[i][j].rgbtRed = GxGyRed;
            image[i][j].rgbtGreen = GxGyGreen;
            image[i][j].rgbtBlue = GxGyBlue;
        }
    }
    return;
}
