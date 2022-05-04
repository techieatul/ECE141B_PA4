#pragma once
#ifndef Filter_hpp
#define Filter_hpp
#include "Row.hpp"
#include <algorithm>
#include <vector>
#include "BasicTypes.hpp"
#include "DBQuery.hpp"
namespace ECE141 {

class Filter {
   public:
    Filter();
    ~Filter();
    Filter& filterOrderBy(DBQuery &aDB,RawRowCollection &theFilteredRow);
    Filter& filterLimit();
    Filter& filterWhere();
};

}  // namespace ECE141

#endif