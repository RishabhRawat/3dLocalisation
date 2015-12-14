#Notes
###TODOs and other take care stuff

1. findHomography fails if not enough matched points are present, so we need a check before it crashes
2. Todo implement plotting position.
3. x and y are along image and z is perpendicular to the image (initial image is used as a reference), will be a good idea to plot stuff in x-z plane
4. Pointcloud is visualised using meshlab 
5. Homography is for plane things only, so it will not work.. unfortunately and some [good lectures](http://isit.u-clermont1.fr/~ab/Classes/DIKU-3DCV2/) read lecture 16 especially
6. Need to convert depth maps into voxel grids
7. The depth map merging is available [pcl](https://github.com/PointCloudLibrary/pcl/blob/master/gpu/kinfu/src/cuda/tsdf_volume.cu) under the function tsdf23 

###DONE
1. Implemented Disparity Maps, the depth maps need a little bit more work
2. Understood the implementation of crazy tough  [See original Paper](http://homes.cs.washington.edu/~newcombe/papers/newcombe_etal_ismar2011.pdf) eqn 6-9
3. Created a simplified Document for that
4. Completed Initial Marching Cubes implementation
5. Half implemented Voxel API
