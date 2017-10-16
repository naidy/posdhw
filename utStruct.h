#include <vector>
#include "atom.h"
#include "struct.h"
#include "number.h"
#include "variable.h"

// When Struct s contains a Variable X
// Then #symbol() should return "s(X)"
// and #value() should also return "s(X)"
TEST(Struct, var)
{
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  ASSERT_EQ("s(X)", s.symbol());
  ASSERT_EQ("s(X)", s.value());
}

// Given there is Struct s contains a Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() should return "s(X)"
// and #value() should also return "s(tom)"
TEST(Struct, var_match_atom)
{
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Atom tom("tom");
  X.match(tom);
  ASSERT_EQ("s(X)", s.symbol());
  ASSERT_EQ("s(tom)", s.value());
}

// Given there are Struct s1 and Struct s2
// When Struct s1 contains Struct s2
// And Struct s2 contains a Variable X
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should also return "s1(s2(X))"
TEST(Struct, nested_struct1)
{
  Variable X("X");
  std::vector<Term *> v2 = {&X};
  Struct s2(Atom("s2"), v2);
  std::vector<Term *> v1 = {&s2};
  Struct s1(Atom("s1"), v1);
  ASSERT_EQ("s1(s2(X))", s1.symbol());
  ASSERT_EQ("s1(s2(X))", s1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(tom))"
TEST(Struct, nested_struct2)
{
  Variable X("X");
  std::vector<Term *> v2 = {&X};
  Struct s2(Atom("s2"), v2);
  std::vector<Term *> v1 = {&s2};
  Struct s1(Atom("s1"), v1);
  Atom tom("tom");
  X.match(tom);
  ASSERT_EQ("s1(s2(X))", s1.symbol());
  ASSERT_EQ("s1(s2(tom))", s1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Number pi: 3.14
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(3.14))"
TEST(Struct, nested_struct3)
{
  Variable X("X");
  std::vector<Term *> v2 = {&X};
  Struct s2(Atom("s2"), v2);
  std::vector<Term *> v1 = {&s2};
  Struct s1(Atom("s1"), v1);
  Number pi(3.14);
  X.match(pi);
  ASSERT_EQ("s1(s2(X))", s1.symbol());
  ASSERT_EQ("s1(s2(3.14))", s1.value());
}

// Given there are Struct s1 contains Struct s2 and Variable X
// And Struct s2 contains Variable Y
// When Variable X matches Variable Y
// And Variable X matches Atom "kent_beck"
// Then #symbol() of s1 should return "s1(s2(Y), X)"
// and #value() of s1 should return "s1(s2(kent_beck), kent_beck)"
TEST(Struct, nested_struct_and_multiVariable)
{
  Variable X("X"), Y("Y");
  std::vector<Term *> v2 = {&Y};
  Struct s2(Atom("s2"), v2);
  std::vector<Term *> v1 = {&s2, &X};
  Struct s1(Atom("s1"), v1);
  Atom kent_beck("kent_beck");
  X.match(Y);
  X.match(kent_beck);
  ASSERT_EQ("s1(s2(Y), X)", s1.symbol());
  ASSERT_EQ("s1(s2(kent_beck), kent_beck)", s1.value());
}
