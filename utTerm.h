#ifndef UTTERM_H
#define UTTERM_H
#include "atom.h"
#include "number.h"
#include "variable.h"

//test Number.value()
TEST (Number,ctor) {
	Number n(25);
	ASSERT_EQ("25", n.value());
}
//test Number.symbol()
TEST (Number, symbol) {
	Number n(25);
	n._symbol = "n";
	ASSERT_EQ("n", n.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
	Number n(25);
	ASSERT_TRUE(n.match(25));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
	Number n(25);
	ASSERT_FALSE(n.match(0));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
	Number n(25);
	Atom atom("tom");
	ASSERT_FALSE(n.match(atom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVariable) {
	Number n(25);
	Variable X("X");
	ASSERT_TRUE(n.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
	Atom tom("tom");
	Number n(25);
	ASSERT_FALSE(tom.match(n));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVariable) {
	Atom tom("tom");
	Variable X("X");
	tom.match(&X);
	ASSERT_EQ("tom", X.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVariableInstantedToDiffConstant) {
	Variable X("X");
	Atom tom("tom");
	X.match(tom);
	tom.match(&X);
	ASSERT_EQ("tom", X.value());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVariableInstantedToDiffConstant) {
	Variable X("X");
	Atom jerry("jerry");
	Atom tom ("tom");
	X.match(jerry);
	ASSERT_FALSE(tom.match(&X));
}

// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
	Variable X("X");
	Number n(5);
	X.match(n);
	ASSERT_EQ("5", X.value());
}

// ?- X=25, X= 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
	Variable X("X");
	Number n(25), m(100);
	X.match(n);
	ASSERT_FALSE(X.match(m));
}

// ?- X=tom, X= 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
	Variable X("X");
	Atom tom("tom");
	Number n(25);
	X.match(tom);
	ASSERT_FALSE(X.match(n));
}
//?- tom=X, 25=X.
//false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
	Atom tom("tom");
	Variable X("X");
	Number n(25);
	tom.match(&X);
	ASSERT_FALSE(n.match(&X));
}
//?- X=tom, X=tom.
//true.
TEST(Variable, reAssignTheSameAtom){
	Variable X("X");
	Atom tom("tom");
	X.match(tom);
	ASSERT_TRUE(X.match(tom));
}
#endif