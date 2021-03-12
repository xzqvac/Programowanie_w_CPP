#include <iostream>
#include <cmath>

using namespace std;

double a(int i)
{
    if(i == 0)
    {
        return 1.0/sqrt(3);
    }
    else
    {
        return (sqrt(pow(a(i-1),2)+1.0)-1.0)/a(i-1.0);
    }
}

double b(int i)
{
    if(i == 0)
    {
        return 1.0/sqrt(3);
    }
    else
    {
        return (b(i-1)/(sqrt(pow(b(i-1),2)+1)+1));
    }
}


int main()
{
    cout.precision(10); //Zwiekszenie precyzji wyswietlania z domyslnego 6 na 10, aby mozna bylo porownac liczby
    cout<<"Punkt a"<<endl;
    for(int j= 0;j<=30;j++)
        cout<<j<<" = " << 6*pow(2,j)*a(j)<<endl;
    cout<<"W przypadku podpunktu a blad metody nie maleje wraz z i dla zadanego zakres 0:30"<<endl;

    cout<<"Punkt b"<<endl;
    for(int j= 0;j<=30;j++)
        cout<<j<<" = " << 6*pow(2,j)*b(j)<<endl;
    cout<<"W przypadku podpunktu b blad metody maleje wraz z i dla zadanego zakres 0:30."
          "W przypadku 16 iteracji wynik zgadza sie to z rozwinieciem liczby pi"<<endl;
    return 0;
}
