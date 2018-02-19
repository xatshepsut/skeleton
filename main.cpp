#include <cstring>
#include <cstdio>

#include "simple/graphical/software_window.h"
#include "simple/graphical/algorithm.h"

using namespace simple;
using namespace graphical::color_literals;

using graphical::point2D;
using graphical::range2D;
using graphical::vector2D;
using graphical::anchored_rect;
using window = graphical::software_window;

constexpr vector2D half = vector2D::one() * 0.5f;

int main() try
{
	SDL_Init(SDL_INIT_EVERYTHING);
	{
		window win("Skeleton", point2D(600, 600), window::flags::borderless);
		const auto black = win.surface().format().color(0x0_rgb);
		const auto white = win.surface().format().color(0xffffff_rgb);

		anchored_rect scull {win.size()*60/100, win.size()/2 - win.size()*point2D::j()*10/100, half};

		anchored_rect right_eye {scull.size*30/100, scull.position - scull.size*25/100*point2D::i(), half};
		anchored_rect left_eye {scull.size*30/100, scull.position - scull.size*25/100*-point2D::i(), half};
		left_eye.position += point2D::j() * scull.size*10/100;
		right_eye.position += point2D::j() * scull.size*10/100;

		anchored_rect nose {scull.size*25/100, scull.position + scull.size*35/100*point2D::j(), half * vector2D::i()};
		const int nose_levels = 10;


		anchored_rect middle_tooth {scull.size*20/100, scull.position + scull.size/2*point2D::j(), half * vector2D::i()};
		auto left_tooth = middle_tooth;
		auto right_tooth = middle_tooth;
		left_tooth.position += point2D::i() * left_tooth.size*110/100;
		right_tooth.position -= point2D::i() * left_tooth.size*110/100;

		graphical::fill(win.surface(), black);

		graphical::fill(win.surface(), white, scull);

		graphical::fill(win.surface(), black, left_eye);
		graphical::fill(win.surface(), black, right_eye);

		auto step = nose.size/nose_levels;
		auto n = nose;
		n.size -= point2D::j() * (n.size - step);
		while( n.size > point2D::zero() )
		{
			graphical::fill(win.surface(), black, n);
			n.position -= point2D::j() * step;
			n.size -= point2D::i() * step;
		}

		graphical::fill(win.surface(), white, left_tooth);
		graphical::fill(win.surface(), white, middle_tooth);
		graphical::fill(win.surface(), white, right_tooth);

		win.update();
		SDL_Delay(3313);
	}
	SDL_Quit();
	return 0;
}
catch(...)
{
	if(errno)
		std::puts(std::strerror(errno));
	throw;
}
