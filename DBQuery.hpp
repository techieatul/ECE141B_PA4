#ifndef DBQuery_hpp
#define DBQuery_hpp

#include <stdio.h>
#include <string>
#include <optional>
#include <vector>
#include "Attribute.hpp"
#include "Row.hpp"
#include "Entity.hpp"
#include "Tokenizer.hpp"
#include "Filters.hpp"

namespace ECE141
{
  class DBQuery
  {
  public:
    DBQuery();
    DBQuery(const DBQuery &aCopy);
    ~DBQuery();
    DBQuery &operator=(const DBQuery &aCopy);

   
    bool        getAllField() { return theAllField; };
    StringList  getAttr() { return theAttr; };
    std::string getEntityName() { return theEntityName; };
    Entity*     getEntity() { return theEntity; };
    std::string&    getOrderBy(){ return theOrderBy;}
    bool         getIsAscending(){return isAscending;}
    Filters&     getFilter(){return theFilter;}
    int          getLimit(){return theLimit;}
   
    DBQuery& setAllField(bool aValue);
    DBQuery& setAttr(const std::string &aField);
    DBQuery& setEntityName(const std::string &aName);
    DBQuery& setEntity(Entity *anEntity);
    DBQuery& setOrderBy(std::string &anOrderBy);
    DBQuery& setIsAcending(bool &anAsc);
    DBQuery& setLimit(int &aLimit);


  protected:
    std::string theEntityName;
    Entity*     theEntity;
    StringList  theAttr;
    bool        theAllField;
    std::string theOrderBy;
    bool        isAscending;
    Filters     theFilter;
    int         theLimit;
  };
} // namespace ECE141


#endif /* DBQuery_hpp */