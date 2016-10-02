/*
* calculator "engine" :)
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
* 10 Mar 2003	AL	* completly rewritten
*					* moved from "Grammar.h"
*
*/

#include <string>
using namespace std;

#if defined(_DEBUG)
#	include <fstream>
std::ofstream file("debug.txt");
#	define BOOST_SPIRIT_DEBUG
#	define BOOST_SPIRIT_DEBUG_OUT file
#endif

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/functor_parser.hpp>
#include <boost/spirit/attribute.hpp>
#include <boost/spirit/symbols.hpp>
#include <boost/spirit/error_handling/exceptions.hpp> 

#include <boost/spirit/phoenix/primitives.hpp>
#include <boost/spirit/phoenix/special_ops.hpp> 
#include <boost/spirit/phoenix/casts.hpp>
#include <boost/spirit/phoenix/binders.hpp>
#include <boost/spirit/phoenix/statements.hpp>

using namespace boost;
using namespace boost::spirit;
using namespace phoenix;

typedef unsigned long DWORD;


#include <core/Engine.h>
#include "Token.h"
#include "Actions.h"
#include "Parsers.h"
#include "Grammar.h"


Value_t Calculate(const char* first) {
	Value_t ret=0.0;

#if defined(_DEBUG)
	file<<endl<<"-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-=*=-"<<endl;
#endif

	varible_p.remove_all();
	varible_p.init();
	if(!parse(first,Calculator[var(ret)=arg1],space_p).full)
		throw runtime_error("not fully parsed");

	return ret;
}