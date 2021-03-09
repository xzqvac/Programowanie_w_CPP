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
        return (sqrt(pow(a(i-1),2)+1)-1)/a(i-1);
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
        return (b(i-1)/(sqrt(pow(b(i-1),2)+1)));
    }
}


int main()
{
    cout<<"Punkt a"<<endl;
    for(int j= 0;j<=30;j++)
        cout<<j<<" = " << 6*pow(2,j)*a(j)<<endl;

    cout<<"Punkt b"<<endl;
    for(int j= 0;j<=30;j++)
        cout<<j<<" = " << 6*pow(2,j)*b(j)<<endl;
    return 0;
}
