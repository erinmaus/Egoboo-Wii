// This file is part of Egoboo-Wii.
//
// Egoboo-Wii is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Egoboo-Wii is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Egoboo-Wii.  If not, see <http:// www.gnu.org/licenses/>.

#include <cmath>
#include "SpecularEffect.hpp"

Adventure::Color Adventure::SpecularEffect::Apply(const Vector3& vertexPosition, const Vector3& vertexNormal)
{
	Vector3 p = Vector3::Transform(vertexPosition, GetWorld());
	Vector3 n = Vector3::TransformNormal(vertexNormal, GetWorld());
	Vector3 v = Vector3::Normalize(p - GetCameraPosition());
	Vector3 u = GetPosition() - p;
	float ul = u.CalculateLength();
	Vector3 l = u / ul;
	Vector3 h = Vector3::Normalize(v + l);
	float d = Vector3::Dot(h, n);
	float a = GetAttenuation().Calculate(ul);
	
	if (d < 0.0f)
		d = 0.0f;
	
	float s = pow(d, power);
	
	Vector3 result = GetColorRgb() * s * a;
	
	return Color(result.X, result.Y, result.Z, GetColorAlpha());
}
