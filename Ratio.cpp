//#include <algorithm>
//#include <fstream>
//#include <sstream>
//#include "Ratio.h"
//#include <cstdlib>
//#include <iostream>
//namespace ratio {
//
//
//
//
//
////    template <typename T, typename charT, typename traits>
////    std::basic_ostream<charT, traits>& operator<< (std::basic_ostream<charT, traits>& os, const Ratio<T>& z)
////    {
////        std::basic_ostringstream<charT, traits> ss;
////        ss.copyfmt(os);
////        ss.width(0);    // We have copied width from os. Clear it.
////        ss << z.chys;
////        if(z.znam!=1)
////            ss << '/' << z.znam;
////        os << ss.str();
////        return os;
////    }
////    template<typename T>
////    std::istream &operator>> (std::istream &os, Ratio<T> &z)
////    {
////        int n, d;
////        if (os >> n) {
////            if (os.peek() == '/') {
////                char t;
////                os >> t;
////                if (os >> d) {
////                    z.num = n;
////                    z.denom = d;
////                }
////            } else {
////                z.num = n;
////                z.denom = 1;
////            }
////        }
////        return os;
////    }
//
//
//}