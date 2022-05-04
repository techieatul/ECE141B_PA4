#pragma once
#include "SelectStatement.hpp"

#include "Helpers.hpp"

namespace ECE141{

    SelectStatement::SelectStatement(Keywords aStatementType):SQLStatement::SQLStatement(aStatementType){}

    StatusResult SelectStatement::parseStatement(Tokenizer &aTokenizer){
        // First word is SELECT, so skip that
        aTokenizer.next();
        StatusResult theStatus = this->parseSelect(aTokenizer);
        if(!theStatus){
            return StatusResult(Errors::unknownCommand);

        }

        aTokenizer.next(); // FROM
        aTokenizer.next(); // TableName
        this->theDBQuery.setEntityName(aTokenizer.current().data);
        return StatusResult(Errors::noError);

    }

    StatusResult SelectStatement::parseSelect(Tokenizer &aTokenizer){
        // Means we have *
        if(aTokenizer.current().data == "*"){
            this->theDBQuery.setAllField(true);
            return StatusResult(Errors::noError);
        }
        
        
        // Means we have atleast one field
        while(aTokenizer.peek(aTokenizer.getIndex()+1).keyword != Keywords::from_kw){
            this->theDBQuery.setAttr(aTokenizer.current().data);
            aTokenizer.next(2);

        }
        // To push the last field
        this->theDBQuery.setAttr(aTokenizer.current().data);

        return StatusResult(Errors::noError);

    }

}

