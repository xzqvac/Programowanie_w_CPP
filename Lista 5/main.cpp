#include "image.h"

int main()
{
    Image image;
    image.load("D:\\Studia UWr\\Semestr 2\\Programowanie  w C++\\Programowanie w C++\\Programowanie_w_CPP\\Lista 5\\obrazek.ppm");
    //image.add_watermark();
    /*for(int i=0;i<10;i++)
    {
        image.blurr();
    }*/
    //image.extract_layer(ColorLayer::Green);
    //image.filter();
    //image.flip_horizontally();
    //image.flip_vertically();
    //image.inflate();
    //image.negative();
    //image.inflate();
    //image.rotate_clockwise_90();
    //image.to_grayscale();
    //image.sepia();
    //image.shrink();
    //image.height();
    //image.width();
    image.save_as("x.ppm");
    
    return 0;
}
