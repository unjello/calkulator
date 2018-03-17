// andrzej lichnerowicz, unlicensed (~public domain)
#include <core/Engine.h>
#include <limits>
#include <spdlog/spdlog.h>

namespace _0xaL::calkulator::core {
	Boxed_Value const Calkulator::eval(const char* first) const {
		Boxed_Value ret;

		//spd::apply_all([&](std::shared_ptr<spdlog::logger> l)
		//{
		//	l->info("End of example.");
		//});

		std::numeric_limits<long double>::max();
		/*varible_p.remove_all();
		varible_p.init();
		if(!parse(first,Calculator[var(ret)=arg1],space_p).full)
			throw runtime_error("not fully parsed");
	*/
		return ret;
	}
} // namespace _0xaL::calkulator::core