#ifndef __TOOLS_HPP__
#define __TOOLS_HPP__

    inline float absolute_value(float d)
    {
        return (d < 0) ? -d : d;
    };

    inline double absolute_value(double d)
    {
        return (d < 0) ? -d : d;
    };

    inline long double absolute_value(long double d)
    {
        return (d < 0) ? -d : d;
    };

    inline bool is_zero(float d)
    {
        float a = absolute_value(d);
        return (a < 1E-7) ? true : false;
    };

    inline bool is_zero(double d)
    {
        double a = absolute_value(d);
        return (a < 1E-7) ? true : false;
    };

    inline bool is_zero(long double d)
    {
        long double a = absolute_value(d);
        return (a < 1E-7) ? true : false;
    };

#endif
