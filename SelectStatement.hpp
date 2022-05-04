#pragma once
#include <iostream>
#include "Statement.hpp"
#include "SQLStatement.hpp"
#include <string>
#include "Attribute.hpp"
#include "DBQuery.hpp"
namespace ECE141{
    class SelectStatement:public SQLStatement{
        public:
        SelectStatement(Keywords aStatementType);
        ~SelectStatement(){};
        StatusResult parseStatement(Tokenizer &aTokenizer);
        StatusResult parseSelect(Tokenizer &aTokenizer);
        
    };

}