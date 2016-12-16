#ifndef SORTDOUBLE_H
#define SORTDOUBLE_H

class SortDouble
{
public:
    SortDouble();

    bool operator() (const double d1, const double d2)
    {
        return d1 < d2;
    }
};

#endif // SORTDOUBLE_H
