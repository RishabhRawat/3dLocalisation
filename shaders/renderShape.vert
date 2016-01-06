#version 440
uniform float scale;
uniform vec3 alterPosition;

uniform vec3 t_gk;
uniform mat3 invR;
uniform mat3 K_camera;

in vec3 Vertex;

void main(void)
{
    vec3 pixelCoord = K_camera*(invR*((Vertex*scale-alterPosition)-t_gk));
    ivec2 pix = ivec2(pixelCoord/pixelCoord.z);
    gl_Position = vec4(pix.x/640.0f,pix.y/480.0f,0,1);

}
