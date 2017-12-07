#include "list.h"
#include "iterator.h"
Iterator<Term*> * List::createIterator()
{
  return new TermIterator<Term*>(this);
}

Iterator<Term*> * List::createBFSIterator(){
	return nullptr;
}

Iterator<Term*> * List::createDFSIterator(){
	return nullptr;
}