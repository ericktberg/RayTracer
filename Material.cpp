#include "Material.h"
#include "RGBColor.h"
#include "Light.h"
#include <math.h>
#include <vector>

using namespace std;

Material::Material(RGBColor mtl, RGBColor spec, double a, double d, double s, double n) : diffuse(mtl), specular(spec), glossiness(n), a(a), d(d), s(s)
{
}

Material::~Material()
{
}


RGBColor Material::calcAmbient() const{
	return diffuse*a;
}
//Currently implements Phong shading
//TODO think of a way to implement separate shading models implicitly
RGBColor Material::calcDiffSpec(Vector3D normalDir, Vector3D lightDir, Vector3D h, RGBColor lightColor, double shadowTag, const RGBColor* override_color) const {
	
	RGBColor color;
	if (!override_color){
		color = diffuse;
	}
	else{
		color = *override_color;
	}
	double dot = normalDir.dot(lightDir);
	RGBColor diff = color*d*dot;
	RGBColor spec = specular*s*pow(normalDir.dot(h), glossiness);

	double r = shadowTag*lightColor.r * (diff.r + spec.r);
	double g = shadowTag*lightColor.g * (diff.g + spec.g);
	double b = shadowTag*lightColor.b * (diff.b + spec.b);
	
	return { r, g, b };
}