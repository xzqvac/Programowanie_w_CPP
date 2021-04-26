#include "image.h"

int main()
{
    Image image;
    image.load("D:\\Studia UWr\\Semestr 2\\Programowanie  w C++\\Programowanie w C++\\Programowanie_w_CPP\\Lista 5\\obrazek.ppm");
    /*image.add_watermark();
    for(int i=0;i<10;i++)
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
    image.shrink();
    image.save_as("x.ppm");

    /*const int Mil = 0;
    Mil = 3;
    const int Mol;
    Mol = 0;*/

    /* Dane zapisane w trybie binarnym są w niezmienionej formie zapisywane do pliku,
      podczas gdy w trybie tekstowym, dane są modyfikowane, by pasowały do konwencji zapisu tekstu w danym środowisku.*/




    return 0;
}
