ofxPolyvox
==========

a simple OpenFrameworks addon that wrap the polyvox library, to make voxel meshes with a Minecraft style or as Marching cubes.

This addon is under eavy development. I'm using the git version from the master branch of polyvox 

http://gitorious.org/polyvox but should be better use the more stable release from here:

http://www.volumesoffun.com/polyvox-download/

For info about polyvox:

http://www.volumesoffun.com/polyvox-about/

http://www.volumesoffun.com/polyvox-documentation/

Anyway you can just use as it is the addon without change polyvox version. For now you can create your polyvox mesh and draw with OpenGL calls via an Vertex and Index buffer or with void polyvoxToOfMesh(const PolyVox::SurfaceMesh<PositionMaterialNormal>& surfaceMesh, ofMesh& polyvxToOfMesh) outputting the polyvox mesh to an ofMesh. 

Tested with OF 0072.

roadmap:

- add other examples.
- add LoadRawVolume(), id est a method to import .raw file (from Acropora) to display a volume.
- add polyvoxToOfVbo to outputting a polyvox mesh to an ofVbo. ( already exist but is not working...)
- add simple routines to smooth and decimate a mesh.
