#include "struct.h"
#include "iterator.h"
Iterator<Term*> * Struct::createIterator()
{
  return new TermIterator<Term*>(this);
}

Iterator<Term*> * Struct::createBFSIterator(){
	return nullptr;
}

Iterator<Term*> * Struct::createDFSIterator(){
	return nullptr;
}