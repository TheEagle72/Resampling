#include "Image.hpp"

#include "BitmapPlusPlus.hpp"

Pixel::Pixel()
{
	r = 0;
	g = 0;
	b = 0;
}

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue)
{
	r = red;
	g = green;
	b = blue;
}

Pixel Image::get_pixel(size_t x, size_t y) const
{
	return data.at(y * width + x);
}

void Image::set_pixel(size_t x, size_t y, Pixel pixel)
{
	data.at(y * width + x) = pixel;
}

Image::Image(size_t w, size_t h)
{
	width = w;
	height = h;
	pixel_count = w * h;

	data.resize(pixel_count);

	for (auto& pixel : data)
	{
		pixel.r = 0;
		pixel.g = 0;
		pixel.b = 0;
	}
}

bool Image::load(const std::string& path)
{
	bmp::Bitmap bmp;

	if (!bmp.Load(path))
	{
		return false;
	}
	width = bmp.Width();
	height = bmp.Height();
	pixel_count = width * height;
	data.resize(pixel_count);

	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			auto index = y * width * 3 + x * 3;
			bmp::Pixel p = bmp.Get(x, y);
			set_pixel(x, y, Pixel(p.r, p.g, p.b));
		}
	}


	return true;
}

bool Image::save(const std::string& path) const
{
	if (pixel_count == 0)
	{
		return false;
	}

	bmp::Bitmap bmp(width, height);

	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			const Pixel pixel = get_pixel(x, y);
			bmp.Set(x, y, bmp::Pixel(pixel.r, pixel.g, pixel.b));
		}
	}

	return bmp.Save(path);
}

void Image::resize(Image& output, size_t w, PFN_INTERPOLATE f) const
{
	for (size_t y = 0; y < output.height; ++y)
	{
		for (size_t x = 0; x < output.width; ++x)
		{
			double new_x, new_y;
			double x_mult, y_mult;

			x_mult = 1.0 * width / output.width;
			y_mult = 1.0 * height / output.height;

			new_x = (x + 0.5) * x_mult;
			new_y = (y + 0.5) * y_mult;

			size_t i = round(new_x);
			size_t j = round(new_y);

			uint8_t r = 0, g = 0, b = 0;
			int l_border = (-(int)w);
			int r_border = (int)w;

			for (int k = l_border; k < r_border; ++k)
			{
				for (int l = l_border; l < r_border; ++l)
				{
					int x_ = i + l;
					int y_ = j + k;

					if (x_ >= width || y_ >= height || x_ < 0 || y_ < 0)
					{
						continue;
					}

					auto [red, green, blue] = get_pixel(x_, y_);
					//const double weight = f(x_ - new_x) * f(y_ - new_y);
					const double weight = f(new_x - x_) * f(new_y - y_);
					r += red * weight;
					g += green * weight;
					b += blue * weight;
				}
			}
			output.set_pixel(x, y, Pixel(r, g, b));
		}
	}
}
