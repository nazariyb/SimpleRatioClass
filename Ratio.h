#ifndef RATIO_RATIO_H
#define RATIO_RATIO_H

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <cmath>

unsigned gcd (unsigned a, unsigned b)
{
    assert(a != 0 && b != 0);
    while (a != b) {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}

namespace ratio {

#define ASSERT_CHECK_IF_REDUCED(obj) \
assert ( \
(obj).denom > 0 && \
( (obj).num == 0 || gcd( std::abs((obj).num), (obj).denom ) == 1 ) \
)

#define ASSERT_CHECK_IF_REDUCED_THIS \
ASSERT_CHECK_IF_REDUCED( *this );

#define ASSERT_CHECK_IF_REDUCED_BOTH do{ \
ASSERT_CHECK_IF_REDUCED( *this );\
ASSERT_CHECK_IF_REDUCED( rhs ); \
} while(false)

    template<typename T>
    class Ratio
        {
    private:
        T num;
        T denom;

        void reduce ();

    public:
        explicit Ratio (T n, T d) :
                num(n), denom(d)
        {
            reduce();
        }

        explicit Ratio () : Ratio(0, 1) { }

        template<typename U>
        explicit Ratio (U n) : Ratio(n, 1) { }

        Ratio operator- () const;

        inline Ratio operator+ () const { return *this; }

        inline bool operator== (const Ratio &rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_BOTH;
            return num == rhs.num && denom == rhs.denom;
        }

        template<typename U>
        inline bool operator== (U rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_THIS
            return num == rhs && denom == 1;
        }

        inline bool operator!= (const Ratio &rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_BOTH;
            return num != rhs.num || denom != rhs.denom;
        }

        template<typename U>
        inline bool operator!= (U rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_THIS
            return num != rhs || denom != 1;
        }

        inline bool operator> (const Ratio &rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_BOTH;
            return num * rhs.denom > rhs.num * denom;
        }

        template<typename U>
        inline bool operator> (U rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_THIS
            return num > rhs * denom;
        }

        inline bool operator>= (const Ratio &rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_BOTH;
            return (*this > rhs) || (*this == rhs);
        }

        template<typename U>
        inline bool operator>= (U rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_THIS
            return (*this > rhs) || (*this == rhs);
        }

        inline bool operator< (const Ratio &rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_BOTH;
            return !(*this >= rhs);
        }

        template<typename U>
        inline bool operator< (U rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_THIS
            return !(*this >= rhs);
        }

        inline bool operator<= (const Ratio &rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_BOTH;
            return (*this < rhs) || (*this == rhs);
        }

        template<typename U>
        inline bool operator<= (U rhs) const
        {
            ASSERT_CHECK_IF_REDUCED_THIS
            return (*this < rhs) || (*this == rhs);
        }

        Ratio<T> &operator+= (const Ratio<T> &rhs);

        template<typename U>
        Ratio &operator+= (U rhs);

        Ratio<T> &operator-= (const Ratio<T> &rhs);

        template<typename U>
        Ratio &operator-= (U rhs);

        Ratio &operator*= (const Ratio &rhs);

        template<typename U>
        Ratio &operator*= (U rhs);

        Ratio &operator/= (const Ratio &rhs);

        template<typename U>
        Ratio &operator/= (U rhs);

        Ratio &invert ();

        template<typename U>
        friend std::ostream &operator<< (std::ostream &os, const Ratio<U> &z);

        template<typename U>
        friend std::istream &operator>> (std::istream &os, Ratio<U> &z);

        template<typename U>
        friend Ratio<U> modf (Ratio<U> x, Ratio<U> *iptr);

        template<typename U>
        friend Ratio<U> pow (const Ratio<U> &base, int exponent);

        template<typename U>
        friend Ratio<U> ceil (const Ratio<U> &x);

        template<typename U>
        friend Ratio<U> floor (const Ratio<U> &x);

        inline Ratio<T> fabs (const Ratio<T> &x)
        {
            assert(x.denom > 0);
            return initRatio(x.num > 0 ? x.num : -x.num, x.denom);
        }

        inline Ratio<T> abs (const Ratio<T> &x)
        {
            return fabs(x);
        }

        template<typename U>
        friend Ratio<U> trunc (const Ratio<U> &x);

        };

    template<typename T>
    void Ratio<T>::reduce ()
    {
        if (num == 0) denom = 1;

        if (denom < 0) {
            num = -num;
            denom = -denom;
        }

        if (num == 1 || denom == 1) return;

        int dv = num > 0 ? gcd(num, denom) : gcd(-num, denom);
        num /= dv;
        denom /= dv;

    }

    template<typename T>
    Ratio<T> Ratio<T>::operator- () const
    {
        Ratio res(*this);
        res.num = -res.num;
        return res;
    }

    template<typename T>
    Ratio<T> &Ratio<T>::operator+= (const Ratio<T> &rhs)
    {
        num = num * rhs.denom + denom * rhs.num;
        denom *= rhs.denom;
        reduce();
        return *this;
    }

    template<typename T>
    template<typename U>
    Ratio<T> &Ratio<T>::operator+= (U rhs)
    {
        num += (denom * rhs);
        return *this;
    }

    template<typename T>
    Ratio<T> &Ratio<T>::operator-= (const Ratio<T> &rhs)
    {
        num = num * rhs.denom - denom * rhs.num;
        denom *= rhs.denom;
        reduce();
        return *this;
    }

    template<typename T>
    template<typename U>
    Ratio<T> &Ratio<T>::operator-= (U rhs)
    {
        num -= denom * rhs;
        return *this;
    }

    template<typename T>
    Ratio<T> &Ratio<T>::operator*= (const Ratio<T> &rhs)
    {
        num *= rhs.num;
        denom *= rhs.denom;
        reduce();
        return *this;
    }

    template<typename T>
    template<typename U>
    Ratio<T> &Ratio<T>::operator*= (U rhs)
    {
        num *= rhs;
        reduce();
        return *this;
    }

    template<typename T>
    Ratio<T> &Ratio<T>::operator/= (const Ratio<T> &rhs)
    {
        num *= rhs.denom;
        denom *= rhs.num;
        reduce();
        return *this;
    }

    template<typename T>
    template<typename U>
    Ratio<T> &Ratio<T>::operator/= (U rhs)
    {
        denom *= rhs;
        reduce();
        return *this;
    }

    template<typename T>
    std::ostream &operator<< (std::ostream &os, const Ratio<T> &z)
    {
        std::stringstream ss;
        ss << z.num;
        if (z.denom != 1)
            ss << '/' << z.denom;
        os << ss.str();
        return os;
    }

    template<typename T>
    std::istream &operator>> (std::istream &os, Ratio<T> &z)
    {
        int num, denom;
        if (os >> num) {
            if (os.peek() == '/') {
                char t;
                os >> t;
                if (os >> denom) {
                    z.num = num;
                    z.denom = denom;
                }
            } else {
                z.num = num;
                z.denom = 1;
            }
        }
        return os;
    }


    template<typename T, typename U>
    inline bool operator== (U lhs, const Ratio<T> &rhs)
    {
        return rhs == lhs;
    }

    template<typename T, typename U>
    inline bool operator!= (U lhs, const Ratio<T> &rhs)
    {
        return !(rhs == lhs);
    }

    template<typename T, typename U>
    inline bool operator> (U lhs, const Ratio<T> &rhs)
    {
        return rhs < lhs;
    }

    template<typename T, typename U>
    inline bool operator>= (U lhs, const Ratio<T> &rhs)
    {
        return rhs <= lhs;
    }

    template<typename T, typename U>
    inline bool operator< (U lhs, const Ratio<T> &rhs)
    {
        return rhs > lhs;
    }

    template<typename T, typename U>
    inline bool operator<= (U lhs, const Ratio<T> &rhs)
    {
        return rhs >= lhs;
    }

    template<typename T>
    inline Ratio<T> operator+ (Ratio<T> lhs, const Ratio<T> &rhs)
    {
        return lhs += rhs;
    }

    template<typename T, typename U>
    inline Ratio<T> operator+ (Ratio<T> lhs, U rhs)
    {
        return lhs += rhs;
    }

    template<typename T, typename U>
    inline Ratio<T> operator+ (U lhs, Ratio<T> rhs)
    {
        return rhs += lhs;
    }

    template<typename T>
    inline Ratio<T> operator- (Ratio<T> lhs, const Ratio<T> &rhs)
    {
        return lhs -= rhs;
    }

    template<typename T, typename U>
    inline Ratio<T> operator- (Ratio<T> lhs, U rhs)
    {
        return lhs -= rhs;
    }

    template<typename T, typename U>
    inline Ratio<T> operator- (U lhs, Ratio<T> rhs)
    {
        return (-rhs) += lhs;
    }

    template<typename T>
    inline Ratio<T> operator* (Ratio<T> lhs, const Ratio<T> &rhs)
    {
        return lhs *= rhs;
    }

    template<typename T, typename U>
    inline Ratio<T> operator* (Ratio<T> lhs, U rhs)
    {
        return lhs *= rhs;
    }

    template<typename T, typename U>
    inline Ratio<T> operator* (U lhs, Ratio<T> rhs)
    {
        return rhs *= lhs;
    }

    template<typename T>
    inline Ratio<T> operator/ (Ratio<T> lhs, const Ratio<T> &rhs)
    {
        return lhs /= rhs;
    }

    template<typename T, typename U>
    inline Ratio<T> operator/ (Ratio<T> lhs, U rhs)
    {
        return lhs /= rhs;
    }

    template<typename T, typename U>
    inline Ratio<T> operator/ (U lhs, Ratio<T> rhs)
    {
        return rhs.invert() *= lhs;
    }

    template<typename T>
    Ratio<T> &Ratio<T>::invert ()
    {
        std::swap(num, denom);
        return *this;
    }

    template<typename T>
    Ratio<T> modf (Ratio<T> x, Ratio<T> *iptr)
    {
        Ratio<T> res{x.num % x.denom, x.denom};
        iptr->num = x.num / x.denom;
        iptr->denom = 1;
        return res;
    }

    template<typename T>
    Ratio<T> pow (const Ratio<T> &base, int exponent)
    {
        if (exponent == 0) {
            return Ratio<T>{1};
        }
        return (exponent < 0) ?
               Ratio<T>{
                       std::pow(base.denom, exponent),
                       std::pow(base.num, exponent)} :
               Ratio<T>{
                       std::pow(base.num, exponent),
                       std::pow(base.denom, exponent)};
    }


    template<typename T>
    Ratio<T> ceil (const Ratio<T> &x)
    {
        return Ratio<T>{static_cast<T>(std::ceil(static_cast<double>(x.num) / x.denom))};
    }

    template<typename T>
    Ratio<T> floor (const Ratio<T> &x)
    {
        return Ratio<T>{static_cast<T>(std::floor(x.num / x.denom))};
    }

    template<typename T>
    Ratio<T> trunc (const Ratio<T> &x)
    {
        return Ratio<T>{static_cast<T>(std::trunc(x.num / x.denom))};
    }

}
#endif //RATIO_RATIO_H
