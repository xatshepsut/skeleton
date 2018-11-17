#include <cstring>
#include <cstdio>
#include <thread>

#include "simple/graphical/initializer.h"
#include "simple/graphical/software_window.h"
#include "simple/graphical/algorithm.h"

using namespace std::chrono_literals;
using namespace simple;
using namespace graphical::color_literals;

using graphical::int2;
using graphical::range2D;
using graphical::float2;
using graphical::anchored_rect;
using window = graphical::software_window;

constexpr float2 half = float2::one() * 0.5f;

int main() try
{
	graphical::initializer init;

	window win("Skeleton", int2(600, 600), window::flags::borderless);
	const auto black = win.surface().format().color(0x0_rgb);
	const auto white = win.surface().format().color(0xffffff_rgb);

	anchored_rect scull {win.size()*60/100, win.size()/2 - win.size()*int2::j()*10/100, half};

	anchored_rect right_eye {scull.size*30/100, scull.position - scull.size*25/100*int2::i(), half};
	anchored_rect left_eye {scull.size*30/100, scull.position - scull.size*25/100*-int2::i(), half};
	left_eye.position += int2::j() * scull.size*10/100;
	right_eye.position += int2::j() * scull.size*10/100;

	anchored_rect nose {scull.size*25/100, scull.position + scull.size*35/100*int2::j(), half * float2::i()};
	const int nose_levels = 10;


	anchored_rect middle_tooth {scull.size*20/100, scull.position + scull.size/2*int2::j(), half * float2::i()};
	auto left_tooth = middle_tooth;
	auto right_tooth = middle_tooth;
	left_tooth.position += int2::i() * left_tooth.size*110/100;
	right_tooth.position -= int2::i() * left_tooth.size*110/100;

	graphical::fill(win.surface(), black);

	graphical::fill(win.surface(), white, scull);

	graphical::fill(win.surface(), black, left_eye);
	graphical::fill(win.surface(), black, right_eye);

	auto step = nose.size/nose_levels;
	auto n = nose;
	n.size -= int2::j() * (n.size - step);
	while( n.size > int2::zero() )
	{
		graphical::fill(win.surface(), black, n);
		n.position -= int2::j() * step;
		n.size -= int2::i() * step;
	}

	graphical::fill(win.surface(), white, left_tooth);
	graphical::fill(win.surface(), white, middle_tooth);
	graphical::fill(win.surface(), white, right_tooth);

	win.update();
	std::this_thread::sleep_for(3313ms);
	return 0;
}
catch(...)
{
	if(errno)
		std::puts(std::strerror(errno));
	throw;
}
