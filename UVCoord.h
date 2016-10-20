#pragma once

namespace object{

	struct UVCoord{
		UVCoord(double u = 0, double v = 0) : u(u), v(v) {};

		friend UVCoord operator*(UVCoord uv, double s) {
			return { uv.u*s, uv.v*s };
		}
		friend UVCoord operator+(UVCoord uv1, UVCoord uv2) {
			return{ uv1.u+uv2.u, uv1.v+uv2.v };
		}
		double u;
		double v;
	};

}