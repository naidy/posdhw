#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"

using std::string;
/*
namespace util { template <typename T> std::string to_string(const T& t) { std::string str{std::to_string (t)}; int offset{1}; if (str.find_last_not_of('0') == str.find('.')) { offset = 0; } str.erase(str.find_last_not_of('0') + offset, std::string::npos); return str; } }

class Number : public Term{
public:
  Number(double value):_value(value){}
  string _symbol;
  string symbol() const { return util::to_string(_value);}
  string value() const { return util::to_string(_value); }
  bool match(Term & term){
  	return this->value() == term.value();
  }

private:
  double _value;
};
*/

class Number : public Term{
public:
  Number(double db):Term(db) {}
};

#endif