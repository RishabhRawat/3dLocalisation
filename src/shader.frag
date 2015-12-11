#version 330
/*
uniform sampler3D my_color_texture;
in vec3 fragTexCoord;
out vec4 out_Color;

void main() {
	out_Color = texture(my_color_texture,fragTexCoord)+vec4(5.0f/256,5.0f/256,5.0f/256,5.0f/256);
}
*/
uniform sampler3D my_color_texture;
in vec3 fragTexCoord;
out vec4 out_Color;

void main() {
	out_Color = texture(my_color_texture,fragTexCoord)+vec4(5.0f/256,5.0f/256,5.0f/256,5.0f/256);
}