#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct Pixel
{
	Pixel();
	Pixel(uint8_t,uint8_t,uint8_t);
	uint8_t r, g, b;
};

class Image final
{
private:
	size_t height = 0;
	size_t width = 0;
	size_t pixel_count = 0;
	std::vector<Pixel> data;

	[[nodiscard]] Pixel get_pixel(size_t, size_t) const;
	void set_pixel(size_t, size_t, Pixel);

public:
	typedef double (*PFN_INTERPOLATE) (double);

	Image(void) {}               // конструктор пустого изображени€
	Image(size_t w, size_t h); // конструктор изображени€ размером w*h (черный фон)
	bool load(const std::string&); // загрузка изображени€ из bmp-файла (как Bitmap:load)
	bool save(const std::string&) const; // сохранение изображени€ в bmp-файл (как Bitmap:save)

	// передискретизаци€ с заданной интерпол€ционной формулой
	void resize(
		Image& output,   // выходное изображение в которое будет записан результат
		size_t w,         // "окрестности" интерпол€ции ~ "радиус" интерпол€ционного окна
		PFN_INTERPOLATE f // интерпол€ционна€ формула
	) const;
};