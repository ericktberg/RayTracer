#pragma once
#include "PPMFile.h"
#include "RGBColor.h"
#include "Vector3D.h"

class Material
{
public:
	Material(RGBColor,RGBColor,double a, double d, double s,double n);
	~Material();

	RGBColor get_diffuse(){ return diffuse; };
	RGBColor get_specular(){ return specular; };
	Vector3D get_levels() { return{ a, d, s }; };
	double get_glossiness(){ return glossiness; };

	virtual RGBColor calcAmbient(const RGBColor* override_color) const;
	virtual RGBColor calcDiffSpec(Vector3D normalDir, Vector3D lightDir, Vector3D h, RGBColor lightColor, double shadow, const RGBColor* override_color) const;

private:
	RGBColor diffuse; //Od[r,g,b]
	RGBColor specular; //Os[r,g,b]
	//To use dot product for phong illumination.
	double a, d, s; //k[a,d,s]
	double glossiness;
};

