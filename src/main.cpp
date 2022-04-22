//#define DEBUG_VALUES
//#define DO_TEST
#define OOF_IMPL

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

#include "../ext/oof/oof.h"

#include "math/Fixed.h"
#include "math/Vector3D.h"
#include "misc/Image.h"
#include "misc/Random.h"
#include "misc/FastWrite.h"

thread_local unsigned int Random::Seed = 0xACE1u;
const Fixed Fixed::PI = Fixed::CustomFixed::pi();
const Fixed Fixed::TAU = Fixed::CustomFixed::two_pi();

// private variable
const unsigned int Image::Threshold[] = {
	  0, 192,  48, 240,  12, 204,  60, 252,   3, 195,  51, 243,  15, 207,  63, 255,
	128,  64, 176, 112, 140,  76, 188, 124, 131,  67, 179, 115, 143,  79, 191, 127,
	 32, 224,  16, 208,  44, 236,  28, 220,  35, 227,  19, 211,  47, 239,  31, 223,
	160,  96, 144,  80, 172, 108, 156,  92, 163,  99, 147,  83, 175, 111, 159,  95,
	  8, 200,  56, 248,   4, 196,  52, 244,  11, 203,  59, 251,   7, 199,  55, 247,
	136,  72, 184, 120, 132,  68, 180, 116, 139,  75, 187, 123, 135,  71, 183, 119,
	 40, 232,  24, 216,  36, 228,  20, 212,  43, 235,  27, 219,  39, 231,  23, 215,
	168, 104, 152,  88, 164, 100, 148,  84, 171, 107, 155,  91, 167, 103, 151,  87,
	  2, 194,  50, 242,  14, 206,  62, 254,   1, 193,  49, 241,  13, 205,  61, 253,
	130,  66, 178, 114, 142,  78, 190, 126, 129,  65, 177, 113, 141,  77, 189, 125,
	 34, 226,  18, 210,  46, 238,  30, 222,  33, 225,  17, 209,  45, 237,  29, 221,
	162,  98, 146,  82, 174, 110, 158,  94, 161,  97, 145,  81, 173, 109, 157,  93,
	 10, 202,  58, 250,   6, 198,  54, 246,   9, 201,  57, 249,   5, 197,  53, 245,
	138,  74, 186, 122, 134,  70, 182, 118, 137,  73, 185, 121, 133,  69, 181, 117,
	 42, 234,  26, 218,  38, 230,  22, 214,  41, 233,  25, 217,  37, 229,  21, 213,
	170, 106, 154,  90, 166, 102, 150,  86, 169, 105, 153,  89, 165, 101, 149,  85
};

int main() {
	FastWrite::EnableVTMode();

	std::cout << oof::cursor_visibility(false) << oof::reset_formatting() << oof::clear_screen() << oof::bg_color({ 12, 12, 12 });

	std::cout << std::setprecision(15);

#ifdef DO_TEST
	Fixed angle = 1e-2;
	//angle = angle * (Fixed::Pow(10, -1));
	Fixed sinAngle = Fixed::Sin(angle);
	std::cout << "Angle: " << angle << "\nSin Angle: " << sinAngle << '\n';

	Fixed sqrt2 = Fixed::Sqrt(2);
	Fixed sqrtMag2 = sqrt2 * sqrt2;
	std::cout << "\nSquare root of 2: " << sqrt2 << "\nTimes itself: " << sqrtMag2 << '\n';

	system("pause");
#endif

	int imageSize = 128;
	Image blueNoise(imageSize, imageSize, 1);
	int pointCount = 256;

	std::fstream points;
	points.open("points.txt", std::ios_base::out);
	points << std::setprecision(15);

	std::vector<Vector3D> existingPoints;
	existingPoints.reserve(pointCount);

	int m = 5;
	Fixed max = 63;

	for (int i = 0; i < pointCount; i++) {
		int candidateCount = (int)existingPoints.size() * m + 1;

		Vector3D furthestPoint;
		furthestPoint.WithZAxis(false);
		Fixed furthestDist = Fixed::Min();
		for (int j = 0; j < candidateCount; j++) {
			Vector3D currentPoint = Vector3D::RandomVector(0, max, false);
			Fixed closestDist = Fixed::Max();

			for (size_t k = 0; k < existingPoints.size(); k++) {
				Fixed currentDist = Vector3D::ToroidalDistance(currentPoint, existingPoints[k], Vector3D(0), Vector3D(max));

				if (currentDist < closestDist) {
					closestDist = currentDist;
				}
			}

			if (closestDist > furthestDist) {
				furthestPoint = currentPoint;
				furthestDist = closestDist;
			}
		}

		existingPoints.push_back(furthestPoint);

		furthestPoint /= max;
		points << furthestPoint << '\n';

		furthestPoint *= Vector3D(1, 1, 0);
		furthestPoint += Vector3D(0, 0, 1);

		Vector3D texturePoint = Vector3D::Floor(furthestPoint * imageSize);
		int pointX = texturePoint.GetX().ToInt();
		int pointY = texturePoint.GetY().ToInt();
		//Fixed color = 255;
		//Fixed color = furthestPoint.GetZ() * 255;

#ifdef DEBUG_VALUES
		Fixed::FlOrDo distDebug = furthestDist.ToFloat();
		distDebug *= 1;
#endif // DEBUG_VALUES

		blueNoise.SetColor(pointX, pointY, 255, 255, 255);

		//system("CLS");
		//std::cout << i << '/' << pointCount << '\n';

		FastWrite::Reset();

		std::string output = "";

		output += "Progress: ";

		output += std::to_string(i + 1);
		output += '/';
		output += std::to_string(pointCount);
		//output += '\a';
		//Beep(523, 500);

		FastWrite::Write(output);
	}
	std::string sound = "\a";
	FastWrite::Write(sound);
	points.close();
	blueNoise.Write("points_visual.png");

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	//system("pause");
	return 0;
}