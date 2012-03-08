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

#include "Allocator.hpp"
#include "File.hpp"
#include "Interpolation.hpp"
#include "Md2Model.hpp"

#define MD2_NORMAL_COUNT 162

const Adventure::Md2Normal Md2Normals[MD2_NORMAL_COUNT] =
{
	{-0.525731, 0.000000, 0.850651}, 
	{-0.442863, 0.238856, 0.864188}, 
	{-0.295242, 0.000000, 0.955423}, 
	{-0.309017, 0.500000, 0.809017}, 
	{-0.162460, 0.262866, 0.951056}, 
	{0.000000, 0.000000, 1.000000}, 
	{0.000000, 0.850651, 0.525731}, 
	{-0.147621, 0.716567, 0.681718}, 
	{0.147621, 0.716567, 0.681718}, 
	{0.000000, 0.525731, 0.850651}, 
	{0.309017, 0.500000, 0.809017}, 
	{0.525731, 0.000000, 0.850651}, 
	{0.295242, 0.000000, 0.955423}, 
	{0.442863, 0.238856, 0.864188}, 
	{0.162460, 0.262866, 0.951056}, 
	{-0.681718, 0.147621, 0.716567}, 
	{-0.809017, 0.309017, 0.500000}, 
	{-0.587785, 0.425325, 0.688191}, 
	{-0.850651, 0.525731, 0.000000}, 
	{-0.864188, 0.442863, 0.238856}, 
	{-0.716567, 0.681718, 0.147621}, 
	{-0.688191, 0.587785, 0.425325}, 
	{-0.500000, 0.809017, 0.309017}, 
	{-0.238856, 0.864188, 0.442863}, 
	{-0.425325, 0.688191, 0.587785}, 
	{-0.716567, 0.681718, -0.147621}, 
	{-0.500000, 0.809017, -0.309017}, 
	{-0.525731, 0.850651, 0.000000}, 
	{0.000000, 0.850651, -0.525731}, 
	{-0.238856, 0.864188, -0.442863}, 
	{0.000000, 0.955423, -0.295242}, 
	{-0.262866, 0.951056, -0.162460}, 
	{0.000000, 1.000000, 0.000000}, 
	{0.000000, 0.955423, 0.295242}, 
	{-0.262866, 0.951056, 0.162460}, 
	{0.238856, 0.864188, 0.442863}, 
	{0.262866, 0.951056, 0.162460}, 
	{0.500000, 0.809017, 0.309017}, 
	{0.238856, 0.864188, -0.442863}, 
	{0.262866, 0.951056, -0.162460}, 
	{0.500000, 0.809017, -0.309017}, 
	{0.850651, 0.525731, 0.000000}, 
	{0.716567, 0.681718, 0.147621}, 
	{0.716567, 0.681718, -0.147621}, 
	{0.525731, 0.850651, 0.000000}, 
	{0.425325, 0.688191, 0.587785}, 
	{0.864188, 0.442863, 0.238856}, 
	{0.688191, 0.587785, 0.425325}, 
	{0.809017, 0.309017, 0.500000}, 
	{0.681718, 0.147621, 0.716567}, 
	{0.587785, 0.425325, 0.688191}, 
	{0.955423, 0.295242, 0.000000}, 
	{1.000000, 0.000000, 0.000000}, 
	{0.951056, 0.162460, 0.262866}, 
	{0.850651, -0.525731, 0.000000}, 
	{0.955423, -0.295242, 0.000000}, 
	{0.864188, -0.442863, 0.238856}, 
	{0.951056, -0.162460, 0.262866}, 
	{0.809017, -0.309017, 0.500000}, 
	{0.681718, -0.147621, 0.716567}, 
	{0.850651, 0.000000, 0.525731}, 
	{0.864188, 0.442863, -0.238856}, 
	{0.809017, 0.309017, -0.500000}, 
	{0.951056, 0.162460, -0.262866}, 
	{0.525731, 0.000000, -0.850651}, 
	{0.681718, 0.147621, -0.716567}, 
	{0.681718, -0.147621, -0.716567}, 
	{0.850651, 0.000000, -0.525731}, 
	{0.809017, -0.309017, -0.500000}, 
	{0.864188, -0.442863, -0.238856}, 
	{0.951056, -0.162460, -0.262866}, 
	{0.147621, 0.716567, -0.681718}, 
	{0.309017, 0.500000, -0.809017}, 
	{0.425325, 0.688191, -0.587785}, 
	{0.442863, 0.238856, -0.864188}, 
	{0.587785, 0.425325, -0.688191}, 
	{0.688191, 0.587785, -0.425325}, 
	{-0.147621, 0.716567, -0.681718}, 
	{-0.309017, 0.500000, -0.809017}, 
	{0.000000, 0.525731, -0.850651}, 
	{-0.525731, 0.000000, -0.850651}, 
	{-0.442863, 0.238856, -0.864188}, 
	{-0.295242, 0.000000, -0.955423}, 
	{-0.162460, 0.262866, -0.951056}, 
	{0.000000, 0.000000, -1.000000}, 
	{0.295242, 0.000000, -0.955423}, 
	{0.162460, 0.262866, -0.951056}, 
	{-0.442863, -0.238856, -0.864188}, 
	{-0.309017, -0.500000, -0.809017}, 
	{-0.162460, -0.262866, -0.951056}, 
	{0.000000, -0.850651, -0.525731}, 
	{-0.147621, -0.716567, -0.681718}, 
	{0.147621, -0.716567, -0.681718}, 
	{0.000000, -0.525731, -0.850651}, 
	{0.309017, -0.500000, -0.809017}, 
	{0.442863, -0.238856, -0.864188}, 
	{0.162460, -0.262866, -0.951056}, 
	{0.238856, -0.864188, -0.442863}, 
	{0.500000, -0.809017, -0.309017}, 
	{0.425325, -0.688191, -0.587785}, 
	{0.716567, -0.681718, -0.147621}, 
	{0.688191, -0.587785, -0.425325}, 
	{0.587785, -0.425325, -0.688191}, 
	{0.000000, -0.955423, -0.295242}, 
	{0.000000, -1.000000, 0.000000}, 
	{0.262866, -0.951056, -0.162460}, 
	{0.000000, -0.850651, 0.525731}, 
	{0.000000, -0.955423, 0.295242}, 
	{0.238856, -0.864188, 0.442863}, 
	{0.262866, -0.951056, 0.162460}, 
	{0.500000, -0.809017, 0.309017}, 
	{0.716567, -0.681718, 0.147621}, 
	{0.525731, -0.850651, 0.000000}, 
	{-0.238856, -0.864188, -0.442863}, 
	{-0.500000, -0.809017, -0.309017}, 
	{-0.262866, -0.951056, -0.162460}, 
	{-0.850651, -0.525731, 0.000000}, 
	{-0.716567, -0.681718, -0.147621}, 
	{-0.716567, -0.681718, 0.147621}, 
	{-0.525731, -0.850651, 0.000000}, 
	{-0.500000, -0.809017, 0.309017}, 
	{-0.238856, -0.864188, 0.442863}, 
	{-0.262866, -0.951056, 0.162460}, 
	{-0.864188, -0.442863, 0.238856}, 
	{-0.809017, -0.309017, 0.500000}, 
	{-0.688191, -0.587785, 0.425325}, 
	{-0.681718, -0.147621, 0.716567}, 
	{-0.442863, -0.238856, 0.864188}, 
	{-0.587785, -0.425325, 0.688191}, 
	{-0.309017, -0.500000, 0.809017}, 
	{-0.147621, -0.716567, 0.681718}, 
	{-0.425325, -0.688191, 0.587785}, 
	{-0.162460, -0.262866, 0.951056}, 
	{0.442863, -0.238856, 0.864188}, 
	{0.162460, -0.262866, 0.951056}, 
	{0.309017, -0.500000, 0.809017}, 
	{0.147621, -0.716567, 0.681718}, 
	{0.000000, -0.525731, 0.850651}, 
	{0.425325, -0.688191, 0.587785}, 
	{0.587785, -0.425325, 0.688191}, 
	{0.688191, -0.587785, 0.425325}, 
	{-0.955423, 0.295242, 0.000000}, 
	{-0.951056, 0.162460, 0.262866}, 
	{-1.000000, 0.000000, 0.000000}, 
	{-0.850651, 0.000000, 0.525731}, 
	{-0.955423, -0.295242, 0.000000}, 
	{-0.951056, -0.162460, 0.262866}, 
	{-0.864188, 0.442863, -0.238856}, 
	{-0.951056, 0.162460, -0.262866}, 
	{-0.809017, 0.309017, -0.500000}, 
	{-0.864188, -0.442863, -0.238856}, 
	{-0.951056, -0.162460, -0.262866}, 
	{-0.809017, -0.309017, -0.500000}, 
	{-0.681718, 0.147621, -0.716567}, 
	{-0.681718, -0.147621, -0.716567}, 
	{-0.850651, 0.000000, -0.525731}, 
	{-0.688191, 0.587785, -0.425325}, 
	{-0.587785, 0.425325, -0.688191}, 
	{-0.425325, 0.688191, -0.587785}, 
	{-0.425325, -0.688191, -0.587785}, 
	{-0.587785, -0.425325, -0.688191}, 
	{-0.688191, -0.587785, -0.425325}
};

Adventure::Md2Model::Md2Model()
{
	texCoords = NULL;
	texCoordCount = 0;
	
	triangles = NULL;
	triangleCount = 0;
	
	frames = NULL;
	frameCount = 0;
	
	vertexCount = 0;
	
	allocator = NULL;
}

Adventure::Md2Model::~Md2Model()
{
	Deallocate(texCoords, allocator);
	Deallocate(triangles, allocator);
	Deallocate(frames, allocator);
}

Adventure::IModelAnimator* Adventure::Md2Model::CreateAnimator()
{
	return new(allocator) Md2Animator(this);
}

void Adventure::Md2Model::DestroyAnimator(IModelAnimator* animator)
{
	Deallocate(animator, allocator);
}

Adventure::Md2Model* Adventure::Md2Model::LoadFromFile(File& file, Allocator* allocator)
{
	struct
	{
		File::UInt8 Identifier[4];
		File::Int32 Version;
		File::Int32 SkinWidth;
		File::Int32 SkinHeight;
		File::Int32 FrameSize;
		File::Int32 SkinCount;
		File::Int32 PositionCount;
		File::Int32 TexCoordCount;
		File::Int32 TriangleCount;
		File::Int32 GLCommandCount;
		File::Int32 FrameCount;
		File::Int32 SkinOffset;
		File::Int32 TexCoordOffset;
		File::Int32 TriangleOffset;
		File::Int32 FrameOffset;
		File::Int32 GLCommandOffset;
		File::Int32 EndOfFile;
	} header;
	
	TRACE(DEBUG_FILE_LOADING, "Attempting to load MD2...");
	
	file.Read(header.Identifier[0]);
	file.Read(header.Identifier[1]);
	file.Read(header.Identifier[2]);
	file.Read(header.Identifier[3]);
	
	if (header.Identifier[0] != 'I' && header.Identifier[1] != 'D' && header.Identifier[2] != 'P' && header.Identifier[3] != '2')
	{
		TRACE(DEBUG_FILE_LOADING, "Not a valid MD2 header");
		return NULL;
	}
	
	file.Read(header.Version);
	
	if (header.Version != 8)
	{
		TRACE(DEBUG_FILE_LOADING, "Incorrect version");
		return NULL;
	}
	
	file.Read(header.SkinWidth);
	file.Read(header.SkinHeight);
	Vector2 inverseTexCoordScale(1.0f / header.SkinWidth, 1.0f / header.SkinHeight);
	
	file.Read(header.FrameSize);
	file.Read(header.SkinCount);
	file.Read(header.PositionCount);
	file.Read(header.TexCoordCount);
	file.Read(header.TriangleCount);
	file.Read(header.GLCommandCount);
	file.Read(header.FrameCount);
	
	file.Read(header.SkinOffset);
	file.Read(header.TexCoordOffset);
	file.Read(header.TriangleOffset);
	file.Read(header.FrameOffset);
	file.Read(header.GLCommandOffset);
	file.Read(header.EndOfFile);
	
	TRACE(DEBUG_FILE_LOADING, "Read header; constructing model...");
	
	Md2Model* model = new(allocator) Md2Model();
	model->vertexCount = header.PositionCount;
	model->inverseTexCoordScale = inverseTexCoordScale;
	model->allocator = allocator;
	
	// Load texture coordinates
	model->texCoords = new(allocator) Md2TexCoord[header.TexCoordCount];
	model->texCoordCount = header.TexCoordCount;
	file.GetStream().seekg(header.TexCoordOffset, std::ios::beg);
	
	for (int i = 0; i < header.TexCoordCount; i++)
	{
		file.Read(model->texCoords[i].U);
		file.Read(model->texCoords[i].V);
	}
	
	TRACE(DEBUG_FILE_LOADING, "Loaded texture coordinates");
	
	// Load triangles
	model->triangles = new(allocator) Md2Triangle[header.TriangleCount];
	model->triangleCount = header.TriangleCount;
	file.GetStream().seekg(header.TriangleOffset, std::ios::beg);
	
	for (int i = 0; i < header.TriangleCount; i++)
	{
		file.Read(model->triangles[i].Vertex[0]);
		file.Read(model->triangles[i].Vertex[1]);
		file.Read(model->triangles[i].Vertex[2]);
		
		file.Read(model->triangles[i].TexCoord[0]);
		file.Read(model->triangles[i].TexCoord[1]);
		file.Read(model->triangles[i].TexCoord[2]);
	}
	
	TRACE(DEBUG_FILE_LOADING, "Loaded triangles");
	
	// Load frames
	model->frames = new(allocator) Md2Frame[header.FrameCount];
	model->frameCount = header.FrameCount;
	file.GetStream().seekg(header.FrameOffset, std::ios::beg);
	
	for (int i = 0; i < header.FrameCount; i++)
	{
		union
		{
			float FloatValue[3];
			File::Int32 IntValue[3];
		} scratch;
		
		file.Read(scratch.IntValue[0]);
		file.Read(scratch.IntValue[1]);
		file.Read(scratch.IntValue[2]);
		
		model->frames[i].Scale = Vector3(scratch.FloatValue[0], scratch.FloatValue[1], scratch.FloatValue[2]);
		
		file.Read(scratch.IntValue[0]);
		file.Read(scratch.IntValue[1]);
		file.Read(scratch.IntValue[2]);
		
		model->frames[i].Translation = Vector3(scratch.FloatValue[0], scratch.FloatValue[1], scratch.FloatValue[2]);
		
		char nameBuffer[64];
		
		file.GetStream().read(nameBuffer, 64);
		nameBuffer[63] = 0;
		
		model->frames[i].Name = nameBuffer;
		
		model->frames[i].Vertices = new (allocator) Md2Vertex[header.PositionCount];
		for (int j = 0; j < header.PositionCount; j++)
		{
			file.Read(model->frames[i].Vertices[j].X);
			file.Read(model->frames[i].Vertices[j].Y);
			file.Read(model->frames[i].Vertices[j].Z);
			file.Read(model->frames[i].Vertices[j].Normal);
		}
	}
	
	TRACE(DEBUG_FILE_LOADING, "Loaded vertices");
	
	TRACE(DEBUG_FILE_LOADING, "Model created");
	
	return model;
}

Adventure::Md2Animator::Md2Animator(Md2Model* model)
	: model(model)
{
	allocator = NULL;
	interval = 1.0f;
	initialized = false;
	
	previousFrame = 0;
	currentFrame = 0;
	nextFrame = 0;
	
	// Build up the animations
	const Md2Frame* frames = model->GetFrames();
	int prevAnimationFrame = 0;
	
	// For now, just keep in line with Egoboo frame names (XX##...)
	std::string prevAnimationName = frames[0].Name.substr(2);
	
	for (int i = 1; i < model->GetFrameCount(); i++)
	{
		std::string animationName = frames[i].Name.substr(2);
		
		// The animation names are different, so create a new animation
		if (prevAnimationName != animationName)
		{
			Animation animation;
			
			animation.Name = prevAnimationName;
			animation.StartFrame = prevAnimationFrame;
			animation.EndFrame = i - 1;
			
			animations[animationName] = animation;
			
			prevAnimationName = animationName;
			prevAnimationFrame = i;
		}
	}
}

Adventure::Md2Animator::~Md2Animator()
{
	// Nothing...
}

bool Adventure::Md2Animator::Initialize(Allocator* allocator)
{
	if (initialized)
		return false;
	
	initialized = true;
	
	this->allocator = allocator;
	
	// Allocate stuff...
	vertexCache = new(allocator) Md2CacheVertex[model->GetPositionCount()];
	
	if (!frame.Positions.Initialize(model->GetPositionCount(), allocator))
	{
		TRACE(DEBUG_RENDERING_LOW, "Could not initialize positions");
		
		return false;
	}
	
	if (!frame.Normals.Initialize(model->GetPositionCount(), allocator))
	{
		TRACE(DEBUG_RENDERING_LOW, "Could not initialize normals");
		
		return false;
	}
	
	if (!frame.Colors.Initialize(model->GetPositionCount(), allocator))
	{
		TRACE(DEBUG_RENDERING_LOW, "Could not initialize colors");
		
		return false;
	}
	
	if (!frame.TexCoords.Initialize(model->GetTexCoordCount(), allocator))
	{
		TRACE(DEBUG_RENDERING_LOW, "Could not initialize texture coordinates");
		
		return false;
	}
	
	if (!frame.Indices.Initialize(model->GetTriangleCount() * 3, allocator))
	{
		TRACE(DEBUG_RENDERING_LOW, "Could not initialize indices");
		
		return false;
	}
	
	// Buffer index data (with a scoped lock)
	{
		ElementArrayLock<ModelIndexArray> indices(frame.Indices);
		
		if (!indices)
		{
			TRACE(DEBUG_RENDERING_LOW, "Could not lock indices");
			
			return false;
		}
		
		const Md2Triangle* triangles = model->GetTriangles();
		for (int i = 0; i < model->GetTriangleCount(); i++)
		{
			// Position, normal, material (color), and texture coordinates
			// Note: position, normal, and material share the same indices
			indices.ElementArray.Buffer(triangles[i].Vertex[0], triangles[i].Vertex[0], triangles[i].Vertex[0], triangles[i].TexCoord[0]);
			indices.ElementArray.Buffer(triangles[i].Vertex[1], triangles[i].Vertex[1], triangles[i].Vertex[1], triangles[i].TexCoord[1]);
			indices.ElementArray.Buffer(triangles[i].Vertex[2], triangles[i].Vertex[2], triangles[i].Vertex[2], triangles[i].TexCoord[2]);
		}
	}
	
	return true;
}

bool Adventure::Md2Animator::GetAnimation(const std::string& name, Animation& animation) const
{
	std::map<std::string, Animation>::const_iterator a = animations.find(name);
	
	if (a != animations.end())
	{
		animation = a->second;
		
		return true;
	}
	
	return false;
}

void Adventure::Md2Animator::SetInterval(float newInterval)
{
	interval = newInterval;
	
	// This is to ensure that everything stays nice and synchronized
	UpdateAnimation(0.0f);
}

void Adventure::Md2Animator::UpdateAnimation(float delta)
{
	currentDelta += delta;
	
	if (currentDelta > interval)
	{
		previousFrame = currentFrame;
		currentFrame = nextFrame;
		
		nextFrame++;
		
		if (nextFrame > currentAnimation.EndFrame)
			nextFrame = currentAnimation.StartFrame;
	}
}

bool Adventure::Md2Animator::SwitchTo(const std::string& name)
{
	Animation newAnimation;
	
	if (GetAnimation(name, newAnimation))
	{
		currentAnimation = newAnimation;
		
		return true;
	}
		
	return false;
}

bool Adventure::Md2Animator::Render()
{
	// Get the previous and current frames
	const Md2Frame* prevFrame = &model->GetFrames()[this->previousFrame];
	const Md2Frame* curFrame = &model->GetFrames()[this->currentFrame];
	const Md2Frame* nextFrame = &model->GetFrames()[this->nextFrame];
	
	// Calculate interpolation factor
	float mu = currentDelta / interval;
	
	// Render the model
	for (int i = 0; i < model->GetPositionCount(); i++)
	{
		Md2Vertex prevVertex = prevFrame->Vertices[i];
		Md2Vertex curVertex = curFrame->Vertices[i];
		Md2Vertex nextVertex = nextFrame->Vertices[i];
		
		// Scale and translate positions
		Vector3 prevPosition = prevFrame->Scale * Vector3(prevVertex.X, prevVertex.Y, prevVertex.Z) + prevFrame->Translation;
		Vector3 curPosition = curFrame->Scale * Vector3(curVertex.X, curVertex.Y, curVertex.Z) + curFrame->Translation;
		Vector3 nextPosition = nextFrame->Scale * Vector3(nextVertex.X, nextVertex.Y, nextVertex.Z) + nextFrame->Translation;
		
		// Get normals from Md2Normals table
		Md2Normal prevNormal = Md2Normals[prevFrame->Vertices[i].Normal];
		Md2Normal curNormal = Md2Normals[curFrame->Vertices[i].Normal];
		Md2Normal nextNormal = Md2Normals[nextFrame->Vertices[i].Normal];
		
		// Interpolate and set
		vertexCache[i].Position = Math::QuadraticInterpolate(prevPosition, curPosition, nextPosition, mu);
		vertexCache[i].Normal = Math::QuadraticInterpolate(Vector3(prevNormal.X, prevNormal.Y, prevNormal.Z), Vector3(curNormal.X, curNormal.Y, curNormal.Z), Vector3(nextNormal.X, nextNormal.Y, nextNormal.Z), mu);
	}
	
	return true;
}

Adventure::ModelFrame* Adventure::Md2Animator::GetCurrentFrame()
{
	// Lock the buffers
	ElementArrayLock<CompressedVector3Array> positions(frame.Positions);
	ElementArrayLock<CompressedNormalArray> normals(frame.Normals);
	ElementArrayLock<ColorArray> colors(frame.Colors);
	
	if (!positions || !normals || !colors)
	{
		TRACE(DEBUG_RENDERING_LOW, "Could not lock buffer(s)");
		
		return NULL;
	}
	
	// Calculate vertex data
	for (int i = 0; i < model->GetPositionCount(); i++)
	{
		positions.ElementArray.Buffer(vertexCache[i].Position.X, vertexCache[i].Position.Y, vertexCache[i].Position.Z);
		normals.ElementArray.Buffer(vertexCache[i].Normal.X, vertexCache[i].Normal.Y, vertexCache[i].Normal.Z);
		
		// TODO: Have an effect change the color of the vertex
		colors.ElementArray.Buffer(Color(1.0f, 1.0f, 1.0f));
	}
	
	return &frame;
}
