#ifndef ITERATOR_H
#define ITERATOR_H

#include <vector>
using std::vector;

template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template <class T>
class TermIterator :public Iterator<T>{
public:
  TermIterator(T term): _index(0), _term(term) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _term->args(_index);
  }

  bool isDone() const {
    return _index >= _term->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  T _term;
};

template <class T>
class BFSIterator :public Iterator<T>{
public:
  BFSIterator(T term): _index(0), _term(term) {
    vector<T> q;
    q.push_back(_term);
    while(!q.empty()){
      T t = q.front();
      _v.push_back(t);

      q.pop_back();

      if (t->arity() == 0)
        break;

      for (int i = 0; i < t->arity(); i++){
        q.insert(q.begin(), t->args(i));
      }
    }
  }

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _term->args(_index);
  }

  bool isDone() const {
    return _index >= _term->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  T _term;
  vector<T> _v;
};

template <class T>
class DFSIterator :public Iterator<T>{
public:
  DFSIterator(T term): _index(0), _term(term) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _term->args(_index);
  }

  bool isDone() const {
    return _index >= _term->arity();
  }

  void next() {
    _index++;
  }
  
private:
  int _index;
  T _term;
};

/*
template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

class NullIterator :public Iterator<Term*>{
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

class StructIterator :public Iterator<Term*> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

class ListIterator :public Iterator<Term*> {
public:
  ListIterator(List *list): _index(0), _list(list) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  List* _list;
};
*/
#endif
