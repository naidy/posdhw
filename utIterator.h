#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator<Term*> *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term*> *it = s.createIterator();
    it->first();
    it->next();
    Struct *s2 = dynamic_cast<Struct *>(it->currentItem());

    Iterator<Term*> *it2 = s2->createIterator();
    it2->first();
    ASSERT_EQ("X", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_EQ("2", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*> *itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  Iterator<Term*> * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, Struct_BFSIterator){
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term*> * it = s.createBFSIterator();
  it->first();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("t(X, 2)", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_TRUE(it->isDone());
}

TEST(iterator, List_BFSIterator){
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  List l({ &one, &t, &Y });
  Iterator<Term*> * it = l.createBFSIterator();
  it->first();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("t(X, 2)", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_TRUE(it->isDone());
}

TEST(iterator, Struct_DFSIterator){
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term*> * it = s.createDFSIterator();
  it->first();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("t(X, 2)", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_TRUE(it->isDone());
}

TEST(iterator, List_DFSIterator){
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  List l({ &one, &t, &Y });
  Iterator<Term*> * it = l.createDFSIterator();
  it->first();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("t(X, 2)", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("X", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("Y", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_TRUE(it->isDone());
}

TEST(iterator, Struct_and_List_BFSIterator){
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"), 
    sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"), pickleSlice2("pickleSlice2"), 
    onion1("onion1"), onion2("onion2"), coke("coke"), fries1("fries1"), fries2("fries2");
  List pickleSlice({ &pickleSlice1, &pickleSlice2});
  List onion({ &onion1, &onion2});
  List fries({ &fries1, &fries2});
  Struct bigMac(Atom("bigMac"), { &bun, &beefPatty, &shreddedLettuce, &sauce, &cheese, 
    &pickleSlice, &onion});
  Struct combo1(Atom("combo1"), { &bigMac, &coke, &fries});

  Iterator<Term*> * it = combo1.createBFSIterator();
  it->first();
  EXPECT_EQ("bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onion1, onion2])", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("coke", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("[fries1, fries2]", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("bun", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("beefPatty", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("shreddedLettuce", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("sauce", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("cheese", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("[pickleSlice1, pickleSlice2]", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("[onion1, onion2]", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("fries1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("fries2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("pickleSlice1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("pickleSlice2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("onion1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("onion2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_TRUE(it->isDone());
}

TEST(iterator, Struct_and_List_DFSIterator){
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"), 
    sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"), pickleSlice2("pickleSlice2"), 
    onion1("onion1"), onion2("onion2"), coke("coke"), fries1("fries1"), fries2("fries2");
  List pickleSlice({ &pickleSlice1, &pickleSlice2});
  List onion({ &onion1, &onion2});
  List fries({ &fries1, &fries2});
  Struct bigMac(Atom("bigMac"), { &bun, &beefPatty, &shreddedLettuce, &sauce, &cheese, 
    &pickleSlice, &onion});
  Struct combo1(Atom("combo1"), { &bigMac, &coke, &fries});

  Iterator<Term*> * it = combo1.createDFSIterator();
  it->first();
  EXPECT_EQ("bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onion1, onion2])", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("bun", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("beefPatty", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("shreddedLettuce", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("sauce", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("cheese", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("[pickleSlice1, pickleSlice2]", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("pickleSlice1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("pickleSlice2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("[onion1, onion2]", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("onion1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("onion2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("coke", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("[fries1, fries2]", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("fries1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("fries2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_TRUE(it->isDone());
}

TEST(iterator, List_and_Struct_BFSIterator){
  Number one(1), two(2), three(3), four(4), five(5), six(6);
  Struct odd(Atom("odd"), { &one, &three, &five});
  Struct even(Atom("even"), { &two, &four, &six});
  List l({ &odd, &even});

  Iterator<Term*> * it = l.createBFSIterator();
  it->first();
  EXPECT_EQ("odd(1, 3, 5)", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("even(2, 4, 6)", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("3", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("5", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("4", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("6", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_TRUE(it->isDone());
}

TEST(iterator, List_and_Struct_DFSIterator){
  Number one(1), two(2), three(3), four(4), five(5), six(6);
  Struct odd(Atom("odd"), { &one, &three, &five});
  Struct even(Atom("even"), { &two, &four, &six});
  List l({ &odd, &even});

  Iterator<Term*> * it = l.createDFSIterator();
  it->first();
  EXPECT_EQ("odd(1, 3, 5)", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("1", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("3", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("5", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("even(2, 4, 6)", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("2", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("4", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_EQ("6", it->currentItem()->symbol());
  EXPECT_FALSE(it->isDone());
  it->next();
  EXPECT_TRUE(it->isDone());
}

#endif
