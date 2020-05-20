//
// Created by RinChanNOW! on 2020/5/20.
// 语法树的节点
//

#ifndef PASCAL_C_COMPILER_SYNTAX_TREE_H
#define PASCAL_C_COMPILER_SYNTAX_TREE_H
// 非终结符
class Program;
//class ProgramHead;
class ProgramBody;
class IdentifierList;
class ConstDeclarations;
class ConstDeclaration;
//class TypeDeclarations;
class VarDeclarations;
class SubProgramDeclarations;
class CompoundStatement;
class ConstVariable;
//class TypeDeclaration;
class Type;
class StandardType;
// TODO Record 类型
// class RecordBody
class Periods;
class Period;
class VarDeclaration;
class SubProgramDeclaration;
class SubProgramHead;
// 简化语言，不允许函数和过程嵌套
class SubProgramBody;
class FormalParameter;
class ParameterLists;
class Parameter;
//class ParameterList;
class VarParameter;
class ValueParameter;
class StatementList;
class Statement;
class Variable;
class Expression;
//class Updown;
class CallProcedureStatement;
class IdVarParts;
class IdVarPart;
class ExpressionList;
//class ElsePart;
class SimpleExpression;
class Term;
class Factor;
//class UnsignConstVariable;
// 终结符
class Id;
class Not;
class IfThenElseStatement;
class ForStatement;
class AssignOp;
class RelOp;
class AddOp;
class MulOp;

#endif //PASCAL_C_COMPILER_SYNTAX_TREE_H
