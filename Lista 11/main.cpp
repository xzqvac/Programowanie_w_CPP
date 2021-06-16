#include <iostream>
#include <string>

void run(int argc, const char* argv[])
{
    int myint1 = std::stoi(argv[1]);
    int myint2 = std::stoi(argv[3]);
    int result = 0;

    char* char_arr;
    std::string mathSign(argv[2]);
    char_arr = &mathSign[0];

    int obj = int(char_arr[0]);
    std::cout << obj << std::endl;


    switch(obj)
    {
        case '+':
            result = myint1 + myint2;
            break;
        case '-':
            result = myint1 - myint2;
            break;
        case '/':
            result = myint1 / myint2;
            break;
        case '*':
            result = myint1 * myint2;
            break;
        case '%':
            result = myint1 % myint2;
            break;
        case '&':
            result = myint1 & myint2;
            break;
        case '|':
            result = myint1 | myint2;
            break;
        case '^':
            result = myint1 ^ myint2;
            break;
    }
    std::cout<< result << std::endl;
}

int main(int argc, const char* argv[]) {
    run(argc, argv);
    return 0;
}
