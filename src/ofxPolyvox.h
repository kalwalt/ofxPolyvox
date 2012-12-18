#pragma once
#include "ofMain.h"
#include "PolyVoxCore/CubicSurfaceExtractorWithNormals.h"
#include "PolyVoxCore/SurfaceMesh.h"
#include "PolyVoxCore/SimpleVolume.h"
#include "PolyVoxCore/VertexTypes.h"
#include "PolyVoxCore/Material.h"

using namespace PolyVox;
class ofxPolyvox
{

    public:
        ofxPolyvox();
        virtual ~ofxPolyvox();

        void setSurfaceMeshToRender(const PolyVox::SurfaceMesh<PositionMaterialNormal>& surfaceMesh);
       	void polyvoxToOfMesh(const PolyVox::SurfaceMesh<PositionMaterialNormal>& surfaceMesh, ofMesh& polyvxToOfMesh, bool setColor);
        void draw();
        void drawWireframe();

    private:

	ofFloatColor  convertMaterialIDToColour(int materialID);
   	//Index/vertex buffer data
	GLuint m_uBeginIndex;
	GLuint m_uEndIndex;
	GLuint noOfIndices;
	GLuint indexBuffer;
	GLuint vertexBuffer;


};

