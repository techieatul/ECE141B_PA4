#include "DBQuery.hpp"

namespace ECE141
{
  DBQuery::DBQuery() : theEntityName(""), theAllField(false), theEntity(nullptr),theOrderBy(""),isAscending(true),theLimit(-1) {}

  DBQuery::DBQuery(const DBQuery &aCopy) {
    *this = aCopy;
  }

  DBQuery::~DBQuery() {}

  DBQuery& DBQuery::operator=(const DBQuery &aCopy) {
    theEntityName = aCopy.theEntityName;
    theAttr = aCopy.theAttr;
    theAllField = aCopy.theAllField;
    return *this;
  }

  DBQuery& DBQuery::setOrderBy(std::string &anOrderBy){
    this->theOrderBy = anOrderBy;
    return *this;
  }
  DBQuery& DBQuery::setIsAcending(bool &anAsc){
    this->isAscending = anAsc;
    return *this;
  }

  DBQuery& DBQuery::setAllField(bool aValue){
    theAllField = aValue;
    return *this;
  }
  DBQuery& DBQuery::setAttr(const std::string &aField){
    theAttr.push_back(aField);
    return *this;
  }  

  DBQuery& DBQuery::setAttrPrimary(const std::string &aField){
    theAttr.insert(theAttr.begin(),aField);
    return *this;
  }
  DBQuery& DBQuery::setLimit(int &aLimit){
    this->theLimit = aLimit;
    return *this;
  }

  DBQuery& DBQuery::setEntityName(const std::string &aName){
    theEntityName = aName;
    return *this;
  }

  DBQuery& DBQuery::setEntity(Entity *aEntity){
    theEntity = aEntity;
    return *this;
  }

  DBQuery& DBQuery::setFilterKey(const Keywords &aKey){
    theFilterKey.push_back(aKey);
    return *this;
  }

 

} // namespace ECE141
