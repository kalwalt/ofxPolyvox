#include "testApp.h"
#include "ofxPolyvox.h"
#include "PolyVoxCore/MarchingCubesSurfaceExtractor.h"
#include "PolyVoxCore/RawVolume.h"
#include "PolyVoxCore/MaterialDensityPair.h"
#include "PolyVoxCore/Density.h"
#include "PolyVoxCore/PolyVoxForwardDeclarations.h"
#include "PolyVoxCore/LowPassFilter.h"
#include "PolyVoxCore/MeshDecimator.h"

//Use the PolyVox namespace
using namespace PolyVox;


void createSphereInVolume(RawVolume<Density8>& volData, float fRadius)
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

				//If the current voxel is less than 'radius' units from the center then we make it solid.
				if(fDistToCenter <= fRadius)
				{

                    Density8 voxel(210);

                    volData.setVoxelAt(x, y, z, voxel);

				}


			}
		}
	}
}
//--------------------------------------------------------------
void testApp::setup(){

    //We'll be rendering with index/vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	const int32_t g_uVolumeSideLength = 255;

	PolyVox::Region reg(Vector3DInt32(0,0,0), Vector3DInt32(g_uVolumeSideLength-1, g_uVolumeSideLength-1, g_uVolumeSideLength-1));

	//Create empty volume
	RawVolume<Density8> volData(reg);

    //we make a simple sphere, nothing so exciting but easy...
	createSphereInVolume(volData,110);

    //we crete another volume resultVolume where we'll put the result of the LowPassFilter
    RawVolume<Density8> resultVolume(reg);

    //kernelSize : the size of the kernel
    uint32_t kernelSize = 9;

    // LowPassFilter used to smooth the voxel data in this case from a RawVolume (volData) , the result is stored in RawVolume (resultVolume)
	LowPassFilter< RawVolume<Density8>, RawVolume<Density8> > pass1(&volData, reg, &resultVolume, reg, kernelSize);

    ofLog(OF_LOG_NOTICE, "kernel size is %d", kernelSize);

    //this is very important ! use executeSAT()! you can use execute() if you grab the polyvox develop branch!
	//pass1.execute();
	pass1.executeSAT();

    ofLog(OF_LOG_NOTICE, "LowPassFilter executed!");

    SurfaceMesh<PositionMaterialNormal> mesh;


	MarchingCubesSurfaceExtractor< RawVolume<Density8> > surfaceExtractor(&resultVolume, resultVolume.getEnclosingRegion(), &mesh);

	surfaceExtractor.execute();

    ofLog(OF_LOG_NOTICE, "Marching cube surface created!");


    SurfaceMesh<PositionMaterialNormal> decimatedMesh;
    MeshDecimator<PositionMaterialNormal> decimator(&mesh, &decimatedMesh);
    decimator.execute();

    ofLog(OF_LOG_NOTICE, "Decimation algorithm applyed to the mesh!");

    ofLog(OF_LOG_NOTICE, "polyvoxMesh : num vertices is:",  mesh.getNoOfVertices());

    ofLog(OF_LOG_NOTICE, "DecimatedMesh: num. vertices is: ", decimatedMesh.getNoOfVertices());

    polyvox.setSurfaceMeshToRender(decimatedMesh);

}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){

    cam.begin();

    //Enable smooth lighting
	ofEnableLighting();

	glEnable(GL_LIGHT0);


    ofTranslate(-254.0f,-254.0f,-500.0f);
    ofScale(2,2,2);

    polyvox.drawWireframe();
    //polyvox.draw();

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
