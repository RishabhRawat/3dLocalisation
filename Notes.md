#Notes
###TODOs and other take care stuff

1. findHomography fails if not enough matched points are present, so we need a check before it crashes
2. 4 matrices given by decompose Homography Mat, need to eliminate others, i.e. [implement this](https://hal.inria.fr/inria-00174036v3/document#15)
3. Todo implement plotting position.
4. x and y are along image and z is perpendicular to the image (initial image is used as a reference), will be a good idea to plot stuff in x-z plane
