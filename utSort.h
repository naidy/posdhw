#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

TEST (Sort, sortByIncreasingPerimeter) {
	Rectangle r(0, 0, 3, 4);
	Circle c(0, 0, 3);
	vertex v1, v2, v3;
	v1.x = v1.y = 0;
	v2.x = 0; v2.y = 1;
	v3.x = 1; v3.y = 0;
	Triangle t(v1, v2, v3);

	std::list<Shape *> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);

	Sort s;
	s.sortByIncreasingPerimeter(&shapeList);

	std::array<Shape *, 3> sa;
	int i = 0;
	for (Shape *s: shapeList)
		sa[i++] = s;
	EXPECT_LE(sa[0]->perimeter(), sa[1]->perimeter());
	EXPECT_LE(sa[1]->perimeter(), sa[2]->perimeter());
}

TEST (Sort, sortByDecreasingPerimeter) {
	Rectangle r(0, 0, 3, 4);
	Circle c(0, 0, 3);
	vertex v1, v2, v3;
	v1.x = v1.y = 0;
	v2.x = 0; v2.y = 1;
	v3.x = 1; v3.y = 0;
	Triangle t(v1, v2, v3);

	std::list<Shape *> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);

	Sort s;
	s.sortByDecreasingPerimeter(&shapeList);

	std::array<Shape *, 3> sa;
	int i = 0;
	for (Shape *s: shapeList)
		sa[i++] = s;
	EXPECT_GE(sa[0]->perimeter(), sa[1]->perimeter());
	EXPECT_GE(sa[1]->perimeter(), sa[2]->perimeter());
}

TEST (Sort, sortByIncreasingArea) {
	Rectangle r(0, 0, 3, 4);
	Circle c(0, 0, 3);
	vertex v1, v2, v3;
	v1.x = v1.y = 0;
	v2.x = 0; v2.y = 1;
	v3.x = 1; v3.y = 0;
	Triangle t(v1, v2, v3);

	std::list<Shape *> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);

	Sort s;
	s.sortByIncreasingArea(&shapeList);

	std::array<Shape *, 3> sa;
	int i = 0;
	for (Shape *s: shapeList)
		sa[i++] = s;
	EXPECT_LE(sa[0]->area(), sa[1]->area());
	EXPECT_LE(sa[1]->area(), sa[2]->area());
}

TEST (Sort, sortByDecreasingArea) {
	Rectangle r(0, 0, 3, 4);
	Circle c(0, 0, 3);
	vertex v1, v2, v3;
	v1.x = v1.y = 0;
	v2.x = 0; v2.y = 1;
	v3.x = 1; v3.y = 0;
	Triangle t(v1, v2, v3);

	std::list<Shape *> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);

	Sort s;
	s.sortByDecreasingArea(&shapeList);

	std::array<Shape *, 3> sa;
	int i = 0;
	for (Shape *s: shapeList)
		sa[i++] = s;
	EXPECT_GE(sa[0]->area(), sa[1]->area());
	EXPECT_GE(sa[1]->area(), sa[2]->area());
}

TEST (Sort, sortByIncreasingCompactness) {
	Rectangle r(0, 0, 3, 4);
	Circle c(0, 0, 3);
	vertex v1, v2, v3;
	v1.x = v1.y = 0;
	v2.x = 0; v2.y = 1;
	v3.x = 1; v3.y = 0;
	Triangle t(v1, v2, v3);

	std::list<Shape *> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);

	Sort s;
	s.sortByIncreasingCompactness(&shapeList);

	std::array<Shape *, 3> sa;
	int i = 0;
	for (Shape *s: shapeList)
		sa[i++] = s;
	EXPECT_LE(sa[0]->area()/sa[0]->perimeter(), sa[1]->area()/sa[1]->perimeter());
	EXPECT_LE(sa[1]->area()/sa[1]->perimeter(), sa[2]->area()/sa[2]->perimeter());
}

#endif
