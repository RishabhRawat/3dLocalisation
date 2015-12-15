#ifndef VOXEL_H
#define VOXEL_H
#define VOXELNUM 3
class Voxel{
public:
	Voxel();
	~Voxel();
	void readPCD(const char * filename);
	
	float depthData[VOXELNUM*VOXELNUM*VOXELNUM*4];
	float colorWeightData[VOXELNUM*VOXELNUM*VOXELNUM*4];
	
	
private:
	float x[VOXELNUM];
	float y[VOXELNUM];
	float z[VOXELNUM];
	
	float normal_x[VOXELNUM];
	float normal_y[VOXELNUM];
	float normal_z[VOXELNUM];
	
};


#endif // VOXEL_H