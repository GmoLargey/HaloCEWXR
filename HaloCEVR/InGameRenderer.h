#pragma once
#include "Maths/Vectors.h"
#include "Maths/Matrices.h"
#include <vector>
#include <d3d9.h>


class InGameRenderer
{
public:
	// Debug API functions
	void DrawLine2D(const struct Vector2& start, const struct Vector2& end, D3DCOLOR color);
	void DrawInvertedShape2D (const struct Vector2& centre, const struct Vector2& innerSize, const struct Vector2& size, int sides, float radius, D3DCOLOR color);
	void DrawLine3D(const struct Vector3& start, const struct Vector3& end, D3DCOLOR color, bool bRespectDepth = true, float thickness = 0.05f);
	void DrawPolygon(const struct Vector3& centre, const struct Vector3& facing, const struct Vector3& upVector, int sides, float radius, D3DCOLOR color, bool bRespectDepth = true, float angleAmount = 1.0f);
	void DrawCoordinate(const struct Vector3& pos, const class Matrix3& rot, float size = 0.05f, bool bRespectDepth = true);
	void DrawRenderTarget(struct IDirect3DTexture9* renderTarget, const struct Vector3& pos, const class Matrix3& rot, const struct Vector2& size, bool bRespectDepth = true, bool bRespectStencil = false);

	// Core functions
	void ExtractMatrices(struct Renderer* playerRenderer);
	void Render(struct IDirect3DDevice9* pDevice);
	void PostRender();

	void ClearRenderTargets();

	//WinlatorXR Change
	int OpenXRFrameID = 0;
	bool firstClear = false;
protected:

	void Draw2DLines(struct IDirect3DDevice9* pDevice);
	void Draw2DPolygons(struct IDirect3DDevice9* pDevice);
	void Draw3DLines(struct IDirect3DDevice9* pDevice);
	void DrawRenderTargets(struct IDirect3DDevice9* pDevice);
	void DrawPolygons(struct IDirect3DDevice9* pDevice);
	int SrgbToLinear(float srgb);

	static constexpr int MAX_LINES = 32;
	static constexpr int MAX_RECTS = 16;

	struct VertexData2D
	{
		float x, y, z, rhw;
		DWORD color;
	};

	struct VertexData3D
	{
		float x, y, z;
		DWORD color;
	};

	struct VertexDataTex
	{
		float x, y, z;
		float u, v;
	};

	struct RenderTarget
	{
		Vector3 pos;
		Matrix3 rot;
		Vector2 size;
		struct IDirect3DTexture9* texture;
		bool bRespectDepth;
		bool bRespectStencil;
	};

	struct Polygon
	{
		bool bIsStencil;
		std::vector<VertexData3D> vertices;
	};

	struct Polygon2D
	{
		std::vector<VertexData2D> vertices;
	};

	VertexData2D vertices2D[MAX_LINES];
	VertexData3D vertices3D[MAX_LINES];
	int vertex2DCount = 0;
	int vertex3DCount = 0;
	
	std::vector<VertexData2D> lines2D;
	std::vector<Polygon2D> polygons2D;
	std::vector<VertexData3D> lines3D;
	std::vector<VertexData3D> depthLines3D;
	std::vector<RenderTarget> renderTargets;
	std::vector<Polygon> polygons;
	std::vector<Polygon> depthPolygons;

	// MVP matrices the current camera is using, must match exactly or 3D elements will be misaligned
	D3DMATRIX world;
	D3DMATRIX view;
	D3DMATRIX projection;
};
