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

#ifndef ADVENTURE_LIGHT_HPP_
#define ADVENTURE_LIGHT_HPP_

#include "Matrix.hpp"
#include "IEffect.hpp"

namespace Adventure
{
	struct LightAttenuation
	{
		public:
			float Constant;
			float Linear;
			float Quadratic;
			
			inline static LightAttenuation FromRadius(float radius)
			{
				LightAttenuation atten;
				
				atten.Constant = 1.0f;
				atten.Linear = 2.0f / radius;
				atten.Quadratic = 1.0f / (radius * radius);
				
				return atten;
			}
			
			inline float Calculate(float distance)
			{
				return 1.0f / (Constant + Linear * distance + Quadratic * distance * distance);
			}
	};
	
	class LightEffect : public IEffect
	{
		public:
			inline Matrix GetWorld() const
			{
				return world;
			}
			
			inline void SetWorld(const Matrix& value)
			{
				world = value;
			}
			
			// Gets and sets the light position in world space
			inline Vector3 GetPosition() const
			{
				return lightPosition;
			}
			
			inline void SetPosition(const Vector3& value)
			{
				lightPosition = value;
			}
			
			// Gets and sets the camera position in world space
			inline Vector3 GetCameraPosition() const
			{
				return cameraPosition;
			}
			
			inline void SetCameraPosition(const Vector3& value)
			{
				cameraPosition = value;
			}
			
			inline Color GetColor() const
			{
				return Color(color.X, color.Y, color.Z, alpha);
			}
			
			inline void SetColor(const Color& value)
			{
				color.X = (float)value.Red / Color::MaxChannelValue;
				color.Y = (float)value.Green / Color::MaxChannelValue;
				color.Z = (float)value.Blue / Color::MaxChannelValue;
				alpha = (float)value.Alpha / Color::MaxChannelValue;
			}
			
			inline LightAttenuation GetAttenuation() const
			{
				return attenuation;
			}
			
			inline void SetAttenuation(const LightAttenuation& value)
			{
				attenuation = value;
			}
		
		protected:
			Vector3 GetColorRgb() const
			{
				return color;
			}
			
			float GetColorAlpha() const
			{
				return alpha;
			}
			
		private:
			Matrix world;
			
			Vector3 cameraPosition;
			Vector3 lightPosition;
			
			Vector3 color;
			float alpha;
			
			LightAttenuation attenuation;
	};
}

#endif
