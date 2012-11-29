#include "testApp.h"
#include "PolyVoxCore/CubicSurfaceExtractorWithNormals.h"
#include "PolyVoxCore/SurfaceMesh.h"
#include "PolyVoxCore/SimpleVolume.h"

using namespace PolyVox;


void createMultiSphereInVolume(SimpleVolume<uint8_t>& volData, vector <float> radii, float num, vector <Vector3DFloat> centers)
{

for (int n = 0; n < num; n++)
    {


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
                    float fDistToCenter = (v3dCurrentPos - centers[n]).length();

                    uint8_t uMaterial = 0;

                    //If the current voxel is less than 'radius' units from the center then we make it solid.
                    if(fDistToCenter <= radii[n])
                    {
                        //Our new density value
                        uMaterial = 1;
                        //Write the voxel value into the volume
                        volData.setVoxelAt(x, y, z, uMaterial);
                    }




                }
            }
        }

	 }
}

//--------------------------------------------------------------
void testApp::setup(){

    num = 12;
    maxDim = 128;

	for(int i = 0; i < num; i++){
	Vector3DFloat vecf( ofRandom(0, maxDim*.5), ofRandom(0, maxDim*.5), ofRandom(0, maxDim*.5) );
    centers.push_back(vecf);
    cout << centers[i] << endl;
	}

	for(int i = 0; i < num; i++){
	float r= ofRandom(0,18);
    radii.push_back(r);
    cout << radii[i] << endl;
	}



    //Create an empty volume and then place a sphere in it
	SimpleVolume<uint8_t> volData(PolyVox::Region(Vector3DInt32(0,0,0), Vector3DInt32(maxDim, maxDim, maxDim)));
	createMultiSphereInVolume(volData, radii, num, centers );

	//Extract the surface
	SurfaceMesh<PositionMaterialNormal> mesh;
	CubicSurfaceExtractorWithNormals< SimpleVolume<uint8_t> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
	surfaceExtractor.execute();
    poly.polyvoxToOfMesh(mesh, outMesh,true);

}
//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){


	//Enable the depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Anable smooth lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);


	cam.begin();

	ofTranslate(-maxDim*.5,-maxDim*.5,-maxDim*.5);
	ofScale(2,2,2);

    	outMesh.draw();

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
