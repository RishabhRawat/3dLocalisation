#ifndef VOXELOPERATIONS_H
#define VOXELOPERATIONS_H
#include "Common.h"
#define VOXELNUM 4
GLuint utilCreate3DVoxel(int size);
void updateVoxel(GLuint FramebufferName, GLuint gVAO, GLuint Voxel);

GLfloat const identityMat [] =
{
1.0f, 0.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f, 0.0f,
0.0f, 0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 1.0f
};

#endif // VOXELOPERATIONS_H
