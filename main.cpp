#include "TimeDiagramOperators.hpp"

void exit(Diagram& sel) {exit(0);}
void print_diagram(Diagram& diagram) {std::cout << diagram;}
void input_diagram(Diagram& diagram)
{
    std::cout << "Input signal sections for diagram:\n\
    number of section - first line;\n\
    sections - then (format <state|0, 1 or X> <time|integer>): \n";
    std::cin >> diagram;
}

void add_diagram(Diagram& diagram)
{
    std::cout << "Input second chart to add (e.g. 00001110101XXX): ";
    std::string inp;
    std::cin >> inp;
    Diagram other;
    try
    {
        other = Diagram(inp.c_str());
    }
    catch( std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
    try
    {
        std::cout << "Resolved diagram: \n" << diagram + other;
    }
    catch(std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

void replace_diagram_part(Diagram& diagram)
{
    std::cout << "Input timestamp to replace: ";
    int ts;
    std::cin >> ts;
    std::cout << "Input second chart to replace with (e.g. 00001110101XXX): ";
    std::string inp;
    std::cin >> inp;
    Diagram other;
    try
    {
        other = Diagram(inp.c_str());
    }
    catch(std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
    try
    {
        std::cout << "Resolved diagram: \n" << diagram(ts, other);
    }
    catch(std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

void repeat_diagram(Diagram& diagram)
{
    std::cout << "Input n (repetition number): ";
    size_t n;
    std::cin >> n;
    try
    {
        std::cout << "Resolved diagram: \n" << (diagram *= n);
    }
    catch(std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

void lshift_diagram(Diagram& diagram)
{
    std::cout << "Input shifting time: ";
    int ts;
    std::cin >> ts;
    try
    {
        std::cout << "Resolved diagram: \n" << (diagram <<= ts);
    }
    catch(std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

void rshift_diagram(Diagram& diagram)
{
    std::cout << "Input shifting time: ";
    int ts;
    std::cin >> ts;
    try
    {
        std::cout << "Resolved diagram: \n" << (diagram >>= ts);
    }
    catch(std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

void (*options[])(Diagram&) = {exit, print_diagram, input_diagram, add_diagram, replace_diagram_part, repeat_diagram, lshift_diagram, rshift_diagram};

int main()
{
    Diagram diagram;
    while (1)
    {
        std::cout << "Ask...\n\
        [0]Exit\n\
        [1]Print diagram\n\
        [2]Input diagram\n\
        [3]Add diagram to other\n\
        [4]Replace spec timestamp of diagram with other diagram\n\
        [5]Repeat diagram n times\n\
        [6]Shift diagram to the left\n\
        [7]]Shift diagram to the right\n"
        ">>";
        int choice;
        std::cin >> choice;
        if (choice > sizeof(options) / 8 - 1 || choice < 0)
        {
            std::cout << "Try again!\n";
            continue;
        }
        std::cin.get();
        options[choice](diagram);
        std::cout << std::endl;
    }
}