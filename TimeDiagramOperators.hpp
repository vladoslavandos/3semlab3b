#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>

struct Signal
{
    char state;
    int time;
    Signal(char _state = 'X', int _time = 0);
    friend std::istream& operator>>(std::istream& st, Signal& sig);
    friend std::ostream& operator<<(std::ostream& st, Signal const& sig); 
};

class Diagram
{
    public:
    static size_t constexpr __n = 20;

    private:
    Signal sections[__n];
    size_t csize;

    public:
    inline size_t size() const { return csize; }
    Diagram();
    Diagram(char const* ascii_symbs);
    Diagram(char _state);
    friend std::istream& operator>>(std::istream& st, Diagram& diagram);
    friend std::ostream& operator<<(std::ostream& st, Diagram const& diagram);
    Diagram operator+(Diagram const& second) const;
    Diagram& operator()(int timestamp, Diagram const& second);
    Diagram& operator*=(size_t n);
    Diagram& operator>>=(int tshift);
    Diagram& operator<<=(int tshift);
    Diagram& mergeBlocks();
    int get_total_time() const;
    void insertSignalBlock(Signal&& sig);
};