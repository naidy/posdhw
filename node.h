#ifndef NODE_H
#define NODE_H
#include "term.h"
#include <iostream>
#include <string>

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

	void traversal(vector<Term*> &terms){
		if (payload == TERM)
			terms.push_back(term);
		else{
			left->traversal(terms);
			right->traversal(terms);
		}
	}

	bool evaluate() {
		if (payload == SEMICOLON){
			return left->evaluate() && right->evaluate();
		} else if (payload == COMMA){
			vector<Term*> terms;
			traversal(terms);
			for (int i = 0; i < terms.size()-1; i++){
				for (int j = i + 1; j < terms.size(); j++){
					for (int k = 0; k < terms[i]->arity(); k++){
						for (int l = 0; l < terms[j]->arity(); l++){
							//std::cout << terms[i]->args(k)->symbol() << std::string(" == ") << terms[j]->args(l)->symbol() << std::endl;
							if (terms[i]->args(k)->symbol() == terms[j]->args(l)->symbol())
								terms[i]->args(k)->match(*(terms[j]->args(l)));
						}
					}
				}
			}
			return left->evaluate() && right->evaluate();
		} else if (payload == EQUALITY){
			return left->term->match(*(right->term));
		}
	}

  Operators payload;
  Term* term;
  Node* left;
  Node* right;
};

#endif