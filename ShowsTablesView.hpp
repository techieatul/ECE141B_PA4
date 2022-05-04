#pragma once

#include <iostream>
#include "View.hpp"
#include <vector>
#include "Row.hpp"
#include "Entity.hpp"
#include "DBQuery.hpp"




namespace ECE141{
    class ShowsTablesView: public View{
        protected:
            std::vector<std::string> theRow;
            std::vector<std::vector<std::string>> theRows;
            std::vector<size_t> theColWidth;
            size_t theCurrCol;

        public:
            ShowsTablesView(bool aPrintRow);
            ~ShowsTablesView();
            bool printrow;
            bool addToRow(std::string aMember);
            bool addRow(std::vector<std::string>& aRow);
            bool endOfRow();
            bool show(std::ostream &aStream);
            bool showQuery(RawRowCollection &theRows, DBQuery &aDBQuery,std::ostream &anOutput);
            bool printLine(std::ostream &aStream);
            bool printRow(std::ostream &aStream,std::vector<std::string> aRow);
            

};

}


