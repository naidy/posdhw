#ifndef NUMBER_H
#define NUMBER_H

#include "atom.h"
#include "variable.h"

class Number{
public:
  Number(int i):_value(i){}
  string _symbol;
  string symbol(){ return _symbol;}
  int value(){ return _value; }
  bool match( int i ){
    return _value == i;
  }
  bool match(Number n){
  	return _value == n.value();
  }
  bool match(Atom atom){return false;}
  bool match(Variable v);
  bool match(Variable* v);

private:
  int _value;
};

#endif