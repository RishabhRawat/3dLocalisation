#ifndef VOXEL_H
#define VOXEL_H
#define VOXELNUM 64
#include <cstdint>

class Voxel{
public:
	~Voxel();
	void readPCD(const char * filename);
	int readPngDepthMap(const char * filename);
	
	uint16_t *depthMap = 0;
	int height, width;
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