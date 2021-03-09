#include <iostream>
#include <climits>

using namespace std;

int main()
{
    int n=40;
    int wynik=0;
    for (int i=0;i<=n;i++)
    {
        if(i == 0)
        {
            wynik =  1;
        }
        else
        {
            wynik *= i;
        }
        cout << i <<"! = "<< wynik << endl;
    }
    cout <<"Najwyzsza poprawna wartosc osiaga dzialanie 12!"<< endl;
    cout <<"Wartosc dzialania 13! nie miesci sie w zakresie zmiennej typu int"<< endl;
    cout <<"Maksymalna wartosc dla typu int (zalezna od implementacji)"<<INT_MAX<< endl;
    cout <<"Problem mozna rozwiazac poprzez zamiane z typu int na long long int"<< endl;

    return 0;
}

