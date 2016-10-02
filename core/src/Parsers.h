/*
* functions and varible parsers
*
* calculator
* (c) 2003 andrzej lichnerowicz. all rights reserved.
* 
* permission to copy, use, modify, sell and distribute this software 
* is granted provided this copyright notice appears in all copies. 
* this software is provided "as is" without express or implied warranty, 
* and with no claim as to its suitability for any purpose.
*
* Changeslog:
* 12 Mar 2003	AL	+ added assign operators parser
*					* moved AddVarible to AssignVarible with proper fixes
* 08 Mar 2003	AL	- initial revision
*
*/
#pragma once

struct UnaryFunctions_t : TokenDB<UnaryFunction_t> {
	UnaryFunctions_t() {
		add("sin",		Func_Sin,	FuncSin		);
		add("cos",		Func_Cos,	FuncCos		);
		add("tg",		Func_Tg,	FuncTg		);
		add("ctg",		Func_Ctg,	FuncCtg		);
		add("arctg",	Func_ArcTg,	FuncArcTg	);
		add("sqrt",		Func_Sqrt,	FuncSqrt	);
		add("sqr",		Func_Sqr,	FuncSqr		);
		add("log",		Func_Log,	FuncLog		);
		add("ln",		Func_Ln,	FuncLn		);
		add("rad",		Func_Rad,	FuncRad		);
		add("deg",		Func_Deg,	FuncDeg		);
		add("abs",		Func_Abs,	FuncAbs		);
		add("floor",	Func_Floor,	FuncFloor	);
		add("ceil",		Func_Ceil,	FuncCeil	);
		add("exp",		Func_Exp,	FuncExp		);
		add("sign",		Func_Sign,	FuncSign	);
	}
} unary_function_p;

struct BinaryFunctions_t : TokenDB<BinaryFunction_t> {
	BinaryFunctions_t() {
		add("pow",		Func_Pow,	FuncPow	);
	}
} binary_function_p;

struct Varible_t : symbols<Value_t> {
	void init() {
		add("pi",	pi		);
		add("e",	euler	);
	}
} varible_p;

struct AssignOperator_t : TokenDB<BinaryFunction_t> {
	AssignOperator_t() {
		add("=",		Assign,				OpAssign			);
		add("*=",		Assign_Mul,			OpAssignMul			);
		add("/=",		Assign_Div,			OpAssignDiv			);
		add("%=",		Assign_Modulo,		OpAssignModulo		);
		add("+=",		Assign_Add,			OpAssignAdd			);
		add("-=",		Assign_Sub,			OpAssignSub			);
		add("<<=",		Assign_ShiftLeft,	OpAssignShiftLeft	);
		add(">>=",		Assign_ShiftRight,	OpAssignShiftRight	);
		add("&=",		Assign_BitAnd,		OpAssignBitAnd		);
		add("^=",		Assign_BitXor,		OpAssignBitXor		);
		add("|=",		Assign_BitOr,		OpAssignBitOr		);
	}
} assign_operator_p;

struct AssignVarible_t {
	template<class Arg1T,class Arg2T,class Arg3T> struct result { typedef Value_t type; };
	Value_t operator()(TokenID const& token,string const& label,Value_t const& arg) {
		const char* lbl=label.c_str();

		if(find(binary_function_p,lbl)
			|| find(unary_function_p,lbl))
		throw runtime_error("label is not unique");

		Value_t* tmp=find(varible_p,lbl);
		Value_t old=0.0;
		if(tmp) {
			old=*tmp;
			varible_p.remove(lbl);
		}

		Value_t val=(*assign_operator_p.find(token))(old,arg);
		varible_p.add(lbl,val);

		return val;
	}
};
function<AssignVarible_t> const AssignVarible; 

struct UnaryCall_t {
	template<class Arg1T,class Arg2T> struct result { typedef Value_t type; };

	Value_t operator()(TokenID const& token,Value_t const& arg) const	{
		return (*unary_function_p.find(token))(arg);
	}
};
function<UnaryCall_t> const UnaryCall; 

struct BinaryCall_t {
	template<class Arg1T,class Arg2T,class Arg3T> struct result { typedef Value_t type; };

	Value_t operator()(TokenID const& token,Value_t const& a1,Value_t const& a2) const	{ 
		return (*binary_function_p.find(token))(a1,a2);
	}
};
function<BinaryCall_t> const BinaryCall; 

