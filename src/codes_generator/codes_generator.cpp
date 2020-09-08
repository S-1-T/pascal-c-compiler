#include "codes_generator.h"
#include <fstream>
#include <strstream>

using namespace std;

vector< pair<string, vector<int> > >arr_id_list;

template<class src_type>
string type2str(src_type src) {
	strstream ss;
	ss << src;
	string ret;
	ss >> ret;

	return ret;
}


string Program::outputCodes() const {

	string Code_head =
		"#include <stdio.h>\n"
		"#include <stdlib.h>\n"
		"\n"
		"#define bool int\n"
		"#define true 1\n"
		"#define false 0\n"
		"\n";

	string Code_program_body = mp_Program_Body->outputCodes();

	string codes = Code_head + Code_program_body;

	return codes;
}

string ProgramBody::outputCodes() const {

	string Code_const = mp_Const_Declarations->outputCodes();

	string Code_var = mp_Var_Declarations->outputCodes();

	string Code_sub_program = mp_SubProgram_Declarations->outputCodes();

	string Code_main_begin =
		"int main(int argc, char* argv[]) {\n";

	string Code_Statement_List = mp_Statement_List->outputCodes();

	string Code_main_end =
		"	return 0;\n"
		"}\n"
		"\n";

	string Code_Return = Code_const + Code_var + Code_sub_program + Code_main_begin + Code_Statement_List + Code_main_end;

	return Code_Return;
}

string ConstDeclarations::outputCodes() {

	string codes = "\n";

	for (auto & i : mv_Const) {
		bool CONST_ID = false;

		switch (i.second->func_checkValueType()) {
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

			if(i.second->m_postNeg == CONST_NEGATIVE)
				codes += "-";
			codes += i.second->mp_Id->outputCodes();
			codes += " \n";
			CONST_ID = true;

			break;

		default:
			throw "Invalid Type!!!";
			break;
		}
		if(!CONST_ID) {
			codes += i.first->outputCodes();
			codes += " = ";
			codes += i.second->outputCodes();
			codes += ";\n";
		}
	}

	codes += "\n";

	return codes;
}

string VarDeclarations::outputCodes() {
	string codes = "\n";

	for (auto & i : mv_Var) {
		if (i.second->checkIsArray()) {
			// array type
			codes += i.second->outputCodes();
			codes += " ";

			vector<Id*>mv_Id = i.first->getIds();
			vector<pair<int, int>> mv_Period = i.second->getPeriod();
			string Code_Period = i.second->codeGetPeriod();

			for (int j = 0; j < mv_Id.size(); j++) {

				string Code_Id = mv_Id[j]->outputCodes();

				codes += Code_Id;		// A
				codes += Code_Period;	// [n]

				if (j != mv_Id.size() - 1)
					codes += ", ";

				arr_id_list.emplace_back(Code_Id, vector<int>());
				for (auto & k : mv_Period){
				    arr_id_list[arr_id_list.size() - 1].second.push_back(k.first);
				}

			}

			codes += ";\n";
		}
		else {
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

string SubProgramDeclarations::outputCodes() {
	string codes;

	for (auto & i : mv_Common) {
		codes += i->outputCodes();
	}

	return codes;
}

string StatementList::outputCodes(const string& name) {
	string codes = "\n";

	for (auto & i : mv_Statement) {
		codes += i->outputCodes(name);
		codes += "\n";
	}

	codes += "\n";

	return codes;
}

// 过程无返回值
string Procedure::outputCodes() {
	string codes = "\n";

	codes += "void ";
	string pro_name = mp_Id->outputCodes();
	codes += pro_name;
	codes += "(";
	if (mp_Parameter_List)
		codes += mp_Parameter_List->outputCodes();
	codes += ") {\n";

	codes += mp_Const_Declarations->outputCodes();
	codes += mp_Var_Declarations->outputCodes();
	codes += mp_Statement_List->outputCodes(pro_name);

	codes += "}\n";
	codes += "\n";

	return codes;
}

string Function::outputCodes() {
	string codes = "\n";

	switch (checkReturnType()) {
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
		throw "Invalid Type!!!";
		break;
	}

	string func_name = mp_Id->outputCodes();
	codes += func_name;
	codes += "(";
	if (mp_Parameter_List)
		codes += mp_Parameter_List->outputCodes();
	codes += ") {\n";

	codes += mp_Const_Declarations->outputCodes();
	codes += mp_Var_Declarations->outputCodes();
	codes += mp_Statement_List->outputCodes(func_name);

	codes += "}\n";
	codes += "\n";

	return codes;
}

string Statement::outputCodes(const string& name) const {
	string codes;

	switch (m_stateType) {
	case STATEMENT_ASSIGN:
		codes += mp_AssignOp->outputCodes(name);
		break;

	case STATEMENT_PROCEDURE:
		codes += mp_Procedure_call->outputCodes();
		break;

	case STATEMENT_COMPOUND:
		codes += "{\n";
		codes += mp_Statement_List->outputCodes(name);
		codes += "}\n";
		break;

	case STATEMENT_IF:
		codes += mp_If_Then_Else->outputCodes(name);
		break;

	case STATEMENT_FOR:
		codes += mp_For->outputCodes(name);
		break;

	default:
		throw "Invalid statement TYPE!!!";
		break;
	}

	return codes;
}

string ParameterList::outputCodes() {
	string codes;

	for (int i = 0; i < mv_Patameter.size(); i++) {
		codes += mv_Patameter[i]->outputCodes();
		if (i != mv_Patameter.size() - 1) {
			codes += ", ";
		}
	}

	return codes;
}

string Parameter::outputCodes() {
	string codes;
	string Code_Type;
	vector<Id*>mv_id = getIds();

	switch (m_Type) {
	case TYPE_INTEGER:
		Code_Type += "int ";
		break;

	case TYPE_REAL:
		Code_Type += "float ";
		break;

	case TYPE_CHAR:
		Code_Type += "char ";
		break;

	case TYPE_BOOLEAN:
		Code_Type += "bool ";
		break;

	default:
		throw "Invalid Type!!!";
		break;
	}

	for (int i = 0; i < mv_id.size(); i++) {
		codes += Code_Type;
		codes += mv_id[i]->outputCodes();
		if (i != mv_id.size() - 1)
			codes += ", ";
	}

	return codes;
}

string Variable::outputCodes() const {
	string codes;

	codes += mp_Id->outputCodes();

	if (m_isArray) {
		vector<Expression*>mv_Expression = mp_Expression_List->getExpressions();

		int index = -1;
		for(int i = 0 ; i< arr_id_list.size(); i++)
		    if (arr_id_list[i].first == codes ){
                index = i;
                break;
            }

		for (int i = 0; i < mv_Expression.size(); i++) {
			codes += "[";

			codes += mv_Expression[i]->outputCodes();

			codes += " - ";

			codes += type2str(arr_id_list[index].second[i]);

			codes += "]";
		}
	}

	return codes;
}

string ProcedureCall::outputCodes() const {
	string codes;
	string Code_FormateStr;

	if(mp_Expression_List) {
		vector<int> mv_Type = mp_Expression_List->getTypes();

		if (m_proCall_Tpye != PROCECALL_NORMAL) {
			for (int i : mv_Type) {
				switch (i) {
					case TYPE_INTEGER:
						Code_FormateStr += "%d";
						break;

					case TYPE_REAL:
						Code_FormateStr += "%f";
						break;

					case TYPE_CHAR:
						Code_FormateStr += "%c";
						break;

					case TYPE_BOOLEAN:
						Code_FormateStr += "%d";
						break;

					default:
						break;
				}
			}
		}
	}


	string t_id_name = mp_Id->getName();
	if (m_proCall_Tpye == PROCECALL_READ) {
		codes += "scanf(\"";
		codes += Code_FormateStr;
		codes += "\"";
		if(mp_Expression_List){
			codes += ", ";
			codes += mp_Expression_List->outputCodes(true);
		}
		codes += ");";
	}
	else if (m_proCall_Tpye == PROCECALL_READLN) {
		codes += "scanf(\"";
		codes += Code_FormateStr;
		codes += "\"";
		if(mp_Expression_List){
			codes += ", ";
			codes += mp_Expression_List->outputCodes(true);
		}
		codes += "); getchar();";
	}
	else if (m_proCall_Tpye == PROCECALL_WRITE) {
		codes += "printf(\"";
		codes += Code_FormateStr;
		codes += "\"";
		if(mp_Expression_List){
			codes += ", ";
			codes += mp_Expression_List->outputCodes();
		}
		codes += ");";
	}
	else if (m_proCall_Tpye == PROCECALL_WRITELN) {
		codes += "printf(\"";
		codes += Code_FormateStr;
		codes += "\\n\"";
		if(mp_Expression_List){
			codes += ", ";
			codes += mp_Expression_List->outputCodes();
		}
		codes += ");";
	}
	else {
		codes += mp_Id->outputCodes();
		codes += "(";
		if(mp_Expression_List)
			codes += mp_Expression_List->outputCodes();
		codes += ");";
	}



	return codes;
}

string FunctionCall::outputCodes() const {
	string codes;

	codes += mp_Id->outputCodes();
	codes += "(";
	if(mp_Expression_List)
		codes += mp_Expression_List->outputCodes();
	codes += ")";

	return codes;
}

string Expression::outputCodes() const {
	string codes;

	if (mp_Relop != nullptr) {
		codes += mp_Relop->outputCodes();
	}
	else {
		codes += mp_Simple_Expression->outputCodes();
	}

	return codes;
}

string SimpleExpression::outputCodes() const {
	string codes;

	if (mp_AddOp != nullptr) {
		codes += mp_AddOp->outputCodes();
	}
	else {
		codes += mp_Term->outputCodes();
	}

	return codes;
}

string Term::outputCodes() const {
	string codes;

	if (mp_MulOp != nullptr) {
		codes += mp_MulOp->outputCodes();
	}
	else {
		codes += mp_Factor->outputCodes();
	}

	return codes;
}

string Factor::outputCodes() const {
	string codes;

	switch (m_factorType) {
	case FACTOR_VAR:
		codes += mp_Variable->outputCodes();
		break;

	case FACTOR_FUNCCALL:
		codes += mp_Function_Call->outputCodes();
		break;

	case FACTOR_BRACKETS:
		codes += "(";
		codes += mp_Expression->outputCodes();
		codes += ")";
		break;

	case FACTOR_NOT:
		codes += mp_Not->outputCodes();
		break;

	case FACTOR_UMINUS:
		codes += mp_Uminus->outputCodes();
		break;

	case FACTOR_VALUE_INT:
		codes += type2str(m_int);
		break;

	case FACTOR_VALUE_REAL:
		codes += type2str(m_real);
		break;

	case FACTOR_VALUE_CHAR:
		codes += "\'";
		codes += type2str(m_char);
		codes += "\'";
		break;

	case FACTOR_VALUE_BOOL:
		if (m_bool)
			codes += "true";
		else
			codes += "false";
		break;

	default:
		throw "Invalid FACTORTYPE!!!";
		break;
	}

	return codes;
}

string Not::outputCodes() const {
	string codes = "!";

	codes += mp_Factor->outputCodes();

	return codes;
}

string Uminus::outputCodes() const {
	string codes;

	switch (m_unimusType) {
	case UMINUS_POSITIVE:
		codes += "+";
		break;

	case UMINUS_NEGATIVE:
		codes += "-";
		break;

	default:
		throw "Invalid UMINUS_TYPE!!!";
		break;
	}

	codes += mp_Factor->outputCodes();

	return codes;
}

string AssignOp::outputCodes(const string& name) const {
	string codes;

	codes += mp_Variable->outputCodes();
	if (codes != name){
		codes += " = ";
	}
	else{
		codes = "return ";
	}
	codes += mp_Expression->outputCodes();
	codes += ";";

	return codes;
}

string IfThenElse::outputCodes(const string& name) const {
	string codes = "if (";

	codes += mp_Expression->outputCodes();
	codes += ") {\n";
	codes += mp_Statement_1->outputCodes(name);
	codes += "\n}";

	if (mp_Statement_2 != nullptr) {
		codes += "\nelse {\n";
		codes += mp_Statement_2->outputCodes(name);
		codes += "\n}";
	}

	return codes;
}

string For::outputCodes(string name) const {
	string codes = "for (";

	codes += mp_Id->outputCodes();
	codes += " = ";
	codes += mp_Expression_1->outputCodes();
	codes += " ; ";

	codes += mp_Id->outputCodes();
	codes += " <= ";
	codes += mp_Expression_2->outputCodes();
	codes += " ; ";

	codes += mp_Id->outputCodes();
	codes += "++ ) {\n";

	codes += mp_Statement->outputCodes(name);
	codes += "\n}";

	return codes;
}

string Id::outputCodes() const {
	string codes;

	if (m_isVal) {
		codes += "*";
	}
	codes += m_name;

	return codes;
}

string ConstValue::outputCodes() const {

	string codes;

	switch (m_postNeg) {
	case CONST_NEGATIVE:
		codes += "-";
		break;

	case CONST_POSITIVE:
		codes += "+";
		break;

	case CONST_NULL:
		break;

	default:
		throw "Invalid CONST_POSTNEG Type!!!!";
		break;
	}

	if (m_isId) {
		codes += mp_Id->outputCodes();
	}
	else {
		switch (m_valueType) {
		case TYPE_INTEGER:
			codes += type2str(m_int);
			break;

		case TYPE_REAL:
			codes += type2str(m_real);
			break;

		case TYPE_CHAR:
			codes += "\'";
			codes += type2str(m_char);
			codes += "\'";
			break;

		case TYPE_BOOLEAN:
			if (m_bool)
				codes += "true";
			else
				codes += "false";

		default:
			throw "Invalid BASIC Type!!!";
			break;
		}
	}

	return codes;
}

string IdList::outputCodes() {
	string codes;

	for (int i = 0; i < mv_Id.size(); i++) {
		codes += mv_Id[i]->outputCodes();
		if (i != mv_Id.size() - 1)
			codes += ", ";
	}

	return codes;
}

string Type::outputCodes() const {
	string codes;

	switch (m_simpleType) {
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
		throw "Invalid TYPE!!!";
		break;
	}

	return codes;
}

string Period::outputCodes() {
	string codes;

	for (int i = 0; i < mv_dims.size(); i++) {
		int n = mv_dims[i].second - mv_dims[i].first + 1;
		codes += "[";
		codes += type2str(n);
		codes += "]";
	}

	return codes;
}

string RelOp::outputCodes() const {
	string codes;

	codes += mp_Simple_Expression_1->outputCodes();

	switch (m_relopType) {
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
		throw "Invalid RELOP_TYPE!!!";
		break;
	}

	codes += mp_Simple_Expression_2->outputCodes();

	return codes;
}

string AddOp::outputCodes() const {
	string codes;

	codes += mp_Simple_Expression->outputCodes();

	switch (m_addopType) {
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
		throw "Invalid AddopType!!!";
		break;
	}

	codes += mp_Term->outputCodes();

	return codes;
}

string MulOp::outputCodes() const {
	string codes;

	codes += mp_Term->outputCodes();

	switch (m_mulopType) {
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
		throw "Invalid MULTYPE!!!";
		break;
	}

	codes += mp_Factor->outputCodes();

	return codes;
}

string ExpressionList::outputCodes(bool isScanf
) {
	string codes;

	for (int i = 0; i < mv_Expression.size(); i++) {
		if (mv_VarDefine[i] || isScanf)
			codes += "&( ";
		codes += mv_Expression[i]->outputCodes();
		if (mv_VarDefine[i] || isScanf)
			codes += " )";

		if (i != mv_Expression.size() - 1)
			codes += ", ";
	}

	return codes;
}

void generate_codes(Program* root, const string& file_name) {
	fstream file;
	file.open("./" + file_name + ".c", fstream::out);

	string codes = root->outputCodes();

    file << codes;

    file.close();
}

string Type::codeGetPeriod() const {
	return mp_Period->outputCodes();
}

vector<pair<int, int> > Type::getPeriod() const {
	return mp_Period->getRange();
}

vector<Id*> Parameter::getIds() const {
	return mp_Id_List->getIds();
}