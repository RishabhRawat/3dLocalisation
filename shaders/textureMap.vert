#version 440
in vec3 Vertex;
in vec2 TexCoord_in;
uniform mat3 K_camera;
out vec2 TexCoord;
out vec2 TexCoordd;

void main(void)
{
    gl_Position = vec4(Vertex,1.0f);
    TexCoord = TexCoord_in;
    TexCoordd = vec2(1,1);
}
