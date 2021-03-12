#include <iostream>
#include <cmath>
#include <chrono>


using namespace std;

const int N = 1000000;

double aver1()
{
    double suma = 0.0;
    for(double j = 1.0; j <= N; j++)
    {
        suma += (pow(-1,j+1))/(2*j-1);
    }
    suma = 4*suma;
    cout<<"Podpunkt a - pierwszy sposob "<<suma<<endl;
    return suma;
}

double aver2()
{
    double suma = 0.0;
    for(int j = 1; j <= N; j++)
    {
        if(j % 2 ==0)
            suma += -1.0/(2*j-1);
        else
            suma += 1.0/(2*j-1);
    }
    suma = 4*suma;
    cout<<"Podpunkt a - drugi sposob "<<suma<<endl;
    return suma;
}

double b()
{
    double iloczyn = 1;
    for(double j = 1.0; j <= N; j++)
    {
        iloczyn *= (4*j*j)/(4*j*j-1);
    }
    iloczyn = 2*iloczyn;
    cout<<"Podpunkt b "<<iloczyn<<endl;
    return iloczyn;
}

double c()
{
    double suma = 0;
    for(double j=1.0; j<= N; j++)
    {
        suma += 1/((2*j-1)*(2*j-1));
    }
    suma = sqrt(8 * suma);
    cout<<"Podpunkt c "<<suma<<endl;
    return suma;
}

int main() {
    std::chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2;

    start1 = std::chrono::system_clock::now();
    aver1();
    end1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
    std::cout<< "Czas wykonywania (pow): " << elapsed_seconds1.count() << "s\n";

    start2 = std::chrono::system_clock::now();
    aver2();
    end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    std::cout<< "Czas wykonywania (modulo): " << elapsed_seconds2.count() << "s\n";
    cout<<"Roznica jednego rzedu, a wiec bardzo duza"<<endl;
    b();
    c();
    return 0;
}
