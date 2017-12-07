#include "list.h"
#include "iterator.h"
Iterator<Term*> * List::createIterator()
{
  return new Iterator<Term*>(this);
}

Iterator<Term*> * List::createBFSIterator(){
	return nullptr;
}

Iterator<Term*> * List::createDFSIterator(){
	return nullptr;
}