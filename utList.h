#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
//#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List l;
  ASSERT_EQ("[]", l.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128, 496]"
TEST(List, Numbers) {
  Number m(8128), n(496);
  vector<Term*> args = {&m, &n};
  List l(args);
  ASSERT_EQ("[8128, 496]", l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom a("terence_tao"), b("alan_mathison_turing");
  vector<Term*> args = {&a, &b};
  List l(args);
  ASSERT_EQ("[terence_tao, alan_mathison_turing]", l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X"), Y("Y");
  vector<Term*> args = {&X, &Y};
  List l(args);
  ASSERT_EQ("[X, Y]", l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Atom tom("tom");
  Number n(496);
  Variable X("X");
  Atom a("terence_tao");
  vector<Term*> args = {&n, &X, &a};
  List l(args);
  ASSERT_FALSE(tom.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number m(8128);
  Number n(496);
  Variable X("X");
  Atom a("terence_tao");
  vector<Term*> args = {&n, &X, &a};
  List l(args);
  ASSERT_FALSE(m.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Variable X("X");
  vector<Term*> args1 = {&X};
  Struct s(Atom("s"), args1);
  Number n(496);
  Atom a("terence_tao");
  vector<Term*> args2 = {&n, &X, &a};
  List l(args2);
  ASSERT_FALSE(s.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable Y("Y");
  Number n(496);
  Variable X("X");
  Atom a("terence_tao");
  vector<Term*> args = {&n, &X, &a};
  List l(args);
  ASSERT_TRUE(Y.match(l));
  ASSERT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Number n(496);
  Variable X("X");
  Atom a("terence_tao");
  vector<Term*> args = {&n, &X, &a};
  List l(args);
  ASSERT_FALSE(X.match(l));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number n(496);
  Variable X("X");
  Atom a("terence_tao");
  vector<Term*> args = {&n, &X, &a};
  List l1(args), l2(args);
  ASSERT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number n(496);
  Variable X("X"), Y("Y");
  Atom a("terence_tao");
  vector<Term*> args1 = {&n, &X, &a};
  vector<Term*> args2 = {&n, &Y, &a};
  List l1(args1), l2(args2);
  ASSERT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number n(496), m(8128);
  Variable X("X");
  Atom a("terence_tao");
  vector<Term*> args1 = {&n, &X, &a};
  vector<Term*> args2 = {&n, &m, &a};
  List l1(args1), l2(args2);
  ASSERT_TRUE(l1.match(l2));
  ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Number n(496);
  Variable X("X"), Y("Y");
  Atom a("terence_tao"), b("alan_mathison_turing");
  vector<Term*> args = {&n, &X, &a};
  List l(args);
  ASSERT_TRUE(Y.match(l));
  ASSERT_TRUE(X.match(b));
  ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
  ASSERT_EQ("alan_mathison_turing", X.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term*> args1 = {&f};
  List l1(args1);
  vector<Term*> args2 = {&l1, &s, &t};
  List l2(args2);
  ASSERT_EQ("[first]", l2.head()->value());
  ASSERT_EQ("[second, third]", l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  ASSERT_EQ("third", l.tail()->tail()->head()->value());
  ASSERT_EQ("[]", l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  List l;
  ASSERT_THROW(l.head(), std::string);
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List l;
  ASSERT_THROW(l.tail(), std::string);
}




#endif