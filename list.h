#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;

class Variable;

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
  string value() const {
  	string s;
  	s += "[";

  	if (!isEmpty())
  		s += _elements[0]->value();
  	for (int i = 1; i < _elements.size(); i++){
  		s += ", ";
  		s += _elements[i]->value();
  	}
  	s += "]";

  	return s;
  }
  bool isEmpty() const {
  	return _elements.size() == 0;
  }
  bool match(Term & term) {
  	return symbol() == term.symbol();
  }
  bool match(List & term) {
	if (this->isEmpty() && term.isEmpty())
		return true;
	if (this->head()->match(*(term.head())))
		return this->tail()->match(*(term.tail()));
	return false;
  }
  bool match(Variable &);
  bool checkOccur(Term & t) const {
  	for (int i = 0; i < _elements.size(); i++)
  		if (_elements[i] == &t)
  			return true;
  	return false;
  }

public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const {
	if (isEmpty())
		throw string("Accessing head in an empty list");
	else
		return _elements[0];
  }
  List * tail() const{
  	if (isEmpty())
		throw string("Accessing tail in an empty list");
	else{
	  	vector<Term *> _new;
	  	for (int i = 1; i < _elements.size(); i++)
	  		_new.push_back(_elements[i]);
	  	List* l = new List(_new);
	  	return l;
  	}
  }

private:
  vector<Term *> _elements;

};

#endif