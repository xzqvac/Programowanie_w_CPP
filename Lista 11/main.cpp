#include <iostream>
#include <string>

void run(int argc, const char* argv[])
{
    int numberOne;
    int numberTwo;
    int result = 0;

    try
    {
        numberOne = std::stoi(argv[1]);
        numberTwo = std::stoi(argv[3]);
    }

    catch (std::logic_error &ex)
    {
        throw std::logic_error("Podano niewlasciwe argumenty");
    }

        unsigned int sign = int(*argv[2]);

        if (argc == 4)
        {
            switch (sign)
            {
                case '+':
                    result = numberOne + numberTwo;
                    break;
                case '-':
                    result = numberOne - numberTwo;
                    break;
                case '/':
                    if (numberTwo != 0)
                        result = numberOne / numberTwo;
                    else
                        throw std::logic_error("Nie mozna dzielic przez zero");
                    break;
                case '*':
                    result = numberOne * numberTwo;
                    break;
                case '%':
                    if (numberTwo != 0)
                        result = numberOne / numberTwo;
                    else
                        throw std::logic_error("Nie mozna dzielic przez zero");
                    break;
                case '&':
                    result = numberOne & numberTwo;
                    break;
                case '|':
                    result = numberOne | numberTwo;
                    break;
                case '^':
                    result = numberOne ^ numberTwo;
                    break;
                default:
                    throw std::logic_error("Zly operator");
                    break;
            }
            std::cout << result << std::endl;
        }
        else
            throw std::logic_error("Niewlasciwa liczba argumentow");
}

int main(int argc, const char* argv[])
{
    try
    {
       run(argc, argv);
    }

    catch(std::logic_error &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
