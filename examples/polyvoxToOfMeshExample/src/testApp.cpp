#include "testApp.h"
#include "ofxPolyvox.h"
#include "PolyVoxCore/MarchingCubesSurfaceExtractor.h"
#include "PolyVoxCore/RawVolume.h"
#include "PolyVoxCore/MaterialDensityPair.h"
#include "PolyVoxCore/PolyVoxForwardDeclarations.h"
#include "PolyVoxCore/LowPassFilter.h"

//Use the PolyVox namespace
using namespace PolyVox;



void createRawVolume(RawVolume<uint8_t>& volData, float fRadius)
{
	//This vector hold the position of the center of the volume
	Vector3DFloat v3dVolCenter(volData.getWidth() / 2, volData.getHeight() / 2, volData.getDepth() / 2);

	//This three-level for loop iterates over every voxel in the volume
	for (int z = 0; z < volData.getWidth(); z++)
	{
		for (int y = 0; y < volData.getHeight(); y++)
		{
			for (int x = 0; x < volData.getDepth(); x++)
			{
				//Store our current position as a vector...
				Vector3DFloat v3dCurrentPos(x,y,z);
				//And compute how far the current position is from the center of the volume
				float fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();

				if(fDistToCenter <= fRadius)
				{
					//Our new density value

					uint8_t uDensity = std::numeric_limits<uint8_t>::max();


					volData.setVoxelAt(x, y, z, uDensity);
				}


			}
		}
	}
}


//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    //This is needed only if you use for polyvox.draw()
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);

    PolyVox::Region reg(Vector3DInt32(0,0,0), Vector3DInt32(32, 32, 32));
    RawVolume<uint8_t> volData(reg);


    createRawVolume(volData, 7);

    SurfaceMesh<PositionMaterialNormal> mesh;


	//CubicSurfaceExtractorWithNormals< RawVolume<uint8_t> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
	//MarchingCubesSurfaceExtractor< SimpleVolume<uint8_t> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
	MarchingCubesSurfaceExtractor< RawVolume<uint8_t> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);

	surfaceExtractor.execute();

    //	this is not working for now
    //polyvox.extractSurface(mesh, volData);

    ///if you want to render with standard gl calls use this
    //polyvox.setSurfaceMeshToRender(mesh);

    ofLog(OF_LOG_NOTICE, "number of polyvox-indices is %d", mesh.getNoOfIndices());
    ofLog(OF_LOG_NOTICE, "number of polyvox-vertices is %d", mesh.getNoOfVertices());


    OF_mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    polyvox.polyvoxToOfMesh(mesh,OF_mesh,true);

    ofLog(OF_LOG_NOTICE, "OF_mesh vertices in testApp is %d", mesh.getNoOfVertices());

    }

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){

    glEnable(GL_DEPTH_TEST);
    cam.begin();

    //Enable smooth lighting
	ofEnableLighting();

	glEnable(GL_LIGHT0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



//if you want to render with standard gl call uncomment this
    //polyvox.draw();

//we render with ofMesh
    OF_mesh.draw();
    //OF_mesh.drawWireframe();

    cam.end();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
