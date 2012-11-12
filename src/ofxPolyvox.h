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
        void extractSurface( PolyVox::SurfaceMesh<PositionMaterialNormal>& surfaceMesh, SimpleVolume<uint8_t> volData);
       void polyvoxToOfMesh(const PolyVox::SurfaceMesh<PositionMaterialNormal>& surfaceMesh, ofMesh& polyvxToOfMesh, bool setColor);
        void polyvoxToOfVbo(const PolyVox::SurfaceMesh<PositionMaterialNormal>& surfaceMesh, ofVbo& vbo );
        void draw();
        void drawWireframe();

    private:
   //Index/vertex buffer data
	GLuint m_uBeginIndex;
	GLuint m_uEndIndex;
	GLuint noOfIndices;
	GLuint indexBuffer;
	GLuint vertexBuffer;


};

class ofxVboPolyvox: public ofVbo {
    public:
        ofxVboPolyvox();
        void setVertexData(const PolyVox::SurfaceMesh<PositionMaterialNormal>& surfaceMesh,  int usage);
        void setIndexData(const PolyVox::SurfaceMesh<PositionMaterialNormal>& surfaceMesh, int usage);

    private:
   //Index/vertex buffer data
	GLuint m_uBeginIndex;
	GLuint m_uEndIndex;
	GLuint noOfIndices;
	GLuint indexBuffer;
	GLuint vertexBuffer;

};
