#ifndef TYPE_H
#define TYPE_H

#include "tree.h"

void checkAssignCompatible(Type var, Type assigned);
void assign(Symbol *var, Symbol assigned);
#endif
