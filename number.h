#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
#include "variable.h"

using std::string;

class Number{
public:
  Number(int i):_value(i){}
  string _symbol;
  string symbol(){ return _symbol;}
  string value(){ return std::to_string(_value); }
  bool match( int i ){
    return _value == i;
  }
  bool match(Number n){
  	return this->value() == n.value();
  }
  bool match(Atom atom){return false;}
  bool match(Variable v);
  bool match(Variable* v);

private:
  int _value;
};

#endif