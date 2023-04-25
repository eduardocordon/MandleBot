#include "ComplexPlane.h"
#include <cmath>
#include <iostream>
#include <complex>      // std::complex, std::abs
#include <sstream>
using namespace std;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}
void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	//Set a local variable for the x size to BASE_WIDTH* (BASE_ZOOM to the m_ZoomCount power)	
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	//Set a local variable for the y size to BASE_HEIGHT* m_aspectRatio* (BASE_ZOOM to the m_ZoomCount power)
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(x, y);
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(x, y);
}
void ComplexPlane::setCenter(Vector2f coord)
{
	//setCenter for m_view to the given coordinate
	m_view.setCenter(coord);
}
View ComplexPlane::getView()
{
	return m_view;

}
void ComplexPlane::setMouseLocation(Vector2f coord)
{
	//Store the given value in the m_mouseLocation variable
	m_mouseLocation = coord;
}
void ComplexPlane::loadText(Text& text)
{
	Vector2f center;
	center = m_view.getCenter();
	stringstream ss;

	ss << "Mandelbrot Set"<< endl << "Center: ("<<center.x<<","<< center.y<<")" << endl << "Cursor: ("<< m_mouseLocation.x<<", "<< m_mouseLocation.y<< ")" << endl << "Left - click to Zoom in" << endl << "Right - click to Zoom out" << endl;

	text.setString(ss.str());

}
size_t ComplexPlane::countIterations(Vector2f coord)
{
	double re = coord.x;
	double im = coord.y;
	complex<double> c(re, im);
	int counter = 0;
	complex<double> z(0, 0);
	while (abs(z) < 2) {
		z = z * z + c;
		counter++;
		if (counter == MAX_ITER) {
			return counter;
		}
	}
	return counter;

}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	srand(time(NULL));
	int rng = rand() % 255 + 1;

	if (count >= MAX_ITER) {
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count > 52) {
		r = rng;
		g = rng;
		b = rng / count;
	}
	else if (count > 40) {
		r = rng;
		g = rng;
		b = rng / count;
	}
	else if (count > 28) {
		r = rng;
		g = rng;
		b = rng / count;
	}
	else if (count > 16) {
		r = rng;
		g = rng;
		b = rng / count;
	}
	else if (count > 4) {
		r = rng;
		g = rng;
		b = rng / count;
	}
	else {
		r = rng;
		g = rng;
		b = rng;

	}

}