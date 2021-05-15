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

	Image(void) {}               // ����������� ������� �����������
	Image(size_t w, size_t h); // ����������� ����������� �������� w*h (������ ���)
	bool load(const std::string&); // �������� ����������� �� bmp-����� (��� Bitmap:load)
	bool save(const std::string&) const; // ���������� ����������� � bmp-���� (��� Bitmap:save)

	// ����������������� � �������� ���������������� ��������
	void resize(
		Image& output,   // �������� ����������� � ������� ����� ������� ���������
		size_t w,         // "�����������" ������������ ~ "������" ����������������� ����
		PFN_INTERPOLATE f // ���������������� �������
	) const;
};