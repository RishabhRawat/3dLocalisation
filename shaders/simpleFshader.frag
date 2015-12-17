#version 440 
uniform sampler3D my_color_texture;
in vec4 fragColor;
in vec3 surfaceNormal;
out vec4 out_Color;
void main()
{
	//only so that my_color_texture does not get optimised out
	if(texelFetch(my_color_texture,ivec3(0,0,0),0) != vec4(1111,1,1,0))
	{

	vec4 lightVector = vec4(5.0f,5.0f,5.0f,1.0f);
	vec4 normal = vec4(surfaceNormal,1.0f);
	out_Color = fragColor*clamp(dot(lightVector, normal), 0, 1);

	}
}

