#include "testApp.h"
#include "PolyVoxCore/MarchingCubesSurfaceExtractor.h"
#include "PolyVoxCore/RawVolume.h"
#include "PolyVoxCore/MaterialDensityPair.h"
#include "PolyVoxCore/PolyVoxForwardDeclarations.h"
#include "PolyVoxCore/SurfaceMesh.h"

//Use the PolyVox namespace
using namespace PolyVox;


void createRawVolume(RawVolume<MaterialDensityPair44>& volData, float fRadius)
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

			    MaterialDensityPair44 voxel;
				//Store our current position as a vector...
				Vector3DFloat v3dCurrentPos(x,y,z);
				//And compute how far the current position is from the center of the volume
				float fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();

				if(fDistToCenter+(ofNoise(x,y)) <= fRadius+(ofRandomf()))
				{
					//Our new density value

					uint8_t uDensity = std::numeric_limits<uint8_t>::max();

                    //we add a random color to the vertices
                    uint8_t uMaterial = ofRandom(5);

			 		//Modify the material
                    voxel.setMaterial(uMaterial);

					//Modify the density
					voxel.setDensity(uDensity);

					//Density8 voxel(32);
                    volData.setVoxelAt(x, y, z, voxel);

				}


			}
		}
	}
}


//--------------------------------------------------------------
void testApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);

    PolyVox::Region reg(Vector3DInt32(0,0,0), Vector3DInt32(64, 64, 64));
    RawVolume<MaterialDensityPair44> volData(reg);

    createRawVolume(volData, 28);

    SurfaceMesh<PositionMaterialNormal> mesh;

    //swith between the two approach if you want...
	//MarchingCubesSurfaceExtractor< RawVolume<MaterialDensityPair44> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
	CubicSurfaceExtractorWithNormals< RawVolume<MaterialDensityPair44> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);

	surfaceExtractor.execute();

    std::cout << "polyvox vertices: " << mesh.getNoOfVertices() << std::endl;
    std::cout << "polyvox indices: " << mesh.getNoOfIndices() << std::endl;

    OF_mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    //we transform the polyvox mesh into an ofMesh
    polyvox.polyvoxToOfMesh(mesh,OF_mesh,true);

    std::cout << "OF_mesh vertices: " << OF_mesh.getNumVertices() << std::endl;

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

    OF_mesh.draw();

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
