#include "list.h"
#include "variable.h"

bool Variable::match(List & term){
  if (term.checkOccur(*this))
  	return false;
  else{
    if(!_inst){
      _inst = &term ;
      return true;
    }
    return _inst->match(term);
  }
}
