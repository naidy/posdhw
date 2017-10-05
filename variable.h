#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"
using std::string;

class Number;

class Variable{
public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string value(){ return _value; }
  bool match( Atom atom ){
    if (_value == atom._symbol)
      return true;
    bool ret = _assignable;
    if(_assignable){
      _value = atom._symbol ;
      _assignable = false;
    }
    return ret;
  }
  bool match( Atom* atom ){
    if (_value == atom->_symbol)
      return true;
    bool ret = _assignable;
    if(_assignable){
      _value = atom->_symbol ;
      _assignable = false;
    }
    return ret;
  }
  bool match(Number* n);
  bool match(Number n);

private:
  string _value;
  bool _assignable = true;
};

#endif
