#pragma once
#include "SelectStatement.hpp"

#include "Filters.hpp"
#include "Helpers.hpp"

namespace ECE141 {
SelectStatement::SelectStatement(Keywords aStatementType, Entity *anEntity) : SQLStatement::SQLStatement(aStatementType), entity(anEntity) {}

StatusResult SelectStatement::parseOperand(Tokenizer &aTokenizer, Operand &anOperand) {
    StatusResult theResult{noError};
    if (aTokenizer.current().type == TokenType::identifier) {
        anOperand.ttype = TokenType::identifier;
        try {
            int index = 0;

            while (theTableAttributes[index].getName() != aTokenizer.current().data) {
                index++;
            }
            anOperand.dtype = theTableAttributes[index].getType();
            anOperand.name = theTableAttributes[index].getName();

        } catch (...) {
            anOperand.ttype = TokenType::string;
            anOperand.value = aTokenizer.current().data;
        }
    } else if (aTokenizer.current().type == TokenType::number) {
        anOperand.ttype = TokenType::number;
        anOperand.value = aTokenizer.current().data;
    } else if (aTokenizer.current().type == TokenType::string) {
        anOperand.ttype = TokenType::string;
        anOperand.value = aTokenizer.current().data;
    } else {
        theResult.error = syntaxError;
    }
    return theResult;
}

StatusResult SelectStatement::parseStatement(Tokenizer &aTokenizer) {
    // First word is SELECT, so skip that
    aTokenizer.next();
    StatusResult theStatus = this->parseSelect(aTokenizer);
    if (!theStatus) {
        return StatusResult(Errors::unknownCommand);
    }

    aTokenizer.next();  // FROM
    aTokenizer.next();  // TableName
    this->theDBQuery.setEntityName(aTokenizer.current().data);
    aTokenizer.next();
    Filters thefilters;
    while (aTokenizer.more() && aTokenizer.current().data != ";") {
        switch (aTokenizer.current().keyword) {
            case Keywords::where_kw:
                // aTokenizer.next(1);  // skip where
                // while (aTokenizer.more() && aTokenizer.current().data != ";") {
                //     // LHS
                //     Operand theLHS;
                //     if (!this->parseOperand(aTokenizer, theLHS)) {
                //         return StatusResult(Errors::syntaxError);
                //     }
                //     // todo : entity id

                //     // Operator
                //     aTokenizer.next();
                //     Operators theOps = Helpers::toOperator(aTokenizer.current().data);
                //     if (theOps == Operators::unknown_op) {
                //         return StatusResult(Errors::syntaxError);
                //     }
                //     // RHS
                //     aTokenizer.next();
                //     Operand theRHS;
                //     if (!this->parseOperand(aTokenizer, theRHS)) {
                //         return StatusResult(Errors::syntaxError);
                //     }
                //     Logical thelogic = Logical::no_op;
                //     aTokenizer.next();
                //     if (aTokenizer.current().keyword == Keywords::add_kw) {
                //         thelogic = Logical::and_op;
                //     } else if (aTokenizer.current().keyword == Keywords::or_kw) {
                //         thelogic = Logical::or_op;
                //     } else if (aTokenizer.current().keyword == Keywords::not_kw) {
                //         thelogic = Logical::not_op;
                //     }

                //     thefilters.add(new Expression(theLHS, theOps, theRHS, thelogic));
                // }

                theStatus = thefilters.parse(aTokenizer, *entity);
                if (!theStatus) {
                    return StatusResult(theStatus.error);
                }
                break;

            case Keywords::order_kw:
                aTokenizer.next();  // by
                if (aTokenizer.current().type == TokenType::keyword && aTokenizer.current().keyword == Keywords::by_kw) {
                    aTokenizer.next();  // should be fields
                    this->theDBQuery.setOrderBy(aTokenizer.current().data);
                    aTokenizer.next();
                } else {
                    return StatusResult(Errors::syntaxError);
                }
                break;
            case Keywords::limit_kw:
                aTokenizer.next();
                if (aTokenizer.current().type == TokenType::number) {
                    int thelimit = std::stoi(aTokenizer.current().data);
                    this->theDBQuery.setLimit(thelimit);
                } else {
                    return StatusResult(Errors::syntaxError);
                }
                break;
            default:
                break;
        }
    }
    return StatusResult(Errors::noError);
}

StatusResult SelectStatement::parseSelect(Tokenizer &aTokenizer) {
    // Means we have *
    if (aTokenizer.current().data == "*") {
        this->theDBQuery.setAllField(true);
        return StatusResult(Errors::noError);
    }

    // Means we have atleast one field
    // bug "invalid offset"
    while (aTokenizer.peek(aTokenizer.getIndex() + 1).keyword != Keywords::from_kw) {
        this->theDBQuery.setAttr(aTokenizer.current().data);
        aTokenizer.next(2);
    }
    // To push the last field
    this->theDBQuery.setAttr(aTokenizer.current().data);

    return StatusResult(Errors::noError);
}
}  // namespace ECE141
