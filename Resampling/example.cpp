#include <libbitmap.h>

int main(void)
{
	Bitmap bmp;

	// scenario #1: load, edit & save bitmap

	bmp.load("..\\src\\kitty-24.bmp");
	bmp.m_buffer[10000] = 0x30;
	bmp.save("out.bmp");

	bmp.clear(); // reset bitmap object -> ready to new data

	// scenario #2: initialize, edit & save bitmap

	bmp.m_height = 100;
	bmp.m_width = 107;
	bmp.m_buffer = new uint8_t[32400];

	for ( size_t y = 0, p = 0; y < bmp.m_height; ++y, p += 324 )
	{
		for ( size_t x = 0; x < bmp.m_width; ++x )
		{
			bmp.m_buffer[p + x * 3 + 0] = (x * 5) % 256; // blue
			bmp.m_buffer[p + x * 3 + 1] = 0;             // green
			bmp.m_buffer[p + x * 3 + 2] = 255;           // red
		}
	}

	bmp.save("gradient.bmp");

	return 0;
}
