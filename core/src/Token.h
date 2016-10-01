/*
* function tokens
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
* 12 Mar 2003	AL	+ added token types
*					+ added assign operators tokens
*					* fixed TokenDB to work on indexes not id's
* 08 Mar 2003	AL	- initial revision
*
*/
#pragma once

enum TokenType {
	TokenForceDword	= 0x7fffffff,
	TokenIndexMask	= 0x0fffffff,
	TokenTypeMask	= 0xf0000000,

	TokenFunction	= 0x10000000,
	TokenAssigment	= 0x20000000
};

enum TokenID {
	FuncFirst		= TokenFunction,
	// unary functions
	Func_Sin		= FuncFirst,
	Func_Cos,
	Func_Tg,
	Func_Ctg,
	Func_ArcTg,
	Func_Sqr,
	Func_Sqrt,
	Func_Log,
	Func_Ln,
	Func_Rad,
	Func_Deg,
	Func_Abs,
	Func_Floor,
	Func_Ceil,
	Func_Exp,
	Func_Sign,
	// binary functions
	Func_Pow,
	FuncNext,

	AssignFirst		= TokenAssigment,
	Assign			= AssignFirst,
	Assign_Mul,
	Assign_Div,
	Assign_Modulo,
	Assign_Add,
	Assign_Sub,
	Assign_ShiftLeft,
	Assign_ShiftRight,
	Assign_BitAnd,
	Assign_BitXor,
	Assign_BitOr,
	AssignNext
};


template<class FuncT> class TokenDB : public symbols<TokenID> {
public:
	typedef symbols<TokenID> Super_t;
	typedef vector<FuncT*> TokenVector;

	TokenVector vec;

	TokenID add(const char* text,TokenID id,FuncT& actor) {
		const unsigned index = id&TokenIndexMask;
		if(vec.size()<=index) {
			vec.resize(index+1);
		}
		vec[index]=&actor;
		Super_t::add(text,TokenID(index));

		return id;
	}

	FuncT* find(TokenID id) {
		const unsigned index = id&TokenIndexMask;
		assert(vec.size()>index);
		return vec[index];
	}
};

