#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "atom.h"
using std::string;

class Variable : public Term{
public:
  Variable(string s):_symbol(s), _value(s){}
  string const _symbol;
  string symbol() const {return _symbol;}
  string value() const { return _value; }
  bool isMatch(){return !_assignable;}
  bool match(Variable & v){
    for (int i = 0; i < _match.size(); i++){
      if (_match[i] == &v)
        return true;
    }
    _value = v.value() ;
    if (_assignable && v.isMatch()){
      _assignable = false;
    }
    _match.push_back(&v);
    v.match(*this);
    for (int i = 0; i < _match.size(); i++)
      _match[i]->match(v);
    return true;
  }
  bool match(Term & term){
    bool ret = _assignable;
    if(_assignable){
      _value = term.value() ;
      _assignable = false;
      for (int i = 0; i < _match.size(); i++)
        _match[i]->match(term);
    }
    return ret;
  }

private:
  string _value;
  bool _assignable = true;
  std::vector<Variable*> _match;
};

bool Atom::match(Variable & v){
  return v.match(*this);
}

bool Number::match(Variable & v){
  return v.match(*this);
}

#endif
