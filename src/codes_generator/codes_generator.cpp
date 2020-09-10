#include "codes_generator.h"
#include "exceptions.h"
#include "utils.h"

#include <fstream>
#include <strstream>

using namespace std;

vector<pair<string, vector<int>>> arr_id_list;

string Program::outputCodes() const
{

	string head =
		"#include <stdio.h>\n"
		"#include <stdlib.h>\n"
		"\n"
		"#define bool int\n"
		"#define true 1\n"
		"#define false 0\n"
		"\n";

	string programBody = mProgramBody->outputCodes();

	string codes = head + programBody;

	return codes;
}

string ProgramBody::outputCodes() const
{

	string _const = mConstDeclarations->outputCodes();

	string var = mVarDeclarations->outputCodes();

	string sub_program = mSubProgramDeclarations->outputCodes();

	string main_begin =
		"int main(int argc, char* argv[]) {\n";

	string Statement_List = mStatementList->outputCodes();

	string main_end =
		"	return 0;\n"
		"}\n"
		"\n";

	string Return = _const + var + sub_program + main_begin + Statement_List + main_end;

	return Return;
}

string ConstDeclarations::outputCodes()
{

	string codes = "\n";

	for (auto &i : mConstVector)
	{
		bool CONST_ID = false;

		switch (i.second->checkValueType())
		{
		case TYPE_INTEGER:
			codes += "const int ";
			break;

		case TYPE_REAL:
			codes += "const float ";
			break;

		case TYPE_CHAR:
			codes += "const char ";
			break;

		case TYPE_BOOLEAN:
			codes += "const bool ";
			break;

		case TYPE_ID:
			codes += "#define ";
			codes += i.first->outputCodes();
			codes += " ";

			if (i.second->mPolarity == CONST_NEGATIVE)
				codes += "-";
			codes += i.second->mId->outputCodes();
			codes += " \n";
			CONST_ID = true;

			break;

		default:
			throw TypeException();
		}
		if (!CONST_ID)
		{
			codes += i.first->outputCodes();
			codes += " = ";
			codes += i.second->outputCodes();
			codes += ";\n";
		}
	}

	codes += "\n";

	return codes;
}

string VarDeclarations::outputCodes()
{
	string codes = "\n";

	for (auto &i : mVariableVector)
	{
		if (i.second->checkIsArray())
		{
			// array type
			codes += i.second->outputCodes();
			codes += " ";

			vector<Id *> mIdVector = i.first->getIds();
			vector<pair<int, int>> periods = i.second->getPeriod();
			string Period = i.second->codeGetPeriod();

			for (int j = 0; j < mIdVector.size(); j++)
			{

				string Id = mIdVector[j]->outputCodes();

				codes += Id;	  // A
				codes += Period; // [n]

				if (j != mIdVector.size() - 1)
					codes += ", ";

				arr_id_list.emplace_back(Id, vector<int>());
				for (auto &k : periods)
				{
					arr_id_list[arr_id_list.size() - 1].second.push_back(k.first);
				}
			}

			codes += ";\n";
		}
		else
		{
			// simple type
			codes += i.second->outputCodes();
			codes += " ";
			codes += i.first->outputCodes();
			codes += ";\n";
		}
	}

	codes += "\n";

	return codes;
}

string SubProgramDeclarations::outputCodes()
{
	string codes;

	for (auto &i : mCommonVector)
	{
		codes += i->outputCodes();
	}

	return codes;
}

string StatementList::outputCodes(const string &name)
{
	string codes = "\n";

	for (auto &i : mStatementVector)
	{
		codes += i->outputCodes(name);
		codes += "\n";
	}

	codes += "\n";

	return codes;
}

// 过程无返回值
string Procedure::outputCodes()
{
	string codes = "\n";

	codes += "void ";
	string pro_name = mId->outputCodes();
	codes += pro_name;
	codes += "(";
	if (mParameterList)
		codes += mParameterList->outputCodes();
	codes += ") {\n";

	codes += mConstDeclarations->outputCodes();
	codes += mVarDeclarations->outputCodes();
	codes += mStatementList->outputCodes(pro_name);

	codes += "}\n";
	codes += "\n";

	return codes;
}

string Function::outputCodes()
{
	string codes = "\n";

	switch (checkReturnType())
	{
	case TYPE_INTEGER:
		codes += "int ";
		break;

	case TYPE_REAL:
		codes += "float ";
		break;

	case TYPE_CHAR:
		codes += "char ";
		break;

	case TYPE_BOOLEAN:
		codes += "bool ";
		break;

	default:
        throw TypeException();
	}

	string functionName = mId->outputCodes();
	codes += functionName;
	codes += "(";
	if (mParameterList)
		codes += mParameterList->outputCodes();
	codes += ") {\n";

	codes += mConstDeclarations->outputCodes();
	codes += mVarDeclarations->outputCodes();
	codes += mStatementList->outputCodes(functionName);

	codes += "}\n";
	codes += "\n";

	return codes;
}

string Statement::outputCodes(const string &name) const
{
	string codes;

	switch (mStateType)
	{
	case STATEMENT_ASSIGN:
		codes += mAssignOp->outputCodes(name);
		break;

	case STATEMENT_PROCEDURE:
		codes += mProcedure_call->outputCodes();
		break;

	case STATEMENT_COMPOUND:
		codes += "{\n";
		codes += mStatementList->outputCodes(name);
		codes += "}\n";
		break;

	case STATEMENT_IF:
		codes += mIfThenElse->outputCodes(name);
		break;

	case STATEMENT_FOR:
		codes += mFor->outputCodes(name);
		break;

	default:
		throw StatementException();
	}

	return codes;
}

string ParameterList::outputCodes()
{
	string codes;

	for (int i = 0; i < mParameters.size(); i++)
	{
		codes += mParameters[i]->outputCodes();
		if (i != mParameters.size() - 1)
		{
			codes += ", ";
		}
	}

	return codes;
}

string Parameter::outputCodes() const
{
	string codes;
	string Type;
	vector<Id *> ids = getIds();

	switch (mType)
	{
	case TYPE_INTEGER:
		Type += "int ";
		break;

	case TYPE_REAL:
		Type += "float ";
		break;

	case TYPE_CHAR:
		Type += "char ";
		break;

	case TYPE_BOOLEAN:
		Type += "bool ";
		break;

	default:
		throw TypeException();
	}

	for (int i = 0; i < ids.size(); i++)
	{
		codes += Type;
		codes += ids[i]->outputCodes();
		if (i != ids.size() - 1)
			codes += ", ";
	}

	return codes;
}

string Variable::outputCodes() const
{
	string codes;

	codes += mId->outputCodes();

	if (misArray)
	{
		vector<Expression *> mExpressionVector = mExpressionList->getExpressions();

		int index = -1;
		for (int i = 0; i < arr_id_list.size(); i++)
			if (arr_id_list[i].first == codes)
			{
				index = i;
				break;
			}

		for (int i = 0; i < mExpressionVector.size(); i++)
		{
			codes += "[";

			codes += mExpressionVector[i]->outputCodes();

			codes += " - ";

			codes += to_str(arr_id_list[index].second[i]);

			codes += "]";
		}
	}

	return codes;
}

string ProcedureCall::outputCodes() const
{
	string codes;
	string format;

	if (mExpressionList)
	{
		vector<int> mTypeVector = mExpressionList->getTypes();

		if (mProcedureCallType != PROCECALL_NORMAL)
		{
			for (int i : mTypeVector)
			{
				switch (i)
				{
				case TYPE_INTEGER:
					format += "%d";
					break;

				case TYPE_REAL:
					format += "%f";
					break;

				case TYPE_CHAR:
					format += "%c";
					break;

				case TYPE_BOOLEAN:
					format += "%d";
					break;

				default:
					break;
				}
			}
		}
	}

	string t_idName = mId->getName();
	if (mProcedureCallType == PROCECALL_READ)
	{
		codes += "scanf(\"";
		codes += format;
		codes += "\"";
		if (mExpressionList)
		{
			codes += ", ";
			codes += mExpressionList->outputCodes(true);
		}
		codes += ");";
	}
	else if (mProcedureCallType == PROCECALL_READLN)
	{
		codes += "scanf(\"";
		codes += format;
		codes += "\"";
		if (mExpressionList)
		{
			codes += ", ";
			codes += mExpressionList->outputCodes(true);
		}
		codes += "); getchar();";
	}
	else if (mProcedureCallType == PROCECALL_WRITE)
	{
		codes += "printf(\"";
		codes += format;
		codes += "\"";
		if (mExpressionList)
		{
			codes += ", ";
			codes += mExpressionList->outputCodes();
		}
		codes += ");";
	}
	else if (mProcedureCallType == PROCECALL_WRITELN)
	{
		codes += "printf(\"";
		codes += format;
		codes += "\\n\"";
		if (mExpressionList)
		{
			codes += ", ";
			codes += mExpressionList->outputCodes();
		}
		codes += ");";
	}
	else
	{
		codes += mId->outputCodes();
		codes += "(";
		if (mExpressionList)
			codes += mExpressionList->outputCodes();
		codes += ");";
	}

	return codes;
}

string FunctionCall::outputCodes() const
{
	string codes;

	codes += mId->outputCodes();
	codes += "(";
	if (mExpressionList)
		codes += mExpressionList->outputCodes();
	codes += ")";

	return codes;
}

string Expression::outputCodes() const
{
	string codes;

	if (mRelOp != nullptr)
	{
		codes += mRelOp->outputCodes();
	}
	else
	{
		codes += mSimpleExpression->outputCodes();
	}

	return codes;
}

string SimpleExpression::outputCodes() const
{
	string codes;

	if (mAddOp != nullptr)
	{
		codes += mAddOp->outputCodes();
	}
	else
	{
		codes += mTerm->outputCodes();
	}

	return codes;
}

string Term::outputCodes() const
{
	string codes;

	if (mMulOp != nullptr)
	{
		codes += mMulOp->outputCodes();
	}
	else
	{
		codes += mFactor->outputCodes();
	}

	return codes;
}

string Factor::outputCodes() const
{
	string codes;

	switch (mFactorType)
	{
	case FACTOR_VAR:
		codes += mVariable->outputCodes();
		break;

	case FACTOR_FUNCCALL:
		codes += mFunction_Call->outputCodes();
		break;

	case FACTOR_BRACKETS:
		codes += "(";
		codes += mExpression->outputCodes();
		codes += ")";
		break;

	case FACTOR_NOT:
		codes += mNot->outputCodes();
		break;

	case FACTOR_UMINUS:
		codes += mUminus->outputCodes();
		break;

	case FACTOR_VALUE_INT:
		codes += to_str(mInt);
		break;

	case FACTOR_VALUE_REAL:
		codes += to_str(mReal);
		break;

	case FACTOR_VALUE_CHAR:
		codes += "\'";
		codes += to_str(mChar);
		codes += "\'";
		break;

	case FACTOR_VALUE_BOOL:
		if (mBool)
			codes += "true";
		else
			codes += "false";
		break;

	default:
		throw FactorException();
	}

	return codes;
}

string Not::outputCodes() const
{
	string codes = "!";

	codes += mFactor->outputCodes();

	return codes;
}

string Uminus::outputCodes() const
{
	string codes;

	switch (mUnimusType)
	{
	case UMINUS_POSITIVE:
		codes += "+";
		break;

	case UMINUS_NEGATIVE:
		codes += "-";
		break;

	default:
		throw UminusException();
	}

	codes += mFactor->outputCodes();

	return codes;
}

string AssignOp::outputCodes(const string &name) const
{
	string codes;

	codes += mVariable->outputCodes();
	if (codes != name)
	{
		codes += " = ";
	}
	else
	{
		codes = "return ";
	}
	codes += mExpression->outputCodes();
	codes += ";";

	return codes;
}

string IfThenElse::outputCodes(const string &name) const
{
	string codes = "if (";

	codes += mExpression->outputCodes();
	codes += ") {\n";
	codes += mStatement_1->outputCodes(name);
	codes += "\n}";

	if (mStatement_2 != nullptr)
	{
		codes += "\nelse {\n";
		codes += mStatement_2->outputCodes(name);
		codes += "\n}";
	}

	return codes;
}

string For::outputCodes(const string& name) const
{
	string codes = "for (";

	codes += mId->outputCodes();
	codes += " = ";
	codes += mExpression_1->outputCodes();
	codes += " ; ";

	codes += mId->outputCodes();
	codes += " <= ";
	codes += mExpression_2->outputCodes();
	codes += " ; ";

	codes += mId->outputCodes();
	codes += "++ ) {\n";

	codes += mStatement->outputCodes(name);
	codes += "\n}";

	return codes;
}

string Id::outputCodes() const
{
	string codes;

	if (mIsVal)
	{
		codes += "*";
	}
	codes += mName;

	return codes;
}

string ConstValue::outputCodes() const
{

	string codes;

	switch (mPolarity)
	{
	case CONST_NEGATIVE:
		codes += "-";
		break;

	case CONST_POSITIVE:
		codes += "+";
		break;

	case CONST_NULL:
		break;

	default:
		throw ConstException();
	}

	if (misId)
	{
		codes += mId->outputCodes();
	}
	else
	{
		switch (mValueType)
		{
		case TYPE_INTEGER:
			codes += to_str(mInt);
			break;

		case TYPE_REAL:
			codes += to_str(mReal);
			break;

		case TYPE_CHAR:
			codes += "\'";
			codes += to_str(mChar);
			codes += "\'";
			break;

		case TYPE_BOOLEAN:
			if (mBool)
				codes += "true";
			else
				codes += "false";

		default:
			throw TypeException();
		}
	}

	return codes;
}

string IdList::outputCodes()
{
	string codes;

	for (int i = 0; i < mIdVector.size(); i++)
	{
		codes += mIdVector[i]->outputCodes();
		if (i != mIdVector.size() - 1)
			codes += ", ";
	}

	return codes;
}

string Type::outputCodes() const
{
	string codes;

	switch (mSimpleType)
	{
	case TYPE_INTEGER:
		codes += "int";
		break;

	case TYPE_REAL:
		codes += "float";
		break;

	case TYPE_CHAR:
		codes += "char";
		break;

	case TYPE_BOOLEAN:
		codes += "bool";
		break;

	default:
		throw TypeException();
	}

	return codes;
}

string Period::outputCodes()
{
	string codes;

	for (auto & i : mDimsVector)
	{
		int n = i.second - i.first + 1;
		codes += "[";
		codes += to_str(n);
		codes += "]";
	}

	return codes;
}

string RelOp::outputCodes() const
{
	string codes;

	codes += mSimple_Expression_1->outputCodes();

	switch (mRelOpType)
	{
	case OP_EQUAL:
		codes += " == ";
		break;

	case OP_NOT_EQUAL:
		codes += " != ";
		break;

	case OP_LESS:
		codes += " < ";
		break;

	case OP_LESS_EQUAL:
		codes += " <= ";
		break;

	case OP_LARGER:
		codes += " > ";
		break;

	case OP_LARGER_EQUAL:
		codes += " >= ";
		break;

	default:
		throw OperatorException();
	}

	codes += mSimple_Expression_2->outputCodes();

	return codes;
}

string AddOp::outputCodes() const
{
	string codes;

	codes += mSimpleExpression->outputCodes();

	switch (mAddOpType)
	{
	case OP_ADD:
		codes += " + ";
		break;

	case OP_SUB:
		codes += " - ";
		break;

	case OP_OR:
		codes += " || ";
		break;

	default:
		throw OperatorException();
	}

	codes += mTerm->outputCodes();

	return codes;
}

string MulOp::outputCodes() const
{
	string codes;

	codes += mTerm->outputCodes();

	switch (mMulOpType)
	{
	case OP_MULTIPLY:
		codes += " * ";
		break;

	case OP_REAL_DIV:
	case OP_INT_DIV:
		codes += " / ";
		break;

	case OP_MOD:
		codes += " % ";
		break;

	case OP_AND:
		codes += " && ";
		break;

	default:
		throw OperatorException();
	}

	codes += mFactor->outputCodes();

	return codes;
}

string ExpressionList::outputCodes(bool isScanf)
{
	string codes;

	for (int i = 0; i < mExpressionVector.size(); i++)
	{
		if (mVarDefineVector[i] || isScanf)
			codes += "&( ";
		codes += mExpressionVector[i]->outputCodes();
		if (mVarDefineVector[i] || isScanf)
			codes += " )";

		if (i != mExpressionVector.size() - 1)
			codes += ", ";
	}

	return codes;
}

void generate_codes(Program *root, const string &file_name)
{
	fstream file;
	file.open("./" + file_name + ".c", fstream::out);

	string codes = root->outputCodes();

	file << codes;

	file.close();
}

string Type::codeGetPeriod() const
{
	return mPeriod->outputCodes();
}

vector<pair<int, int>> Type::getPeriod() const
{
	return mPeriod->getRange();
}

vector<Id *> Parameter::getIds() const
{
	return mIdList->getIds();
}