#version 330
uniform mat4 Transform;
in vec3 Vertex;
in vec2 vertTexCoord;
out vec3 fragTexCoord;
void main() {			
	gl_Position = Transform*vec4(Vertex,1.0);
	fragTexCoord = vec3(vertTexCoord,0.0f);
}