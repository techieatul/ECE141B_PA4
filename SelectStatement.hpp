#pragma once
#include <iostream>
#include <string>

#include "Attribute.hpp"
#include "DBQuery.hpp"
#include "SQLStatement.hpp"
#include "Statement.hpp"
namespace ECE141 {
class SelectStatement : public SQLStatement {
   public:
    SelectStatement(Keywords aStatementType, Entity *anEntity);
    ~SelectStatement(){};
    StatusResult parseStatement(Tokenizer &aTokenizer);
    StatusResult parseSelect(Tokenizer &aTokenizer);
    StatusResult parseOperand(Tokenizer &aTokenizer, Operand &anOperand);

   protected:
    Entity *entity;
};

}  // namespace ECE141