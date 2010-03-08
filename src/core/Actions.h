/*
* function actors
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
* 12 Mar 2003	AL	+ added assign operators actions
* 08 Mar 2003	AL	* completly rewritten
*					* moved from "Grammar.h"
*
*/
#pragma once

struct UnaryFunction_t : unary_function<Value_t,Value_t> {
	virtual result_type operator()(argument_type const&) const  { return 0.0; }
};

struct BinaryFunction_t : binary_function<Value_t,Value_t,Value_t> {
	virtual result_type operator()(first_argument_type const&,second_argument_type const&) const { return 0.0; }
};


class FuncSin_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return sin(arg); } 
} FuncSin;
class FuncCos_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return cos(arg); } 
} FuncCos;
class FuncTg_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return tan(arg); } 
} FuncTg;
class FuncCtg_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return cos(arg)/sin(arg); } 
} FuncCtg;
class FuncArcTg_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return atan(arg); } 
} FuncArcTg;
class FuncSqr_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return arg*arg; } 
} FuncSqr;
class FuncSqrt_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return sqrt(arg); } 
} FuncSqrt;
class FuncLog_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return log10(arg); } 
} FuncLog;
class FuncLn_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return log(arg); } 
} FuncLn;
class FuncRad_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return arg*pi/180.0; } 
} FuncRad;
class FuncDeg_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return arg*180.0/pi; } 
} FuncDeg;
class FuncAbs_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return fabs(arg); } 
} FuncAbs;
class FuncFloor_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return floor(arg); } 
} FuncFloor;
class FuncCeil_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return ceil(arg); } 
} FuncCeil;
class FuncExp_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return exp(arg); } 
} FuncExp;
class FuncSign_t : public UnaryFunction_t { 
	result_type operator()(argument_type const& arg) const { return arg>0?1:-1; } 
} FuncSign;

class FuncPow_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return pow(arg1,arg2); } 
} FuncPow;

class OpAssign_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return arg2; } 
} OpAssign;
class OpAssignMul_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return arg1*arg2; } 
} OpAssignMul;
class OpAssignDiv_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return arg1/arg2; } 
} OpAssignDiv;
class OpAssignModulo_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return static_cast<DWORD>(arg1)%static_cast<DWORD>(arg2); } 
} OpAssignModulo;
class OpAssignAdd_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return arg1+arg2; } 
} OpAssignAdd;
class OpAssignSub_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return arg1-arg2; } 
} OpAssignSub;
class OpAssignShiftLeft_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return static_cast<DWORD>(arg1)<<static_cast<DWORD>(arg2); } 
} OpAssignShiftLeft;
class OpAssignShiftRight_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return static_cast<DWORD>(arg1)>>static_cast<DWORD>(arg2); } 
} OpAssignShiftRight;
class OpAssignBitAnd_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return static_cast<DWORD>(arg1)&static_cast<DWORD>(arg2); } 
} OpAssignBitAnd;
class OpAssignBitXor_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return static_cast<DWORD>(arg1)^static_cast<DWORD>(arg2); } 
} OpAssignBitXor;
class OpAssignBitOr_t : public BinaryFunction_t { 
	result_type operator()(first_argument_type const& arg1,second_argument_type const& arg2) const { return static_cast<DWORD>(arg1)|static_cast<DWORD>(arg2); } 
} OpAssignBitOr;
