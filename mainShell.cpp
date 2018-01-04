#include <iostream>
#include <string>
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include "parser.h"

using std::string;

int main( int argc , char **argv )
{
    string str, input, result;

    while(1){
	    do{
	    	input.clear();
		    std::cout << "?- ";
		    getline(std::cin, input);
		    str += input;
		} while (input == "");
	    if (input == "halt.")
	    	return 0;
	    while (input == "" || input.at(input.length()-1) == ';' || input.at(input.length()-1) == ','){
	    	input.clear();
		    std::cout << "|   ";
		    getline(std::cin, input);
		    str += input;
		    if (input == "halt.")
	    		return 0;
	    }
	    //std::cout << str << std::endl;
	    Scanner s(str);
		Parser p(s);
		try{
			p.buildExpression();
		    result = p.getExpressionTree()->getEvaluateString()+".";
		} catch (std::string & msg) {
		    std::cout << msg << std::endl;
		}
		std::cout << result << "\n" << std::endl;

		str.clear();
		result.clear();
	}

    return 0;
}