#include "image.h"

#include <fstream>
#include <ostream>
#include <experimental/filesystem>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cstdlib>

void Image::load(const std::string& filename)
{
    constexpr auto MAGIC = "P6";

    this->filename = filename;

    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::invalid_argument("failed to open \"" + filename + "\"");

    in >> magic;
    if (magic != MAGIC) throw std::logic_error("unknown magic number " + magic);

    in >> my_width >> my_height >> color_depth;

    if (!in || my_width < 0 || my_width > 10000 || my_height < 0 || my_height > 10000 || color_depth <= 0 ||
        color_depth > 255)
        throw std::logic_error("invalid image parameter(s): " + std::to_string(my_width) + " " +
                               std::to_string(my_height) + " " + std::to_string(color_depth));
    in.ignore(1);
    pixels.resize(my_height);
    for (auto& line : pixels)
    {
        line.resize(my_width);
        in.read(reinterpret_cast<char*>(&line[0]), my_width * sizeof(RGB));
        if (!in) throw std::logic_error("failed to read binary pixel data from file " + filename);
    }
}

void Image::save_as(const std::string& filename)
{
    constexpr auto MAGIC = "P6";

    this->filename = filename;

    std::ofstream out(filename, std::ios::binary);
    if (!out) throw std::invalid_argument("failed to open \"" + filename + "\"");

    out << magic;
    if (magic != MAGIC) throw std::logic_error("unknown magic number " + magic);
    out << my_width << " " << my_height << " " << color_depth << '\n';


    pixels.resize(my_height);
    for (auto& line : pixels)
    {
        line.resize(my_width);
        out.write(reinterpret_cast<char*>(&line[0]), my_width * sizeof(RGB));
        if (!out) throw std::logic_error("failed to read binary pixel data from file " + filename);
    }


}

void Image::add_watermark()
{
    for(int i=my_height-331; i<my_height-100; i++)
    {
        for (int j=my_width-224; j<my_width-30; j++)
        {
                pixels[i][j].red = 71;
                pixels[i][j].green = 225;
                pixels[i][j].blue = 12;
        }
    }
}

void Image::blurr()
{
    int tempred = 0;
    int tempgreen = 0;
    int tempblue = 0;

    for(int i = 0;i < my_height; i++)
    {
        for (int j = 0; j < my_width; j++)
        {
           if(i >= 1 && j >= 1 && i < my_height -1 && j < my_width -1)
           {

               tempred = pixels[i-1][j].red + pixels[i-1][j+1].red + pixels[i][j+1].red + pixels[i+1][j+1].red +
                      pixels[i+1][j].red + pixels[i+1][j-1].red + pixels[i][j-1].red + pixels[i-1][j-1].red +
                      pixels[i][j].red;
               tempgreen = pixels[i-1][j].green + pixels[i-1][j+1].green + pixels[i][j+1].green + pixels[i+1][j+1].green +
                      pixels[i+1][j].green + pixels[i+1][j-1].green + pixels[i][j-1].green + pixels[i-1][j-1].green +
                      pixels[i][j].green;
               tempblue = pixels[i-1][j].blue + pixels[i-1][j+1].blue + pixels[i][j+1].blue + pixels[i+1][j+1].blue +
                      pixels[i+1][j].blue + pixels[i+1][j-1].blue + pixels[i][j-1].blue + pixels[i-1][j-1].blue +
                      pixels[i][j].blue;

               pixels[i][j].red = (unsigned char)round(tempred / 9);
               pixels[i][j].green = (unsigned char)round(tempgreen / 9);
               pixels[i][j].blue = (unsigned char)round(tempblue / 9);
           }

           else if(i == 0 && j == 0)
           {
               tempred = pixels[i][j+1].red + pixels[i+1][j+1].red + pixels[i+1][j].red + pixels[i][j].red;
               tempgreen = pixels[i][j+1].green + pixels[i+1][j+1].green + pixels[i+1][j].green + pixels[i][j].green;
               tempblue = pixels[i][j+1].blue + pixels[i+1][j+1].blue + pixels[i+1][j].blue + pixels[i][j].blue;

               pixels[i][j].red = (unsigned char)round(tempred / 4);
               pixels[i][j].green = (unsigned char)round(tempgreen / 4);
               pixels[i][j].blue = (unsigned char)round(tempblue / 4);
           }

           else if(i == 0 && j == my_width -1)
           {
               tempred = pixels[i+1][j].red + pixels[i+1][j-1].red + pixels[i][j-1].red + pixels[i][j].red;
               tempgreen = pixels[i+1][j].green + pixels[i+1][j-1].green + pixels[i][j-1].green + pixels[i][j].green;
               tempblue = pixels[i+1][j].blue + pixels[i+1][j-1].blue + pixels[i][j-1].blue + pixels[i][j].blue;

               pixels[i][j].red = (unsigned char)round(tempred / 4);
               pixels[i][j].green = (unsigned char)round(tempgreen / 4);
               pixels[i][j].blue = (unsigned char)round(tempblue / 4);
           }

           else if(i == my_height - 1 && j == 0)
           {
               tempred = pixels[i-1][j].red + pixels[i-1][j+1].red + pixels[i][j+1].red + pixels[i][j].red;
               tempgreen = pixels[i-1][j].green + pixels[i-1][j+1].green + pixels[i][j+1].green + pixels[i][j].green;
               tempblue = pixels[i-1][j].blue + pixels[i-1][j+1].blue + pixels[i][j+1].blue + pixels[i][j].blue;

               pixels[i][j].red = (unsigned char)round(tempred / 4);
               pixels[i][j].green = (unsigned char)round(tempgreen / 4);
               pixels[i][j].blue = (unsigned char)round(tempblue / 4);
           }

           else if(i == my_height - 1 && j == my_width -1)
           {
               tempred = pixels[i][j-1].red + pixels[i-1][j-1].red + pixels[i-1][j].red + pixels[i][j].red;
               tempgreen = pixels[i][j-1].green + pixels[i-1][j-1].green + pixels[i-1][j].green + pixels[i][j].green;
               tempblue = pixels[i][j-1].blue + pixels[i-1][j-1].blue + pixels[i-1][j].blue + pixels[i][j].blue;

               pixels[i][j].red = (unsigned char)round(tempred / 4);
               pixels[i][j].green = (unsigned char)round(tempgreen / 4);
               pixels[i][j].blue = (unsigned char)round(tempblue / 4);
           }

           else if(i == 0 && j >= 1 && j <= my_width - 1)
           {
               tempred = pixels[i][j+1].red + pixels[i+1][j+1].red + pixels[i+1][j].red + pixels[i+1][j+1].red +
                       pixels[i][j-1].red + pixels[i][j].red;
               tempgreen = pixels[i][j+1].green + pixels[i+1][j+1].green + pixels[i+1][j].green + pixels[i+1][j+1].green +
                       pixels[i][j-1].green + pixels[i][j].green;
               tempblue = pixels[i][j+1].blue + pixels[i+1][j+1].blue + pixels[i+1][j].blue + pixels[i+1][j+1].blue +
                       pixels[i][j-1].blue + pixels[i][j].blue;

               pixels[i][j].red = (unsigned char)round(tempred / 6);
               pixels[i][j].green = (unsigned char)round(tempgreen / 6);
               pixels[i][j].blue = (unsigned char)round(tempblue / 6);
           }

           else if(i >= 1 && j == 0 && i <= my_height - 1)
           {
               tempred = pixels[i-1][j].red + pixels[i-1][j+1].red + pixels[i][j+1].red + pixels[i+1][j+1].red +
                         pixels[i+1][j].red + pixels[i][j].red;
               tempgreen = pixels[i-1][j].green + pixels[i-1][j+1].green + pixels[i][j+1].green + pixels[i+1][j+1].green +
                           pixels[i+1][j].green + pixels[i][j].green;
               tempblue = pixels[i-1][j].blue + pixels[i-1][j+1].blue + pixels[i][j+1].blue + pixels[i+1][j+1].blue +
                          pixels[i+1][j].blue + pixels[i][j].blue;

               pixels[i][j].red = (unsigned char)round(tempred / 6);
               pixels[i][j].green = (unsigned char)round(tempgreen / 6);
               pixels[i][j].blue = (unsigned char)round(tempblue / 6);
           }

           else if(i == my_height - 1 && j >= 1 && j <= my_width - 1)
           {
               tempred = pixels[i][j-1].red + pixels[i-1][j-1].red + pixels[i-1][j].red + pixels[i-1][j+1].red +
                         pixels[i][j+1].red + pixels[i][j].red;
               tempgreen = pixels[i][j-1].green + pixels[i-1][j-1].green + pixels[i-1][j].green + pixels[i-1][j+1].green +
                           pixels[i][j+1].green + pixels[i][j].green;
               tempblue = pixels[i][j-1].blue + pixels[i-1][j-1].blue + pixels[i-1][j].blue + pixels[i-1][j+1].blue +
                          pixels[i][j+1].blue + pixels[i][j].blue;

               pixels[i][j].red = (unsigned char)round(tempred / 6);
               pixels[i][j].green = (unsigned char)round(tempgreen / 6);
               pixels[i][j].blue = (unsigned char)round(tempblue / 6);
           }

           else
           {
               tempred = pixels[i+1][j].red + pixels[i+1][j+1].red + pixels[i][j-1].red + pixels[i-1][j-1].red +
                         pixels[i-1][j].red + pixels[i][j].red;
               tempgreen = pixels[i+1][j].green + pixels[i+1][j+1].green + pixels[i][j-1].green + pixels[i-1][j-1].green +
                           pixels[i-1][j].green + pixels[i][j].green;
               tempblue = pixels[i+1][j].blue + pixels[i+1][j+1].blue + pixels[i][j-1].blue + pixels[i-1][j-1].blue +
                          pixels[i-1][j].blue + pixels[i][j].blue;

               pixels[i][j].red = (unsigned char)round(tempred / 6);
               pixels[i][j].green = (unsigned char)round(tempgreen / 6);
               pixels[i][j].blue = (unsigned char)round(tempblue / 6);
           }
        }
    }
}

void Image::extract_layer(ColorLayer color_layer)
{
    for(int i=0;i<my_height;i++)
    {
        for (int j=0;j<my_width;j++)
        {
            if(color_layer == ColorLayer::Red)
            {
                pixels[i][j].green = 0;
                pixels[i][j].blue = 0;
            }
            else if(color_layer == ColorLayer::Green)
            {
                pixels[i][j].red = 0;
                pixels[i][j].blue = 0;
            }
            else
            {
                pixels[i][j].green = 0;
                pixels[i][j].red = 0;
            }
        }
    }
}

void Image::filter()
{
    int diffred = 0;
    int diffgreen = 0;
    int diffblue = 0;

    for(int i = 0; i < my_height - 1; i++)
    {
        for (int j = 0; j < my_width; j++)
        {
            if(j >= 0 && j < my_width - 3)
            {
            diffred = abs(pixels[i][j].red - pixels[i + 1][j + 1].red);
            diffgreen = abs(pixels[i][j].green - pixels[i + 1][j + 1].green);
            diffblue = abs(pixels[i][j].blue - pixels[i + 1][j + 1].blue);

            pixels[i][j].red = diffred;
            pixels[i][j].green = diffgreen;
            pixels[i][j].blue = diffblue;
            }
        }
    }
}

void Image::flip_horizontally()
{
    int tempred = 0;
    int tempgreen = 0;
    int tempblue = 0;

    for (int i = 0; i < my_height; i++)
    {
        for (int j = 0; j < my_width / 2; j++)
        {
            tempred = pixels[i][j].red;
            tempgreen = pixels[i][j].green;
            tempblue = pixels[i][j].blue;

            pixels[i][j].red = pixels[i][my_width - j - 1].red;
            pixels[i][j].green = pixels[i][my_width - j - 1].green;
            pixels[i][j].blue = pixels[i][my_width - j - 1].blue;

            pixels[i][my_width - j - 1].red  = tempred;
            pixels[i][my_width - j - 1].green  = tempgreen;
            pixels[i][my_width - j - 1].blue  = tempblue;
        }
    }
}

void Image::flip_vertically()
{
    int tempred = 0;
    int tempgreen = 0;
    int tempblue = 0;

    for (int i = 0; i < my_height / 2; i++)
    {
        for (int j = 0; j < my_width; j++)
        {
            tempred = pixels[i][j].red;
            tempgreen = pixels[i][j].green;
            tempblue = pixels[i][j].blue;

            pixels[i][j].red = pixels[my_height - i - 1][j].red;
            pixels[i][j].green = pixels[my_height - i - 1][j].green;
            pixels[i][j].blue = pixels[my_height - i - 1][j].blue;

            pixels[my_height - i - 1][j].red  = tempred;
            pixels[my_height - i - 1][j].green  = tempgreen;
            pixels[my_height - i - 1][j].blue  = tempblue;
        }
    }
}

void Image::inflate()
{
    std::vector<std::vector<RGB>> temp;
    temp.resize(2 * my_height);

    for (auto& line : temp) {
        line.resize(2 * my_width);
    }

    for (int i = 0; i < my_height; i++)
    {
        for(int j = 0;j < my_width; j++)
        {
            temp[2 * i][2 * j].red = pixels[i][j].red;
            temp[2 * i][2 * j].green = pixels[i][j].green;
            temp[2 * i][2 * j].blue = pixels[i][j].blue;

            temp[2 * i + 1][2 * j].red = pixels[i][j].red;
            temp[2 * i + 1][2 * j].green = pixels[i][j].green;
            temp[2 * i + 1][2 * j].blue = pixels[i][j].blue;

            temp[2 * i][2 * j + 1].red = pixels[i][j].red;
            temp[2 * i][2 * j + 1].green = pixels[i][j].green;
            temp[2 * i][2 * j + 1].blue = pixels[i][j].blue;

            temp[2 * i + 1][2 * j + 1].red = pixels[i][j].red;
            temp[2 * i + 1][2 * j + 1].green = pixels[i][j].green;
            temp[2 * i + 1][2 * j + 1].blue = pixels[i][j].blue;
        }
    }
    pixels.swap(temp);
}

void Image::negative()
{
    for (int i = 0; i < my_height; i++)
    {
        for (int j = 0; j < my_width; j++)
        {
            pixels[i][j].red = 255 - pixels[i][j].red;
            pixels[i][j].green = 255 - pixels[i][j].green;
            pixels[i][j].blue = 255 - pixels[i][j].blue;
        }
    }
}

void Image::rotate_clockwise_90()
{
    std::vector<std::vector<RGB>> temp;
    temp.resize(my_width);

    for(int i = 0; i < my_width; i++)
    {
        temp[i].resize(my_height);
        for(int j = 0 ;j < my_height; j++)
        {
            temp[i][j].red = pixels[my_height - 1 - j][i].red;
            temp[i][j].green = pixels[my_height - 1 - j][i].green;
            temp[i][j].blue = pixels[my_height - 1 - j][i].blue;
        }
    }
    pixels.resize(my_width);

    for(int i = 0; i < my_width; i++)
    {
        pixels[i].resize(my_height);
    }

    for(int i = 0; i < my_width; i++)
    {
        for(int j = 0; j < my_height; j++)
        {
            pixels[i][j].red = temp[i][j].red;
            pixels[i][j].green = temp[i][j].green;
            pixels[i][j].blue = temp[i][j].blue;
        }
    }
    int temp_size = my_width;
    my_width = my_height;
    my_height = temp_size;
}

void Image::sepia()
{
    to_grayscale();
    for (int i = 0; i < my_height; i++)
    {
        for (int j = 0; j < my_width; j++)
        {
            pixels[i][j].red = round((pixels[i][j].red * 162 / 255));
            pixels[i][j].green = round((pixels[i][j].green * 128 / 255));
            pixels[i][j].blue = round((pixels[i][j].blue * 101 / 255));
        }
    }
}

void Image::shrink()
{
    std::vector<std::vector<RGB>> temp;
    temp.resize((my_height - 1) * 0.5);

    for (auto& line : temp) {
        line.resize(my_width * 0.5);
    }
    int avgred = 0;
    int avggreen = 0;
    int avgblue = 0;

    for (double i = 0; i < my_height - 1; i++) //  my_height - 1 poniewaz wysokosc obraza jest liczba nieparzysta
    {
        for(double j = 0; j < my_width; j++)
        {
            if(i == 0 && j == 0)
            {
                avgred = round((pixels[i][j + 1].red + pixels[i + 1][j].red) / 2);
                avggreen = round((pixels[i][j + 1].green + pixels[i + 1][j].green) / 2);
                avgblue = round((pixels[i][j + 1].blue + pixels[i + 1][j].blue) / 2);

                temp[i][j].red = avgred;
                temp[i][j].green = avggreen;
                temp[i][j].blue = avgblue;
            }

            else if(i >= 1 && j >= 1 && i <= my_height - 1 && j <= my_width - 1)
            {
                avgred = round((pixels[i][j - 1].red + pixels[i - 1][j].red + pixels[i][j + 1].red + pixels[i + 1][j].red) / 4);
                avggreen = round((pixels[i][j - 1].green + pixels[i - 1][j].green + pixels[i][j + 1].green + pixels[i + 1][j].green) / 4);
                avgblue = round((pixels[i][j - 1].blue + pixels[i - 1][j].blue + pixels[i][j + 1].blue + pixels[i + 1][j].blue) / 4);

                temp[i/2][j/2].red = avgred;
                temp[i/2][j/2].green = avggreen;
                temp[i/2][j/2].blue = avgblue;
            }

            else if(i == 0 && j == my_width -1)
            {
                tempred = pixels[i+1][j].red + pixels[i+1][j-1].red + pixels[i][j-1].red + pixels[i][j].red;
                tempgreen = pixels[i+1][j].green + pixels[i+1][j-1].green + pixels[i][j-1].green + pixels[i][j].green;
                tempblue = pixels[i+1][j].blue + pixels[i+1][j-1].blue + pixels[i][j-1].blue + pixels[i][j].blue;

                pixels[i][j].red = (unsigned char)round(tempred / 4);
                pixels[i][j].green = (unsigned char)round(tempgreen / 4);
                pixels[i][j].blue = (unsigned char)round(tempblue / 4);
            }
            /*
            else if(i == my_height - 1 && j == 0)
            {
                tempred = pixels[i-1][j].red + pixels[i-1][j+1].red + pixels[i][j+1].red + pixels[i][j].red;
                tempgreen = pixels[i-1][j].green + pixels[i-1][j+1].green + pixels[i][j+1].green + pixels[i][j].green;
                tempblue = pixels[i-1][j].blue + pixels[i-1][j+1].blue + pixels[i][j+1].blue + pixels[i][j].blue;

                pixels[i][j].red = (unsigned char)round(tempred / 4);
                pixels[i][j].green = (unsigned char)round(tempgreen / 4);
                pixels[i][j].blue = (unsigned char)round(tempblue / 4);
            }

            else if(i == my_height - 1 && j == my_width -1)
            {
                tempred = pixels[i][j-1].red + pixels[i-1][j-1].red + pixels[i-1][j].red + pixels[i][j].red;
                tempgreen = pixels[i][j-1].green + pixels[i-1][j-1].green + pixels[i-1][j].green + pixels[i][j].green;
                tempblue = pixels[i][j-1].blue + pixels[i-1][j-1].blue + pixels[i-1][j].blue + pixels[i][j].blue;

                pixels[i][j].red = (unsigned char)round(tempred / 4);
                pixels[i][j].green = (unsigned char)round(tempgreen / 4);
                pixels[i][j].blue = (unsigned char)round(tempblue / 4);
            }*/
    }
    pixels.swap(temp);
}


void Image::to_grayscale()
{
    int avg = 0;
    for (int i = 0; i < my_height; i++)
    {
        for (int j = 0; j < my_width; j++)
        {
            avg = round((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3);
            pixels[i][j].red = avg;
            pixels[i][j].green = avg;
            pixels[i][j].blue = avg;
        }
    }
}

int Image::height() const
{
    return my_height;
}

int Image::width() const
{
    return my_width;
}
