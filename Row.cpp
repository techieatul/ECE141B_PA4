//
//  Row.cpp
//  PA3
//
//  Created by rick gessner on 4/2/22.
//

#include "Row.hpp"

#include <stdio.h>

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "BasicTypes.hpp"
#include "Helpers.hpp"

namespace ECE141 {

//
Row::Row(const Row &aRow) : blockNumber(aRow.blockNumber), data(aRow.data),entityId(aRow.entityId) {
    *this = aRow;
}
Row::Row(KeyValues aKeyValueList) : blockNumber(0), data(aKeyValueList) {}
Row::~Row() {}

Row &Row::operator=(const Row &aRow) {
    auto iter = aRow.data.begin();
    while(iter!=aRow.data.end()){
        std::string key = iter->first;
        Value v = iter->second;
        this->set(key,v);
        iter++;
    }
    entityId = aRow.entityId;
    return *this;
}



bool Row::operator==(Row &aCopy) const {
    if(aCopy.entityId!=this->entityId){
        return false;
    }
    if(aCopy.blockNumber!=this->blockNumber){
        return false;
    }
    if(aCopy.data.size() != this->data.size()){
        return false;
    }
    KeyValues theData = this->data;
    auto iter = aCopy.data.begin();
    while(iter!=aCopy.data.end()){
        std::string theKey = iter->first;
        Value theVal = iter->second;
        if(theData.find(theKey)==theData.end()){
            return false;
        }
        if(theData[theKey]!=theVal){
            return false;
        }

        iter++;

        
    }
    return true; 
}

// STUDENT: What other methods do you require?
void Row::getBlock(Block &aBlock) {
    aBlock.header.theEntityId = this->entityId;
    aBlock.header.type = 'D';
    this->encode(aBlock);
}

void Row::encode(Block &aBlock) {
    std::map<int, std::string> KeyValueToString = {
        {0, "B"}, {1, "I"}, {2, "D"}, {3, "S"}};
    KeyValues         theRowData = this->getData();
    std::stringstream ss;
    // Check below from dicussion in slidespace and correct later
    for (auto const &[key, val] : theRowData) {
        ss << key << " ";
        std::visit([&ss](const auto &elem) { ss << elem << " "; }, val);
        std::string valType = KeyValueToString[val.index()];
        ss << valType << " ";
    }
    ss << "END"<<" ";
    // Entity id(not null) first_name(nullable) last_name(nullable) email(not
    // null) Insert into users (email) VALUES (... , ....) decode Entity ->
    // AttributeList loop over the fields If field is missing and it is allowed
    // to be null, "NULL"

    ss.read(aBlock.payload, ECE141::kPayloadSize);
}

void Row::decode(Block &aBlock) {
    std::stringstream theStream;
    theStream.write(aBlock.payload, ECE141::kPayloadSize);
    std::string                                  theKey;
    std::string                                  theValtype;
    std::string                                  theVal;
    std::variant<bool, int, double, std::string> value;
    this->setBlockNumber(aBlock.header.theBlockId);
    this->entityId = aBlock.header.theTableNameHash;
    while (theStream >> theKey && theKey!="END") {
        theStream >> theVal >> theValtype;
        if (theValtype == "S") {
            this->set(theKey, std::string(theVal));

        } else if (theValtype == "I") {
            this->set(theKey, Helpers::convertStrToInt(theVal));

        } else if (theValtype == "B") {
            this->set(theKey, Helpers::convertStrToBool(theVal));

        } else {
            this->set(theKey, Helpers::convertStrToDouble(theVal));
        }
    }
}

Row &Row::set(const std::string &aKey, const Value &aValue) {
    this->data[aKey] = aValue;
    return *this;
}


}  // namespace ECE141
