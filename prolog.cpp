#include "atom.h"
#include "number.h"
#include "variable.h"

//Number
bool Number::match(Variable& v){
	Number n(_value);
	return v.match(n);
}

bool Number::match(Atom atom){
	return this->value() == atom._symbol;
}

//Variable
bool Variable::match(Number n){
	if (n.value() == _value)
		return true;
	bool ret = _assignable;
	if(_assignable){
	  _value = n.value();
	  _assignable = false;
	}
	return ret;
}

//Atom
bool Atom::match(Number n){
	return n.value() == _symbol;
}

bool Atom::match(Variable& v){
	Atom tom(_symbol);
	return v.match(tom);
}