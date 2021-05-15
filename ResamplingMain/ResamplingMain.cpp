#include "Image.hpp"

static double linear(double x)
{
	return x < 1.0 ? 1.0 - x : 0.0;
}

static double bicubic(double x)
{
	if (x < 1)
	{
		double x_abs = abs(x);
		return (0.5 * (x_abs * x_abs - 1) * (x_abs - 2));
	}
	else
		if (x < 2)
		{
			double x_abs = abs(x);
			return (-(1.0 / 6.0) * (x_abs - 1) * (x_abs - 2) * (x_abs - 3));
		}
		else
		{
			return 0.0;
		}
}

static double lanczos(double x)
{
	return x < 1.0 ? 1.0 - x : 0.0;
}

int main(void)
{
	Image image;

	size_t new_width = 300;
	size_t new_height = 200;

	Image image_linear(new_width, new_height);
	Image image_bicubic(new_width, new_height);
	Image image_lanczos(new_width, new_height);

	image.load("raven.bmp");

	image.resize(image_linear, 1, linear);
	image.resize(image_bicubic, 2, bicubic);
	image.resize(image_lanczos, 2, lanczos);

	image_linear.save("linear.bmp");
	image_bicubic.save("bicubic.bmp");
	image_lanczos.save("lanczos.bmp");

	return 0;
}

