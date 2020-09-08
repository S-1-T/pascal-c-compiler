#ifndef SEMANTICANALYSIS_H_
#define SEMANTICANALYSIS_H_

#include <utility>
#include <iostream>

#include "syntax_tree/syntax_tree.h"
#include "../defines/types.h"
#include "symbol_sheet.h"

bool semantic_analyse(Program* root);

#endif