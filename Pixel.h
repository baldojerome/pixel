#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>

using namespace std;

class Pixel
{
public:
	Pixel(int rouge, int vert, int bleu)
	{
		r = validerCouleur(rouge);
		v = validerCouleur(vert);
		b = validerCouleur(bleu);
	}
	int getRouge() const { return r; }
	int getVert() const { return v; }
	int getBleu() const { return b; }

	void ajusterRouge(int ajustement) { r = validerCouleur(r + ajustement); }
	void ajusterVert(int ajustement) { v = validerCouleur(v + ajustement); }
	void ajusterBleu(int ajustement) { b = validerCouleur(b + ajustement); }

	friend ostream& operator<<(ostream& out, const Pixel& pixel)
	{

		out << "#" << std::hex << pixel.r << "-" << pixel.v << "-" << pixel.b
			<< "\t(" << std::dec << pixel.r << "-" << pixel.v << "-" << pixel.b << ")";
		return out;
	}

	bool operator==(const Pixel& pixel) const
	{
		return (r == pixel.r && v == pixel.v && b == pixel.b);
	}

private:
	int r;	// red
	int v;	// green
	int b;	// blue

	int validerCouleur(int valeur) const { return min(255, max(valeur, 0)); }
};

#endif

