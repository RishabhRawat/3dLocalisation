#version 440
uniform float scale;
uniform vec3 alterPosition;

uniform vec3 t_gk;
uniform mat3 invR;
uniform mat3 ModelR;
uniform mat4 K_camera;

in vec3 Vertex;

void main(void)
{
    mat4 Extrinsic;
    Extrinsic[0] = vec4(invR[0],0);
    Extrinsic[1] = vec4(invR[1],0);
    Extrinsic[2] = vec4(invR[2],0);
    Extrinsic[3] = vec4(-invR*t_gk,1);
    //Only extrinsic means z comes outside screen


    vec4 test  = K_camera*(Extrinsic*vec4(ModelR*(Vertex*scale)+alterPosition,1.0f));
    //if(test.w < 0)
    //test = -test;
    gl_Position = test;


    //far and near negative will mess stuff up
//    gl_Position  = K_camera*vec4(ModelR*(Vertex*scale)+alterPosition,1.0f);

//    0.91 1.602 -1.7 0.07
//    gl_Position = K_camera*(Extrinsic*(vec4(ModelR*(Vertex*scale),1.0f)-vec4(alterPosition,0.0f)));
// K transpose

}
