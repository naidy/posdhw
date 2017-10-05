#include "atom.h"
#include "number.h"
#include "variable.h"

//Number
bool Number::match(Variable* v){
	return v->match(this);
}

bool Number::match(Variable v){
	return v.match(this);
}

//Variable
bool Variable::match(Number* n){
	if (n->value() == _value)
		return true;
	bool ret = _assignable;
	if(_assignable){
	  _value = n->value();
	  _assignable = false;
	}
	return ret;
}
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
	return false;
}

bool Atom::match(Variable* v){
	v->match(this);
}

bool Atom::match(Variable v){
	return v.match(this);
}