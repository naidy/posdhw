#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "number.h"
#include "list.h"

class Node;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      /*for (int i = 0; i < _terms.size(); i++){
        if (_terms[i]->symbol() == symtable[_scanner.tokenValue()].first)
            return _terms[i];
        for (int j = 0; j < _terms[i]->arity(); j++){
          if (_terms[i]->args(j)->symbol() == symtable[_scanner.tokenValue()].first)
            return _terms[i]->args(j);
        }
      }*/
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }

  void matchings();

  Node* expressionTree() {
    return _et;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Node* _et;
  Scanner _scanner;
  int _currentToken;
};

#include "node.h"

void Parser::matchings() {
  Term* ct;
  Node *l, *r, *top;
  int token;

  ct = createTerm();
  _terms.push_back(ct);
  l = new Node(TERM, ct, nullptr, nullptr);  //std::cout << l->payload << std::endl;
  token = _scanner.nextToken();
  while(token == '=' || token == ',' || token == ';'){
    if (token == '='){
      ct = createTerm();
      _terms.push_back(ct);
      r = new Node(TERM, ct, nullptr, nullptr);
      top = new Node(EQUALITY, nullptr, l, r);
    }
    else if (token == ',' || token == ';'){
      Node* tmp = top;
      ct = createTerm();
      _terms.push_back(ct);
      l = new Node(TERM, ct, nullptr, nullptr);
      _scanner.nextToken();  // '='
      ct = createTerm();
      _terms.push_back(ct);
      r = new Node(TERM, ct, nullptr, nullptr);
      top = new Node(EQUALITY, nullptr, l, r);
      l = tmp;
      r = top;
      if (token == ','){
        top = new Node(COMMA, nullptr, l, r);
      }
      else if (token == ';'){
        top = new Node(SEMICOLON, nullptr, l, r);
      }
    }
    token = _scanner.nextToken();
  }
  _et = top;
}

#endif