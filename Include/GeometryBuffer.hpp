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

#ifndef ADVENTURE_GEOMETRY_BUFFER_HPP_
#define ADVENTURE_GEOMETRY_BUFFER_HPP_

namespace Adventure
{
	class GeometryBuffer
	{
		public:
			GeometryBuffer(Description description, IndexSize indexSize, bool compress);
			~GeometryBuffer();
		
			enum Description
			{
				// Description used for 3D model data
				// Expected elements are: Position (Vector3), Normal (Vector3), Material (RGBA), UV (Vector2)
				Model,
				
				// Description used for billboards and other particles
				// Expected elements are: Position (Vector3), Color (RGBA), UV (Vector2)
				Particle,
				
				// Description used for sprites, e.g. HUD
				// Expected elements are: Position (Vector2), Color (RGBA), UV (Vector2)
				Sprite
			};
			
			enum IndexSize
			{
				// Geometry has more than 255 vertices
				// This will use an unsigned short
				LargeIndex
				
				// Geometry has less than 255 vertices
				// This will use an unsigned byte
				SmallIndex
			};
	};
}

#endif
