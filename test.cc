#include <fstream>
#include <iostream>



// -----------------------------------------------------------
// Sample Type for proving this works with user-defined types.
//
// You can use this type by running, for example:
//     make TYPE="SampleType" SENTINEL="SampleType(-1, -1)"
struct SampleType {
    int x;
    int y;

    SampleType() { }
    SampleType(int x, int y) : x(x), y(y) { }
};

bool operator==(const SampleType& l, const SampleType& r) {
    return (l.x == r.x && l.y == r.y);
}

bool operator<(const SampleType& l, const SampleType& r) {
    return (l.x < r.x && l.y <= r.y);
}

std::istream& operator>>(std::istream& is, SampleType& obj) {
    is >> obj.x;
    obj.y = 42;
    return is;
}

std::ostream& operator<<(std::ostream& os, const SampleType& obj) {
    os << "[" << obj.x << ":" << obj.y << "]";
    return os;
}
// -----------------------------------------------------------

