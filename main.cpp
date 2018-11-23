#include <cstring>
#include <cstdio>
#include <thread>

#include "simple/graphical/initializer.h"
#include "simple/graphical/software_window.h"
#include "simple/graphical/gl_window.h"
#include "simple/graphical/algorithm.h"
#include "simple_vg.h"

using namespace std::chrono_literals;
using namespace simple;
using namespace graphical::color_literals;

using graphical::int2;
using graphical::float2;
using rect = vg::anchored_rect2f;
using graphical::gl_window;
using window = graphical::software_window;

constexpr float2 half = float2::one() * 0.5f;

int main() try
{
	graphical::initializer init;

	gl_window::global.require<gl_window::attribute::major_version>(2);
	gl_window::global.request<gl_window::attribute::stencil>(8);
	gl_window win("nanovg", int2(600, 600), window::flags::borderless);
	float2 win_size(win.size());

	const vg::rgb_vector black(0x0_rgb);
	const vg::rgb_vector white(0xffffff_rgb);

	rect scull {win_size*0.6f, win_size/2.f - win_size*float2::j()*0.1f, half};
	float2 eye_size = scull.size*0.3f;
	rect right_eye {eye_size, scull.position - scull.size*0.25f*float2::i(), half};
	rect left_eye  {eye_size, scull.position + scull.size*0.25f*float2::i(), half};
	left_eye.position += float2::j() * scull.size * 0.1f;
	right_eye.position += float2::j() * scull.size * 0.1f;

	rect nose {scull.size*0.25f, scull.position + scull.size*0.35*float2::j(), half * float2::i()};
	const int nose_levels = 10;

	rect middle_tooth {scull.size*0.2f, scull.position + scull.size/2 * float2::j(), half * float2::i()};
	auto left_tooth = middle_tooth;
	auto right_tooth = middle_tooth;
	left_tooth.position += float2::i() * left_tooth.size*1.10f;
	right_tooth.position -= float2::i() * left_tooth.size*1.10f;


	glewInit();
	auto canvas = vg::canvas(vg::canvas::flags::antialias | vg::canvas::flags::stencil_strokes);
	canvas.clear();
	{ auto frame = canvas.begin_frame(win_size);

		scull.size *= 1.20f;
		frame.begin_sketch()
			.ellipse(scull)
			.rectangle(left_tooth)
			.rectangle(middle_tooth)
			.rectangle(right_tooth)
			.fill(black)
		;

		frame.begin_sketch()
			.ellipse(left_eye)
			.ellipse(right_eye)
			.fill(white)
		;

		{ auto nose_sketch = frame.begin_sketch();

			auto step = nose.size/nose_levels;
			auto n = nose;
			n.size -= float2::j() * (n.size - step);
			while( n.size > float2::zero() )
			{
				nose_sketch.rectangle(n);
				n.position -= float2::j() * step;
				n.size -= float2::i() * step;
			}
			nose_sketch.fill(white);

		}
	}

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
