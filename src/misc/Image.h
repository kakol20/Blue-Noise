#ifndef IMAGE_H
#define IMAGE_H

#include "../math/Fixed.h"

class Image {
public:
	enum class Interpolation { Linear, Closest, Cubic };
	enum class Extrapolation { Repeat, Extend, Clip };
	enum class ColorSpace { Non_Color, sRGB };

	enum class FileType { PNG, JPG, BMP, TGA, NONE };

public:
	Image(const char* file, const Interpolation interpolation, const Extrapolation extrapolation, const ColorSpace colorSpace);
	Image(const Image& copyImage);
	Image(const int w = 0, const int h = 0, const int channels = 0, const Interpolation interpolation = Interpolation::Closest, const Extrapolation extrapolation = Extrapolation::Repeat, const ColorSpace colorSpace = ColorSpace::Non_Color);

	~Image();

	Image& operator=(const Image& copyImage);

	bool Write(const char* file);

	void GetColor(const Fixed& x, const Fixed& y, Fixed& r, Fixed& g, Fixed& b);
	void SetColor(const int& x, const int& y, const Fixed& r, const Fixed& g, const Fixed& b);

	void SetColorSpace(const ColorSpace& colorSpace) { m_colorSpace = colorSpace; };

	void Dither(const int& factor = 255);

	static Fixed LinearToSRGB(const Fixed& color);
	static Fixed sRGBToLinear(const Fixed& color);

private:
	size_t m_size;
	int m_w;
	int m_h;
	int m_channels;

	Interpolation m_interpolation;
	Extrapolation m_extrapolation;
	ColorSpace m_colorSpace;

	// ----- DATA -----

	uint8_t* m_data;
	Fixed* m_dataF;

	// ----- FUNCTIONS -----

	bool Read(const char* file);

	FileType GetFileType(const char* file);
	int GetIndex(const int& x, const int& y);
	void MissingTexture();

	void FromColorSpace();
	void IndexToXY(const size_t& index, int& x, int& y);
	void ToColorSpace();

	// ----- INTERPOLATION FUNCTIONS -----

	void Bicubic(const Fixed& x, const Fixed& y, Fixed& r, Fixed& g, Fixed& b);
	void Bilinear(const Fixed& x, const Fixed& y, Fixed& r, Fixed& g, Fixed& b);
	void NearestNeighbour(const Fixed& x, const Fixed& y, Fixed& r, Fixed& g, Fixed& b);

	// ----- PRIVATE STATIC -----

	// private variable
	static const unsigned int Threshold[];
};

#endif // !IMAGE_H
