#include <iostream>
#include <cmath>

using namespace std;

float a()
{
    float suma = 0;
    for(float j = 1; j <= 1000000; j++)
    {
        suma = suma + (pow(-1,j+1))/(2*j-1);
    }
    suma = 4*suma;
    cout<<"Podpunkt a "<<suma<<endl;

}

float b()
{
    float iloczyn = 1;
    for(int j = 1; j <= 1000000; j++)
    {
        iloczyn = iloczyn * (4*pow(j,2))/(4*pow(j,2)-1);
    }
    iloczyn = 2*iloczyn;
    cout<<"Podpunkt b "<<iloczyn<<endl;

}

float c()
{
    float suma = 0;
    for(int j=1; j<= 1000000; j++)
    {
        suma = suma + 1/(pow(2*j-1,2));
    }
    suma = sqrt(8 * suma);
    cout<<"Podpunkt c "<<suma<<endl;

}

int main() {
    a();
    b();
    c();
    return 0;
}
