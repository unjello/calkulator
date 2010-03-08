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
* 14 Mar 2003	AL	* moved as dll
*					+ dll export/import guards
* 08 Mar 2003	AL	- initial revision
*
*/
#pragma once

#if defined(CORE_EXPORTS)
#	define CORE_API __declspec(dllexport)
#else
#	define CORE_API __declspec(dllimport)
#endif

typedef double Value_t;

const Value_t pi = 3.141592653;
const Value_t euler  = 2.718281828;

CORE_API Value_t Calculate(const char* first);
