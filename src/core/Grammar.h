/*
* standard include
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
* 12 Mar 2003	AL	* all dec numbers are interpreted as reals
*					+ added assigment operators
*					* fixed bug with functions parsing
* 10 Mar 2003	AL	* completly rewritten
*					* splitted to several grammars
*					+ added more flexible function calls
*					+ added c/c++ like operators precedences
*					* fixed bug with bit operators
* 30 Jan 2003	AL	- initial revision
*
*/
#pragma once

template<typename ItemT> struct ResultClosure_t : spirit::closure<ResultClosure_t<ItemT>,ItemT> {
	member1 val;
};

struct DumbClosure_t : spirit::closure<DumbClosure_t,double,string> {
	member1 val;
	member2 name;
};

typedef ResultClosure_t<Value_t> Closure_t;
typedef ResultClosure_t<TokenID> TokenClosure_t;
typedef ResultClosure_t<string> NameClosure_t;
typedef Closure_t::context_t Context_t;
typedef TokenClosure_t::context_t TokenContext_t;
typedef NameClosure_t::context_t NameContext_t;


struct Number_t : grammar<Number_t,Context_t> {
	Number_t() {
		BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this,"number_grammar",BOOST_SPIRIT_DEBUG_TRACENODE);
	}

	template<typename ScannerT> struct definition {
		subrule<0>  submain;
		subrule<1>  hex;
		subrule<2>  oct;
		subrule<3>  bin;
		subrule<5>  exp;

		definition(Number_t const& self) {
			main = 
				(
					submain = bin||hex||oct||exp,

					hex =
						"0x">>hex_p [self.val=static_cast_<Value_t>(arg1)]
						| '$'>>hex_p [self.val=static_cast_<Value_t>(arg1)]
						| hex_p [self.val=static_cast_<Value_t>(arg1)] >>'h',

					oct = 
						"0">>oct_p [self.val=static_cast_<Value_t>(arg1)]
						| oct_p[self.val=static_cast_<Value_t>(arg1)] >>'o',

					bin = 
						"0b">>bin_p [self.val=static_cast_<Value_t>(arg1)]
						| bin_p [self.val=static_cast_<Value_t>(arg1)] >>'b',

					exp = ureal_p [self.val=arg1]
				);

				BOOST_SPIRIT_DEBUG_RULE(main);
				BOOST_SPIRIT_DEBUG_RULE(submain);
				BOOST_SPIRIT_DEBUG_RULE(hex);
				BOOST_SPIRIT_DEBUG_RULE(oct);
				BOOST_SPIRIT_DEBUG_RULE(bin);
				BOOST_SPIRIT_DEBUG_RULE(exp);
		}

		typedef rule<ScannerT> Rule_t;
		Rule_t main;
		Rule_t const& start() const { return main; }
	};
} number_p;


struct Identifier_t : grammar<Identifier_t,NameContext_t> {
	Identifier_t() {
		BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this,"identifier_grammar",BOOST_SPIRIT_DEBUG_TRACENODE);
	}

	template<class ScannerT> struct definition {
		definition(Identifier_t const& self) {
			main = lexeme_d [(alpha_p|'_')>>*(alnum_p|'_')]
					[
						self.val=construct_<string>(arg1,arg2)
					];

			BOOST_SPIRIT_DEBUG_RULE(main);
		}

		typedef rule<ScannerT> Rule_t;
		Rule_t main;
		Rule_t const& start() const { return main; }
	};
} identifier_p;


struct Calculator_t : grammar<Calculator_t,Context_t> {

	Calculator_t() {
		BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this,"calculator_grammar",BOOST_SPIRIT_DEBUG_TRACENODE);
	}

	typedef Calculator_t Self_t;

	template<typename ScannerT> struct definition {
        subrule<0,Context_t> shift_left;
		subrule<1,Context_t> shift_right;
		subrule<4,Context_t> tmp;
		subrule<5,TokenContext_t> uid;
		subrule<6,TokenContext_t> bid;
		subrule<6,TokenContext_t> aid;

		definition(Self_t const& self) {
			main = eps_p [self.val=0] >> *(varible_assign [self.val=arg1]) >>!p7 [self.val=arg1];

			p7 = 
				p6[p7.val=arg1] >> *(
					( '|' >> p6 [ p7.val=static_cast_<DWORD>(p7.val)|static_cast_<DWORD>(arg1) ] )
				);

			p6 = 
				p5[p6.val=arg1] >> *(
					( '^' >> p5 [ p6.val=static_cast_<DWORD>(p6.val)^static_cast_<DWORD>(arg1) ] )
				);

			p5 = 
				p4[p5.val=arg1] >> *(
					( '&' >> p4 [ p5.val=static_cast_<DWORD>(p5.val)&static_cast_<DWORD>(arg1) ] )
				);

			p4 = 
				p3[p4.val=arg1] >> *(
					( shift_left="<<" >> p3 
						[
							shift_left.val=arg1,
							if_(shift_left.val<-64) 
							[ 
								shift_left.val=-64 
							],
							if_(shift_left.val>64) 
							[ 
								shift_left.val=64 
							],
							p4.val=static_cast_<DWORD>(p4.val)<<static_cast_<DWORD>(shift_left.val)
						]
					) |
					( shift_right=">>" >> p3
						[
							shift_right.val=arg1,
							if_(shift_right.val<-64) 
							[ 
								shift_right.val=-64 
							],
							if_(shift_right.val>64) 
							[ 
								shift_right.val=64 
							],
							p4.val=static_cast_<DWORD>(p4.val)>>static_cast_<DWORD>(shift_right.val)
						]
					)
				);

			p3 = 
				p2[p3.val=arg1] >> *(
					( '+' >> p2 [ p3.val+=arg1] ) |
					( '-' >> p2 [ p3.val-=arg1] )
				);

			p2 = 
				p1[p2.val=arg1] >> *(
					( '*' >> p1 [ p2.val*=arg1] ) |
					( '/' >> p1 [ p2.val/=arg1] ) |
					( '%' >> p1 [ p2.val=static_cast_<DWORD>(p2.val)%static_cast_<DWORD>(arg1)] )
				);

			//p7 = p2[p7.val=arg1];
			p1 =
				p0 [p1.val=arg1] 
				| '(' >> p7 [p1.val=arg1] >>')'
				| unary_call [p1.val=arg1]
				| binary_call [p1.val=arg1]
				| varible_p [p1.val=arg1]
				| ('-' >> p1 [p1.val=-arg1])
				| ('+' >> p1 [p1.val=arg1])
				| ('~' >> p1 [p1.val=~static_cast_<DWORD>(arg1)]);

			p0 = number_p[p0.val=arg1];

			varible_assign = (
					 name = identifier_p [name.name=arg1] >> (
						aid = assign_operator_p [aid.val=arg1] >> p7 
						[
							varible_assign.val=AssignVarible(aid.val,name.name,arg1)
						]
				));

			unary_call = (
				uid = unary_function_p [uid.val=arg1] >> '(' >> p7[unary_call.val=arg1] >> ')' >> eps_p 
					[
						unary_call.val=UnaryCall(uid.val,unary_call.val)
					]
				);

			binary_call = (
				bid = binary_function_p [bid.val=arg1] >> (
					tmp = '(' >> p7[binary_call.val=arg1] >> ',' >> p7[tmp.val=arg1] >> ')' >> eps_p
					[
						binary_call.val=BinaryCall(bid.val,binary_call.val,tmp.val)
					]
				));

			BOOST_SPIRIT_DEBUG_RULE(main);
			BOOST_SPIRIT_DEBUG_RULE(p0);
			BOOST_SPIRIT_DEBUG_RULE(p1);
			BOOST_SPIRIT_DEBUG_RULE(p2);
			BOOST_SPIRIT_DEBUG_RULE(p3);
			BOOST_SPIRIT_DEBUG_RULE(p4);
			BOOST_SPIRIT_DEBUG_RULE(p5);
			BOOST_SPIRIT_DEBUG_RULE(p6);
			BOOST_SPIRIT_DEBUG_RULE(p7);
			BOOST_SPIRIT_DEBUG_RULE(unary_call);
			BOOST_SPIRIT_DEBUG_RULE(binary_call);
			BOOST_SPIRIT_DEBUG_RULE(varible_assign);

			BOOST_SPIRIT_DEBUG_RULE(shift_left);
			BOOST_SPIRIT_DEBUG_RULE(shift_right);
			BOOST_SPIRIT_DEBUG_RULE(tmp);
			BOOST_SPIRIT_DEBUG_RULE(uid);
			BOOST_SPIRIT_DEBUG_RULE(bid);
			BOOST_SPIRIT_DEBUG_RULE(aid);
			BOOST_SPIRIT_DEBUG_RULE(name);
		}

		typedef rule<ScannerT> SimpleRule_t;
		typedef rule<ScannerT,Context_t> Rule_t;
		typedef rule<ScannerT,DumbClosure_t::context_t> NameRule_t;

		Rule_t p0,p1,p2,p3,p4,p5,p6,p7;
		Rule_t unary_call, binary_call;
		Rule_t varible_assign;
		NameRule_t name;

		SimpleRule_t main;
		SimpleRule_t const& start() const { return main; }
	};
} Calculator;
