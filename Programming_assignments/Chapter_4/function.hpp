/**********************************************************************
 * Ver 2.3.* updated on Oct. 2nd, 2023, by EunTilofy
 * Only use the part of normal function.
***********************************************************************/
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <bits/stdc++.h>


// The class of all kinds of functions which maps x(in X) to y(in Y).
template <class Xtype, class Ytype = Xtype> 
class Function{
public:
    virtual Ytype operator() (const Xtype& x) const = 0;
};

#endif