#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>
using std::vector;

class Variable ;

class List : public Term {
public:
  string symbol() const {
    string s;
    s += "[";

    if (!isEmpty())
      s += _elements[0]->symbol();
    for (int i = 1; i < _elements.size(); i++){
      s += ", ";
      s += _elements[i]->symbol();
    }
    s += "]";

    return s;
  }
  bool isEmpty() const {
    return _elements.size() == 0;
  }
  string value() const {};
  bool match(Term & term) {};
public:
  List (): _elements(0) {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const {};
  List * tail() const {};
  Term * args(int index) {
    return _elements[index];
  }
  int arity() const {return _elements.size();}
private:
  vector<Term *> _elements;
};

#endif