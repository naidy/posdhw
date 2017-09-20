#include <list>
#include "Shapes.h"

class Sort {
  
  public :static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
  	struct Compare
  	{
    	bool operator()(Shape* a, Shape* b) const {
        	return a->perimeter() < b->perimeter();
    	}
  	};
  	shapeList->sort(Compare());
  };

  public :static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
  	struct Compare
  	{
    	bool operator()(Shape* a, Shape* b) const {
        	return a->perimeter() > b->perimeter();
    	}
  	};
  	shapeList->sort(Compare());
  };

  public :static void sortByIncreasingArea(std::list<Shape *> * shapeList){
  	struct Compare
  	{
    	bool operator()(Shape* a, Shape* b) const {
        	return a->area() < b->area();
    	}
  	};
  	shapeList->sort(Compare());
  };

  public :static void sortByDecreasingArea(std::list<Shape *> * shapeList){
  	struct Compare
  	{
    	bool operator()(Shape* a, Shape* b) const {
        	return a->area() > b->area();
    	}
  	};
  	shapeList->sort(Compare());
  };
  
  public :static void sortByIncreasingCompactness(std::list<Shape *> * shapeList){
  	struct Compare
  	{
    	bool operator()(Shape* a, Shape* b) const {
        	return (a->area() / a->perimeter()) < (b->area() / b->perimeter());
    	}
  	};
  	shapeList->sort(Compare());
  };
  // Compactness = area/perimeter
};
