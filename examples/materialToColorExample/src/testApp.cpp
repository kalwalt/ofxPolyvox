#include "testApp.h"
#include "ofxPolyvox.h"
#include "PolyVoxCore/MarchingCubesSurfaceExtractor.h"
#include "PolyVoxCore/RawVolume.h"
#include "PolyVoxCore/MaterialDensityPair.h"
#include "PolyVoxCore/PolyVoxForwardDeclarations.h"
#include "PolyVoxCore/LowPassFilter.h"
//Use the PolyVox namespace
using namespace PolyVox;



void createRawVolume(RawVolume<MaterialDensityPair44>& volData, float fRadius)
{
	//This vector hold the position of the center of the volume
	Vector3DFloat v3dVolCenter(volData.getWidth() / 2, volData.getHeight() / 2, volData.getDepth() / 2);

    MaterialDensityPair44 voxel;
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
                //cout << fDistToCenter << endl;
				if(fDistToCenter <= fRadius)
				{

                    uint8_t uMaterial = 2;


					//Modify the density and material
					voxel.setMaterial( uMaterial );

					voxel.setDensity( MaterialDensityPair44::getMaxDensity() );

                    uint8_t mat = voxel.getMaterial();
                    //cout << "mat:" << int(mat) << endl;

                    volData.setVoxelAt( x, y, z, voxel );


				}

			}
		}
	}
}


//--------------------------------------------------------------
void testApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);

    PolyVox::Region reg(Vector3DInt32(0,0,0), Vector3DInt32(32, 32, 32));
    RawVolume<MaterialDensityPair44> volData(reg);

    createRawVolume(volData, 12);

    SurfaceMesh<PositionMaterialNormal> mesh;

	MarchingCubesSurfaceExtractor< RawVolume<MaterialDensityPair44> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);

	surfaceExtractor.execute();


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

    ofScale(2,2,2);
    //OF_mesh.draw();
    OF_mesh.drawFaces();

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
