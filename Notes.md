#Notes
###TODOs and other take care stuff

1. findHomography fails if not enough matched points are present, so we need a check before it crashes
2. 4 matrices given by decompose Homography Mat, need to eliminate others, i.e. [implement this](https://hal.inria.fr/inria-00174036v3/document#15)
3. Todo implement plotting position.
4. x and y are along image and z is perpendicular to the image (initial image is used as a reference), will be a good idea to plot stuff in x-z plane
5. Bad depthmap... pointcloud is visualised using meshlab 
6. Need to do the disparity stuff without rectifying, or rectify it ourselves
7. Homography is for plane things only, so it will not work.. unfortunately and some [good lectures](http://isit.u-clermont1.fr/~ab/Classes/DIKU-3DCV2/) read lecture 16 especially
8. Improve essential matrix calculation too.