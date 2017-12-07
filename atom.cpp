#include "atom.h"
#include "variable.h"
#include "iterator.h"
#include <typeinfo>

Iterator<Term*> * Term::createIterator(){
  return new Iterator<Term*>(this);
}

Iterator<Term*> * Term::createBFSIterator(){
	return nullptr;
}

Iterator<Term*> * Term::createDFSIterator(){
	return nullptr;
}

bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable))
    return a.match(*this);
  else
    return symbol() == a.symbol();
}
